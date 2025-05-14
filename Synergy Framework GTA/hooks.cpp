#include "hooks.h"
#include "detour.h"
#include "scheduler.h"
#include "Graphics.h"
#include "func.h"
#include "Native.h"
#include "pad.h"
#include "animation.h"
#include "config.h"


Detour *IS_PLAYER_ONLINE_t;


Detour* sceNpBasicSetPresenceDetails2_t;
std::int32_t sceNpBasicSetPresenceDetails2_h(SceNpBasicPresenceDetails2* pres, uint32_t options)
{
	char newStatus[SCE_NP_BASIC_PRESENCE_EXTENDED_STATUS_SIZE_MAX];
	sprintf(newStatus, "Synergy Framework | %s", pres->status);
	strncpy(pres->status, newStatus, SCE_NP_BASIC_PRESENCE_EXTENDED_STATUS_SIZE_MAX - 1);
	pres->status[SCE_NP_BASIC_PRESENCE_EXTENDED_STATUS_SIZE_MAX - 1] = '\0';
	return sceNpBasicSetPresenceDetails2(pres, options);
}


namespace hooks
{
	void start()
	{
		scheduler::start();
		g_Menu = new Menu();
		Config = new Configuration();
		*(int*)0x1CF74E4 = 0xE94081;
		g_Natives = (Native_s**)FindNativeTableAddress();

		IS_PLAYER_ONLINE_t = new Detour(0x3E3A20, scheduler::IS_PLAYER_ONLINE, true);
		sceNpBasicSetPresenceDetails2_t = new Detour(0x1806A24, sceNpBasicSetPresenceDetails2_h, true);

		ps3_gamepad::start();

	}

	void stop()
	{
		IS_PLAYER_ONLINE_t->~Detour();
		sceNpBasicSetPresenceDetails2_t->~Detour();
		ps3_gamepad::stop();
		delete g_Menu;
		delete Config;

	}
}