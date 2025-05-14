#include "menu.h"
#include "Graphics.h"
#include "Native.h"
#include "pad.h"
#include "animation.h"

#include "Players.h"
#include "self.h"
#include "freeze.h"

bool block;
bool aksas{};
bool aksadawdsas{};

Menu* g_Menu = nullptr;
bool freeze{};

void Deportation_bag(bool enable)
{
	*(unsigned int*)0x1775F50 = enable ? 0x60000000 : 0x306307F4; // russian - DE
}


bool variacao41 = false;
void variacao4(bool enable)
{
	*(unsigned int*)0xA0F0A4 = enable ? 0x60000000 : 0x8167001C; //
	*(unsigned int*)0xA0F0BC = enable ? 0x60000000 : 0x2C030000; //
}


bool eu641 = false;
void eu64(bool enable)
{
	*(int*)0xA8C1C4 = enable ? 0x4E800020 : 0x7C0802A6;
}


bool write_serialize1 = false;
void write_serialize(bool enable)
{
	*(int*)0xA8B5FC = enable ? 0x4E800020 : 0x7CC81E70; //SerializeSyncDataWriter
}


void Boolean(bool enable)
{
	*(unsigned int*)0xA8C328 = enable ? 0x4E800020 : 0x7C0802A6; // WriteSyncDataBool_post_plus_0xC
	*(unsigned int*)0xA8C32C = enable ? 0x4E800020 : 0x48A7E765; // WriteSyncDataBool_post_plus_0xC
	*(unsigned int*)0x16542D4 = enable ? 0x60000000 : 0x4B438055; // rage_CSyncDataWriter_WriteBool

}

void String(bool enable)
{
	*(unsigned int*)0x1654F70 = enable ? 0x4E800020 : 0x7C0802A6; // rage_CSyncDataWriter_WriteString
	*(unsigned int*)0xA8BC90 = enable ? 0x4E800020 : 0x7C0802A6; // sub_A8BC90  //serialize string
}

void Byte(bool enable)
{
	*(unsigned int*)0x1654684 = enable ? 0x4E800020 : 0x7C0802A6; // rage_CSyncDataWriter_WriteByte
}


void Interager(bool enable)
{
	*(unsigned int*)0x16544E8 = enable ? 0x4E800020 : 0x7C0802A6; // rage_CSyncDataWriter_WriteIntegerAlot
	*(unsigned int*)0x16547A8 = enable ? 0x60000000 : 0x2C030000; // rage_CSyncDataWriter_WriteInteger
	*(unsigned int*)0x1654784 = enable ? 0x4E800020 : 0x7C0802A6; // rage_CSyncDataWriter_WriteInteger
}

void BrodcastData(bool enable)
{
	*(unsigned int*)0x9FB3CC = enable ? 0x4E800020 : 0x48B0F681; // CGamePlayerBroadcastDataHandler_Local_WriteLogSyncData
	*(unsigned int*)0x9FB3C8 = enable ? 0x4E800020 : 0x7C0802A6; // CGamePlayerBroadcastDataHandler_Local_WriteLogSyncData
}

bool Arrays1 = false;
void Arrays(bool enable)
{
	*(unsigned int*)0x9FD774 = enable ? 0x60000000 : 0x7C0802A6; // rage_netArrayHandlerBase_HandleReceived
	*(unsigned int*)0x12BCF8C = enable ? 0x4E800020 : 0x7C0802A6; // CScriptArrayDataVerifyEvent_WriteSyncData
	*(unsigned int*)0x1656A18 = enable ? 0x60000000 : 0x38600004; // rage_netArrayHandler_SyncDataSizeCalculator
	*(unsigned int*)0x9FF3A8 = enable ? 0x4E800020 : 0x7C0802A6; // rage_netArrayManager_msgUpdateAck  a raiz de todos eu acho
	*(unsigned int*)0x9FBC18 = enable ? 0x4E800020 : 0x7C0802A6; // sub - XREF -> rage_netArrayManager_msgUpdateAck+120↓p
}

void SyncTreeBuff(bool enable) {
	*(unsigned int*)0xA17248 = enable ? 0x60000000 : 0x807C0008; // netSyncTree_ReadFromBuffer  orginal hextic v3
}

void ScriptID(bool enable)
{
	*(unsigned int*)0x46E30C = enable ? 0x4E800020 : 0x7C0802A6; // CGameScriptId_Serialize
	*(unsigned int*)0xA5544C = enable ? 0x4E800020 : 0x7C0802A6; // sub_A5544C - XREF -> CGameScriptId_Serialize+18↑p
}




bool freeze2;
bool freeze3;
bool freeze4;
bool freeze5;
bool freeze6;
bool freeze7;
bool freeze8;
bool freeze9;
bool freeze10;
bool freeze11;
bool freeze12;

