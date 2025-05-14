#include "Players.h"
#include "Native.h"
#include "frz.h"

int ClientNum{};
bool SyncPlayer[18];
namespace submenus
{
	void Players(Menu& menu)
	{
		for (size_t i = 0; i < 18; i++)
		{
			std::string name = invoke<const char*>(0x406B4B20, i);

			if (name.compare("**Invalid**") == 0)
				continue;


			menu.Option(name.data()).Submenu([](Menu& menu)
			{
				menu.Option("Block Sync").toggle(SyncPlayer[ClientNum]);

				menu.Option("Give Script Host").action([]
				{
					auto cnet = getCNetGamePlayer(ClientNum);
					if (!assureHostOfFreemode(PLAYER::PLAYER_ID()) || cnet == 0) {
						printf("Try Again");
					}
					else
					{
						giveHostToPlayer(ClientNum);
						printf("~g~Gived!");
					}
				});

			
				menu.Option("Freeze Console").action([]
				{
					crashScriptHostStart(ClientNum);
				});

				menu.Option("Freeze V4").action([]
				{
					freezePlayerV4(ClientNum);
				});

			}, i);
		}
	}
}