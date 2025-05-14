#include "Players.h"
#include "Native.h"
#include "config.h"
#include "scheduler.h"
#include "func.h"
#include "pad.h"


const char* weps[] = { "WEAPON_UNARMED","WEAPON_KNIFE","WEAPON_NIGHTSTICK","WEAPON_HAMMER","WEAPON_BAT","WEAPON_GOLFCLUB","WEAPON_CROWBAR","WEAPON_PISTOL","WEAPON_COMBATPISTOL","WEAPON_APPISTOL","WEAPON_PISTOL50","WEAPON_MICROSMG","WEAPON_SMG","WEAPON_ASSAULTSMG","WEAPON_ASSAULTRIFLE","WEAPON_ADVANCEDRIFLE","WEAPON_MG","WEAPON_COMBATMG","WEAPON_PUMPSHOTGUN","WEAPON_SAWNOFFSHOTGUN","WEAPON_ASSAULTSHOTGUN","WEAPON_BULLPUPSHOTGUN","WEAPON_STUNGUN","WEAPON_SNIPERRIFLE","WEAPON_HEAVYSNIPER","WEAPON_REMOTESNIPER","WEAPON_GRENADELAUNCHER","WEAPON_GRENADELAUNCHER_SMOKE","WEAPON_RPG","WEAPON_STINGER","WEAPON_MINIGUN","WEAPON_GRENADE","WEAPON_STICKYBOMB","WEAPON_SMOKEGRENADE","WEAPON_BZGAS","WEAPON_MOLOTOV","WEAPON_FIREEXTINGUISHER","WEAPON_PETROLCAN","WEAPON_BALL","WEAPON_FLARE","WEAPON_BOTTLE","WEAPON_GUSENBERG","WEAPON_SPECIALCARBINE","WEAPON_HEAVYPISTOL","WEAPON_SNSPISTOL","WEAPON_BULLPUPRIFLE","WEAPON_DAGGER","WEAPON_VINTAGEPISTOL","WEAPON_FIREWORK","WEAPON_MUSKET","WEAPON_HEAVYSHOTGUN","WEAPON_MARKSMANRIFLE","WEAPON_HOMINGLAUNCHER","WEAPON_PROXMINE","WEAPON_SNOWBALL","WEAPON_FLAREGUN","WEAPON_GARBAGEBAG","WEAPON_COMBATPDW","WEAPON_MARKSMANPISTOL","WEAPON_KNUCKLE","WEAPON_CARBINERIFLE" };

void godmode()
{
	PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
}

void Ragdoll()
{
	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
}

void wanted()
{
	PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), false);
}

void Invisibility()
{
	ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false);
}

void rapidfire()
{
	Hash cur;
	if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &cur, 1))
	{
		if (WEAPON::IS_WEAPON_VALID(cur))
		{
			if (!WEAPON::HAS_WEAPON_ASSET_LOADED(cur))
			{
				WEAPON::REQUEST_WEAPON_ASSET(cur, 31, 0);
			}
			PED::SET_PED_FIRING_PATTERN(PLAYER::PLAYER_PED_ID(), 0x00BAC39B);
			if (CONTROLS::IS_CONTROL_PRESSED(2, 24))
			{
				vec3_t camvf = get_coords_from_cam(3.0f);
				vec3_t camvt = get_coords_from_cam(100.0f);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS1(camvf.x, camvf.y, camvf.z,
					camvt.x, camvt.y, camvt.z,
					250, 1, cur, PLAYER::PLAYER_PED_ID(), 0, 1, 500.0f);
			}
		}
	}
}

void oneshot()
{
	PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999);
}


Detour* cellNetCtlGetInfo_t;
int cellNetCtlGetInfo(int code, CellNetCtlInfo *info)// a8 e3 ee 8e 3b b2
{
	auto ret = cellNetCtlGetInfo_t->CallOriginal<int>(code, info);
	if (ret == 0) {
		uint8_t spoofed_mac[CELL_NET_CTL_ETHER_ADDR_LEN] = { 0xa8, 0xe3, 0xee, 0x8e, 0x3b, 0xb2 };
		for (int i = 0; i < CELL_NET_CTL_ETHER_ADDR_LEN; i++) {
			info->ether_addr.data[i] = spoofed_mac[i];
		}
	}
	return ret;
}


namespace submenus
{
	void self(Menu& menu)
	{
		menu.Option("Inject Bypass").action([]
		{
			sys_prx_module_info_t info;
			sys_prx_segment_info_t segments[10];
			char filename[SYS_PRX_MODULE_FILENAME_SIZE];
			info.size = sizeof(info);
			info.segments = segments;
			info.segments_num = sizeof(segments) / sizeof(sys_prx_segment_info_t);
			info.filename = filename;
			info.filename_size = sizeof(filename);
			int ret = sys_prx_get_module_info(sys_prx_get_module_id_by_name("refive", 0, 0), NULL, &info);

			//I'll keep this private for now
		});
		menu.Option("God Mode").toggle(Config->self.godmode, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, godmode, 5000);
				}
				else
				{
					scheduler::remove(scheduler::renderer, godmode);
					PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
				}
			});
		menu.Option("No Ragdoll").toggle(Config->self.NoRagdoll, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, Ragdoll, 5000);
				}
				else
				{
					scheduler::remove(scheduler::renderer, Ragdoll);
					PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
				}
			});
		menu.Option("Invisibility").toggle(Config->self.Invisibility, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, Invisibility);
				}
				else
				{
					scheduler::remove(scheduler::renderer, Invisibility);
					ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);

				}
			});
		menu.Option("Never Wanted").toggle(Config->self.NeverWanted, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, wanted, 5000);
				}
				else
				{
					scheduler::remove(scheduler::renderer, wanted);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), true);
				}
			});
		menu.Option("Give Weapons").action([]
			{
				for (int i = 0; i < 61; i++) {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), GAMEPLAY::GET_HASH_KEY(weps[i]), 9999, 1);
				}
			});
		menu.Option("Unlimited Ammo").toggle(Config->self.UnlimitedAmmo, [](bool enable)
			{
				WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), enable);
			});
		menu.Option("Rapid Fire").toggle(Config->self.rapidfire, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, rapidfire);
				}
				else
				{
					scheduler::remove(scheduler::renderer, rapidfire);
				}
			});
		menu.Option("1 Shot 1 Kill").toggle(Config->self.ShotKill, [](bool enable)
			{
				if (enable)
				{
					scheduler::loop(scheduler::renderer, oneshot);
				}
				else
				{
					scheduler::remove(scheduler::renderer, oneshot);
					PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1);
				}
			});
	}
}