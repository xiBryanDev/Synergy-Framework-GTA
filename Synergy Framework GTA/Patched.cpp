//Credits - xiBryan - Dontcry - Ventura





#include "Patched.h"
#include "detour.h"
#include "func.h"
#include "Players.h"

#define VALID_ADDR(x) ((unsigned int)(x) > 0x10000)

#define TOC 0x1C85330

#define __declspec(...) __attribute__((__VA_ARGS__))
__declspec(naked) inline void __blr() { asm("blr"); }

Detour* rage_netSyncNodeBase_HasBeenSent_t;
__declspec(naked) void rage_netSyncNodeBase_HasBeenSent() {
	asm(
		"mr %r5, %r25;"
		"mr %r6, %r26;"
		"mr %r8, %r27;"

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r7, %r0;"      //r7 < 0x10200
		"blt skip_lwz;"



		"lwz %r11, 0x1C(%r7);"

		"b continue_execution;" // Continua execução normal

		"skip_lwz:"
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xF148;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution:"//0xA0F0A8
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xF0A8;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* netSyncTree_ReadFromBuffer_t;
__declspec(naked) void netSyncTree_ReadFromBuffer() { 
	asm(
		"mr %r31, %r7;"
		"mr %r30, %r6;"
		"mr %r29, %r4;"

		"cmpwi %r28, 0;"
		"beq skip_lwz1;"

		"lwz %r3, 8(%r28);"

		"b continue_execution1;"

		"skip_lwz1:"//0xA172E0
		"lis %r12, 0x00A1;"
		"ori %r12, %r12, 0x72E0;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution1:"//0xA1724C
		"lis %r12, 0x00A1;"
		"ori %r12, %r12, 0x724C;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_368520_t;
__declspec(naked) void sub_368520() {
	asm(
		"lwz %r4, 0(%r5);"
		"mr %r3, %r5;"

		"cmpwi %r4, -1;"
		"beq skip_lwz2;"

		"lwz %r4, 0x19C(%r4);"
		"lwz %r4, 0(%r4);"

		"b continue_execution2;"

		"skip_lwz2:"//0x3686D0
		"lis %r12, 0x0036;"
		"ori %r12, %r12, 0x86D0;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution2:"//0x368618
		"lis %r12, 0x0036;"
		"ori %r12, %r12, 0x8618;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_35AC20_t;
__declspec(naked) void sub_35AC20() {
	asm(
		"cmpwi %r3, 0;"             // Verifica se r3 é zero
		"beq loc_35B064;"           // Se for, pula para loc_35B064

		"lwz %r4, 0(%r3);"          // Carrega o valor apontado por r3 em r4
		"cmpwi %r4, -1;"            // Verifica se r4 é -1
		"beq loc_35B064;"           // Se for, pula para loc_35B064

		"lwz %r4, 0x1A0(%r4);"      // Se não for -1, continua normalmente

		"b continue_execution5;"

		"loc_35B064:"               // Endereço 35B064
		"lis %r12, 0x0035;"
		"ori %r12, %r12, 0xB064;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution5:"      // Endereço 35B058
		"lis %r12, 0x0035;"
		"ori %r12, %r12, 0xB058;"
		"mtctr %r12;"
		"bctr;"
	);
}

//extern "C"
//{
//	__declspec(noinline) bool check(int r3)
//	{
//
//	}
//}
//Detour* rage_netSyncNodeBase_IsEntityTypeSynced_t;
//__declspec(naked) void rage_netSyncNodeBase_IsEntityTypeSynced() {
//	asm(
//		"mr %r5, %r29;"           // Copia r29 para r5
//		"mr %r6, %r30;"           // Copia r30 para r6
//		"lwz %r7, 0(%r26);"       // Carrega valor de r26 em r7
//
//		"mr %r3, %r7;"
//
//		"stdu %r1, -0xB0(%r1);"      // Aloca espaço na pilha (compatível com o original)
//		"mflr %r0;"                  // Salva o LR original
//		"std %r0, 0xC0(%r1);"        // Armazena LR na pilha
//		"std %r26, 0xA8(%r1);"       // Salva r26
//		"std %r29, 0xA0(%r1);"       // Salva r29
//		"std %r30, 0x98(%r1);"       // Salva r30
//		"std %r31, 0x90(%r1);"       // Salva r31
//
//		// Preparar argumentos para check (se necessário)
//		"mr %r5, %r29;"              // Copia r29 para r5
//		"mr %r6, %r30;"              // Copia r30 para r6
//		"lwz %r7, 0(%r26);"          // Carrega valor de r26 em r7
//		"mr %r3, %r7;"               // Passa r7 como argumento para check
//
//		// Chamar check
//		"bl check;"                  // Chama a função check
//
//		// Restaurar registradores
//		"ld %r31, 0x90(%r1);"        // Restaura r31
//		"ld %r30, 0x98(%r1);"        // Restaura r30
//		"ld %r29, 0xA0(%r1);"        // Restaura r29
//		"ld %r26, 0xA8(%r1);"        // Restaura r26
//		"ld %r0, 0xC0(%r1);"         // Carrega o LR original
//		"mtlr %r0;"                  // Restaura o LR (corrigido de mflr para mtlr)
//		"addi %r1, %r1, 0xB0;"       // Restaura a pilha
//
//
//		"lis %r0, 0x1;"
//		"ori %r0, %r0, 0x0200;"
//		"cmplw %r7, %r0;"    
//		"blt skip_lwzP;"
//
//		"lwz %r8, 0x20(%r7);"    
//		"b continue_executionP1;"  
//
//		"skip_lwzP:"              
//		"lis %r12, 0x00A0;"
//		"ori %r12, %r12, 0xF23C;" // Endereço 0xA0F23C
//		"mtctr %r12;"
//		"bctr;"                   
//
//		"continue_executionP1:"    
//		"lis %r12, 0x00A0;"
//		"ori %r12, %r12, 0xF214;"
//		"mtctr %r12;"
//		"bctr;"                
//		);
//}


Detour* rage_netSyncNodeBase_IsEntityTypeSynced_t;
__declspec(naked) void rage_netSyncNodeBase_IsEntityTypeSynced() {
	asm(
		"mr %r5, %r29;"
		"mr %r6, %r30;"
		"lwz %r7, 0(%r26);"

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r7, %r0;"     
		"blt skip_lwzP;"



		"lwz %r8, 0x20(%r7);"

		"b continue_executionP;"

		"skip_lwzP:"
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xF23C;"
		"mtctr %r12;"
		"bctr;"

		"continue_executionP:"
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xF214;"
		"mtctr %r12;"
		"bctr;"
		);
}



Detour* rage_netSyncParentNode_RecursiveDestory_t;
__declspec(naked) void rage_netSyncParentNode_RecursiveDestory() {
	asm(
		"clrldi %r30, %r4, 32;"
		"mr %r3, %r30;"
		"lwz %r4, 0(%r30);"

		"cmpwi %r4, 0;"
		"beq skip_lwzssssP;"

		"lwz %r4, 0x14(%r4);"

		"b continue_executionPsssss;"

		"skip_lwzssssP:"//00A0EF70
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xEF70;"
		"mtctr %r12;"
		"bctr;"

		"continue_executionPsssss:"//A0F214
		"lis %r12, 0x00A0;"
		"ori %r12, %r12, 0xEF50;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* netSyncParentNode_Reset_t;
__declspec(naked) void netSyncParentNode_Reset() {
	asm(
		"lwz %r6, 8(%r3);"
		"cmpwi %r6, 0;"
		"beq locret_15B7768;"
		"li %r4, 0;"
		"li %r7, 0;"

		"loc_15B7724:"
		"addi %r7, %r7, 1;"
		"cmpwi %r7, 30;"
		"bgt locret_15B7768;"
		"lwz %r5, 0(%r3);"
		"cmpwi %r5, 0;"
		"beq loc_15B7760;"
		"lwz %r6, 4(%r5);"
		"stw %r6, 0(%r3);"
		"stw %r4, 4(%r5);"
		"lwz %r5, 0(%r3);"
		"cmpwi %r5, 0;"
		"beq loc_15B7750;"
		"stw %r4, 8(%r5);"
		"b loc_15B7754;"

		"loc_15B7750:"
		"stw %r4, 4(%r3);"

		"loc_15B7754:"
		"lwz %r6, 8(%r3);"
		"addic %r6, %r6, -1;"
		"stw %r6, 8(%r3);"

		"loc_15B7760:"
		"cmpwi %r6, 0;"
		"bne loc_15B7724;"

		"locret_15B7768:"
		"blr;"
	);
}

Detour* sub_6939D0_t;
__declspec(naked) void sub_6939D0() {
	asm(
		"cmpwi %r30, 0;"
		"beq loc_693A34;"
		"lwz %r30, 0x28(%r30);"

		"lwz %r4, 0(%r3);"
		"cmpwi %r30, 0;"
		"beq loc_693A34;"

		"lwz %r30, 0x14(%r30);"

		"b continue_execution5aaa;"

		"loc_693A34:" //0x693A34            
		"lis %r12, 0x0069;"
		"ori %r12, %r12, 0x3A34;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution5aaa:"   //6939F8
		"lis %r12, 0x0069;"
		"ori %r12, %r12, 0x39F8;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_9E9230_t;
__declspec(naked) void sub_9E9230() {//sub_9E9230
	asm(
		"cmpwi %r5, 7;"
		"beq skip_lwzssssPss;"

		"lbz %r4, 0x91(%r5);"
		"addic %r6, %r6, 1;"
		"cmpwi %r4, 0xC;"
		"beq loc_9E9270;"

		"b continue_execution5aaaa;"

		"skip_lwzssssPss:"
		"lis %r12, 0x009E;"
		"ori %r12, %r12, 0x9284;"
		"mtctr %r12;"
		"bctr;"


		"loc_9E9270:"
		"lis %r12, 0x009E;"
		"ori %r12, %r12, 0x9270;"
		"mtctr %r12;"
		"bctr;"

		"continue_execution5aaaa:"
		"lis %r12, 0x009E;"
		"ori %r12, %r12, 0x925C;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_152DFB4_t;
__declspec(naked) void sub_152DFB4() {
	asm(
		"mr %r30, %r5;"           // Original instruction

		// Check if r3 == 0 and patch it
		"cmpwi %r3, 0;"           // Compare r3 with 0
		"bne skip_patch;"         // If r3 != 0, skip the patch
		"lis %r3, 0x3242;"        // Load upper 16 bits of 0x32421778 into r3
		"ori %r3, %r3, 0x1778;"   // Load lower 16 bits into r3
		"skip_patch:;"            // Label to continue execution

		"lwz %r5, 4(%r3);"        // Original instruction that caused crash if r3 = 0
		"lwz %r28, 0(%r4);"
		"sldi %r6, %r5, 6;"
		"sldi %r5, %r5, 3;"
		"cntlzw %r29, %r30;"
		"addc %r5, %r6, %r5;"
		"extrwi %r29, %r29, 1,26;"
		"addc %r3, %r3, %r5;"
		"clrldi %r31, %r3, 32;"
		"addic %r27, %r3, 8;"
		"clrldi %r27, %r27, 32;"
		"lhz %r4, 0x30(%r31);"
		"lhz %r3, 0x32(%r31);"
		"cmpw %r4, %r3;"

		"lis %r12, 0x0152;"//0152E000
		"ori %r12, %r12, 0xE000;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_152D824_t;
__declspec(naked) void sub_152D824() {
	asm(
		"cmpwi %r3, 0;"
		"bne skip_patcaah;"
		"lis %r3, 0x3216;"
		"ori %r3, %r3, 0x3160;"
		"skip_patcaah:;"

		"lwz %r5, 4(%r3);"
		"lwz %r30, 0(%r4);"
		"sldi %r6, %r5, 6;"
		"sldi %r5, %r5, 3;"

		"lis %r12, 0x0152;"
		"ori %r12, %r12, 0xD84C;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_15B1CC_t;
__declspec(naked) void sub_15B1CC() {//idk
	asm(
		"cmpwi %r3, 0;"
		"bne skip_patcaahq;"
		"lis %r3, 0x3216;"
		"ori %r3, %r3, 0x3160;"
		"skip_patcaahq:;"

		"lwz %r5, 4(%r3);"
		"lwz %r30, 0(%r4);"
		"sldi %r6, %r5, 6;"
		"sldi %r5, %r5, 3;"

		"lis %r12, 0x0152;"
		"ori %r12, %r12, 0xD84C;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* CRemoveWeaponEvent_HandleReceived_t;
__declspec(naked) void CRemoveWeaponEvent_HandleReceived() {//idk
	asm(

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r30, %r0;"
		"blt ddosssss;"



		"lbz %r4, 0x27(%r30);"
		"cmpwi %r4, 0;"
		"beq loc_12C3C58;"
		"lwz %r4, 0x20(%r31);"
		"b aaaaaasssaaaa;"

		"loc_12C3C58:"
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3C58;"
		"mtctr %r12;"
		"bctr;"


		"aaaaaasssaaaa:"
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3C50;"
		"mtctr %r12;"
		"bctr;"

		"ddosssss:"//12C 3C6C
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3C6C;"
		"mtctr %r12;"
		"bctr;"

	);
}

Detour* CRemoveAllWeaponsEvent_HandleReceived_t;
__declspec(naked) void CRemoveAllWeaponsEvent_HandleReceived() {
	asm(

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r31, %r0;"
		"blt dsafwefawfaw;"

		"lbz %r4, 0x27(%r31);"
		"cmpwi %r4, 0;"
		"beq loc_12C3E30;"
		"lis %r12, 0x012C;"//12C 3D0C
		"ori %r12, %r12, 0x3D0C;"
		"mtctr %r12;"
		"bctrl;"
		"b continuaaaa;"


		"dsafwefawfaw:"//12C 3E40
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3E40;"
		"mtctr %r12;"
		"bctr;"

		"continuaaaa:"//12C 3E2C
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3E2C;"
		"mtctr %r12;"
		"bctr;"



		"loc_12C3E30:"
		"lis %r12, 0x012C;"
		"ori %r12, %r12, 0x3E30;"
		"mtctr %r12;"
		"bctr;"
	);
}

Detour* sub_1341420_t;
__declspec(naked) void sub_1341420() {
	asm(
		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r4, %r0;"
		"blt adwdwdawd;"

		"lwz %r27, 0x1C(%r31);"
		"mr %r3, %r27;"
		"lwz %r4, 0(%r27);"
		"lwz %r4, 0x7C(%r4);"

		"lis %r12, 0x0134;"//0134 1478
		"ori %r12, %r12, 0x1478;"
		"mtctr %r12;"
		"bctr;"

		"adwdwdawd:"
		"lis %r12, 0x0134;"//134 14BC
		"ori %r12, %r12, 0x14BC;"
		"mtctr %r12;"
		"bctr;"


	);
}

Detour* CNetworkObjectMgr_HandleCloneSync_t;
__declspec(naked) void CNetworkObjectMgr_HandleCloneSync() {
	asm(
		"lwz %r4, 0(%r28);"
		"mr %r3, %r28;"

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r4, %r0;"
		"blt safgweafwf;"

		"cmpwi %r4, -1;"
		"beq safgweafwf;"

		"lwz %r4, 0x38(%r4);"
		"lwz %r4, 0(%r4);"

		"lis %r12, 0x0133;"//0133 D798
		"ori %r12, %r12, 0xD798;"
		"mtctr %r12;"
		"bctr;"

		"safgweafwf:"
		"lis %r12, 0x133;"//133 DA74
		"ori %r12, %r12, 0xDA74;"
		"mtctr %r12;"
		"bctr;"


	);
}

Detour* CNetworkObjectMgr_HandleCloneSync_ht;
uint32_t CNetworkObjectMgr_HandleCloneSync_h(uint32_t cNetworkObjectMgr, uint32_t CNetGamePlayer_client, uint32_t CNetGamePlayer_self, uint32_t syncTreetype, uint16_t object_id, uint32_t r8, uint32_t r9, uint32_t r10) {
	if (syncTreetype > 13)
	{
		SyncPlayer[*(uint8_t*)(CNetGamePlayer_client + 0x29)] = true;
		return 6;
	}

	uint32_t sync_pool = Game::invoke<uint32_t>(0x13398D4, cNetworkObjectMgr, syncTreetype);
	if (!sync_pool)
	{
		SyncPlayer[*(uint8_t*)(CNetGamePlayer_client + 0x29)] = true;
		return 6;
	}

	if (SyncPlayer[*(uint8_t*)(CNetGamePlayer_client + 0x29)])
		return 6;

	return CNetworkObjectMgr_HandleCloneSync_ht->CallOriginal<uint32_t>(cNetworkObjectMgr, CNetGamePlayer_client, CNetGamePlayer_self, syncTreetype, object_id, r8, r9, r10);
}

Detour* jenkinsHash_t;
int jenkinsHash(char *string, int zero)
{
	if ((uintptr_t)string < 0x10200) {
		printf("0x%x - %i\n", __builtin_return_address(), __reg(3));
		return -1;
	}
	
	return jenkinsHash_t->CallOriginal<int>(string, zero);
}
//__declspec(naked) void jenkinsHash() {
//	asm(
//		"mr %r5, %r4;"
//
//		"lis %r0, 0x1;"
//		"ori %r0, %r0, 0x0200;"
//		"cmplw %r3, %r0;"
//		"blt skip_freezeV2;"
//
//
//		"lbz %r4, 0(%r3);"      // lbz r4, 0(r3)
//		"lis %r6, 0x0184;"       // lis r6, unk_18457E5@h (0x184)
//		"addic %r4, %r4, -0x22;"
//		"b idkkkkkkkkkk;"
//
//
//
//		"skip_freezeV2:"//D014 F180
//		"lis %r3, 0xD014;"
//		"ori %r3, %r3, 0xF180;"
//		"b idkkkkkkkkkk;"
//
//		"idkkkkkkkkkk:"//AE 582C
//		"lis %r12, 0x00AE;"
//		"ori %r12, %r12, 0x582C;"
//		"mtctr %r12;"
//		"bctr;"
//
//	);
//}

Detour* sub_1567FC0_t;
__declspec(naked) void sub_1567FC0() {
	asm(
		"lwz %r6, 8(%r4);"
		"lwz %r7, 4(%r4);"

		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r6, %r0;"
		"blt blod;"

		"stw %r7, 4(%r6);"
		"lwz %r6, 4(%r4);"

		"b blod_continua;"

		"blod_continua:"//0 35 7E58
		"lis %r12, 0x0156;"
		"ori %r12, %r12, 0x8034;"
		"mtctr %r12;"
		"bctr;"

		"blod:"//156 8050
		"lis %r12, 0x0156;"
		"ori %r12, %r12, 0x8050;"
		"mtctr %r12;"
		"bctr;"

	);
}

Detour* CNetworkSpecialFireEquippedWeaponEvent_HandleReceived_t;
__declspec(naked) void CNetworkSpecialFireEquippedWeaponEvent_HandleReceived() {
	asm(
		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r4, %r0;"      //r7 < 0x10200
		"blt pulaaaaaaaaaa;"

		"lwz %r4, 0x7C(%r4);"
		"cmpwi %r4, -1;"
		"beq loc_12D3134;"
		"beq %cr1, loc_12D3104;"
		"b idkkkkdkdkdkdkd;"

		"loc_12D3134:"//0 12D 3134
		"lis %r12, 0x012D;"
		"ori %r12, %r12, 0x3134;"
		"mtctr %r12;"
		"bctr;"

		"idkkkkdkdkdkdkd:"//0 012D 30E8
		"lis %r12, 0x012D;"
		"ori %r12, %r12, 0x30E8;"
		"mtctr %r12;"
		"bctr;"


		"loc_12D3104:"//0 12D 3134
		"lis %r12, 0x012D;"
		"ori %r12, %r12, 0x3104;"
		"mtctr %r12;"
		"bctr;"



		"pulaaaaaaaaaa:"//0 12D 334C
		"lis %r12, 0x012D;"
		"ori %r12, %r12, 0x334C;"
		"mtctr %r12;"
		"bctr;"

	);
}

void CNetworkObjectMgr_HandleCloneCreate(uint64_t r3, CNetGamePlayer* sender, void* receiver, unsigned int entitySpawnType, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10) {
	if (!VALID_ADDR(r9) || !VALID_ADDR(sender) || SyncPlayer[sender->nonPhysicalPlayerData->playerIndex]) return;

	bool callSpawn = true, doAntiFreezeBool = false;
	unsigned int modelHash = *(unsigned int*)(r9 + 0x20);

	if (entitySpawnType == 5) {
		uint64_t longHash = *(uint64_t*)(r9 + 0x20) >> 27;
		if (Game::invoke<int>(0x4364EC, (unsigned int)(longHash & 0xFFFFFFFF))) doAntiFreezeBool = true;
	}

	CObjModelInfo* info = getCModelInfo(modelHash);
	if (VALID_ADDR(info)) {
		if ((entitySpawnType == 9 && info->modelType != 1) || (entitySpawnType == 4 && info->modelType != 6)) {
			doAntiFreezeBool = true;
		}
	}

	if (doAntiFreezeBool || !(modelHash == 0x705E61F2 || modelHash == 0x9C9EFFD8)) return;

	Game::invoke<int>(0x133C430, r3, sender, receiver, entitySpawnType, r7, r8, r9, r10);
}

unsigned int scriptEventDetour(unsigned int r3, unsigned int senderData, unsigned int recieverData, unsigned int r6, unsigned int r7, unsigned int r8, unsigned int r9)
{
	int addressOfArgs = r3 + 10 * 0x4;

	switch (*(int*)addressOfArgs) {
	case 0x2: {
		switch (*(int*)(addressOfArgs + 0x8)) {
		case 0x35:

			*(int*)addressOfArgs = 0;
			break;
		case 0x34:

			*(int*)addressOfArgs = 0;
			break;
		case 0x2E:

			*(int*)addressOfArgs = 0;
			break;
		}
		break;
	}
	case 0xDA:
	case 0xDB:
		*(int*)addressOfArgs = 0;
		break;

	case 0x3:
		if (*(int*)(addressOfArgs + 0x8) == 0x14) {
			*(int*)addressOfArgs = 0;
		}
		break;

	case 0x37:
		*(int*)addressOfArgs = 0;
		break;

	case 0x138:
		*(int*)addressOfArgs = 0;
		break;

	case 0xD8:
		*(int*)addressOfArgs = 0;
		break;

	case 0x16C:
		*(int*)addressOfArgs = 0;
		break;

	case 0x23:
		*(int*)addressOfArgs = 0;
		break;

	case 0x24:
		*(int*)addressOfArgs = 0;
		break;

	case 0x98:
		*(int*)addressOfArgs = 0;
		break;

	case 0x29:
		*(int*)addressOfArgs = 0;
		break;

	case 0x1E:
		*(int*)addressOfArgs = 0;
		break;

	case 0x1F:
		*(int*)addressOfArgs = 0;
		break;

	case 0x187198C:
		*(int*)addressOfArgs = 0;
		break;

	case 0x10:
		*(int*)addressOfArgs = 0;
		break;
	}

	switch (*(int*)(addressOfArgs + 0x8)) {
	case 0x3A:
		*(int*)addressOfArgs = 0;
		break;

	case 0x40:
		*(int*)addressOfArgs = 0;
		break;

	case 0x35:
		*(int*)addressOfArgs = 0;
		break;

	case 0x36:

		*(int*)addressOfArgs = 0;
		break;

	case 0x37:

		*(int*)addressOfArgs = 0;
		break;

	case 0x38:
		*(int*)addressOfArgs = 0;
		break;
	}

	return Game::invoke<unsigned int>(0x12C8D60, r3, senderData, recieverData, r6, r7, r8, r9);
}

Detour* sub_12C09D4_t;
__declspec(naked) void sub_12C09D4() {
	asm(
		"lwz %r3, 0(%r28);"
	
		"lis %r0, 0x1;"
		"ori %r0, %r0, 0x0200;"
		"cmplw %r3, %r0;"      //r7 < 0x10200
		"blt feaveavweveva;"

		"lwz %r4, 0(%r3);"
		"lwz %r4, 0x44(%r4);"
		"lwz %r4, 0(%r4);"
		"lis %r15, 0x012C;"//012C 0D1C
		"ori %r15, %r15, 0x0D1C;"
		"mtctr %r15;"
		"bctr;"



		"feaveavweveva:"
		"lis %r15, 0x012C;"//012C 0D54
		"ori %r15, %r15, 0x0D54;"
		"mtctr %r15;"
		"bctr;"
	);
}

Detour* sub_9F9C60_t;
__declspec(naked) void sub_9F9C60() {
	asm(
		"cmpwi %r3, 0;"
		"beq loc_9F9D24;"

		"lwz %r4, 0(%r3);"

		"lis %r15, 0x1;"
		"ori %r15, %r15, 0x0200;"
		"cmplw %r4, %r15;"
		"blt asdwdwafwfaw;"

		"cmpwi %r4, -1;"
		"beq asdwdwafwfaw;"

		"lwz %r4, 0x38(%r4);"

		"lis %r15, 0x009F;"//0 9F 9D00
		"ori %r15, %r15, 0x9D00;"
		"mtctr %r15;"
		"bctr;"


		"asdwdwafwfaw:"//9F9D3C
		"lis %r15, 0x009F;"
		"ori %r15, %r15, 0x9D3C;"
		"mtctr %r15;"
		"bctr;"


		"loc_9F9D24:"//9F 9D24
		"lis %r15, 0x009F;"
		"ori %r15, %r15, 0x9D24;"
		"mtctr %r15;"
		"bctr;"
	);
}

Detour* sub_12D5E70_t;
__declspec(naked) void sub_12D5E70() {
	asm(
		"addic %r3, %r31, 0x1C;"
		"lbz %r4, 0x29(%r30);"

		"lis %r15, 0xD004;"//D004 0FE4
		"ori %r15, %r15, 0x0FE4;"
		"cmplw %r31, %r15;"
		"beq loc_12D5EE4;"

		"stb %r4, 0x1C(%r31);"

		"lis %r15, 0x00FE;"//FE B3A0
		"ori %r15, %r15, 0xB3A0;"
		"mtctr %r15;"
		"bctrl;"

		"lis %r15, 0x012D;"//12D 5EAC
		"ori %r15, %r15, 0x5EAC;"
		"mtctr %r15;"
		"bctr;"



		"loc_12D5EE4:"//12D 5EE4
		"lis %r15, 0x012D;"
		"ori %r15, %r15, 0x5EE4;"
		"mtctr %r15;"
		"bctr;"
	);
}

Detour* sub_1336D90_t;
__declspec(naked) void sub_1336D90() {
	asm(
		"mr %r31, %r3;"

		"lis %r15, 0x1;"
		"ori %r15, %r15, 0x0200;"
		"cmplw %r31, %r15;"
		"blt loc_1336E0C;"

		"lwz %r4, 0x78(%r31);"
		"cmpwi %r4, 0;"
		"beq loc_1336E08;"

		"lis %r15, 0x0133;"//133 6DB0
		"ori %r15, %r15, 0x6DB0;"
		"mtctr %r15;"
		"bctr;"

		"loc_1336E08:"
		"lis %r15, 0x0133;"
		"ori %r15, %r15, 0x6E08;"
		"mtctr %r15;"
		"bctr;"


		"loc_1336E0C:"
		"lis %r15, 0x0133;"
		"ori %r15, %r15, 0x6E0C;"
		"mtctr %r15;"
		"bctr;"
	);
}


Detour* sub_472B44_t;
__declspec(naked) void sub_472B44() {//0047 2C38
	asm(
		"lis %r15, 0x1;"
		"ori %r15, %r15, 0x0200;"
		"cmplw %r3, %r15;"
		"blt loc_472DDC;"

		"lwz %r4, 0(%r3);"
		"lwz %r4, 8(%r4);"
		"lwz %r4, 0(%r4);"
		"mtctr %r4;"
		"bctrl;"

		"lis %r15, 0x0047;"//72C38
		"ori %r15, %r15, 0x2C38;"
		"mtctr %r15;"
		"bctr;"


		"loc_472DDC:"//loc_47 2DDC
		"lis %r15, 0x0047;"
		"ori %r15, %r15, 0x2DDC;"
		"mtctr %r15;"
		"bctr;"
	);
}


#define IS_LOADED_INTO_LOBBY ((bool)(*(int*)(*(int*)0x1CF72C4+0xA098) == 8))  

Detour* networkEventHandlerForStuffLikeKick__t;
void networkEventHandlerForStuffLikeKick__hook(unsigned int r3, unsigned int r4, unsigned int r5) {
	bool callit = true;

	int evtid = -1;

	int fiveVal = call<int>(*(int*)(*(int*)(*(int*)r5 + 0xC) + 0x0))(r5);

	if (fiveVal == 5) {

		unsigned int r26 = *(unsigned int*)(r5 + 0x28);
		int val = call<int>(0x16276C4)(&evtid, *(unsigned int*)(r26 + 0x48), *(unsigned int*)(r26 + 0x44));

		if (val != 0) {
			int someWeirdID = 0;

			char *freezeval_ptr = (char*)(*(int*)(r26 + 0x48));
			//int val1 = *(int*)(ptr + 0x0);
			//int val2 = *(int*)(ptr + 0x4);

			char freezeval_arr[] = { 0xC9, 0x18, 0x35, 0x90, 0xEA, 0xAA, 0xFA };

			if (evtid != 3 && evtid != 0x20 && evtid != 0x3E && evtid != 0x37 && evtid != 0x3D) {
				if (evtid == 0x1A) {
					bool freezeVal = true;
					for (int i = 0; i < sizeof(freezeval_arr); i++) {
						if (freezeval_ptr[i] != freezeval_arr[i])
							freezeVal = false;
					}

					if (freezeVal) {
						callit = false;
					}
				}
				if (evtid == 0xD/**(int*)0x2259578*/) {

					if (!IS_LOADED_INTO_LOBBY) {

					}
					else {
						callit = false;
					}
				}
				if (evtid == 0x9) {
					callit = false;
				}
			}
		}
	}

	if (callit)
		call<unsigned int>(0x138E0C8)(*(unsigned int*)0x1CF72C4, r4, r5);
}

Detour* UpdateNetworkObject_t;
void UpdateNetworkObject(int netPlayer, int netObject, int msgBuffer, int seqNum, int sendImmediately)
{
	printf("UpdateNetworkObject: a1: %i | a2: %i | a3: %i | a4: %i | a5: %i\n", netPlayer, netObject, msgBuffer, seqNum, sendImmediately);
	UpdateNetworkObject_t->CallOriginal<void>(netPlayer, netObject, msgBuffer, seqNum, sendImmediately);
}


namespace Patched
{
	void start()
	{
		int nop = 0x60000000;
		int branch = 0x4800020C;
		int blr = 0x4e800020;
		write_memory(0x12F0FFC, &nop, 4);

		write_memory(0x133B084, &nop, 4);
		write_memory(0x9FBBC8, &nop, 4);
		write_memory(0x9FBBCC, &nop, 4);
		write_memory(0x9FBA00, &branch, 4);//by gopro2027
		write_memory(0xA128E4, &nop, 4);
		write_memory(0x1309AC8, &blr, 4);//host crash
		write_memory(0x15B1CC, &blr, 4);//sunshade sky crash
		
		*(int*)0xF6CF88 = 0x4e800020;


		*(int*)0xA07700 = 0xFAA1FFA8;//std %r21, -0x58
	//	UpdateNetworkObject_t = new Detour(0xA076FC, UpdateNetworkObject, false);

		*(int*)0xFEB520 = 0xFB61FFD8;

		//vehicleFragmentPhysics_t = new Detour(0xFEB51C, vehicleFragmentPhysics, false);

		//*(int*)0xA07700 = 0xFAA1FFA8;

		//HookFunctionStart_fix(0xA076FC, *(unsigned int*)(UpdateNetworkObject), *(unsigned int*)(UpdateNetworkObject_Stub));

		networkEventHandlerForStuffLikeKick__t = new Detour(0x138F9DC, networkEventHandlerForStuffLikeKick__hook, true);


		//Sync
		rage_netSyncNodeBase_HasBeenSent_t = new Detour(0xA0F098, rage_netSyncNodeBase_HasBeenSent, true);
		netSyncTree_ReadFromBuffer_t = new Detour(0xA1723C, netSyncTree_ReadFromBuffer, true);
		sub_368520_t = new Detour(0x368608, sub_368520, true);
		sub_35AC20_t = new Detour(0x35B048, sub_35AC20, true);
		rage_netSyncNodeBase_IsEntityTypeSynced_t = new Detour(0xA0F204, rage_netSyncNodeBase_IsEntityTypeSynced, true);
		rage_netSyncParentNode_RecursiveDestory_t = new Detour(0xA0EF40, rage_netSyncParentNode_RecursiveDestory, true);
		netSyncParentNode_Reset_t = new Detour(0x15B7714, netSyncParentNode_Reset, true);
		sub_12C09D4_t = new Detour(0x12C0D0C, sub_12C09D4, true);
		sub_9F9C60_t = new Detour(0x9F9CF0, sub_9F9C60, true);
		sub_12D5E70_t = new Detour(0x12D5E9C, sub_12D5E70, true);
		//sub_1336D90_t = new Detour(0x1336DA0, sub_1336D90, true);
		//sub_472B44_t = new Detour(0x472C24, sub_472B44, true);


		//sunshade sky
		sub_6939D0_t = new Detour(0x6939E8, sub_6939D0, true);
		sub_9E9230_t = new Detour(0x9E924C, sub_9E9230, true);
		sub_152DFB4_t = new Detour(0x152DFC4, sub_152DFB4, true);
		sub_152D824_t = new Detour(0x152D83C, sub_152D824, true);
		sub_15B1CC_t = new Detour(0x15B288, sub_15B1CC, true);

		//Events
		CRemoveWeaponEvent_HandleReceived_t = new Detour(0x12C3C40, CRemoveWeaponEvent_HandleReceived, true);
		CRemoveAllWeaponsEvent_HandleReceived_t = new Detour(0x12C3E1C, CRemoveAllWeaponsEvent_HandleReceived, true);
		sub_1341420_t = new Detour(0x1341468, sub_1341420, true);
		CNetworkObjectMgr_HandleCloneSync_t = new Detour(0x133D788, CNetworkObjectMgr_HandleCloneSync, true);
		*(int*)0x133D6F0 = 0xFB01FFC0;//fix bl para chamar a funcao original sem travar
		CNetworkObjectMgr_HandleCloneSync_ht = new Detour(0x133D6EC, CNetworkObjectMgr_HandleCloneSync_h);

		//paradise
		//*(int*)0X109320C = 0X4E800020;
		//jenkinsHash_t = new Detour(0xAE580C, jenkinsHash, false);
		//sub_109320C_t = new Detour(0x109320C, sub_109320C, false);
		//sub_1273838_t = new Detour(0x1273B0C, sub_1273838, true);
		// Nota: A função sub_1273838 chama sub_109320C, que por sua vez chama jenkinsHash. Se eu aplicar o patch apenas no jenkinsHash,
		// o sub_1273838 continuará em execução e enviará um valor inválido para outras funcao. Por isso, o patch deve ser feito a partir de sub_1273838.


		//slod
		sub_1567FC0_t = new Detour(0x1568024, sub_1567FC0, true);

		//cell
		CNetworkSpecialFireEquippedWeaponEvent_HandleReceived_t = new Detour(0x12D30D8, CNetworkSpecialFireEquippedWeaponEvent_HandleReceived, true);

		*(uint64_t*)(0x1C707E0) = *(uint64_t*)((uint64_t)CNetworkObjectMgr_HandleCloneCreate);//by gopro2027

		*(uint64_t*)(0x1C6BD80) = *(uint64_t*)((uint64_t)scriptEventDetour);


	}

	void stop()
	{
		UpdateNetworkObject_t->~Detour();
		networkEventHandlerForStuffLikeKick__t->~Detour();
		rage_netSyncNodeBase_HasBeenSent_t->~Detour();
		netSyncTree_ReadFromBuffer_t->~Detour();
		sub_368520_t->~Detour();
		sub_35AC20_t->~Detour();
		rage_netSyncNodeBase_IsEntityTypeSynced_t->~Detour();
		rage_netSyncParentNode_RecursiveDestory_t->~Detour();
		netSyncParentNode_Reset_t->~Detour();
		sub_6939D0_t->~Detour();
		sub_9E9230_t->~Detour();
		sub_152DFB4_t->~Detour();
		sub_152D824_t->~Detour();
		sub_15B1CC_t->~Detour();
		CRemoveWeaponEvent_HandleReceived_t->~Detour();
		CRemoveAllWeaponsEvent_HandleReceived_t->~Detour();
		sub_1341420_t->~Detour();
		CNetworkObjectMgr_HandleCloneSync_t->~Detour();
		sub_1567FC0_t->~Detour();
		CNetworkSpecialFireEquippedWeaponEvent_HandleReceived_t->~Detour();
		*(uint64_t*)(0x1C707E0) = 0x0133C43001C85330;
		*(uint64_t*)(0x1C6BD80) = 0x012C8D6001C85330;
		sub_9F9C60_t->~Detour();
		sub_12C09D4_t->~Detour();
		sub_12D5E70_t->~Detour();
		CNetworkObjectMgr_HandleCloneSync_ht->~Detour();
		
	}
}