Menu::Menu()
{
	rootMenu = [](Menu& menu)
		{
			menu.Tab("Self", submenus::self);
			menu.Tab("Vehicle", nullptr);
			menu.Tab("Players", submenus::Players);
			menu.Tab("Game", [](Menu& menu)
				{
				menu.Option("No Russian").toggle(freeze, Deportation_bag);
				menu.Option("Brodcast Data").toggle(freeze2, BrodcastData);
				menu.Option("Hextic v3").toggle(freeze3, SyncTreeBuff);
				menu.Option("String").toggle(freeze4, String);
				menu.Option("Arrays").toggle(freeze5, Arrays);
				menu.Option("Script ID").toggle(freeze6, ScriptID);


				});
			menu.Tab("Frz", submenus::freeze);

			menu.Tab("Settings", nullptr);

		};
}

bool Menu::IsOpened()
{
	return Opened || !IsInputReady();
}

void Menu::InputSleep(int ms)
{
	InputTick = Sys_Milliseconds() + ms;
}

bool Menu::IsInputReady()
{
	return Sys_Milliseconds() >= InputTick;
}

void Menu::OnTabChange(int direction)
{
	// Don't go further if we are in a submenu
	if (submenuLevel > -1)
		return;
	optionCurrent = 1;

	tabCurrent += direction;

	if (tabCurrent < 1)
		tabCurrent = tabCount;
	if (tabCurrent > tabCount)
		tabCurrent = 1;

	InputSleep(200);
}

void Menu::OnScroll(int direction)
{
	optionCurrent += direction;

	if (optionCurrent < 1)
		optionCurrent = optionCount;
	if (optionCurrent > optionCount)
		optionCurrent = 1;

	InputSleep(150);
}

void Menu::OnCancel()
{
	if (submenuLevel == -1)
	{
		if (block)
		{
			block = false;
		}
		InputSleep(200);
	}
	else
	{
		optionCurrent = submenuCurrentOption[submenuLevel];
		submenuLevel--;
		InputSleep(200);
	}
}
float MenuPosX = 1500;
void Menu::OnOpen()
{
	g_Menu->Opened = true;

	g_anim.add_animation("opened", []
		{
		}, easing::in_out_back, &MenuPosX, 0, 500); // Usando out_back para overshoot

	InputSleep(200);
}

void Menu::OnClose()
{
	g_anim.add_animation("opened", []
		{
			g_Menu->Opened = false;

		}, easing::in_quint, &MenuPosX, 1500, 500);
	InputSleep(100);
}

void Menu::RunControls()
{
	if (IsInputReady())
	{
		if (!Opened)
		{
			if (IsButtonDown(BUTTON_R3) && IsButtonDown(BUTTON_DPAD_LEFT))
				OnOpen();
		}
		else
		{
			if (block)
			{
				if (IsButtonDown(BUTTON_CIRCLE))
					OnCancel();
				else if (IsButtonDown(BUTTON_DPAD_UP))
					OnScroll(-1);
				else if (IsButtonDown(BUTTON_DPAD_DOWN))
					OnScroll(1);
			}
			else
			{
				if (IsButtonDown(BUTTON_DPAD_UP))
					OnTabChange(-1);
				else if (IsButtonDown(BUTTON_DPAD_DOWN))
					OnTabChange(1);
				else if (IsButtonDown(BUTTON_CROSS))
				{
					block = true;
					InputSleep(200);

				}
				else if (IsButtonDown(BUTTON_CIRCLE))
					OnClose();

			}

		}
	}
}


std::string tabName;
void Menu::Run()
{
	RunControls();

	if (!Opened)
		return;

	if (strcmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "ingamehud") == 0)
	{
		Rect myRect(1000 + MenuPosX, 100, 350, 25, true);
		Color Main{ 255, 0, 255, 255 };
		UIElement::DrawRect(myRect, Main, UI_ANCHOR_TOP_CENTER);
		char name[100];
		snprintf(name, 100, "Vortex 1.0.0 (VIP) > %s", tabName.c_str());
		UIElement::DrawText(name, 0, {1000 + MenuPosX - (350 / 2), 98, 420,350, true }, {255,255,255,255}, 0);


		tabCount = tabCurrentDrawn;
		tabCurrentDrawn = 0;

		optionCount = optionCurrentDrawn;
		optionCurrentDrawn = 0;

		//tabs
		UIElement::DrawRect({ 1000 + MenuPosX - (350 / 2), 100 + 25 + 4, 80, 4 + (30 * tabCount), true }, { 0, 0, 0, 144 }, UI_ANCHOR_TOP_LEFT);

		//tabContent
		UIElement::DrawRect({ 1000 + MenuPosX + (350 / 2), 100 + 25 + 4, 267, 5 + 300 , true }, { 0, 0, 0, 144 }, UI_ANCHOR_TOP_RIGHT);

		//scroller tab
		float buf = InfiniteScroll(optionCurrent);
		static float TabscrollerY;
		g_anim.add_animation("Tabscroller", nullptr, easing::interpolate, &TabscrollerY, (30 * tabCurrent), 150);
		UIElement::DrawRect({ 1000 + MenuPosX - (350 / 2), 100 + TabscrollerY, 80, 30, true }, Main, UI_ANCHOR_TOP_LEFT);

		//scroller
		if (block)
		{
			float buf = InfiniteScroll(optionCurrent);
			static float scrollerY;
			g_anim.add_animation("scroller", nullptr, easing::interpolate, &scrollerY, (30 * buf - 1), 150);
			UIElement::DrawRect({ 1000 + MenuPosX + (350 / 2), 100 + scrollerY, 266, 30, true }, Main, UI_ANCHOR_TOP_RIGHT);
		}
		if (rootMenu)
			rootMenu(*this);

		if (submenuLevel > -1)
			submenus[submenuLevel](*this);

		if (submenuToEnter)
			EnterSubmenu();


	}
}

