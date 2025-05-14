#include "stdafx.h"

#define I_AM_ONLINE (*(char*)0x223F0C0)
#define VALID_ADDR(x) ((unsigned int)(x) > 0x10000)
#define METPLAYERS_MAX 99
CNetGamePlayer *getCNetGamePlayer(int player);


bool assureHostOfFreemode(int player);


extern GtaThread* freemodeScriptGtaThread;
extern CGameScriptHandlerNetwork* freemodeScriptCGameScriptHandlerNetwork;
GtaThread* getCurrentGtaThread();
CGameScriptHandlerNetwork* getCurrentCGameScriptHandlerNetwork();
void crashScriptHostStart(int player);
void giveHostToPlayer(int player);
void freezePlayerV4(int player);