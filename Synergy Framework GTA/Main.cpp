#include "stdafx.h"
#include "scheduler.h"
#include "Detour.h"
#include "hooks.h"
#include "Patched.h"
#include "freeze.h"
#include "bryan.h"


//#include "Menu.h"
//#include "pad.h"

#pragma diag_suppress 77
SYS_MODULE_INFO("GTA", 0, 1, 1);
SYS_MODULE_START(module_start);
SYS_MODULE_STOP(module_stop);


void DrawOkayMessageDialog(const char* format, ...)
{
	va_list argptr;
	char text[CELL_MSGDIALOG_STRING_SIZE];
	va_start(argptr, format);
	vsprintf(text, format, argptr);
	va_end(argptr);
	cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK, text, NULL, NULL, NULL);
}


sys_ppu_thread_t Start_ThreadID;
void Thread(uint64_t nothing)
{
	libpsutil::sleep(20000);
	
    hooks::start();
    Patched::start();
   freezes::start(); //isso nao deixa dar Unload

    *(short*)0x4A0E34 = 0x4800; //unlock fps
    sys_ppu_thread_exit(nothing);
}



extern "C"
{
    int module_start()
    {
		//Synergy(module_start);
		sys_ppu_thread_create(&Start_ThreadID, Thread, 0, 0x4AA, 0x8000, 0, "Synergy");
        return 0;
    }

    int module_stop()
    {
        scheduler::stop();
        hooks::stop();
        Patched::stop();
      //  freezes::stop();

        return 0;
    }
}