void Menu::EnterSubmenu()
{
	if (submenuLevel < 9)
	{
		submenuLevel++;
		submenus[submenuLevel] = submenuToEnter;
		submenuCurrentOption[submenuLevel] = optionCurrent;
		optionCurrent = 1;
	}

	submenuToEnter = nullptr;
}

float Menu::GetAnimationMenuPos()
{
	static float aa = -1280;

	if (Opened)
	{
	}
	else
	{
		g_anim.add_animation("closed", nullptr, easing::in_out_back, &aa, 2000, 700);
	}
	return aa;
}

Menu& Menu::Tab(const char* name, MenuContent tabContent)
{
	this->tabCurrentDrawn++;
	UIElement::DrawText(name, 0, { 1000 + MenuPosX - (350 / 2) + 5, 100 + (30 * tabCurrentDrawn), 448 + 10,378+ 10, true }, {255,255,255,255}, 0);
	if (submenuLevel == -1 && tabCurrent == tabCurrentDrawn)
	{
		tabName = name;
		if (tabContent)
			tabContent(*this);
	}
	return *this;
}

float Menu::InfiniteScroll(float optionCurrentDrawn)
{
	int MaxOption = 10;
	if ((optionCurrent <= MaxOption && optionCurrentDrawn <= MaxOption) ||
		((optionCurrentDrawn > (optionCurrent - MaxOption)) && optionCurrentDrawn <= optionCurrent))
	{
		float buf = (optionCurrent <= MaxOption && optionCurrentDrawn <= MaxOption) ?
			(optionCurrentDrawn) : (optionCurrentDrawn - (optionCurrent - MaxOption));

		return buf;
	}
	return 0;

}
Menu& Menu::Option(const char* name)
{
	optionCurrentDrawn++;

	float buf = InfiniteScroll(optionCurrentDrawn);
	if (buf > 0)
	{
		UIElement::DrawText(name, 0, { 1000 + MenuPosX - (350 / 2) + 85, 100 + (30 * buf - 1), 448 + 10,378 + 10, true }, { 255,255,255,255 }, 0);
	}
	return *this;
}

Menu& Menu::Submenu(Menu::MenuContent submenuContent)
{
	float buf = InfiniteScroll(optionCurrentDrawn);
	if (buf > 0)
	{
		UIElement::DrawSprite("commonmenu", "arrowright", { 1000 + MenuPosX - (350 / 2) + 68 + 267, 115 + (30 * buf - 1), 12.8 + 5, 27 , true }, 0, { 255,255,255,255 }, 0);
	}
	if (IsInputReady() && optionCurrent == optionCurrentDrawn)
	{
		if (IsButtonDown(BUTTON_CROSS) && block)
		{
			if (submenuContent)
				submenuToEnter = submenuContent;

			InputSleep(200);
		}
	}
	return *this;
}

Menu& Menu::Submenu(Menu::MenuContent submenuContent, int clientnum)
{
	float buf = InfiniteScroll(optionCurrentDrawn);
	if (buf > 0)
	{
		UIElement::DrawSprite("commonmenu", "arrowright", { 1000 + MenuPosX - (350 / 2) + 68 + 267, 115 + (30 * buf - 1), 12.8 + 5, 27, true }, 0, { 255, 255, 255, 255 }, 0);
	}
	if (IsInputReady() && optionCurrent == optionCurrentDrawn)
	{
		if (IsButtonDown(BUTTON_CROSS) && block)
		{
			if (submenuContent)
				submenuToEnter = submenuContent;

			ClientNum = clientnum;
			InputSleep(200);
		}
	}
	return *this;
}

Menu& Menu::toggle(bool& value, void(*callback)(bool))
{
	float buf = InfiniteScroll(optionCurrentDrawn);
	if (buf > 0)
	{
		UIElement::DrawSprite("commonmenu", value ? "shop_box_tick" : "shop_box_blank", {1000 + MenuPosX - (350 / 2) + 68 + 267, 115 + (30 * buf - 1), 44.8 - 10, 48.6 - 10 , true}, 0, {255,255,255,255}, 0);
	}
	if (IsInputReady() && optionCurrent == optionCurrentDrawn)
	{
		if (IsButtonDown(BUTTON_CROSS) && block)
		{
			value ^= 1;

			if (callback)
				callback(value);

			InputSleep(200);
		}
	}

	return *this;
}

Menu& Menu::action(void(*callback)())
{
	if (IsInputReady() && optionCurrent == optionCurrentDrawn)
	{
		if (IsButtonDown(BUTTON_CROSS) && block)
		{
			if (callback)
				callback();
			InputSleep(200);
		}
	}

	return *this;
}


