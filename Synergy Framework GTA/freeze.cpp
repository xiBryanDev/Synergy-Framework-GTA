#include "Players.h"
#include "Native.h"
#include "detour.h"



bool rage_CSyncDataWriter_WriteByte_b{};
Detour* rage_CSyncDataWriter_WriteByte_t;
void rage_CSyncDataWriter_WriteByte(int a1, uint8_t* a2, int a3) 
{
	//printf("0x%x\n", a2);
	if (rage_CSyncDataWriter_WriteByte_b)
	{
		libpsutil::math::srand((unsigned int)time(NULL));
		a3 = libpsutil::math::rand() % 254;
	}

	rage_CSyncDataWriter_WriteByte_t->CallOriginal(a1, a2, a3);
}

bool rage_CSyncDataWriter_WriteInteger_b{};
Detour* rage_CSyncDataWriter_WriteInteger_t;
void rage_CSyncDataWriter_WriteInteger(int a1, int* a2, int a3)
{
	if (rage_CSyncDataWriter_WriteByte_b)
	{
		libpsutil::math::srand((unsigned int)time(NULL));
		a3 = libpsutil::math::rand() % 254;
		//a3 = libpsutil::math::rand() % 13;

	}
	rage_CSyncDataWriter_WriteInteger_t->CallOriginal(a1, a2, a3);
}

bool rage_CSyncDataWriter_WriteUshort_b{};

Detour* rage_CSyncDataWriter_WriteUshort_t;
void rage_CSyncDataWriter_WriteUshort(int a1, uint8_t* a2, int a3)
{
	if (rage_CSyncDataWriter_WriteUshort_b)
	{
		libpsutil::math::srand((unsigned int)time(NULL));
		a3 = libpsutil::math::rand() % 254;
		//a3 = libpsutil::math::rand() % 13;

	}
	rage_CSyncDataWriter_WriteUshort_t->CallOriginal(a1, a2, a3);
}
namespace submenus
{
	void freeze(Menu& menu)
	{
		menu.Option("Freeze Sync Byte").toggle(rage_CSyncDataWriter_WriteByte_b);
		menu.Option("Freeze Sync Integer").toggle(rage_CSyncDataWriter_WriteInteger_b);
		menu.Option("Freeze Sync Ushort").toggle(rage_CSyncDataWriter_WriteUshort_b);
	}
}



namespace freezes
{
	void start()
	{
		*(int*)0x1654688 = 0xFBC1FFF0;//fix bl
		rage_CSyncDataWriter_WriteByte_t = new Detour(0x1654684, rage_CSyncDataWriter_WriteByte);


		*(int*)0x1654788 = 0xFBC1FFF0;//fix bl
		rage_CSyncDataWriter_WriteInteger_t = new Detour(0x1654784, rage_CSyncDataWriter_WriteInteger);

		*(int*)0x1654708 = 0xFBC1FFF0;//fix bl FB 41 FF D0
		rage_CSyncDataWriter_WriteUshort_t = new Detour(0x1654704, rage_CSyncDataWriter_WriteUshort);


		//SerializeSyncDataWriter_t = new Detour(0xA8B5FC, SerializeSyncDataWriter);


	}

	void stop()
	{
		rage_CSyncDataWriter_WriteByte_t->~Detour();
		rage_CSyncDataWriter_WriteInteger_t->~Detour();
		rage_CSyncDataWriter_WriteUshort_t->~Detour();

	}
}