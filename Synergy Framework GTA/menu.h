#pragma once
#include "stdafx.h"


class Menu
{
public:
	using MenuContent = void(*)(Menu&);

	Menu(); 


	Menu& Tab(const char* name, MenuContent tabContent);
	Menu& Option(const char* name);
	Menu& Submenu(Menu::MenuContent submenuContent);
	Menu& toggle(bool& value, void(*callback)(bool) = nullptr);
	Menu& Submenu(Menu::MenuContent submenuContent, int clientnum);
	Menu& action(void(*callback)());
	float GetAnimationMenuPos();
	bool IsOpened();

	void Run();
private:
	void EnterSubmenu();
	void RunControls();
	void OnClose();
	void OnOpen();
	int InputTick{};
	bool Opened{false};
	void InputSleep(int ms);
	bool IsInputReady();
	void OnTabChange(int direction);
	void OnScroll(int direction);
	void OnCancel();

	MenuContent rootMenu{};
	MenuContent submenus[10]{};
	MenuContent submenuToEnter{};
	float tabCurrentDrawn{5};
	int submenuLevel{ -1 };
	float tabCount{};
	float submenuCurrentOption[10]{};

	float tabCurrent{ 1 };
	float optionCurrent{1};
	float optionCurrentDrawn{};
	float optionCount{};
	float InfiniteScroll(float optionCurrentDrawn);
};


extern Menu* g_Menu;