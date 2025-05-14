#include "func.h"
#include "Native.h"


unsigned int FindNativeTableAddress()
{
	unsigned int  l_uiNativeTableAddress = 0;
	unsigned int l_uiStartAddress = 0x390000;
	unsigned int l_uiAddress = 0;
	for (unsigned int i = 0; i < 0x10000; i++)
	{
		if (*(volatile unsigned int*)(l_uiStartAddress + i) == 0x3C6072BD)
			if (*(volatile unsigned int*)(l_uiStartAddress + i + 8) == 0x6063E002)
			{
				l_uiAddress = *(volatile unsigned int*)(l_uiStartAddress + i + 0x10);
				l_uiAddress &= 0xFFFFFF;
				l_uiAddress += (l_uiStartAddress + i + 0x10) - 1;
				//printf("address: 0x%08x\n", l_uiAddress);
				break;
			}
	}
	l_uiNativeTableAddress = (*(volatile unsigned int*)(l_uiAddress + 0x24) << 16) + (*(volatile unsigned int*)(l_uiAddress + 0x2C) & 0xFFFF);
	l_uiNativeTableAddress -= 0x10000;
	return l_uiNativeTableAddress;
}

#define VALID_ADDR(x) ((unsigned int)(x) > 0x10000)


unsigned int modelHashToAddress(unsigned int hash) {
	//returns CVehicleModelInfo
	opd_s modelHashToAddress_t = { 0x9D9830, 0x1C85330 };//appears to be the same
	unsigned int(*modelHashToAddress_1)(unsigned int hash, unsigned int* unk1) = (unsigned int(*)(unsigned int, unsigned int*)) & modelHashToAddress_t;
	unsigned int store = 0xFFFF;
	return modelHashToAddress_1(hash,/*0x10070200*/&store);
}

//same as above
unsigned int getCVehicleModelInfo(unsigned int hash) {
	opd_s modelHashToAddress_t = { 0x9D9830, 0x1C85330 };
	unsigned int(*modelHashToAddress_1)(unsigned int hash, unsigned int* store) = (unsigned int(*)(unsigned int, unsigned int*)) & modelHashToAddress_t;
	unsigned int a;
	return modelHashToAddress_1(hash, &a);
}

CObjModelInfo* getCModelInfo(unsigned int hash) {
	return (CObjModelInfo*)modelHashToAddress(hash);
}

vec3_t get_coords_from_cam(float distance) {
	vec3_t Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	vec3_t Coord = CAM::GET_GAMEPLAY_CAM_COORD();
	Rot.y = distance * cosf(Rot.x);
	Coord.x = Coord.x + Rot.y * sinf(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * cosf(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * sinf(Rot.x);
	return Coord;
}
