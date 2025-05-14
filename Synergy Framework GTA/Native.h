#include "stdafx.h"

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

union ScriptArg { unsigned int ui; float f; int i; char* str; };

struct Native_s
{
	Native_s* LastNativesTable;
	unsigned int NativeFunctions[7];
	unsigned int NativeCount;
	unsigned int NativeHashes[7];
};

struct NativeArg_s
{
	int* ReturnValue;
	unsigned int ArgCount;
	int* ArgValues;
	unsigned int ReadCount;
};

extern Native_s** g_Natives;
static NativeArg_s* NativeArg = (NativeArg_s*)0x10060000; // Open space addr

static void ResetArgs()
{
	NativeArg->ArgCount = 0;
	NativeArg->ReadCount = 0;
	NativeArg->ArgValues = (int*)0x10050000;
	NativeArg->ReturnValue = NativeArg->ArgValues;
}

template<typename T>
static void PushArg(T Value)
{
	*(T*)&NativeArg->ArgValues[NativeArg->ArgCount] = Value;
	NativeArg->ArgCount++;
}

static void PushArgsRecursively() {
}

template<typename T, typename... Args>
static void PushArgsRecursively(T first, Args... args) {
	PushArg(first);
	PushArgsRecursively(args...);
}

template<typename R>
static R GetReturn()
{
	R* Result = (R*)&NativeArg->ReturnValue[0];
	return *Result;
}

static void CallHash(unsigned int hash, NativeArg_s* pArg)
{
	Native_s* Natives = g_Natives[hash & 0xFF];
	while (Natives != 0)
	{
		for (unsigned int i = 0; i < Natives->NativeCount; i++)
		{
			if (Natives->NativeHashes[i] == hash)
			{
				((void(*)(NativeArg_s*))Natives->NativeFunctions[i])(pArg);
				return;
			}
		}
		Natives = Natives->LastNativesTable;
	}
}

template<typename T, typename... Args>
static T invoke(unsigned int NativeHash, Args... args)
{
	ResetArgs();
	PushArgsRecursively(args...);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

namespace UI
{
	static void SET_TEXT_FONT(Any p0) { invoke<Void>(0x80BC530D, p0); } // 0x80BC530D
	static void _ADD_TEXT_COMPONENT_STRING(const char* text) { invoke<Void>(0x27A244D8, text); } // 0x27A244D8
	static void SET_TEXT_SCALE(float p0, float p1) { invoke<Void>(0xB6E15B23, p0, p1); } // 0xB6E15B23
	static void SET_TEXT_COLOUR(int R, int G, int B, int A) { invoke<Void>(0xE54DD2C8, R, G, B, A); } // 0xE54DD2C8
	static void SET_TEXT_WRAP(float p0, float p1) { invoke<Void>(0x6F60AB54, p0, p1); } // 0x6F60AB54
	static void SET_TEXT_CENTRE(Any p0) { invoke<Void>(0xE26D39A1, p0); } // 0xE26D39A1
	static void SET_TEXT_DROPSHADOW(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xE6587517, p0, p1, p2, p3, p4); } // 0xE6587517
	static void SET_TEXT_OUTLINE() { invoke<Void>(0xC753412F); } // 0xC753412F
	static void _SET_TEXT_ENTRY(const char* text) { invoke<Void>(0x3E35563E, text); } // 0x3E35563E
	static void _DRAW_TEXT(float x, float y) { invoke<Void>(0x6F8350CE, x, y); } // 0x6F8350CE
	static void _0x574EE85C(char* p0) { invoke<Void>(0x574EE85C, p0); } // 0x574EE85C
	static int _SET_NOTIFICATION_MESSAGE(char* picName1, char* picName2, BOOL flash, int iconType, char* sender, char* subject) { return invoke<Any>(0xE7E3C98B, picName1, picName2, flash, iconType, sender, subject); } // 0xE7E3C98B
	static int _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return invoke<int>(0x08F7AF78, blink, p1); } // 0x08F7AF78
	static void _0xF42C43C7(char* p0) { invoke<Void>(0xF42C43C7, p0); } // 0xF42C43C7
	static void _0x38F82261(int Time, int unk) { invoke<Void>(0x38F82261, Time, unk); } // 0x38F82261
	static void HIDE_HUD_COMPONENT_THIS_FRAME(Any p0) { invoke<Void>(0xDB2D0762, p0); } // 0xDB2D0762
	static void HIDE_HELP_TEXT_THIS_FRAME() { invoke<Void>(0xF3807BED); } // 0xF3807BED
	static void SET_TEXT_EDGE(int p0, int p1, int p2, int p3, int p4) { invoke<Void>(0x3F1A5DAB, p0, p1, p2, p3, p4); } // 0x3F1A5DAB
	static BOOL IS_PAUSE_MENU_ACTIVE() { return invoke<BOOL>(0xD3600591); } // 0xD3600591
}

namespace CAM
{
	static void RENDER_SCRIPT_CAMS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x74337969, p0, p1, p2, p3, p4); } // 0x74337969
	static void _0xD3C08183(Any p0, Any p1, Any p2) { invoke<Void>(0xD3C08183, p0, p1, p2); } // 0xD3C08183
	static Any CREATE_CAM(char* camName, Any p1) { return invoke<Any>(0xE9BF2A7D, camName, p1); } // 0xE9BF2A7D
	static Any CREATE_CAM_WITH_PARAMS(char* camName, float* posX, float* posY, float* posZ, float* rotX, float* rotY, float* rotZ, float fov, int p8, int p9) { return invoke<Any>(0x23B02F15, camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); } // 0x23B02F15
	static Any CREATE_CAMERA(Any p0, Any p1) { return invoke<Any>(0x5D6739AE, p0, p1); } // 0x5D6739AE
	static Any CREATE_CAMERA_WITH_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x0688BE9A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0688BE9A
	static void DESTROY_CAM(Any p0, Any p1) { invoke<Void>(0xC39302BD, p0, p1); } // 0xC39302BD
	static void DESTROY_ALL_CAMS(Any p0) { invoke<Void>(0x10C151CE, p0); } // 0x10C151CE
	static BOOL DOES_CAM_EXIST(Any p0) { return invoke<BOOL>(0x1EF89DC0, p0); } // 0x1EF89DC0
	static void SET_CAM_ACTIVE(Any p0, Any p1) { invoke<Void>(0x064659C2, p0, p1); } // 0x064659C2
	static BOOL IS_CAM_ACTIVE(Any p0) { return invoke<BOOL>(0x4B58F177, p0); } // 0x4B58F177
	static BOOL IS_CAM_RENDERING(Any p0) { return invoke<BOOL>(0x6EC6B5B2, p0); } // 0x6EC6B5B2
	static Any GET_RENDERING_CAM() { return invoke<Any>(0x0FCF4DF1); } // 0x0FCF4DF1
	static vec3_t GET_CAM_COORD(Any p0) { return invoke<vec3_t>(0x7C40F09C, p0); } // 0x7C40F09C
	static vec3_t GET_CAM_ROT(Any p0, Any p1) { return invoke<vec3_t>(0xDAC84C9F, p0, p1); } // 0xDAC84C9F
	static Any GET_CAM_FOV(ScrHandle Camera_handle) { return invoke<Any>(0xD6E9FCF5, Camera_handle); } // 0xD6E9FCF5
	static Any GET_CAM_NEAR_CLIP(Any p0) { return invoke<Any>(0xCFCD35EE, p0); } // 0xCFCD35EE
	static Any GET_CAM_FAR_CLIP(Any p0) { return invoke<Any>(0x09F119B8, p0); } // 0x09F119B8
	static Any GET_CAM_FAR_DOF(Any p0) { return invoke<Any>(0x98C5CCE9, p0); } // 0x98C5CCE9
	static void SET_CAM_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0x2167CEBF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x2167CEBF
	static void SET_CAM_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7A8053AF, p0, p1, p2, p3); } // 0x7A8053AF
	static void SET_CAM_ROT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xEE38B3C1, p0, p1, p2, p3, p4); } // 0xEE38B3C1
	static void SET_CAM_FOV(char* camName, float FovVaule) { invoke<Void>(0xD3D5D74F, camName, FovVaule); } // 0xD3D5D74F
	static void SET_CAM_NEAR_CLIP(Any p0, Any p1) { invoke<Void>(0x46DB13B1, p0, p1); } // 0x46DB13B1
	static void SET_CAM_FAR_CLIP(Any p0, Any p1) { invoke<Void>(0x0D23E381, p0, p1); } // 0x0D23E381
	static void SET_CAM_NEAR_DOF(Any p0, Any p1) { invoke<Void>(0xF28254DF, p0, p1); } // 0xF28254DF
	static void SET_CAM_FAR_DOF(Any p0, Any p1) { invoke<Void>(0x58515E8E, p0, p1); } // 0x58515E8E
	static void SET_CAM_DOF_STRENGTH(Any p0, Any p1) { invoke<Void>(0x3CC4EB3F, p0, p1); } // 0x3CC4EB3F
	static void SET_CAM_DOF_PLANES(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAD6C2B8F, p0, p1, p2, p3, p4); } // 0xAD6C2B8F
	static void _0x8306C256(Any p0, Any p1) { invoke<Void>(0x8306C256, p0, p1); } // 0x8306C256
	static void SET_CAM_MOTION_BLUR_STRENGTH(Any p0, Any p1) { invoke<Void>(0xFD6E0D67, p0, p1); } // 0xFD6E0D67
	static void _0x8BBF2950() { invoke<Void>(0x8BBF2950); } // 0x8BBF2950
	static void ATTACH_CAM_TO_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xAD7C45F6, p0, p1, p2, p3, p4, p5); } // 0xAD7C45F6
	static void ATTACH_CAM_TO_PED_BONE(int CameraHandle, Ped PedHandle, int BoneIndex, float X, float Y, float Z, float Heading) { invoke<Void>(0x506BB35C, CameraHandle, PedHandle, BoneIndex, X, Y, Z, Heading); } // 0x506BB35C
	static void DETACH_CAM(char* camName) { invoke<Void>(0xF4FBF14A, camName); } // 0xF4FBF14A
	static void SET_CAM_INHERIT_ROLL_VEHICLE(Any p0, Any p1) { invoke<Void>(0xE4BD5342, p0, p1); } // 0xE4BD5342
	static void POINT_CAM_AT_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x914BC21A, p0, p1, p2, p3); } // 0x914BC21A
	static void POINT_CAM_AT_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7597A0F7, p0, p1, p2, p3, p4, p5); } // 0x7597A0F7
	static void POINT_CAM_AT_PED_BONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x09F47049, p0, p1, p2, p3, p4, p5, p6); } // 0x09F47049
	static void STOP_CAM_POINTING(Any p0) { invoke<Void>(0x5435F6A5, p0); } // 0x5435F6A5
	static void _0x0C74F9AF(Any p0, Any p1) { invoke<Void>(0x0C74F9AF, p0, p1); } // 0x0C74F9AF
	static void _0xE1A0B2F1(Any p0, Any p1) { invoke<Void>(0xE1A0B2F1, p0, p1); } // 0xE1A0B2F1
	static void _0x43220969(Any p0, Any p1) { invoke<Void>(0x43220969, p0, p1); } // 0x43220969
	static void SET_CAM_DEBUG_NAME(Any p0, Any p1) { invoke<Void>(0x9B00DF3F, p0, p1); } // 0x9B00DF3F
	static void ADD_CAM_SPLINE_NODE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xAD3C7EAA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xAD3C7EAA
	static void _0x30510511(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x30510511, p0, p1, p2, p3); } // 0x30510511
	static void _0xBA6C085B(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBA6C085B, p0, p1, p2, p3); } // 0xBA6C085B
	static void _0xB4737F03(Any p0, Any p1, Any p2) { invoke<Void>(0xB4737F03, p0, p1, p2); } // 0xB4737F03
	static void SET_CAM_SPLINE_PHASE(Any p0, Any p1) { invoke<Void>(0xF0AED233, p0, p1); } // 0xF0AED233
	static Any GET_CAM_SPLINE_PHASE(Any p0) { return invoke<Any>(0x39784DD9, p0); } // 0x39784DD9
	static Any GET_CAM_SPLINE_NODE_PHASE(Any p0) { return invoke<Any>(0x7B9522F6, p0); } // 0x7B9522F6
	static void SET_CAM_SPLINE_DURATION(Any p0, Any p1) { invoke<Void>(0x3E91FC8A, p0, p1); } // 0x3E91FC8A
	static void _0x15E141CE(Any p0, Any p1) { invoke<Void>(0x15E141CE, p0, p1); } // 0x15E141CE
	static Any GET_CAM_SPLINE_NODE_INDEX(Any p0) { return invoke<Any>(0xF8AEB6BD, p0); } // 0xF8AEB6BD
	static void _0x21D275DA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x21D275DA, p0, p1, p2, p3); } // 0x21D275DA
	static void _0xA3BD9E94(Any p0, Any p1, Any p2) { invoke<Void>(0xA3BD9E94, p0, p1, p2); } // 0xA3BD9E94
	static void OVERRIDE_CAM_SPLINE_VELOCITY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x326A17E2, p0, p1, p2, p3); } // 0x326A17E2
	static void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x633179E6, p0, p1, p2, p3); } // 0x633179E6
	static void _0xC90B2DDC(Any p0, Any p1, Any p2) { invoke<Void>(0xC90B2DDC, p0, p1, p2); } // 0xC90B2DDC
	static BOOL IS_CAM_SPLINE_PAUSED(Any p0) { return invoke<BOOL>(0x60B34FF5, p0); } // 0x60B34FF5
	static void SET_CAM_ACTIVE_WITH_INTERP(int camTo, int camFrom, int duration, Any unk0, Any unk1) { invoke<Void>(0x7983E7F0, camTo, camFrom, duration, unk0, unk1); } // 0x7983E7F0
	static BOOL IS_CAM_INTERPOLATING(Any p0) { return invoke<BOOL>(0x7159CB5D, p0); } // 0x7159CB5D
	static void SHAKE_CAM(Any p0, Any p1, Any p2) { invoke<Void>(0x1D4211B0, p0, p1, p2); } // 0x1D4211B0
	static void ANIMATED_SHAKE_CAM(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xE1168767, p0, p1, p2, p3, p4); } // 0xE1168767
	static BOOL IS_CAM_SHAKING(Any p0) { return invoke<BOOL>(0x0961FD9B, p0); } // 0x0961FD9B
	static void SET_CAM_SHAKE_AMPLITUDE(Any p0, Any p1) { invoke<Void>(0x60FF6382, p0, p1); } // 0x60FF6382
	static void STOP_CAM_SHAKING(Any p0, Any p1) { invoke<Void>(0x40D0EB87, p0, p1); } // 0x40D0EB87
	static void _0x2B0F05CD(Any p0, Any p1) { invoke<Void>(0x2B0F05CD, p0, p1); } // 0x2B0F05CD
	static void _0xCB75BD9C(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCB75BD9C, p0, p1, p2, p3); } // 0xCB75BD9C
	static Any _0x6AEFE6A5() { return invoke<Any>(0x6AEFE6A5); } // 0x6AEFE6A5
	static void _0x26FCFB96(Any p0) { invoke<Void>(0x26FCFB96, p0); } // 0x26FCFB96
	static Any PLAY_CAM_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<Any>(0xBCEFB87E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xBCEFB87E
	static BOOL IS_CAM_PLAYING_ANIM(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xB998CB49, p0, p1, p2); } // 0xB998CB49
	static void SET_CAM_ANIM_CURRENT_PHASE(Any p0, Any p1) { invoke<Void>(0x3CB1D17F, p0, p1); } // 0x3CB1D17F
	static Any GET_CAM_ANIM_CURRENT_PHASE(Any p0) { return invoke<Any>(0x345F72D0, p0); } // 0x345F72D0
	static Any PLAY_SYNCHRONIZED_CAM_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x9458459E, p0, p1, p2, p3); } // 0x9458459E
	static void _0x56F9ED27(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x56F9ED27, p0, p1, p2, p3); } // 0x56F9ED27
	static void _0x71570DBA(Any p0, Any p1) { invoke<Void>(0x71570DBA, p0, p1); } // 0x71570DBA
	static void _0x60B345DE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x60B345DE, p0, p1, p2, p3); } // 0x60B345DE
	static void _0x44473EFC(Any p0) { invoke<Void>(0x44473EFC, p0); } // 0x44473EFC
	static Any _0xDA931D65(Any p0) { return invoke<Any>(0xDA931D65, p0); } // 0xDA931D65
	static BOOL IS_SCREEN_FADED_OUT() { return invoke<BOOL>(0x9CAA05FA); } // 0x9CAA05FA
	static BOOL IS_SCREEN_FADED_IN() { return invoke<BOOL>(0x4F37276D); } // 0x4F37276D
	static BOOL IS_SCREEN_FADING_OUT() { return invoke<BOOL>(0x79275A57); } // 0x79275A57
	static BOOL IS_SCREEN_FADING_IN() { return invoke<BOOL>(0xC7C82800); } // 0xC7C82800
	static void DO_SCREEN_FADE_IN(int ticks) { invoke<Void>(0x66C1BDEE, ticks); } // 0x66C1BDEE
	static void DO_SCREEN_FADE_OUT(int ticks) { invoke<Void>(0x89D01805, ticks); } // 0x89D01805
	static void SET_WIDESCREEN_BORDERS(int p0, int p1) { invoke<Void>(0x1A75DC9A, p0, p1); } // 0x1A75DC9A
	static vec3_t GET_GAMEPLAY_CAM_COORD() { return invoke<vec3_t>(0x9388CF79); } // 0x9388CF79
	static vec3_t GET_GAMEPLAY_CAM_ROT(Any p0) { return invoke<vec3_t>(0x13A010B5, p0); } // 0x13A010B5
	static Any GET_GAMEPLAY_CAM_FOV() { return invoke<Any>(0x4D6B3BFA); } // 0x4D6B3BFA
	static void _0xA6E73135(Any p0) { invoke<Void>(0xA6E73135, p0); } // 0xA6E73135
	static void _0x1126E37C(Any p0) { invoke<Void>(0x1126E37C, p0); } // 0x1126E37C
	static Any GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return invoke<Any>(0xCAF839C2); } // 0xCAF839C2
	static void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading) { invoke<Void>(0x20C6217C, heading); } // 0x20C6217C
	static Any GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return invoke<Any>(0xFC5A4946); } // 0xFC5A4946
	static void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float x, float Value2) { invoke<Void>(0x6381B963, x, Value2); } // 0x6381B963
	static void SHAKE_GAMEPLAY_CAM(Any p0, Any p1) { invoke<Void>(0xF2EFE660, p0, p1); } // 0xF2EFE660
	static BOOL IS_GAMEPLAY_CAM_SHAKING() { return invoke<BOOL>(0x3457D681); } // 0x3457D681
	static void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(Any p0) { invoke<Void>(0x9219D44A, p0); } // 0x9219D44A
	static void STOP_GAMEPLAY_CAM_SHAKING(Any p0) { invoke<Void>(0xFD569E4E, p0); } // 0xFD569E4E
	static void _0x7D3007A2(Any p0) { invoke<Void>(0x7D3007A2, p0); } // 0x7D3007A2
	static BOOL IS_GAMEPLAY_CAM_RENDERING() { return invoke<BOOL>(0x0EF276DA); } // 0x0EF276DA
	static Any _0xC0B00C20() { return invoke<Any>(0xC0B00C20); } // 0xC0B00C20
	static Any _0x60C23785() { return invoke<Any>(0x60C23785); } // 0x60C23785
	static void _0x20BFF6E5(Any p0) { invoke<Void>(0x20BFF6E5, p0); } // 0x20BFF6E5
	static void _0xA61FF9AC() { invoke<Void>(0xA61FF9AC); } // 0xA61FF9AC
	static BOOL IS_GAMEPLAY_CAM_LOOKING_BEHIND() { return invoke<BOOL>(0x33C83F17); } // 0x33C83F17
	static void _0x2701A9AD(Any p0) { invoke<Void>(0x2701A9AD, p0); } // 0x2701A9AD
	static void _0xC4736ED3(Any p0) { invoke<Void>(0xC4736ED3, p0); } // 0xC4736ED3
	static void _0x6B0E9D57() { invoke<Void>(0x6B0E9D57); } // 0x6B0E9D57
	static BOOL IS_SPHERE_VISIBLE(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xDD1329E2, p0, p1, p2, p3); } // 0xDD1329E2
	static BOOL IS_FOLLOW_PED_CAM_ACTIVE() { return invoke<BOOL>(0x9F9E856C); } // 0x9F9E856C
	static Any SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(Any p0, Any p1) { return invoke<Any>(0x1425F6AC, p0, p1); } // 0x1425F6AC
	static void _0x8DC53629(Any p0, Any p1) { invoke<Void>(0x8DC53629, p0, p1); } // 0x8DC53629
	static void _0x1F9DE6E4() { invoke<Void>(0x1F9DE6E4); } // 0x1F9DE6E4
	static void _CLAMP_GAMEPLAY_CAM_YAW(float minimum, float maximum) { invoke<Void>(0x749909AC, minimum, maximum); } // 0x749909AC
	static void _CLAMP_GAMEPLAY_CAM_PITCH(float minimum, float maximum) { invoke<Void>(0xFA3A16E7, minimum, maximum); } // 0xFA3A16E7
	static void _ANIMATE_GAMEPLAY_CAM_ZOOM(float p0, float _distance) { invoke<Void>(0x77340650, p0, _distance); } // 0x77340650
	static void _0x4B22C5CB(Vehicle p0, int p1) { invoke<Void>(0x4B22C5CB, p0, p1); } // 0x4B22C5CB
	static Any GET_FOLLOW_PED_CAM_ZOOM_LEVEL() { return invoke<Any>(0x57583DF1); } // 0x57583DF1
	static Any GET_FOLLOW_PED_CAM_VIEW_MODE() { return invoke<Any>(0xA65FF946); } // 0xA65FF946
	static void SET_FOLLOW_PED_CAM_VIEW_MODE(Any p0) { invoke<Void>(0x495DBE8D, p0); } // 0x495DBE8D
	static BOOL IS_FOLLOW_VEHICLE_CAM_ACTIVE() { return invoke<BOOL>(0x8DD49B77); } // 0x8DD49B77
	static void _0x9DB5D391(Any p0) { invoke<Void>(0x9DB5D391, p0); } // 0x9DB5D391
	static void _0x92302899(Any p0, Any p1) { invoke<Void>(0x92302899, p0, p1); } // 0x92302899
	static Any GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL() { return invoke<Any>(0x8CD67DE3); } // 0x8CD67DE3
	static void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(Any p0) { invoke<Void>(0x8F55EBBE, p0); } // 0x8F55EBBE
	static Any GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() { return invoke<Any>(0xA4B4DB03); } // 0xA4B4DB03
	static void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(Any p0) { invoke<Void>(0xC4FBBBD3, p0); } // 0xC4FBBBD3
	static Any _0xF3B148A6(Any p0) { return invoke<Any>(0xF3B148A6, p0); } // 0xF3B148A6
	static void _0x1DEBCB45(Any p0, Any p1) { invoke<Void>(0x1DEBCB45, p0, p1); } // 0x1DEBCB45
	static BOOL IS_AIM_CAM_ACTIVE() { return invoke<BOOL>(0xC24B4F6F); } // 0xC24B4F6F
	static Any _0x8F320DE4() { return invoke<Any>(0x8F320DE4); } // 0x8F320DE4
	static BOOL IS_FIRST_PERSON_AIM_CAM_ACTIVE() { return invoke<BOOL>(0xD6280468); } // 0xD6280468
	static void _0x1BAA7182() { invoke<Void>(0x1BAA7182); } // 0x1BAA7182
	static Any _0x33951005() { return invoke<Any>(0x33951005); } // 0x33951005
	static void _0x9F4AF763(float p0) { invoke<Void>(0x9F4AF763, p0); } // 0x9F4AF763
	static void _0x68BA0730(Any p0, Any p1) { invoke<Void>(0x68BA0730, p0, p1); } // 0x68BA0730
	static void _0x2F29F0D5(Any p0, Any p1) { invoke<Void>(0x2F29F0D5, p0, p1); } // 0x2F29F0D5
	static void _0x76DAC96C(Any p0, Any p1) { invoke<Void>(0x76DAC96C, p0, p1); } // 0x76DAC96C
	static void _0x0E21069D(Any p0) { invoke<Void>(0x0E21069D, p0); } // 0x0E21069D
	static void _0x71E9C63E(Any p0) { invoke<Void>(0x71E9C63E, p0); } // 0x71E9C63E
	static void _0xD1EEBC45(Any p0) { invoke<Void>(0xD1EEBC45, p0); } // 0xD1EEBC45
	static vec3_t _0x9C84BDA0() { return invoke<vec3_t>(0x9C84BDA0); } // 0x9C84BDA0
	static vec3_t _0x1FFBEFC5(Any p0) { return invoke<vec3_t>(0x1FFBEFC5, p0); } // 0x1FFBEFC5
	static vec3_t _0xACADF916(Any p0, Any p1) { return invoke<vec3_t>(0xACADF916, p0, p1); } // 0xACADF916
	static Any _0x721B763B() { return invoke<Any>(0x721B763B); } // 0x721B763B
	static Any _0x23E3F106(Any p0) { return invoke<Any>(0x23E3F106, p0); } // 0x23E3F106
	static Any _0x457AE195() { return invoke<Any>(0x457AE195); } // 0x457AE195
	static Any _0x46CB3A49() { return invoke<Any>(0x46CB3A49); } // 0x46CB3A49
	static Any _0x19297A7A() { return invoke<Any>(0x19297A7A); } // 0x19297A7A
	static Any _0xF24777CA() { return invoke<Any>(0xF24777CA); } // 0xF24777CA
	static Any _0x38992E83() { return invoke<Any>(0x38992E83); } // 0x38992E83
	static void SET_GAMEPLAY_COORD_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xF27483C9, p0, p1, p2, p3, p4, p5, p6); } // 0xF27483C9
	static void SET_GAMEPLAY_PED_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x7C27343E, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x7C27343E
	static void SET_GAMEPLAY_VEHICLE_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2C9A11D8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C9A11D8
	static void _0x2ED5E2F8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2ED5E2F8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2ED5E2F8
	static void SET_GAMEPLAY_ENTITY_HINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x66C32306, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x66C32306
	static BOOL IS_GAMEPLAY_HINT_ACTIVE() { return invoke<BOOL>(0xAD8DA205); } // 0xAD8DA205
	static void STOP_GAMEPLAY_HINT(Any p0) { invoke<Void>(0x1BC28B7B, p0); } // 0x1BC28B7B
	static void _0xCAFEE798(Any p0) { invoke<Void>(0xCAFEE798, p0); } // 0xCAFEE798
	static void SET_GAMEPLAY_HINT_FOV(Any p0) { invoke<Void>(0x96FD173B, p0); } // 0x96FD173B
	static void _0x72E8CD3A(Any p0) { invoke<Void>(0x72E8CD3A, p0); } // 0x72E8CD3A
	static void _0x79472AE3(Any p0) { invoke<Void>(0x79472AE3, p0); } // 0x79472AE3
	static void _0xFC7464A0(Any p0) { invoke<Void>(0xFC7464A0, p0); } // 0xFC7464A0
	static void _0x3554AA0E(Any p0) { invoke<Void>(0x3554AA0E, p0); } // 0x3554AA0E
	static void GET_IS_MULTIPLAYER_BRIEF(Any p0) { invoke<Void>(0x2F0CE859, p0); } // 0x2F0CE859
	static void SET_CINEMATIC_BUTTON_ACTIVE(Any p0) { invoke<Void>(0x3FBC5D00, p0); } // 0x3FBC5D00
	static BOOL IS_CINEMATIC_CAM_RENDERING() { return invoke<BOOL>(0x80471AD9); } // 0x80471AD9
	static void SHAKE_CINEMATIC_CAM(Any p0, Any p1) { invoke<Void>(0x61815F31, p0, p1); } // 0x61815F31
	static BOOL IS_CINEMATIC_CAM_SHAKING() { return invoke<BOOL>(0x8376D939); } // 0x8376D939
	static void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(Any p0) { invoke<Void>(0x67510C4B, p0); } // 0x67510C4B
	static void STOP_CINEMATIC_CAM_SHAKING(Any p0) { invoke<Void>(0x71C12904, p0); } // 0x71C12904
	static void _0x5AC6DAC9() { invoke<Void>(0x5AC6DAC9); } // 0x5AC6DAC9
	static void _0x837F8581() { invoke<Void>(0x837F8581); } // 0x837F8581
	static void _0x65DDE8AF() { invoke<Void>(0x65DDE8AF); } // 0x65DDE8AF
	static void _0xD75CDD75() { invoke<Void>(0xD75CDD75); } // 0xD75CDD75
	static Any _0x96A07066() { return invoke<Any>(0x96A07066); } // 0x96A07066
	static void CREATE_CINEMATIC_SHOT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xAC494E35, p0, p1, p2, p3); } // 0xAC494E35
	static BOOL IS_CINEMATIC_SHOT_ACTIVE(Any p0) { return invoke<BOOL>(0xA4049042, p0); } // 0xA4049042
	static void STOP_CINEMATIC_SHOT(Any p0) { invoke<Void>(0xD78358C5, p0); } // 0xD78358C5
	static void _0xFBB85E02(Any p0) { invoke<Void>(0xFBB85E02, p0); } // 0xFBB85E02
	static void _0x4938C82F() { invoke<Void>(0x4938C82F); } // 0x4938C82F
	static void SET_CINEMATIC_MODE_ACTIVE(Any p0) { invoke<Void>(0x2009E747, p0); } // 0x2009E747
	static Any _0x6739AD55() { return invoke<Any>(0x6739AD55); } // 0x6739AD55
	static void STOP_CUTSCENE_CAM_SHAKING(Any p0) { invoke<Void>(0xF07D603D, p0); } // 0xF07D603D
	static void _0x067BA6F5(Any p0) { invoke<Void>(0x067BA6F5, p0); } // 0x067BA6F5
	static Any _0xFD99BE2B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xFD99BE2B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFD99BE2B
	static void _0xE206C450() { invoke<Void>(0xE206C450); } // 0xE206C450
	static void _0xB06CCD38(Any p0) { invoke<Void>(0xB06CCD38, p0); } // 0xB06CCD38
}


namespace CONTROLS
{
	static BOOL IS_CONTROL_ENABLED(int Index, int Control) { return invoke<BOOL>(0x9174AF84, Index, Control); } // 0x9174AF84
	static BOOL IS_CONTROL_PRESSED(int Index, int Control) { return invoke<BOOL>(0x517A4384, Index, Control); } // 0x517A4384
	static BOOL IS_CONTROL_RELEASED(int Index, int Control) { return invoke<BOOL>(0x1F91A06E, Index, Control); } // 0x1F91A06E
	static BOOL IS_CONTROL_JUST_PRESSED(int Index, int Control) { return invoke<BOOL>(0x4487F579, Index, Control); } // 0x4487F579
	static BOOL IS_CONTROL_JUST_RELEASED(int Index, int Control) { return invoke<BOOL>(0x2314444B, Index, Control); } // 0x2314444B
	static Any GET_CONTROL_VALUE(Any p0, Any p1) { return invoke<Any>(0xC526F3C6, p0, p1); } // 0xC526F3C6
	static Any GET_CONTROL_NORMAL(Any p0, Any p1) { return invoke<Any>(0x5DE226A5, p0, p1); } // 0x5DE226A5
	static Any _0xC49343BB(Any p0, Any p1) { return invoke<Any>(0xC49343BB, p0, p1); } // 0xC49343BB
	static BOOL IS_DISABLED_CONTROL_PRESSED(int Index, int Control) { return invoke<BOOL>(0x32A93544, Index, Control); } // 0x32A93544
	static BOOL IS_DISABLED_CONTROL_JUST_PRESSED(int Index, int Control) { return invoke<BOOL>(0xEE6ABD32, Index, Control); } // 0xEE6ABD32
	static BOOL IS_DISABLED_CONTROL_JUST_RELEASED(int Index, Any Control) { return invoke<BOOL>(0xD6A679E1, Index, Control); } // 0xD6A679E1
	static Any GET_DISABLED_CONTROL_NORMAL(Any p0, Any p1) { return invoke<Any>(0x66FF4FAA, p0, p1); } // 0x66FF4FAA
	static Any _0xF2A65A4C(Any p0, Any p1) { return invoke<Any>(0xF2A65A4C, p0, p1); } // 0xF2A65A4C
	static Any _0x0E8EF929(Any p0) { return invoke<Any>(0x0E8EF929, p0); } // 0x0E8EF929
	static Any _0x3551727A(Any p0, Any p1, Any p2) { return invoke<Any>(0x3551727A, p0, p1, p2); } // 0x3551727A
	static Any _0x3EE71F6A(Any p0, Any p1, Any p2) { return invoke<Any>(0x3EE71F6A, p0, p1, p2); } // 0x3EE71F6A
	static void SET_PAD_SHAKE(Any p0, Any p1, Any p2) { invoke<Void>(0x5D38BD2F, p0, p1, p2); } // 0x5D38BD2F
	static void STOP_PAD_SHAKE(Any p0) { invoke<Void>(0x8F75657E, p0); } // 0x8F75657E
	static void _0x7D65EB6E(Any p0, Any p1) { invoke<Void>(0x7D65EB6E, p0, p1); } // 0x7D65EB6E
	static void SET_CONTROL_SHAKE(Any p0, Any p1, Any p2) { invoke<Void>(0xF63D817A, p0, p1, p2); } // 0xF63D817A
	static BOOL IS_LOOK_INVERTED() { return invoke<BOOL>(0x313434B2); } // 0x313434B2
	static Any GET_LOCAL_PLAYER_AIM_STATE() { return invoke<Any>(0x81802053); } // 0x81802053
	static void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(Any p0) { invoke<Void>(0xA86BD91F, p0); } // 0xA86BD91F
	static void SET_INPUT_EXCLUSIVE(int Index, int Control) { invoke<Void>(0x4E8E29E6, Index, Control); } // 0x4E8E29E6
	static void DISABLE_CONTROL_ACTION(int Index, int Control) { invoke<Void>(0x3800C0DC, Index, Control); } // 0x3800C0DC
	static void ENABLE_CONTROL_ACTION(int Index, int Control) { invoke<Void>(0xD2753551, Index, Control); } // 0xD2753551
	static void DISABLE_ALL_CONTROL_ACTIONS(int Index) { invoke<Void>(0x16753CF4, Index); } // 0x16753CF4
	static void ENABLE_ALL_CONTROL_ACTIONS(int Index) { invoke<Void>(0xFC2F119F, Index); } // 0xFC2F119F
	static Any _0xD2C80B2E(char* p0) { return invoke<Any>(0xD2C80B2E, p0); } // 0xD2C80B2E
	static Any _0xBBFC9050(Any p0) { return invoke<Any>(0xBBFC9050, p0); } // 0xBBFC9050
	static void _0x42140FF9() { invoke<Void>(0x42140FF9); } // 0x42140FF9
	static void _0x2CEDE6C5(Any p0) { invoke<Void>(0x2CEDE6C5, p0); } // 0x2CEDE6C5
}


namespace STREAMING
{
	static void LOAD_ALL_OBJECTS_NOW() { invoke<Void>(0xC9DBDA90); } // 0xC9DBDA90
	static void LOAD_SCENE(float p0, float p1, float p2) { invoke<Void>(0xB72403F5, p0, p1, p2); } // 0xB72403F5
	static Any NETWORK_UPDATE_LOAD_SCENE() { return invoke<Any>(0xC76E023C); } // 0xC76E023C
	static void NETWORK_STOP_LOAD_SCENE() { invoke<Void>(0x24857907); } // 0x24857907
	static BOOL IS_NETWORK_LOADING_SCENE() { return invoke<BOOL>(0x6DCFC021); } // 0x6DCFC021
	static void SET_INTERIOR_ACTIVE(Any p0, Any p1) { invoke<Void>(0xE1013910, p0, p1); } // 0xE1013910
	static void REQUEST_MODEL(Hash model) { invoke<Void>(0xFFF1B500, model); } // 0xFFF1B500
	static void _0x48CEB6B4(Any p0) { invoke<Void>(0x48CEB6B4, p0); } // 0x48CEB6B4
	static BOOL HAS_MODEL_LOADED(Hash model) { return invoke<BOOL>(0x62BFDB37, model); } // 0x62BFDB37
	static void _0x939243FB(Any p0, Any p1) { invoke<Void>(0x939243FB, p0, p1); } // 0x939243FB
	static void SET_MODEL_AS_NO_LONGER_NEEDED(Hash Model) { invoke<Void>(0xAE0F069E, Model); } // 0xAE0F069E
	static BOOL IS_MODEL_IN_CDIMAGE(Any p0) { return invoke<BOOL>(0x1094782F, p0); } // 0x1094782F
	static BOOL IS_MODEL_VALID(Any p0) { return invoke<BOOL>(0xAF8F8E9D, p0); } // 0xAF8F8E9D
	static BOOL IS_MODEL_A_VEHICLE(Any p0) { return invoke<BOOL>(0xFFFC85D4, p0); } // 0xFFFC85D4
	static void REQUEST_COLLISION_AT_COORD(float x, float y, float z) { invoke<Void>(0xCD9805E7, x, y, z); } // 0xCD9805E7
	static void REQUEST_COLLISION_FOR_MODEL(Hash vehicleHash) { invoke<Void>(0x3930C042, vehicleHash); } // 0x3930C042
	static BOOL HAS_COLLISION_FOR_MODEL_LOADED(Any p0) { return invoke<BOOL>(0x41A094F8, p0); } // 0x41A094F8
	static void REQUEST_ADDITIONAL_COLLISION_AT_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0xC2CC1DF2, p0, p1, p2); } // 0xC2CC1DF2
	static Any _0xCD31C872(Any p0) { return invoke<Any>(0xCD31C872, p0); } // 0xCD31C872
	static void REQUEST_ANIM_DICT(char* AminSet) { invoke<Void>(0xDCA96950, AminSet); } // 0xDCA96950
	static BOOL HAS_ANIM_DICT_LOADED(char* AminSet) { return invoke<BOOL>(0x05E6763C, AminSet); } // 0x05E6763C
	static void REMOVE_ANIM_DICT(Any p0) { invoke<Void>(0x0AE050B5, p0); } // 0x0AE050B5
	static void REQUEST_ANIM_SET(Any p0) { invoke<Void>(0x2988B3FC, p0); } // 0x2988B3FC
	static BOOL HAS_ANIM_SET_LOADED(Any p0) { return invoke<BOOL>(0x4FFF397D, p0); } // 0x4FFF397D
	static void REMOVE_ANIM_SET(Any p0) { invoke<Void>(0xD04A817A, p0); } // 0xD04A817A
	static void REQUEST_CLIP_SET(char* p0) { invoke<Void>(0x546C627A, p0); } // 0x546C627A
	static BOOL HAS_CLIP_SET_LOADED(char* p0) { return invoke<BOOL>(0x230D5455, p0); } // 0x230D5455
	static void REMOVE_CLIP_SET(char* p0) { invoke<Void>(0x1E21F7AA, p0); } // 0x1E21F7AA
	static void REQUEST_IPL(char* iplName) { invoke<Void>(0x3B70D1DB, iplName); } // 0x3B70D1DB
	static void REMOVE_IPL(char* iplName) { invoke<Void>(0xDF7CBD36, iplName); } // 0xDF7CBD36
	static BOOL IS_IPL_ACTIVE(char* iplName) { return invoke<BOOL>(0xB2C33714, iplName); } // 0xB2C33714
	static void SET_STREAMING(Any p0) { invoke<Void>(0x27EF6CB2, p0); } // 0x27EF6CB2
	static void SET_GAME_PAUSES_FOR_STREAMING(Any p0) { invoke<Void>(0x9211A28A, p0); } // 0x9211A28A
	static void SET_REDUCE_PED_MODEL_BUDGET(Any p0) { invoke<Void>(0xAFCB2B86, p0); } // 0xAFCB2B86
	static void SET_REDUCE_VEHICLE_MODEL_BUDGET(Any p0) { invoke<Void>(0xCDB4FB7E, p0); } // 0xCDB4FB7E
	static void SET_DITCH_POLICE_MODELS(Any p0) { invoke<Void>(0x3EA7FCE4, p0); } // 0x3EA7FCE4
	static Any GET_NUMBER_OF_STREAMING_REQUESTS() { return invoke<Any>(0xC2EE9A02); } // 0xC2EE9A02
	static void REQUEST_PTFX_ASSET() { invoke<Void>(0x2C649263); } // 0x2C649263
	static BOOL HAS_PTFX_ASSET_LOADED() { return invoke<BOOL>(0x3EFF96BE); } // 0x3EFF96BE
	static void REMOVE_PTFX_ASSET() { invoke<Void>(0xC10F178C); } // 0xC10F178C
	static void _REQUEST_DLC_PTFX_ASSET(char* FX) { invoke<Void>(0xCFEA19A9, FX); } // 0xCFEA19A9
	static Any _HAS_DLC_PTFX_LOADED(char* FX) { return invoke<Any>(0x9ACC6446, FX); } // 0x9ACC6446
	static void _REMOVE_DLC_PTFX_ASSET(char* FX) { invoke<Void>(0xC44762A1, FX); } // 0xC44762A1
	static void SET_VEHICLE_POPULATION_BUDGET(Any p0) { invoke<Void>(0x1D56993C, p0); } // 0x1D56993C
	static void SET_PED_POPULATION_BUDGET(Any p0) { invoke<Void>(0xD2D026CD, p0); } // 0xD2D026CD
	static void CLEAR_FOCUS() { invoke<Void>(0x34D91E7A); } // 0x34D91E7A
	static void _0x14680A60(float p0, float p1, float p2, float p3, float p4, float p5) { invoke<Void>(0x14680A60, p0, p1, p2, p3, p4, p5); } // 0x14680A60
	static void SET_FOCUS_ENTITY(Any p0) { invoke<Void>(0x18DB04AC, p0); } // 0x18DB04AC
	static BOOL IS_ENTITY_FOCUS(Any p0) { return invoke<BOOL>(0xB456D707, p0); } // 0xB456D707
	static void _0x403CD434(Any p0, Any p1) { invoke<Void>(0x403CD434, p0, p1); } // 0x403CD434
	static void _0xA07BAEB9(Any p0) { invoke<Void>(0xA07BAEB9, p0); } // 0xA07BAEB9
	static Any _0x10B6AB36(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x10B6AB36, p0, p1, p2, p3, p4, p5); } // 0x10B6AB36
	static Any _0x72344191(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x72344191, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x72344191
	static Any _0xC0157255(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xC0157255, p0, p1, p2, p3, p4, p5, p6); } // 0xC0157255
	static void _0xE80F8ABE(Any p0) { invoke<Void>(0xE80F8ABE, p0); } // 0xE80F8ABE
	static Any _0x1B3521F4(Any p0) { return invoke<Any>(0x1B3521F4, p0); } // 0x1B3521F4
	static Any _0x42CFE9C0(Any p0) { return invoke<Any>(0x42CFE9C0, p0); } // 0x42CFE9C0
	static Any _0x56253356() { return invoke<Any>(0x56253356); } // 0x56253356
	static Any NEW_LOAD_SCENE_START(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0xDF9C38B6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xDF9C38B6
	static void NEW_LOAD_SCENE_STOP() { invoke<Void>(0x7C05B1F6); } // 0x7C05B1F6
	static BOOL IS_NEW_LOAD_SCENE_ACTIVE() { return invoke<BOOL>(0xAD234B7F); } // 0xAD234B7F
	static BOOL IS_NEW_LOAD_SCENE_LOADED() { return invoke<BOOL>(0x3ECD839F); } // 0x3ECD839F
	static void START_PLAYER_SWITCH(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0829E975, p0, p1, p2, p3); } // 0x0829E975
	static void STOP_PLAYER_SWITCH() { invoke<Void>(0x2832C010); } // 0x2832C010
	static Any STOP_PLAYER_REMAIN_ARCADE() { return invoke<Any>(0x56135ACC); } // 0x56135ACC
	static Any GET_PLAYER_SWITCH_TYPE() { return invoke<Any>(0x280DC015); } // 0x280DC015
	static Any GET_IDEAL_PLAYER_SWITCH_TYPE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xD5A450F1, p0, p1, p2, p3, p4, p5); } // 0xD5A450F1
	static Any GET_PLAYER_SWITCH_STATE() { return invoke<Any>(0x39A0E1F2); } // 0x39A0E1F2
	static Any GET_PLAYER_SHORT_SWITCH_STATE() { return invoke<Any>(0x9B7BA38F); } // 0x9B7BA38F
	static Any SET_PLAYER_INVERTED_UP() { return invoke<Any>(0x569847E3); } // 0x569847E3
	static Any DESTROY_PLAYER_IN_PAUSE_MENU() { return invoke<Any>(0x90F64284); } // 0x90F64284
	static void PREFETCH_SRL(Any p0) { invoke<Void>(0x37BE2FBB, p0); } // 0x37BE2FBB
	static BOOL IS_SRL_LOADED() { return invoke<BOOL>(0x670FA2A6); } // 0x670FA2A6
	static void BEGIN_SRL() { invoke<Void>(0x24F49427); } // 0x24F49427
	static void END_SRL() { invoke<Void>(0x1977C56A); } // 0x1977C56A
	static void SET_SRL_TIME(Any p0) { invoke<Void>(0x30F8A487, p0); } // 0x30F8A487
	static void SET_HD_AREA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x80BAA035, p0, p1, p2, p3); } // 0x80BAA035
	static void CLEAR_HD_AREA() { invoke<Void>(0x7CAC6FA0); } // 0x7CAC6FA0
}


namespace GRAPHICS
{

	static void REQUEST_STREAMED_TEXTURE_DICT(const char* Type, BOOL Toggle) { invoke<Void>(0x4C9B035F, Type, Toggle); } // 0x4C9B035F
	static BOOL HAS_STREAMED_TEXTURE_DICT_LOADED(const char* Type) { return invoke<BOOL>(0x3F436EEF, Type); } // 0x3F436EEF
	static void DRAW_SPRITE(const char* Type, const char* IconType, float X, float Y, float Z, float width, float height, int RED, int GREEN, int BLUE, int Alpha) { invoke<Void>(0x1FEC16B0/*drawAddresses.texture*/, Type, IconType, X , Y, Z, width, height, RED, GREEN, BLUE, Alpha); } // 0x1FEC16B0

}

namespace SCRIPT
{
	static const char* GET_THIS_SCRIPT_NAME() { return invoke<const char*>(0xA40FD5D9); } // 0xA40FD5D9
	static void TRIGGER_SCRIPT_EVENT(int always1, ScriptArg *argsStruct, int argsStructCount, int playerbitset) { invoke<Void>(0x54763B35, always1, argsStruct, argsStructCount, playerbitset); } // 0x54763B35

}

namespace WEAPON
{
	static void ENABLE_LASER_SIGHT_RENDERING(Any p0) { invoke<Void>(0xE3438955, p0); } // 0xE3438955
	static Any _0x324FA47A(Any p0) { return invoke<Any>(0x324FA47A, p0); } // 0x324FA47A
	static Any GET_WEAPONTYPE_MODEL(Any p0) { return invoke<Any>(0x44E1C269, p0); } // 0x44E1C269
	static Any GET_WEAPONTYPE_SLOT(Any p0) { return invoke<Any>(0x2E3759AF, p0); } // 0x2E3759AF
	static Any GET_WEAPONTYPE_GROUP(Any p0) { return invoke<Any>(0x5F2DE833, p0); } // 0x5F2DE833
	static void SET_CURRENT_PED_WEAPON(Ped PedHandle, Hash WeaponHash, BOOL EquipNow) { invoke<Void>(0xB8278882, PedHandle, WeaponHash, EquipNow); } // 0xB8278882
	static Any GET_CURRENT_PED_WEAPON(Ped ped, Hash* weapHash, BOOL p2) { return invoke<Any>(0xB0237302, ped, weapHash, p2); } // 0xB0237302
	static Any _0x5D73CD20(Any p0) { return invoke<Any>(0x5D73CD20, p0); } // 0x5D73CD20
	static Any GET_BEST_PED_WEAPON(Any p0, Any p1) { return invoke<Any>(0xB998D444, p0, p1); } // 0xB998D444
	static Any SET_CURRENT_PED_VEHICLE_WEAPON(Any p0, Any p1) { return invoke<Any>(0x8E6F2AF1, p0, p1); } // 0x8E6F2AF1
	static Any GET_CURRENT_PED_VEHICLE_WEAPON(Any p0, Any p1) { return invoke<Any>(0xF26C5D65, p0, p1); } // 0xF26C5D65
	static BOOL IS_PED_ARMED(Any p0, Any p1) { return invoke<BOOL>(0x0BFC892C, p0, p1); } // 0x0BFC892C
	static BOOL IS_WEAPON_VALID(Hash WeapHash) { return invoke<BOOL>(0x38CA2954, WeapHash); } // 0x38CA2954
	static BOOL HAS_PED_GOT_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x43D2FA82, p0, p1, p2); } // 0x43D2FA82
	static Any _0x02A32CB0(Any p0) { return invoke<Any>(0x02A32CB0, p0); } // 0x02A32CB0
	static Any GET_PED_WEAPONTYPE_IN_SLOT(Any p0, Any p1) { return invoke<Any>(0x9BC64E16, p0, p1); } // 0x9BC64E16
	static int GET_AMMO_IN_PED_WEAPON(Ped p0, Hash p1) { return invoke<Any>(0x0C755733, p0, p1); } // 0x0C755733
	static void ADD_AMMO_TO_PED(Ped handle, Hash weaponHash, int ammo) { invoke<Void>(0x7F0580C7, handle, weaponHash, ammo); } // 0x7F0580C7
	static void SET_PED_AMMO(Ped PedHandle, Hash WeaponHash, int ammo) { invoke<Void>(0xBF90DF1A, PedHandle, WeaponHash, ammo); } // 0xBF90DF1A
	static void SET_PED_INFINITE_AMMO(Ped Handle, BOOL Toggle, Hash WeaponHash) { invoke<Void>(0x9CB8D278, Handle, Toggle, WeaponHash); } // 0x9CB8D278
	static void SET_PED_INFINITE_AMMO_CLIP(Ped PedHandle, BOOL Toggle) { invoke<Void>(0x5A5E3B67, PedHandle, Toggle); } // 0x5A5E3B67
	static void GIVE_WEAPON_TO_PED(int pedHandle, Hash weaponAssetHash, int ammoCount, BOOL equipNow, BOOL isAmmoLoaded) { invoke<Void>(0xC4D88A85, pedHandle, weaponAssetHash, ammoCount, equipNow, isAmmoLoaded); } // 0xC4D88A85
	static void GIVE_DELAYED_WEAPON_TO_PED(Ped pedHandle, Hash weaponHash, int ammoCount, BOOL equipNow) { invoke<Void>(0x5868D20D, pedHandle, weaponHash, ammoCount, equipNow); } // 0x5868D20D
	static void REMOVE_ALL_PED_WEAPONS(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xA44CE817, PedHandle, Toggle); } // 0xA44CE817
	static void REMOVE_WEAPON_FROM_PED(Ped Handle, Hash WeaponHash) { invoke<Void>(0x9C37F220, Handle, WeaponHash); } // 0x9C37F220
	static void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Player PedHandle, BOOL Toggle) { invoke<Void>(0x00CFD6E9, PedHandle, Toggle); } // 0x00CFD6E9
	static void SET_PED_CURRENT_WEAPON_VISIBLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x00BECD77, p0, p1, p2, p3); } // 0x00BECD77
	static void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Any p0, Any p1) { invoke<Void>(0x8A444056, p0, p1); } // 0x8A444056
	static BOOL HAS_PED_BEEN_DAMAGED_BY_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xCDFBBCC6, p0, p1, p2); } // 0xCDFBBCC6
	static void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped PedHandle) { invoke<Void>(0x52C68832, PedHandle); } // 0x52C68832
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x6DAABB39, p0, p1, p2); } // 0x6DAABB39
	static void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Any p0) { invoke<Void>(0xCEC2732B, p0); } // 0xCEC2732B
	static void SET_PED_DROPS_WEAPON(Any p0) { invoke<Void>(0x3D3329FA, p0); } // 0x3D3329FA
	static void SET_PED_DROPS_INVENTORY_WEAPON(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x81FFB874, p0, p1, p2, p3, p4, p5); } // 0x81FFB874
	static Any GET_MAX_AMMO_IN_CLIP(Ped ped, Hash WeapHash, BOOL p2) { return invoke<Any>(0x6961E2A4, ped, WeapHash, p2); } // 0x6961E2A4
	static Any GET_AMMO_IN_CLIP(Ped Handle, Hash WeaponHash, BOOL p2) { return invoke<Any>(0x73C100C3, Handle, WeaponHash, p2); } // 0x73C100C3
	static Any SET_AMMO_IN_CLIP(Ped Handle, Hash WeaponHash, int ammo) { return invoke<Any>(0xA54B0B10, Handle, WeaponHash, ammo); } // 0xA54B0B10
	static Any GET_MAX_AMMO(Ped ped, Hash WeapHash, int* ammo) { return invoke<Any>(0x0B294796, ped, WeapHash, ammo); } // 0x0B294796
	static void SET_PED_AMMO_BY_TYPE(Any p0, Any p1, Any p2) { invoke<Void>(0x311C52BB, p0, p1, p2); } // 0x311C52BB
	static Any GET_PED_AMMO_BY_TYPE(Any p0, Any p1) { return invoke<Any>(0x54077C4D, p0, p1); } // 0x54077C4D
	static void SET_PED_AMMO_TO_DROP(Any p0, Any p1) { invoke<Void>(0x2386A307, p0, p1); } // 0x2386A307
	static void _0xD6460EA2(Any p0) { invoke<Void>(0xD6460EA2, p0); } // 0xD6460EA2
	static Any _0x09337863(Any p0, Any p1) { return invoke<Any>(0x09337863, p0, p1); } // 0x09337863
	static Any GET_PED_LAST_WEAPON_IMPACT_COORD(Ped Handle, float* Coords) { return invoke<Any>(0x9B266079, Handle, Coords); } // 0x9B266079
	static void SET_PED_GADGET(Any p0, Any p1, Any p2) { invoke<Void>(0x8A256D0A, p0, p1, p2); } // 0x8A256D0A
	static Any _0x8DDD0B5B(Any p0, Any p1) { return invoke<Any>(0x8DDD0B5B, p0, p1); } // 0x8DDD0B5B
	static Hash GET_SELECTED_PED_WEAPON(Ped p0) { return invoke<Hash>(0xD240123E, p0); } // 0xD240123E
	static void EXPLODE_PROJECTILES(Any p0, Any p1, Any p2) { invoke<Void>(0x35A0B955, p0, p1, p2); } // 0x35A0B955
	static void REMOVE_ALL_PROJECTILES_OF_TYPE(Any p0, Any p1) { invoke<Void>(0xA5F89919, p0, p1); } // 0xA5F89919
	static Any _0x3612110D(Any p0) { return invoke<Any>(0x3612110D, p0); } // 0x3612110D
	static Any _0xB2B2BBAA(Any p0) { return invoke<Any>(0xB2B2BBAA, p0); } // 0xB2B2BBAA
	static BOOL HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xA57E2E80, p0, p1, p2, p3); } // 0xA57E2E80
	static void GIVE_WEAPON_COMPONENT_TO_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x3E1E286D, p0, p1, p2); } // 0x3E1E286D
	static void REMOVE_WEAPON_COMPONENT_FROM_PED(Any p0, Any p1, Any p2) { invoke<Void>(0x412AA00D, p0, p1, p2); } // 0x412AA00D
	static BOOL HAS_PED_GOT_WEAPON_COMPONENT(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xDC0FC145, p0, p1, p2); } // 0xDC0FC145
	static BOOL IS_PED_WEAPON_COMPONENT_ACTIVE(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x7565FB19, p0, p1, p2); } // 0x7565FB19
	static Any _0x82EEAF0F(Any p0) { return invoke<Any>(0x82EEAF0F, p0); } // 0x82EEAF0F
	static Any MAKE_PED_RELOAD(Any p0) { return invoke<Any>(0x515292C2, p0); } // 0x515292C2
	static void REQUEST_WEAPON_ASSET(Any p0, Any p1, Any p2) { invoke<Void>(0x65D139A5, p0, p1, p2); } // 0x65D139A5
	static BOOL HAS_WEAPON_ASSET_LOADED(Any p0) { return invoke<BOOL>(0x1891D5BB, p0); } // 0x1891D5BB
	static void REMOVE_WEAPON_ASSET(Any p0) { invoke<Void>(0x2C0DFE3C, p0); } // 0x2C0DFE3C
	static Any CREATE_WEAPON_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x62F5987F, p0, p1, p2, p3, p4, p5, p6); } // 0x62F5987F
	static void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Any p0, Any p1) { invoke<Void>(0xF7612A37, p0, p1); } // 0xF7612A37
	static void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Any p0, Any p1) { invoke<Void>(0xA6E7ED3C, p0, p1); } // 0xA6E7ED3C
	static BOOL HAS_WEAPON_GOT_WEAPON_COMPONENT(Any p0, Any p1) { return invoke<BOOL>(0x1D368510, p0, p1); } // 0x1D368510
	static void GIVE_WEAPON_OBJECT_TO_PED(Any p0, Any p1) { invoke<Void>(0x639AF3EF, p0, p1); } // 0x639AF3EF
	static Any _0xB1817BAA(Any p0, Any p1) { return invoke<Any>(0xB1817BAA, p0, p1); } // 0xB1817BAA
	static Any GET_WEAPON_OBJECT_FROM_PED(Any p0) { return invoke<Any>(0xDF939A38, p0); } // 0xDF939A38
	static void SET_PED_WEAPON_TINT_INDEX(Ped PedHandle, Hash WeaponHash, int ColorIndex) { invoke<Void>(0xEB2A7B23, PedHandle, WeaponHash, ColorIndex); } // 0xEB2A7B23
	static Any GET_PED_WEAPON_TINT_INDEX(Any p0, Any p1) { return invoke<Any>(0x3F9C90A7, p0, p1); } // 0x3F9C90A7
	static void SET_WEAPON_OBJECT_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x44ACC1DA, p0, p1); } // 0x44ACC1DA
	static Any GET_WEAPON_OBJECT_TINT_INDEX(Any p0) { return invoke<Any>(0xD91D9576, p0); } // 0xD91D9576
	static Any GET_WEAPON_TINT_COUNT(Any p0) { return invoke<Any>(0x99E4EAAB, p0); } // 0x99E4EAAB
	static Any GET_WEAPON_HUD_STATS(Any p0, Any p1) { return invoke<Any>(0xA9AD3D98, p0, p1); } // 0xA9AD3D98
	static Any GET_WEAPON_COMPONENT_HUD_STATS(Any p0, Any p1) { return invoke<Any>(0xBB5498F4, p0, p1); } // 0xBB5498F4
	static Any GET_WEAPON_CLIP_SIZE(Any p0) { return invoke<Any>(0x8D515E66, p0); } // 0x8D515E66
	static void _0xB4F44C6E(Any p0, Any p1, Any p2) { invoke<Void>(0xB4F44C6E, p0, p1, p2); } // 0xB4F44C6E
	static Any _0xEC2E5304(Any p0, Any p1) { return invoke<Any>(0xEC2E5304, p0, p1); } // 0xEC2E5304
	static void _0xE3BD00F9(Any p0) { invoke<Void>(0xE3BD00F9, p0); } // 0xE3BD00F9
	static Any _0xBAF7BFBE(Any p0) { return invoke<Any>(0xBAF7BFBE, p0); } // 0xBAF7BFBE
	static Any SET_WEAPON_SMOKEGRENADE_ASSIGNED(Any p0) { return invoke<Any>(0x76876154, p0); } // 0x76876154
	static Any _0xB0127EA7(Any p0) { return invoke<Any>(0xB0127EA7, p0); } // 0xB0127EA7
	static void SET_WEAPON_ANIMATION_OVERRIDE(Any p0, Any p1) { invoke<Void>(0xA5DF7484, p0, p1); } // 0xA5DF7484
	static Any GET_WEAPON_DAMAGE_TYPE(Any p0) { return invoke<Any>(0x013AFC13, p0); } // 0x013AFC13
	static void _0x64646F1D(Any p0) { invoke<Void>(0x64646F1D, p0); } // 0x64646F1D
	static Any _0x135E7AD4(Any p0) { return invoke<Any>(0x135E7AD4, p0); } // 0x135E7AD4
}


namespace PLAYER
{
	static void SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier) { invoke<Void>(0x362E69AD, player, modifier); } // 0x362E69AD
	static void _SET_MOVE_SPEED_MULTIPLIER(Player player, float multiplier) { invoke<Void>(0x825423C2, player, multiplier); } //  0x825423C2
	static Ped GET_PLAYER_PED(Player player) { return invoke<Ped>(0x6E31E993, player); } // 0x6E31E993
	static Ped GET_PLAYER_PED_SCRIPT_INDEX(Player player) { return invoke<Ped>(0x6AC64990, player); } // 0x6AC64990
	static void SET_PLAYER_MODEL(Player player, Hash modelHash) { invoke<Void>(0x774A4C54, player, modelHash); } // 0x774A4C54
	static void CHANGE_PLAYER_PED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xBE515485, p0, p1, p2, p3); } // 0xBE515485
	static void GET_PLAYER_RGB_COLOUR(Player player, int* Red, int* Green, int* Blue) { invoke<Void>(0x6EF43BBB, player, Red, Green, Blue); } // 0x6EF43BBB
	static int GET_NUMBER_OF_PLAYERS() { return invoke<int>(0x4C1B8867); } // 0x4C1B8867
	static int GET_PLAYER_TEAM(Player player) { return invoke<int>(0x9873E404, player); } // 0x9873E404
	static void SET_PLAYER_TEAM(Player player, int Team) { invoke<Void>(0x725ADCF2, player, Team); } // 0x725ADCF2
	static char* GET_PLAYER_NAME(Player player) { return invoke<char*>(0x406B4B20, player); } // 0x406B4B20
	static float GET_WANTED_LEVEL_RADIUS(Player player) { return invoke<float>(0x1CF7D7DA, player); } // 0x1CF7D7DA
	static vec3_t GET_PLAYER_WANTED_CENTRE_POSITION(Player player) { return invoke<vec3_t>(0x821F2D2C, player); } // 0x821F2D2C
	static void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, float x, float y, float z) { invoke<Void>(0xF261633A, player, x, y, z); } // 0xF261633A
	static int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel) { return invoke<int>(0xD9783F6B, wantedLevel); } // 0xD9783F6B
	static void SET_PLAYER_WANTED_LEVEL(Player player, Hash wantedLevel, BOOL p2) { invoke<Void>(0xB7A0914B, player, wantedLevel, p2); } // 0xB7A0914B
	static void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, BOOL wantedLevel, Any p2) { invoke<Void>(0xED6F44F5, player, wantedLevel, p2); } // 0xED6F44F5
	static void SET_PLAYER_WANTED_LEVEL_NOW(Player player, BOOL p1) { invoke<Void>(0xAF3AFD83, player, p1); } // 0xAF3AFD83
	static BOOL ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player) { return invoke<BOOL>(0xE13A71C7, player); } // 0xE13A71C7
	static BOOL ARE_PLAYER_STARS_GREYED_OUT(Player player) { return invoke<BOOL>(0x5E72AB72, player); } // 0x5E72AB72
	static void SET_DISPATCH_COPS_FOR_PLAYER(Player player, BOOL Enable) { invoke<Void>(0x48A18913, player, Enable); } // 0x48A18913
	static BOOL IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel) { return invoke<BOOL>(0x589A2661, player, wantedLevel); } // 0x589A2661
	static void CLEAR_PLAYER_WANTED_LEVEL(Player player) { invoke<Void>(0x54EA5BCC, player); } // 0x54EA5BCC
	static BOOL IS_PLAYER_DEAD(Player player) { return invoke<BOOL>(0x140CA5A8, player); } // 0x140CA5A8
	static BOOL IS_PLAYER_PRESSING_HORN(Player player) { return invoke<BOOL>(0xED1D1662, player); } // 0xED1D1662
	static void SET_PLAYER_CONTROL(Player playerId, BOOL Toggle, int possiblyFlags) { invoke<Void>(0xD17AFCD8, playerId, Toggle, possiblyFlags); } // 0xD17AFCD8
	static int GET_PLAYER_WANTED_LEVEL(Player player) { return invoke<int>(0xBDCDD163, player); } // 0xBDCDD163
	static void SET_MAX_WANTED_LEVEL(int maxWantedLevel) { invoke<Void>(0x665A06F5, maxWantedLevel); } // 0x665A06F5
	static void SET_POLICE_RADAR_BLIPS(BOOL Toggle) { invoke<Void>(0x8E114B10, Toggle); } // 0x8E114B10
	static void SET_POLICE_IGNORE_PLAYER(Player player, BOOL Toggle) { invoke<Void>(0xE6DE71B7, player, Toggle); } // 0xE6DE71B7
	static BOOL IS_PLAYER_PLAYING(Player player) { return invoke<BOOL>(0xE15D777F, player); } // 0xE15D777F
	static void SET_EVERYONE_IGNORE_PLAYER(Player player, BOOL Toggle) { invoke<Void>(0xC915285E, player, Toggle); } // 0xC915285E
	static void SET_ALL_RANDOM_PEDS_FLEE(Player player, int p1) { invoke<Void>(0x49EAE968, player, p1); } // 0x49EAE968
	static void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { invoke<Void>(0xBF974891, player); } // 0xBF974891
	static void _0x274631FE(Player Player, BOOL Toggle) { invoke<Void>(0x274631FE, Player, Toggle); } // 0x274631FE
	static void _0x02DF7AF4(Any p0) { invoke<Void>(0x02DF7AF4, p0); } // 0x02DF7AF4
	static void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(int playerIndex, BOOL p1) { invoke<Void>(0xA3D675ED, playerIndex, p1); } // 0xA3D675ED
	static void SET_WANTED_LEVEL_MULTIPLIER(float Multiplier) { invoke<Void>(0x1359292F, Multiplier); } // 0x1359292F
	static void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty) { invoke<Void>(0xB552626C, player, difficulty); } // 0xB552626C
	static void RESET_WANTED_LEVEL_DIFFICULTY(Player player) { invoke<Void>(0xA64C378D, player); } // 0xA64C378D
	static void START_FIRING_AMNESTY(Any p0) { invoke<Void>(0x5F8A22A6, p0); } // 0x5F8A22A6
	static void REPORT_CRIME(Player player, int p0, int p1) { invoke<Void>(0xD8EB3A44, player, p0, p1); } // 0xD8EB3A44
	static void _0x59B5C2A2(Any p0, Any p1) { invoke<Void>(0x59B5C2A2, p0, p1); } // 0x59B5C2A2
	static void _0x6B34A160(Any p0) { invoke<Void>(0x6B34A160, p0); } // 0x6B34A160
	static void _0xB9FB142F(Any p0) { invoke<Void>(0xB9FB142F, p0); } // 0xB9FB142F
	static void _0x85725848(Any p0) { invoke<Void>(0x85725848, p0); } // 0x85725848
	static void _0x3A7E5FB6(float* p0f) { invoke<Void>(0x3A7E5FB6, p0f); } // 0x3A7E5FB6
	static void _0xD15C4B1C(Any p0) { invoke<Void>(0xD15C4B1C, p0); } // 0xD15C4B1C
	static void _0xBF6993C7(Any p0) { invoke<Void>(0xBF6993C7, p0); } // 0xBF6993C7
	static void _0x47CAB814() { invoke<Void>(0x47CAB814); } // 0x47CAB814
	static BOOL CAN_PLAYER_START_MISSION(Any p0) { return invoke<BOOL>(0x39E3CB3F, p0); } // 0x39E3CB3F
	static BOOL IS_PLAYER_READY_FOR_CUTSCENE(Any p0) { return invoke<BOOL>(0xBB77E9CD, p0); } // 0xBB77E9CD
	static BOOL IS_PLAYER_TARGETTING_ENTITY(Player Player, Entity Entity) { return invoke<BOOL>(0xF3240B77, Player, Entity); } // 0xF3240B77
	static Any GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity) { return invoke<Any>(0xF6AAA2D7, player, entity); } // 0xF6AAA2D7
	static BOOL IS_PLAYER_FREE_AIMING(Player player) { return invoke<BOOL>(0x1DEC67B7, player); } // 0x1DEC67B7
	static BOOL IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity) { return invoke<BOOL>(0x7D80EEAA, player, entity); } // 0x7D80EEAA
	static BOOL _GET_AIMED_ENTITY(Player player, Entity* entity) { return invoke<BOOL>(0x8866D9D0, player, entity); } // 0x8866D9D0
	static void _0x74D42C03(Any p0, Any p1) { invoke<Void>(0x74D42C03, p0, p1); } // 0x74D42C03
	static void SET_PLAYER_CAN_DO_DRIVE_BY(Any p0, Any p1) { invoke<Void>(0xF4D99685, p0, p1); } // 0xF4D99685
	static void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Any p0, Any p1) { invoke<Void>(0x71B305BB, p0, p1); } // 0x71B305BB
	static void SET_PLAYER_CAN_USE_COVER(Any p0, Any p1) { invoke<Void>(0x13CAFAFA, p0, p1); } // 0x13CAFAFA
	static int GET_MAX_WANTED_LEVEL() { return invoke<int>(0x457F1E44); } // 0x457F1E44
	static BOOL IS_PLAYER_TARGETTING_ANYTHING(Player player) { return invoke<BOOL>(0x456DB50D, player); } // 0x456DB50D
	static void SET_PLAYER_SPRINT(Any p0, Any p1) { invoke<Void>(0x7DD7900C, p0, p1); } // 0x7DD7900C
	static void RESET_PLAYER_STAMINA(Any Player) { invoke<Void>(0xC0445A9C, Player); } // 0xC0445A9C
	static void RESTORE_PLAYER_STAMINA(Any p0, Any p1) { invoke<Void>(0x62A93608, p0, p1); } // 0x62A93608
	static Any _0x47017C90(Any p0) { return invoke<Any>(0x47017C90, p0); } // 0x47017C90
	static Any GET_PLAYER_SPRINT_TIME_REMAINING(Any p0) { return invoke<Any>(0x40E80543, p0); } // 0x40E80543
	static Any GET_PLAYER_UNDERWATER_TIME_REMAINING(Any p0) { return invoke<Any>(0x1317125A, p0); } // 0x1317125A
	static int GET_PLAYER_GROUP(Player Player) { return invoke<int>(0xA5EDCDE8, Player); } // 0xA5EDCDE8
	static Any GET_PLAYER_MAX_ARMOUR(Player Player) { return invoke<Any>(0x02A50657, Player); } // 0x02A50657
	static BOOL IS_PLAYER_CONTROL_ON(Player Player) { return invoke<BOOL>(0x618857F2, Player); } // 0x618857F2
	static BOOL IS_PLAYER_SCRIPT_CONTROL_ON(Any p0) { return invoke<BOOL>(0x61B00A84, p0); } // 0x61B00A84
	static BOOL IS_PLAYER_CLIMBING(Any p0) { return invoke<BOOL>(0x4A9E9AE0, p0); } // 0x4A9E9AE0
	static BOOL IS_PLAYER_BEING_ARRESTED(Any p0, Any p1) { return invoke<BOOL>(0x7F6A60D3, p0, p1); } // 0x7F6A60D3
	static void _0x453C7CAB(Any p0) { invoke<Void>(0x453C7CAB, p0); } // 0x453C7CAB
	static Any GET_PLAYERS_LAST_VEHICLE() { return invoke<Any>(0xE2757AC1); } // 0xE2757AC1
	static Any GET_PLAYER_INDEX() { return invoke<Any>(0x309BBDC1); } // 0x309BBDC1
	static Any INT_TO_PLAYERINDEX(Any p0) { return invoke<Any>(0x98DD98F1, p0); } // 0x98DD98F1
	static Any _0x98F3B274(Any p0) { return invoke<Any>(0x98F3B274, p0); } // 0x98F3B274
	static Any GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Any p0) { return invoke<Any>(0x6E9B8B9E, p0); } // 0x6E9B8B9E
	static Any GET_TIME_SINCE_PLAYER_HIT_PED(Any p0) { return invoke<Any>(0xB6209195, p0); } // 0xB6209195
	static Any GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Any p0) { return invoke<Any>(0x8836E732, p0); } // 0x8836E732
	static float GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(float time) { return invoke<float>(0x9F27D00E, time); } // 0x9F27D00E
	static BOOL IS_PLAYER_FREE_FOR_AMBIENT_TASK(Any p0) { return invoke<BOOL>(0x85C7E232, p0); } // 0x85C7E232
	static Any PLAYER_ID() { return invoke<Any>(0x8AEA886C); } // 0x8AEA886C
	static Any PLAYER_PED_ID() { return invoke<Any>(0xFA92E226); } // 0xFA92E226
	static Any _0x8DD5B838() { return invoke<Any>(0x8DD5B838); } // 0x8DD5B838
	static Any _0x4B37333C(Any p0) { return invoke<Any>(0x4B37333C, p0); } // 0x4B37333C
	static void FORCE_CLEANUP(Any p0) { invoke<Void>(0xFDAAEA2B, p0); } // 0xFDAAEA2B
	static void _0x04256C73(Any p0, Any p1) { invoke<Void>(0x04256C73, p0, p1); } // 0x04256C73
	static void _0x882D3EB3(Any p0, Any p1) { invoke<Void>(0x882D3EB3, p0, p1); } // 0x882D3EB3
	static Any _0x39AA9FC8() { return invoke<Any>(0x39AA9FC8); } // 0x39AA9FC8
	static void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Any p0, Any p1) { invoke<Void>(0xA454DD29, p0, p1); } // 0xA454DD29
	static void _0xAF7AFCC4(Any p0) { invoke<Void>(0xAF7AFCC4, p0); } // 0xAF7AFCC4
	static Any GIVE_ACHIEVEMENT_TO_PLAYER(int achievement) { return invoke<Any>(0x822BC992, achievement); } // 0x822BC992
	static BOOL HAS_ACHIEVEMENT_BEEN_PASSED(int achievement) { return invoke<BOOL>(0x136A5BE9, achievement); } // 0x136A5BE9
	static BOOL IS_PLAYER_ONLINE() { return invoke<BOOL>(0x9FAB6729); } // 0x9FAB6729
	static BOOL IS_PLAYER_LOGGING_IN_NP() { return invoke<BOOL>(0x8F72FAD0); } // 0x8F72FAD0
	static void DISPLAY_SYSTEM_SIGNIN_UI(Any p0) { invoke<Void>(0x4264CED2, p0); } // 0x4264CED2
	static BOOL IS_SYSTEM_UI_BEING_DISPLAYED() { return invoke<BOOL>(0xE495B6DA); } // 0xE495B6DA
	static void SET_PLAYER_INVINCIBLE(Player player, BOOL toggle) { invoke<Void>(0xDFB9A2A2, player, toggle); } // 0xDFB9A2A2
	static Any GET_PLAYER_INVINCIBLE(Any p0) { return invoke<Any>(0x680C90EE, p0); } // 0x680C90EE
	static void _0x00563E0D(Any p0, Any p1) { invoke<Void>(0x00563E0D, p0, p1); } // 0x00563E0D
	static void REMOVE_PLAYER_HELMET(Player player, BOOL p2) { invoke<Void>(0x6255F3B4, player, p2); } // 0x6255F3B4
	static void GIVE_PLAYER_RAGDOLL_CONTROL(Any p0, Any p1) { invoke<Void>(0xC7B4D7AC, p0, p1); } // 0xC7B4D7AC
	static void SET_PLAYER_LOCKON(Any p0, Any p1) { invoke<Void>(0x0B270E0F, p0, p1); } // 0x0B270E0F
	static void SET_PLAYER_TARGETING_MODE(Any Player) { invoke<Void>(0x61CAE253, Player); } // 0x61CAE253
	static void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Any p0) { invoke<Void>(0x1D31CBBD, p0); } // 0x1D31CBBD
	static BOOL HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Any p0) { return invoke<BOOL>(0x14F52453, p0); } // 0x14F52453
	static void _0x7E3BFBC5(Any p0) { invoke<Void>(0x7E3BFBC5, p0); } // 0x7E3BFBC5
	static Any _0xA3707DFC(Any p0) { return invoke<Any>(0xA3707DFC, p0); } // 0xA3707DFC
	static void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Any p0, Any p1) { invoke<Void>(0xF20F72E5, p0, p1); } // 0xF20F72E5
	static void _0xB986FF47(Any p0, Any p1) { invoke<Void>(0xB986FF47, p0, p1); } // 0xB986FF47
	static void _0x825423C2(Any p0, Any p1) { invoke<Void>(0x825423C2, p0, p1); } // 0x825423C2
	static Any GET_TIME_SINCE_LAST_ARREST() { return invoke<Any>(0x62824EF4); } // 0x62824EF4
	static Any GET_TIME_SINCE_LAST_DEATH() { return invoke<Any>(0x24BC5AC0); } // 0x24BC5AC0
	static void ASSISTED_MOVEMENT_CLOSE_ROUTE() { invoke<Void>(0xF23277F3); } // 0xF23277F3
	static void ASSISTED_MOVEMENT_FLUSH_ROUTE() { invoke<Void>(0xD04568B9); } // 0xD04568B9
	static void SET_PLAYER_FORCED_AIM(Player p0, BOOL p1) { invoke<Void>(0x94E42E2E, p0, p1); } // 0x94E42E2E
	static void SET_PLAYER_FORCED_ZOOM(Any p0, Any p1) { invoke<Void>(0xB0C576CB, p0, p1); } // 0xB0C576CB
	static void _0x374F42F0(Any p0, Any p1) { invoke<Void>(0x374F42F0, p0, p1); } // 0x374F42F0
	static void DISABLE_PLAYER_FIRING(Player Player, BOOL Toggle) { invoke<Void>(0x30CB28CB, Player, Toggle); } // 0x30CB28CB
	static void _0xCCD937E7(Any p0, Any p1) { invoke<Void>(0xCCD937E7, p0, p1); } // 0xCCD937E7
	static void SET_PLAYER_MAX_ARMOUR(Player Player, BOOL Toggle) { invoke<Void>(0xC6C3C53B, Player, Toggle); } // 0xC6C3C53B
	static void SPECIAL_ABILITY_DEACTIVATE(Any p0) { invoke<Void>(0x80C2AB09, p0); } // 0x80C2AB09
	static void _0x0751908A(Any p0) { invoke<Void>(0x0751908A, p0); } // 0x0751908A
	static void SPECIAL_ABILITY_RESET(Any p0) { invoke<Void>(0xA7D8BCD3, p0); } // 0xA7D8BCD3
	static void _0x4136829A(Any p0) { invoke<Void>(0x4136829A, p0); } // 0x4136829A
	static void _0x6F463F56(Any p0, Any p1, Any p2) { invoke<Void>(0x6F463F56, p0, p1, p2); } // 0x6F463F56
	static void _0xAB55D8F3(Any p0, Any p1, Any p2) { invoke<Void>(0xAB55D8F3, p0, p1, p2); } // 0xAB55D8F3
	static void _0xF440C04D(Any p0, Any p1, Any p2) { invoke<Void>(0xF440C04D, p0, p1, p2); } // 0xF440C04D
	static void _0x5FEE98A2(Any p0, Any p1) { invoke<Void>(0x5FEE98A2, p0, p1); } // 0x5FEE98A2
	static void _0x72429998(Any p0, Any p1, Any p2) { invoke<Void>(0x72429998, p0, p1, p2); } // 0x72429998
	static void RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC(Any p0, Any p1, Any p2) { invoke<Void>(0x8C7E68C1, p0, p1, p2); } // 0x8C7E68C1
	static void _0xB71589DA(Any p0, Any p1) { invoke<Void>(0xB71589DA, p0, p1); } // 0xB71589DA
	static void _0x9F80F6DF(Any p0, Any p1) { invoke<Void>(0x9F80F6DF, p0, p1); } // 0x9F80F6DF
	static void SPECIAL_ABILITY_LOCK(Any p0) { invoke<Void>(0x1B7BB388, p0); } // 0x1B7BB388
	static void SPECIAL_ABILITY_UNLOCK(Any p0) { invoke<Void>(0x1FDB2919, p0); } // 0x1FDB2919
	static BOOL IS_SPECIAL_ABILITY_UNLOCKED(Any p0) { return invoke<BOOL>(0xC9C75E82, p0); } // 0xC9C75E82
	static BOOL IS_SPECIAL_ABILITY_ACTIVE(Any p0) { return invoke<BOOL>(0x1B17E334, p0); } // 0x1B17E334
	static BOOL IS_SPECIAL_ABILITY_METER_FULL(Any p0) { return invoke<BOOL>(0x2E19D7F6, p0); } // 0x2E19D7F6
	static void ENABLE_SPECIAL_ABILITY(Any p0, Any p1) { invoke<Void>(0xC86C1B4E, p0, p1); } // 0xC86C1B4E
	static BOOL IS_SPECIAL_ABILITY_ENABLED(Any p0) { return invoke<BOOL>(0xC01238CC, p0); } // 0xC01238CC
	static void SET_SPECIAL_ABILITY_MULTIPLIER(Any p0) { invoke<Void>(0xFF1BC556, p0); } // 0xFF1BC556
	static void _0x5D0FE25B(Any p0) { invoke<Void>(0x5D0FE25B, p0); } // 0x5D0FE25B
	static Any _0x46E7E31D(Any p0) { return invoke<Any>(0x46E7E31D, p0); } // 0x46E7E31D
	static Any _0x1E359CC8(Any p0, Any p1) { return invoke<Any>(0x1E359CC8, p0, p1); } // 0x1E359CC8
	static Any _0x8CB53C9F(Any p0, Any p1) { return invoke<Any>(0x8CB53C9F, p0, p1); } // 0x8CB53C9F
	static void START_PLAYER_TELEPORT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xC552E06C, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xC552E06C
	static void STOP_PLAYER_TELEPORT() { invoke<Void>(0x86AB8DBB); } // 0x86AB8DBB
	static BOOL IS_PLAYER_TELEPORT_ACTIVE() { return invoke<BOOL>(0x3A11D118); } // 0x3A11D118
	static float GET_PLAYER_CURRENT_STEALTH_NOISE(Vehicle* p0) { return invoke<float>(0xC3B02362, p0); } // 0xC3B02362
	static void _0x45514731(Any p0, Any p1) { invoke<Void>(0x45514731, p0, p1); } // 0x45514731
	static void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float DamageAmount) { invoke<Void>(0xB02C2F39, player, DamageAmount); } // 0xB02C2F39
	static void _0xAE446344(Player player, float multiplier) { invoke<Void>(0xAE446344, player, multiplier); } // 0xAE446344
	static void _0x362E69AD(Any p0, Any p1) { invoke<Void>(0x362E69AD, p0, p1); } // 0x362E69AD
	static void _0x9F3D577F(Any p0, Any p1) { invoke<Void>(0x9F3D577F, p0, p1); } // 0x9F3D577F
	static void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player Player, float DamageAmount) { invoke<Void>(0x823ECA63, Player, DamageAmount); } // 0x823ECA63
	static void _0xA16626C7(Any p0, Any p1) { invoke<Void>(0xA16626C7, p0, p1); } // 0xA16626C7
	static void SET_PLAYER_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x8EA12EDB, p0, p1); } // 0x8EA12EDB
	static void GET_PLAYER_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x432B0509, p0, p1); } // 0x432B0509
	static void _0x70689638(Any p0, Any p1) { invoke<Void>(0x70689638, p0, p1); } // 0x70689638
	static void _0x77B8EF01(Any p0, Any p1) { invoke<Void>(0x77B8EF01, p0, p1); } // 0x77B8EF01
	static void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0xD79D5D1B, p0, p1); } // 0xD79D5D1B
	static void _0x4E418E13(Any p0, Any p1) { invoke<Void>(0x4E418E13, p0, p1); } // 0x4E418E13
	static void _0xA3E4798E(Any p0) { invoke<Void>(0xA3E4798E, p0); } // 0xA3E4798E
	static Any _0x30DA1DA1(Any p0) { return invoke<Any>(0x30DA1DA1, p0); } // 0x30DA1DA1
	static void _0x832DEB7A(Any p0, Any p1) { invoke<Void>(0x832DEB7A, p0, p1); } // 0x832DEB7A
	static void _0x14FE9264(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x14FE9264, p0, p1, p2, p3); } // 0x14FE9264
	static void _0xF66E5CDD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF66E5CDD, p0, p1, p2, p3); } // 0xF66E5CDD
	static void _0x725C6174(Any p0, Any p1) { invoke<Void>(0x725C6174, p0, p1); } // 0x725C6174
	static void _0xF8A62EFC(Any p0, Any p1) { invoke<Void>(0xF8A62EFC, p0, p1); } // 0xF8A62EFC
	static void SET_PLAYER_NOISE_MULTIPLIER(Player Player, float Multipliyer) { invoke<Void>(0x15786DD1, Player, Multipliyer); } // 0x15786DD1
	static void _0x8D2D89C4(Any p0, Any p1) { invoke<Void>(0x8D2D89C4, p0, p1); } // 0x8D2D89C4
	static Any _0x1C70B2EB(Any p0, Any p1) { return invoke<Any>(0x1C70B2EB, p0, p1); } // 0x1C70B2EB
	static void SIMULATE_PLAYER_INPUT_GAIT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x0D77CC34, p0, p1, p2, p3, p4, p5); } // 0x0D77CC34
	static void RESET_PLAYER_INPUT_GAIT(Any p0) { invoke<Void>(0x4A701EE1, p0); } // 0x4A701EE1
	static void _0xA97C2059(Any p0, Any p1) { invoke<Void>(0xA97C2059, p0, p1); } // 0xA97C2059
	static void _0xA25D767E(Any p0, Any p1) { invoke<Void>(0xA25D767E, p0, p1); } // 0xA25D767E
	static void _0x3D26105F(Any p0, Any p1) { invoke<Void>(0x3D26105F, p0, p1); } // 0x3D26105F
	static Any _0x1D371529(Any p0) { return invoke<Any>(0x1D371529, p0); } // 0x1D371529
	static void _0xE30A64DC(Any p0) { invoke<Void>(0xE30A64DC, p0); } // 0xE30A64DC
	static void SET_PLAYER_SIMULATE_AIMING(Any p0, Any p1) { invoke<Void>(0xF1E0CAFC, p0, p1); } // 0xF1E0CAFC
	static void _0xF7A0F00F(Any p0, Any p1) { invoke<Void>(0xF7A0F00F, p0, p1); } // 0xF7A0F00F
	static void _0xB8209F16(Any p0) { invoke<Void>(0xB8209F16, p0); } // 0xB8209F16
	static void _0x8D9FD4D1(Any p0) { invoke<Void>(0x8D9FD4D1, p0); } // 0x8D9FD4D1
	static void _0xECD12E60(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xECD12E60, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xECD12E60
	static void _0x96100EA4() { invoke<Void>(0x96100EA4); } // 0x96100EA4
	static Any _0x4A01B76A(Any p0) { return invoke<Any>(0x4A01B76A, p0); } // 0x4A01B76A
	static Any _0x013B4F72(Any p0) { return invoke<Any>(0x013B4F72, p0); } // 0x013B4F72
	static Any _0x9DF75B2A(Any p0, Any p1, Any p2) { return invoke<Any>(0x9DF75B2A, p0, p1, p2); } // 0x9DF75B2A
	static void _0x64DDB07D(Any p0, Any p1, Any p2) { invoke<Void>(0x64DDB07D, p0, p1, p2); } // 0x64DDB07D
	static void _0xA97C2F6C() { invoke<Void>(0xA97C2F6C); } // 0xA97C2F6C
	static BOOL IS_PLAYER_RIDING_TRAIN(Player Player) { return invoke<BOOL>(0x9765E71D, Player); } // 0x9765E71D
	static Any _0xFEA40B6C(Any p0) { return invoke<Any>(0xFEA40B6C, p0); } // 0xFEA40B6C
	static void _0xAD8383FA(Any p0, Any p1) { invoke<Void>(0xAD8383FA, p0, p1); } // 0xAD8383FA
	static void _0x9254249D(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x9254249D, p0, p1, p2, p3, p4); } // 0x9254249D
	static void _0xFD60F5AB(Any p0) { invoke<Void>(0xFD60F5AB, p0); } // 0xFD60F5AB
	static void _0x5D382498(Any p0, Any p1) { invoke<Void>(0x5D382498, p0, p1); } // 0x5D382498
	static void _0x6FF034BB(Any p0) { invoke<Void>(0x6FF034BB, p0); } // 0x6FF034BB
	static void _0xA877FF5E(Any p0, Any p1) { invoke<Void>(0xA877FF5E, p0, p1); } // 0xA877FF5E
	static void _0xBB62AAC5(Any p0) { invoke<Void>(0xBB62AAC5, p0); } // 0xBB62AAC5
	static void _0x8C6E611D(Any p0) { invoke<Void>(0x8C6E611D, p0); } // 0x8C6E611D
	static void _0x2849D4B2(Any p0) { invoke<Void>(0x2849D4B2, p0); } // 0x2849D4B2
}

namespace ENTITY
{
	static BOOL DOES_ENTITY_EXIST(Entity entity) { return invoke<BOOL>(0x3AC90869, entity); } // 0x3AC90869
	static Any _0xACFEB3F9(Any p0, Any p1) { return invoke<Any>(0xACFEB3F9, p0, p1); } // 0xACFEB3F9
	static BOOL DOES_ENTITY_HAVE_DRAWABLE(Entity Entity) { return invoke<BOOL>(0xA5B33300, Entity); } // 0xA5B33300
	static BOOL DOES_ENTITY_HAVE_PHYSICS(Entity Entity) { return invoke<BOOL>(0x9BCD2979, Entity); } // 0x9BCD2979
	static BOOL HAS_ENTITY_ANIM_FINISHED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x1D9CAB92, p0, p1, p2, p3); } // 0x1D9CAB92
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity Entity) { return invoke<BOOL>(0x6B74582E, Entity); } // 0x6B74582E
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity Entity) { return invoke<BOOL>(0x53FD4A25, Entity); } // 0x53FD4A25
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity Entity) { return invoke<BOOL>(0x878C2CE0, Entity); } // 0x878C2CE0
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x07FC77E0, p0, p1, p2); } // 0x07FC77E0
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x53576FA7, p0, p1, p2); } // 0x53576FA7
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Any p0, Any p1) { return invoke<BOOL>(0x210D87C8, p0, p1); } // 0x210D87C8
	static BOOL HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity Entity) { return invoke<BOOL>(0x662A2F41, Entity); } // 0x662A2F41
	static Any _0xC0E3AA47(Any p0) { return invoke<Any>(0xC0E3AA47, p0); } // 0xC0E3AA47
	static vec3_t _0xAB415C07(Any p0) { return invoke<vec3_t>(0xAB415C07, p0); } // 0xAB415C07
	static void _0x58D9775F(Any p0) { invoke<Void>(0x58D9775F, p0); } // 0x58D9775F
	static Any GET_ENTITY_ANIM_CURRENT_TIME(Any p0, Any p1, Any p2) { return invoke<Any>(0x83943F41, p0, p1, p2); } // 0x83943F41
	static Any GET_ENTITY_ANIM_TOTAL_TIME(Any p0, Any p1, Any p2) { return invoke<Any>(0x433A9D18, p0, p1, p2); } // 0x433A9D18
	static Entity GET_ENTITY_ATTACHED_TO(Entity Entity) { return invoke<Any>(0xFE1589F9, Entity); } // 0xFE1589F9
	static vec3_t GET_ENTITY_COORDS(Entity entity, BOOL isalive) { return invoke<vec3_t>(0x1647F1CB, entity, isalive); } // 0x1647F1CB
	static float GET_ENTITY_COORDS_FLOAT(Entity entity, BOOL isalive) { return invoke<float>(0x1647F1CB, entity, isalive); } // 0x1647F1CB
	static vec3_t GET_ENTITY_FORWARD_VECTOR(Entity entity) { return invoke<vec3_t>(0x84DCECBF, entity); } // 0x84DCECBF
	static Any GET_ENTITY_FORWARD_X(Entity Entity) { return invoke<Any>(0x49FAE914, Entity); } // 0x49FAE914
	static Any GET_ENTITY_FORWARD_Y(Entity Entity) { return invoke<Any>(0x9E2F917C, Entity); } // 0x9E2F917C
	static float GET_ENTITY_HEADING(Entity Entity) { return invoke<float>(0x972CC383, Entity); } // 0x972CC383
	static Any GET_ENTITY_HEALTH(Entity Entity) { return invoke<Any>(0x8E3222B7, Entity); } // 0x8E3222B7
	static Any GET_ENTITY_MAX_HEALTH(Entity Entity) { return invoke<Any>(0xC7AE6AA1, Entity); } // 0xC7AE6AA1
	static void SET_ENTITY_MAX_HEALTH(Entity Entity, BOOL Toggle) { invoke<Void>(0x96F84DF8, Entity, Toggle); } // 0x96F84DF8
	static Any GET_ENTITY_HEIGHT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xEE443481, p0, p1, p2, p3, p4, p5); } // 0xEE443481
	static Any GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity Entity) { return invoke<Any>(0x57F56A4D, Entity); } // 0x57F56A4D
	static void GET_ENTITY_MATRIX(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xEB9EB001, p0, p1, p2, p3, p4); } // 0xEB9EB001
	static Any GET_ENTITY_MODEL(Entity Entity) { return invoke<Any>(0xDAFCB3EC, Entity); } // 0xDAFCB3EC
	static vec3_t GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Any p0, Any p1, Any p2, Any p3) { return invoke<vec3_t>(0x6477EC9E, p0, p1, p2, p3); } // 0x6477EC9E
	static vec3_t GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS1(Entity Entity, float xCoord, float yCoord, float zCoord) { return invoke<vec3_t>(0xABCF043A, Entity, xCoord, yCoord, zCoord); } // 0xABCF043A
	static vec3_t GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity Entity, int xCoord, int yCoord, int zCoord) { return invoke<vec3_t>(0xABCF043A, Entity, xCoord, yCoord, zCoord); } // 0xABCF043A
	static Any GET_ENTITY_PITCH(Entity Entity) { return invoke<Any>(0xFCE6ECE5, Entity); } // 0xFCE6ECE5
	static void GET_ENTITY_QUATERNION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x5154EC90, p0, p1, p2, p3, p4); } // 0x5154EC90
	static Any GET_ENTITY_ROLL(Entity Entity) { return invoke<Any>(0x36610842, Entity); } // 0x36610842
	static vec3_t GET_ENTITY_ROTATION(Any p0, Any p1) { return invoke<vec3_t>(0x8FF45B04, p0, p1); } // 0x8FF45B04
	static vec3_t GET_ENTITY_ROTATION_VELOCITY(Any p0) { return invoke<vec3_t>(0x9BF8A73F, p0); } // 0x9BF8A73F
	static Any GET_ENTITY_SCRIPT(Any p0, Any p1) { return invoke<Any>(0xB7F70784, p0, p1); } // 0xB7F70784
	static float GET_ENTITY_SPEED(Entity entity) { return invoke<float>(0x9E1E4798, entity); } // 0x9E1E4798
	static vec3_t GET_ENTITY_SPEED_VECTOR(Any p0, Any p1) { return invoke<vec3_t>(0x3ED2B997, p0, p1); } // 0x3ED2B997
	static Any GET_ENTITY_UPRIGHT_VALUE(Any p0) { return invoke<Any>(0xF4268190, p0); } // 0xF4268190
	static vec3_t GET_ENTITY_VELOCITY(Entity entity) { return invoke<vec3_t>(0xC14C9B6B, entity); } // 0xC14C9B6B
	static Any _0xBC5A9C58(Any p0) { return invoke<Any>(0xBC5A9C58, p0); } // 0xBC5A9C58
	static Any _0xC46F74AC(Any p0) { return invoke<Any>(0xC46F74AC, p0); } // 0xC46F74AC
	static Any _0xC69CF43D(Any p0) { return invoke<Any>(0xC69CF43D, p0); } // 0xC69CF43D
	static vec3_t _0x7C6339DF(Any p0, Any p1) { return invoke<vec3_t>(0x7C6339DF, p0, p1); } // 0x7C6339DF
	static Any GET_NEAREST_PLAYER_TO_ENTITY(Entity Entity) { return invoke<Any>(0xCE17FDEC, Entity); } // 0xCE17FDEC
	static Any _0xB1808F56(Any p0, Any p1) { return invoke<Any>(0xB1808F56, p0, p1); } // 0xB1808F56
	static int GET_ENTITY_TYPE(Entity Entity) { return invoke<int>(0x0B1BD08D, Entity); } // 0x0B1BD08D
	static BOOL IS_AN_ENTITY(Entity Entity) { return invoke<BOOL>(0xD4B9715A, Entity); } // 0xD4B9715A
	static BOOL IS_ENTITY_A_PED(Entity Entity) { return invoke<BOOL>(0x55D33EAB, Entity); } // 0x55D33EAB
	static BOOL IS_ENTITY_A_MISSION_ENTITY(Entity Entity) { return invoke<BOOL>(0x2632E124, Entity); } // 0x2632E124
	static BOOL IS_ENTITY_A_VEHICLE(Entity Entity) { return invoke<BOOL>(0xBE800B01, Entity); } // 0xBE800B01
	static BOOL IS_ENTITY_AN_OBJECT(Any p0) { return invoke<BOOL>(0x3F52E561, p0); } // 0x3F52E561
	static BOOL IS_ENTITY_AT_COORD(Entity entity, float x, float y, float z, float xSize, float ySize, float zSize, int p7, int p8, int p9) { return invoke<BOOL>(0xD749B606, entity, x, y, z, xSize, ySize, zSize, p7, p8, p9); } // 0xD749B606
	static BOOL IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, int p5, int p6, int p7) { return invoke<BOOL>(0xDABDCB52, entity1, entity2, xSize, ySize, zSize, p5, p6, p7); } // 0xDABDCB52
	static BOOL IS_ENTITY_ATTACHED(Any p0) { return invoke<BOOL>(0xEC1479D5, p0); } // 0xEC1479D5
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Any p0) { return invoke<BOOL>(0x0B5DE340, p0); } // 0x0B5DE340
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_PED(Any p0) { return invoke<BOOL>(0x9D7A609C, p0); } // 0x9D7A609C
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Any p0) { return invoke<BOOL>(0xDE5C995E, p0); } // 0xDE5C995E
	static BOOL IS_ENTITY_ATTACHED_TO_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0xB0ABFEA8, p0, p1); } // 0xB0ABFEA8
	static BOOL IS_ENTITY_DEAD(Entity entity) { return invoke<BOOL>(0xB6F7CBAC, entity); } // 0xB6F7CBAC
	static BOOL IS_ENTITY_IN_AIR(Entity entity) { return invoke<BOOL>(0xA4157987, entity); } // 0xA4157987
	static BOOL IS_ENTITY_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<BOOL>(0x883622FA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x883622FA
	static BOOL IS_ENTITY_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<BOOL>(0x8C2DFA9D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8C2DFA9D
	static BOOL IS_ENTITY_IN_ZONE(Any p0, Any p1) { return invoke<BOOL>(0x45C82B21, p0, p1); } // 0x45C82B21
	static BOOL IS_ENTITY_IN_WATER(Entity entity) { return invoke<BOOL>(0x4C3C2508, entity); } // 0x4C3C2508
	static Any _0x0170F68C(Any p0) { return invoke<Any>(0x0170F68C, p0); } // 0x0170F68C
	static void _0x40C84A74(Any p0, Any p1) { invoke<Void>(0x40C84A74, p0, p1); } // 0x40C84A74
	static BOOL IS_ENTITY_ON_SCREEN(Any p0) { return invoke<BOOL>(0xC1FEC5ED, p0); } // 0xC1FEC5ED
	static BOOL IS_ENTITY_PLAYING_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x0D130D34, p0, p1, p2, p3); } // 0x0D130D34
	static BOOL IS_ENTITY_STATIC(Any p0) { return invoke<BOOL>(0x928E12E9, p0); } // 0x928E12E9
	static BOOL IS_ENTITY_TOUCHING_ENTITY(Entity p0, Entity p1) { return invoke<BOOL>(0x6B931477, p0, p1); } // 0x6B931477
	static Any _0x307E7611(Any p0, Any p1) { return invoke<Any>(0x307E7611, p0, p1); } // 0x307E7611
	static BOOL IS_ENTITY_UPRIGHT(Any p0, Any p1) { return invoke<BOOL>(0x3BCDF4E1, p0, p1); } // 0x3BCDF4E1
	static BOOL IS_ENTITY_UPSIDEDOWN(Any p0) { return invoke<BOOL>(0x5ACAA48F, p0); } // 0x5ACAA48F
	static BOOL IS_ENTITY_VISIBLE(Entity entity) { return invoke<BOOL>(0x120B4ED5, entity); } // 0x120B4ED5
	static BOOL IS_ENTITY_VISIBLE_TO_SCRIPT(Any p0) { return invoke<BOOL>(0x5D240E9D, p0); } // 0x5D240E9D
	static BOOL IS_ENTITY_OCCLUDED(Any p0) { return invoke<BOOL>(0x46BC5B40, p0); } // 0x46BC5B40
	static Any _0xEA127CBC(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xEA127CBC, p0, p1, p2, p3, p4); } // 0xEA127CBC
	static BOOL IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Any p0) { return invoke<BOOL>(0x00AB7A4A, p0); } // 0x00AB7A4A
	static void _0x28924E98(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x28924E98, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x28924E98
	static void APPLY_FORCE_TO_ENTITY(Entity entity, BOOL p1, float Force_X, float Force_Y, float Force_Z, float Rot_X, float Rot_Y, float Rot_Z, BOOL p8, BOOL p9, BOOL p10, BOOL p11, int p12, BOOL p13) { invoke<Void>(0xC1C0855A, entity, p1, Force_X, Force_Y, Force_Z, Rot_X, Rot_Y, Rot_Z, p8, p9, p10, p11, p12, p13); } // 0xC1C0855A
	static void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, BOOL p9, BOOL useSoftPinning, BOOL collision, BOOL isPed, int vertexIndex, BOOL fixedRot) { invoke<Void>(0xEC024237, entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, useSoftPinning, collision, isPed, vertexIndex, fixedRot); } // 0xEC024237
	static void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, float unknown1, float unknown2, float x1, float y1, float z1, float x2, float y2, float z2, float rot_x, float rot_y, float rot_z, Any unknown3, Any unknown4, Any unknown5, Any unknown6, Any unknown7, Any unknown8) { invoke<Void>(0x0547417F, entity1, entity2, unknown1, unknown2, x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z, unknown3, unknown4, unknown5, unknown6, unknown7, unknown8); } // 0x0547417F
	static void _0x6909BA59(Any p0) { invoke<Void>(0x6909BA59, p0); } // 0x6909BA59
	static Any _0xE4ECAC22(Any p0, Any p1) { return invoke<Any>(0xE4ECAC22, p0, p1); } // 0xE4ECAC22
	static void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity) { invoke<Void>(0x2B83F43B, entity); } // 0x2B83F43B
	static void DELETE_ENTITY(Entity* EntityHandle) { invoke<Void>(0xFAA3D236, EntityHandle); } // 0xFAA3D236
	static void DETACH_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0xC8EFCB41, p0, p1, p2); } // 0xC8EFCB41
	static void FREEZE_ENTITY_POSITION(Entity entity, BOOL Toggle) { invoke<Void>(0x65C16D57, entity, Toggle); } // 0x65C16D57
	static void _0xD3850671(Any p0, Any p1) { invoke<Void>(0xD3850671, p0, p1); } // 0xD3850671
	static Any PLAY_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x878753D5, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x878753D5
	static Any PLAY_SYNCHRONIZED_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x012760AA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x012760AA
	static Any _0xEB4CBA74(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0xEB4CBA74, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xEB4CBA74
	static Any _0x7253D5B2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x7253D5B2, p0, p1, p2, p3, p4, p5); } // 0x7253D5B2
	static Any STOP_ENTITY_ANIM(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC4769830, p0, p1, p2, p3); } // 0xC4769830
	static Any STOP_SYNCHRONIZED_ENTITY_ANIM(Any p0, Any p1, Any p2) { return invoke<Any>(0xE27D2FC1, p0, p1, p2); } // 0xE27D2FC1
	static Any _0x66571CA0(Any p0, Any p1) { return invoke<Any>(0x66571CA0, p0, p1); } // 0x66571CA0
	static Any _0xC41DDA62(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xC41DDA62, p0, p1, p2, p3, p4); } // 0xC41DDA62
	static void SET_ENTITY_ANIM_CURRENT_TIME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x99D90735, p0, p1, p2, p3); } // 0x99D90735
	static void SET_ENTITY_ANIM_SPEED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3990C90A, p0, p1, p2, p3); } // 0x3990C90A
	static void SET_ENTITY_AS_MISSION_ENTITY(Entity entityHandle, BOOL value, BOOL p2) { invoke<Void>(0x5D1F9E0F, entityHandle, value, p2); } // 0x5D1F9E0F
	static void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entityHandle) { invoke<Void>(0xADF2267C, entityHandle); } // 0xADF2267C
	static void SET_PED_AS_NO_LONGER_NEEDED(Ped* pedHandle) { invoke<Void>(0x9A388380, pedHandle); } // 0x9A388380
	static void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicleHandle) { invoke<Void>(0x9B0E10BE, vehicleHandle); } // 0x9B0E10BE
	static void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* objectHandle) { invoke<Void>(0x3F6B949F, objectHandle); } // 0x3F6B949F
	static void SET_ENTITY_CAN_BE_DAMAGED(Entity Entity, BOOL Toggle) { invoke<Void>(0x60B6E744, Entity, Toggle); } // 0x60B6E744
	static void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Any p0, Any p1, Any p2) { invoke<Void>(0x34165B5D, p0, p1, p2); } // 0x34165B5D
	static void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Any p0, Any p1) { invoke<Void>(0x3B13797C, p0, p1); } // 0x3B13797C
	static void SET_ENTITY_COLLISION(Entity entity, BOOL p1, BOOL p2) { invoke<Void>(0x139FD37D, entity, p1, p2); } // 0x139FD37D

	static void SET_ENTITY_COORDS(Entity entity, float X, float Y, float Z, BOOL XAxes, BOOL YAxes, BOOL ZAxes, BOOL unk) { invoke<Void>(0xDF70B41B, entity, X, Y, Z, XAxes, YAxes, ZAxes, unk); } // 0xDF70B41B
	static void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xCoord, float yCoord, float zCoord, BOOL p4, BOOL p5, BOOL p6) { invoke<Void>(0x4C83DE8D, entity, xCoord, yCoord, zCoord, p4, p5, p6); } // 0x4C83DE8D
	static void SET_ENTITY_DYNAMIC(Entity entity, BOOL ToggleDynamics) { invoke<Void>(0x236F525B, entity, ToggleDynamics); } // 0x236F525B
	static void SET_ENTITY_HEADING(Entity entity, float Heading) { invoke<Void>(0xE0FF064D, entity, Heading); } // 0xE0FF064D
	static void SET_ENTITY_HEALTH(Entity entity, int Amount) { invoke<Void>(0xFBCD1831, entity, Amount); } // 0xFBCD1831
	static void SET_ENTITY_INVINCIBLE(Entity entity, BOOL Toggle) { invoke<Void>(0xC1213A21, entity, Toggle); } // 0xC1213A21
	static void SET_ENTITY_IS_TARGET_PRIORITY(Any p0, Any p1, Any p2) { invoke<Void>(0x9729EE32, p0, p1, p2); } // 0x9729EE32
	static void SET_ENTITY_LIGHTS(Any p0, Any p1) { invoke<Void>(0xE8FC85AF, p0, p1); } // 0xE8FC85AF
	static void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, BOOL Toggle) { invoke<Void>(0xC52F295B, entity, Toggle); } // 0xC52F295B
	static Any _0x851687F9(Any p0) { return invoke<Any>(0x851687F9, p0); } // 0x851687F9
	static void SET_ENTITY_MAX_SPEED(Any p0, Any p1) { invoke<Void>(0x46AFFED3, p0, p1); } // 0x46AFFED3
	static void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Any p0, Any p1) { invoke<Void>(0x4B707F50, p0, p1); } // 0x4B707F50
	static void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Any p0, Any p1, Any p2) { invoke<Void>(0x202237E2, p0, p1, p2); } // 0x202237E2
	static void SET_ENTITY_PROOFS(Entity Entity, BOOL bulletProof, BOOL fireProof, BOOL explosionProof, BOOL collisionProof, BOOL meleeProof, Any p6, Any p7, Any p8) { invoke<Void>(0x7E9EAB66, Entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, p6, p7, p8); } // 0x7E9EAB66
	static void SET_ENTITY_QUATERNION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x83B6046F, p0, p1, p2, p3, p4); } // 0x83B6046F
	static void SET_ENTITY_RECORDS_COLLISIONS(Any p0, Any p1) { invoke<Void>(0x6B189A1A, p0, p1); } // 0x6B189A1A
	static void SET_ENTITY_ROTATION(Entity entity, float Pitch, float Roll, float Yaw, Any p4, Any p5) { invoke<Void>(0x0A345EFE, entity, Pitch, Roll, Yaw, p4, p5); } // 0x0A345EFE
	static void SET_ENTITY_VISIBLE(Entity entity, BOOL Toggle) { invoke<Void>(0xD043E8E1, entity, Toggle); } // 0xD043E8E1
	static void SET_ENTITY_VELOCITY(Entity entity, float xVel, float yVel, float zVel) { invoke<Void>(0xFF5A1988, entity, xVel, yVel, zVel); } // 0xFF5A1988
	static void SET_ENTITY_HAS_GRAVITY(Any p0, Any p1) { invoke<Void>(0xE2F262BF, p0, p1); } // 0xE2F262BF
	static void SET_ENTITY_LOD_DIST(Entity entity, int Distance) { invoke<Void>(0xD7ACC7AD, entity, Distance); } // 0xD7ACC7AD
	static Any _0x4DA3D51F(Any p0) { return invoke<Any>(0x4DA3D51F, p0); } // 0x4DA3D51F
	static void SET_ENTITY_ALPHA(Entity entity, int AlphaLVL, Any p2) { invoke<Void>(0xAE667CB0, entity, AlphaLVL, p2); } // 0xAE667CB0
	static Any GET_ENTITY_ALPHA(Entity entity) { return invoke<Any>(0x1560B017, entity); } // 0x1560B017
	static void RESET_ENTITY_ALPHA(Entity entity) { invoke<Void>(0x8A30761C, entity); } // 0x8A30761C
	static void _0xD8FF798A(Any p0, Any p1) { invoke<Void>(0xD8FF798A, p0, p1); } // 0xD8FF798A
	static void SET_ENTITY_RENDER_SCORCHED(Any p0, Any p1) { invoke<Void>(0xAAC9317B, p0, p1); } // 0xAAC9317B
	static void _0xC47F5B91(Any p0, Any p1) { invoke<Void>(0xC47F5B91, p0, p1); } // 0xC47F5B91
	static void CREATE_MODEL_SWAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x0BC12F9E, p0, p1, p2, p3, p4, p5, p6); } // 0x0BC12F9E
	static void REMOVE_MODEL_SWAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xCE0AA8BC, p0, p1, p2, p3, p4, p5, p6); } // 0xCE0AA8BC
	static void CREATE_MODEL_HIDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7BD5CF2F, p0, p1, p2, p3, p4, p5); } // 0x7BD5CF2F
	static void _0x07AAF22C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x07AAF22C, p0, p1, p2, p3, p4, p5); } // 0x07AAF22C
	static void REMOVE_MODEL_HIDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x993DBC10, p0, p1, p2, p3, p4, p5); } // 0x993DBC10
	static void CREATE_FORCED_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x335190A2, p0, p1, p2, p3, p4, p5); } // 0x335190A2
	static void REMOVE_FORCED_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAED73ADD, p0, p1, p2, p3, p4); } // 0xAED73ADD
	static void SET_ENTITY_NO_COLLISION_ENTITY(Entity ent1, Entity ent2, BOOL toogle) { invoke<Void>(0x1E11BFE9, ent1, ent2, toogle); } // 0x1E11BFE9
	static void SET_ENTITY_MOTION_BLUR(Any p0, Any p1) { invoke<Void>(0xE90005B8, p0, p1); } // 0xE90005B8
	static void _0x44767B31(Any p0, Any p1) { invoke<Void>(0x44767B31, p0, p1); } // 0x44767B31
	static void _0xE224A6A5(Any p0, Any p1) { invoke<Void>(0xE224A6A5, p0, p1); } // 0xE224A6A5
}


namespace GAMEPLAY
{
	static void SHOOT_SINGLE_BULLET_BETWEEN_COORDS1(float StartPositionX, float StartPositionY, float StartPositionZ, float HitPositionX, float HitPositionY, float HitPositionZ, Any p6, Any p7, Hash WeaponHash, Ped PedHandle, Any p10, Any p11, float Speed) { invoke<Void>(0xCB7415AC, StartPositionX, StartPositionY, StartPositionZ, HitPositionX, HitPositionY, HitPositionZ, p6, p7, WeaponHash, PedHandle, p10, p11, Speed); } // 0xCB7415AC
	static void _CLEAR_AREA_OF_EVERYTHING(float x, float y, float z, float radius, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { invoke<Void>(0x20E4FFD9, x, y, z, radius, p4, p5, p6, p7); } // 0x20E4FFD9
	static int GET_ALLOCATED_STACK_SIZE() { return invoke<int>(0x4E9CA30A); } // 0x4E9CA30A
	static BOOL _SET_ALLOCATED_STACK_SIZE(int StackSize) { return invoke<BOOL>(0x11A178B8, StackSize); } // 0x11A178B8
	static void SET_RANDOM_SEED(Any p0) { invoke<Void>(0xDB3FEB5C, p0); } // 0xDB3FEB5C
	static void SET_TIME_SCALE(float Time) { invoke<Void>(0xA7F84694, Time); } // 0xA7F84694
	static void SET_MISSION_FLAG(Any p0) { invoke<Void>(0x57592D52, p0); } // 0x57592D52
	static Any GET_MISSION_FLAG() { return invoke<Any>(0x95115F97); } // 0x95115F97
	static void SET_RANDOM_EVENT_FLAG(Any p0) { invoke<Void>(0xA77F31E8, p0); } // 0xA77F31E8
	static Any GET_RANDOM_EVENT_FLAG() { return invoke<Any>(0x794CC92C); } // 0x794CC92C
	static void _0x8B2DE971(Any p0) { invoke<Void>(0x8B2DE971, p0); } // 0x8B2DE971
	static void _0xE77199F7(Any p0) { invoke<Void>(0xE77199F7, p0); } // 0xE77199F7
	static Any _0xA8171E9E() { return invoke<Any>(0xA8171E9E); } // 0xA8171E9E
	static Any _0x353E8056() { return invoke<Any>(0x353E8056); } // 0x353E8056
	static BOOL IS_PREV_WEATHER_TYPE(Any p0) { return invoke<BOOL>(0x250ADA61, p0); } // 0x250ADA61
	static BOOL IS_NEXT_WEATHER_TYPE(Any p0) { return invoke<BOOL>(0x99CB167F, p0); } // 0x99CB167F
	static void SET_WEATHER_TYPE_PERSIST(char* WeatherType) { invoke<Void>(0xC6C04C75, WeatherType); } // 0xC6C04C75
	static void SET_WEATHER_TYPE_NOW_PERSIST(char* WeatherType) { invoke<Void>(0xC869FE97, WeatherType); } // 0xC869FE97
	static void SET_WEATHER_TYPE_NOW(char* WeatherType) { invoke<Void>(0x361E9EAC, WeatherType); } // 0x361E9EAC
	static void _SET_WEATHER_TYPE_OVER_TIME(char* WeatherType, float Time) { invoke<Void>(0x386F0D25, WeatherType, Time); } // 0x386F0D25
	static void SET_RANDOM_WEATHER_TYPE() { invoke<Void>(0xE7AA1BC9); } // 0xE7AA1BC9
	static void CLEAR_WEATHER_TYPE_PERSIST() { invoke<Void>(0x6AB757D8); } // 0x6AB757D8
	static void _0x9A5C1D56(Any p0, Any p1, Any p2) { invoke<Void>(0x9A5C1D56, p0, p1, p2); } // 0x9A5C1D56
	static void _0x5CA74040(Any p0, Any p1, Any p2) { invoke<Void>(0x5CA74040, p0, p1, p2); } // 0x5CA74040
	static void SET_OVERRIDE_WEATHER(char* WeatherType) { invoke<Void>(0xD9082BB5, WeatherType); } // 0xD9082BB5
	static void CLEAR_OVERRIDE_WEATHER() { invoke<Void>(0x7740EA4E); } // 0x7740EA4E
	static void _0x625181DC(Any p0) { invoke<Void>(0x625181DC, p0); } // 0x625181DC
	static void _0xBEBBFDC8(Any p0) { invoke<Void>(0xBEBBFDC8, p0); } // 0xBEBBFDC8
	static void _0x6926AB03(Any p0) { invoke<Void>(0x6926AB03, p0); } // 0x6926AB03
	static void _0xD447439D(Any p0) { invoke<Void>(0xD447439D, p0); } // 0xD447439D
	static void _0x584E9C59(Any p0) { invoke<Void>(0x584E9C59, p0); } // 0x584E9C59
	static void _0x5656D578(Any p0) { invoke<Void>(0x5656D578, p0); } // 0x5656D578
	static void _0x0DE40C28(Any p0) { invoke<Void>(0x0DE40C28, p0); } // 0x0DE40C28
	static void _0x98C9138B(Any p0) { invoke<Void>(0x98C9138B, p0); } // 0x98C9138B
	static void _0xFB1A9CDE(Any p0) { invoke<Void>(0xFB1A9CDE, p0); } // 0xFB1A9CDE
	static void _0x1C0CAE89(Any p0) { invoke<Void>(0x1C0CAE89, p0); } // 0x1C0CAE89
	static void _0x4671AC2E(Any p0) { invoke<Void>(0x4671AC2E, p0); } // 0x4671AC2E
	static void _0xDA02F415(Any p0) { invoke<Void>(0xDA02F415, p0); } // 0xDA02F415
	static void _0x5F3DDEC0(Any p0) { invoke<Void>(0x5F3DDEC0, p0); } // 0x5F3DDEC0
	static void _0x63A89684(Any p0) { invoke<Void>(0x63A89684, p0); } // 0x63A89684
	static void SET_WIND(float speed) { invoke<Void>(0xC6294698, speed); } // 0xC6294698
	static void SET_WIND_SPEED(float Speed) { invoke<Void>(0x45705F94, Speed); } // 0x45705F94
	static float GET_WIND_SPEED() { return invoke<float>(0x098F0F3C); } // 0x098F0F3C
	static void SET_WIND_DIRECTION(Any p0) { invoke<Void>(0x381AEEE9, p0); } // 0x381AEEE9
	static vec3_t GET_WIND_DIRECTION() { return invoke<vec3_t>(0x89499A0D); } // 0x89499A0D
	static Any GET_RAIN_LEVEL() { return invoke<Any>(0xC9F67F28); } // 0xC9F67F28
	static Any GET_SNOW_LEVEL() { return invoke<Any>(0x1B09184F); } // 0x1B09184F
	static void _0xDF38165E() { invoke<Void>(0xDF38165E); } // 0xDF38165E
	static void _0x8727A4C5(Any p0) { invoke<Void>(0x8727A4C5, p0); } // 0x8727A4C5
	static void _0x96B2FD08(Any p0) { invoke<Void>(0x96B2FD08, p0); } // 0x96B2FD08
	static void _0xED88FC61(char* p0, BOOL p1) { invoke<Void>(0xED88FC61, p0, p1); } // 0xED88FC61
	static void _0xC9FA6E07(Any p0, Any p1) { invoke<Void>(0xC9FA6E07, p0, p1); } // 0xC9FA6E07
	static void _0x2D7787BC() { invoke<Void>(0x2D7787BC); } // 0x2D7787BC
	static int GET_GAME_TIMER() { return invoke<int>(0xA4EA0691); } // 0xA4EA0691
	static float* GET_FRAME_TIME() { return invoke<float*>(0x96374262); } // 0x96374262
	static float* GET_FRAME_COUNT() { return invoke<float*>(0xB477A015); } // 0xB477A015
	static float GET_RANDOM_FLOAT_IN_RANGE(float p0, float p1) { return invoke<float>(0x0562C4D0, p0, p1); } // 0x0562C4D0
	static int GET_RANDOM_INT_IN_RANGE(int StartRange, int EndRange) { return invoke<int>(0x4051115B, StartRange, EndRange); } // 0x4051115B
	static Any GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float* groundZ) { return invoke<Any>(0xA1BFD5E0, x, y, z, groundZ); } // 0xA1BFD5E0
	static Any _0x64D91CED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x64D91CED, p0, p1, p2, p3, p4); } // 0x64D91CED
	static Any ASIN(Any p0) { return invoke<Any>(0x998E5CAD, p0); } // 0x998E5CAD
	static Any ACOS(Any p0) { return invoke<Any>(0xF4038776, p0); } // 0xF4038776
	static Any TAN(Any p0) { return invoke<Any>(0xD320CE5E, p0); } // 0xD320CE5E
	static Any ATAN(Any p0) { return invoke<Any>(0x7A03CC8E, p0); } // 0x7A03CC8E
	static Any ATAN2(Any p0, Any p1) { return invoke<Any>(0x2508AC81, p0, p1); } // 0x2508AC81
	static float GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, BOOL unknown) { return invoke<float>(0xF698765E, x1, y1, z1, x2, y2, z2, unknown); } // 0xF698765E
	static Any GET_ANGLE_BETWEEN_2D_VECTORS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xDBF75E58, p0, p1, p2, p3); } // 0xDBF75E58
	static Any GET_HEADING_FROM_VECTOR_2D(Any p0, Any p1) { return invoke<Any>(0xD209D52B, p0, p1); } // 0xD209D52B
	static Any _0x89459F0A(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0x89459F0A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x89459F0A
	static vec3_t _0xCAECF37E(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<vec3_t>(0xCAECF37E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xCAECF37E
	static Any _0xC6CC812C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0xC6CC812C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xC6CC812C
	static void SET_BIT(int* var, int bit) { invoke<Void>(0x4EFE7E6B, var, bit); } // 0x4EFE7E6B
	static void CLEAR_BIT(int* var, int bit) { invoke<Void>(0x8BC9E618, var, bit); } // 0x8BC9E618
	static int GET_HASH_KEY(const char* ToHash) { return invoke<int>(0x98EFF6F1, ToHash); } // 0x98EFF6F1
	static void _0x87B92190(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x87B92190, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x87B92190
	static BOOL IS_AREA_OCCUPIED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<BOOL>(0xC013972F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0xC013972F
	static BOOL IS_POSITION_OCCUPIED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<BOOL>(0x452E8D9E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x452E8D9E
	static BOOL IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xC161558D, p0, p1, p2, p3, p4, p5, p6); } // 0xC161558D
	static void CLEAR_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x854E9AB8, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x854E9AB8
	static void _0x20E4FFD9(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x20E4FFD9, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x20E4FFD9
	static void CLEAR_AREA_OF_VEHICLES(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0x63320F3C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x63320F3C
	static void CLEAR_ANGLED_AREA_OF_VEHICLES(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xF11A3018, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xF11A3018
	static void CLEAR_AREA_OF_OBJECTS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBB720FE7, p0, p1, p2, p3, p4); } // 0xBB720FE7
	static void CLEAR_AREA_OF_PEDS(float* XCoord, float* YCoord, float* zCoord, float Area, Any p4) { invoke<Void>(0x25BE7FA8, XCoord, YCoord, zCoord, Area, p4); } // 0x25BE7FA8
	static void CLEAR_AREA_OF_COPS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x95C53824, p0, p1, p2, p3, p4); } // 0x95C53824
	static void CLEAR_AREA_OF_PROJECTILES(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x18DB5434, p0, p1, p2, p3, p4); } // 0x18DB5434
	static void SET_SAVE_MENU_ACTIVE(Any p0) { invoke<Void>(0xF5CCF164, p0); } // 0xF5CCF164
	static Any _0x39771F21() { return invoke<Any>(0x39771F21); } // 0x39771F21
	static void SET_CREDITS_ACTIVE(Any p0) { invoke<Void>(0xEC2A0ECF, p0); } // 0xEC2A0ECF
	static void _0x75B06B5A(Any p0) { invoke<Void>(0x75B06B5A, p0); } // 0x75B06B5A
	static Any _0x2569C9A7() { return invoke<Any>(0x2569C9A7); } // 0x2569C9A7
	static void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(char* ScriptName) { invoke<Void>(0x9F861FD4, ScriptName); } // 0x9F861FD4
	static void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { invoke<Void>(0x878486CE); } // 0x878486CE
	static Any ADD_HOSPITAL_RESTART(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x4F3E3104, p0, p1, p2, p3, p4); } // 0x4F3E3104
	static void DISABLE_HOSPITAL_RESTART(Any p0, Any p1) { invoke<Void>(0x09F49C72, p0, p1); } // 0x09F49C72
	static Any ADD_POLICE_RESTART(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE96C29FE, p0, p1, p2, p3, p4); } // 0xE96C29FE
	static void DISABLE_POLICE_RESTART(Any p0, Any p1) { invoke<Void>(0x0A280324, p0, p1); } // 0x0A280324
	static void _0x296574AE(Any p0) { invoke<Void>(0x296574AE, p0); } // 0x296574AE
	static void IGNORE_NEXT_RESTART(Any p0) { invoke<Void>(0xDA13A4B6, p0); } // 0xDA13A4B6
	static void _0xC9F6F0BC(Any p0) { invoke<Void>(0xC9F6F0BC, p0); } // 0xC9F6F0BC
	static void _0xCB074B9D(Any p0) { invoke<Void>(0xCB074B9D, p0); } // 0xCB074B9D
	static void SET_FADE_IN_AFTER_DEATH_ARREST(Any p0) { invoke<Void>(0xACDE6985, p0); } // 0xACDE6985
	static void SET_FADE_IN_AFTER_LOAD(Any p0) { invoke<Void>(0x6E00EB0B, p0); } // 0x6E00EB0B
	static Any REGISTER_SAVE_HOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x39C1849A, p0, p1, p2, p3, p4, p5, p6); } // 0x39C1849A
	static void SET_SAVE_HOUSE(Any p0, Any p1, Any p2) { invoke<Void>(0xC3240BB4, p0, p1, p2); } // 0xC3240BB4
	static Any OVERRIDE_SAVE_HOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x47436C12, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x47436C12
	static Any _0xC4D71AB4(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC4D71AB4, p0, p1, p2, p3); } // 0xC4D71AB4
	static void DO_AUTO_SAVE() { invoke<Void>(0x54C44B1A); } // 0x54C44B1A
	static Any _0xA8546914() { return invoke<Any>(0xA8546914); } // 0xA8546914
	static BOOL IS_AUTO_SAVE_IN_PROGRESS() { return invoke<BOOL>(0x36F75399); } // 0x36F75399
	static Any _0x78350773() { return invoke<Any>(0x78350773); } // 0x78350773
	static void _0x5A45B11A() { invoke<Void>(0x5A45B11A); } // 0x5A45B11A
	static void BEGIN_REPLAY_STATS(Any p0, Any p1) { invoke<Void>(0x17F4F44D, p0, p1); } // 0x17F4F44D
	static void _0x81216EE0(Any p0) { invoke<Void>(0x81216EE0, p0); } // 0x81216EE0
	static void END_REPLAY_STATS() { invoke<Void>(0xCB570185); } // 0xCB570185
	static Any _0xC58250F1() { return invoke<Any>(0xC58250F1); } // 0xC58250F1
	static Any _0x50C39926() { return invoke<Any>(0x50C39926); } // 0x50C39926
	static Any _0x710E5D1E() { return invoke<Any>(0x710E5D1E); } // 0x710E5D1E
	static Any _0xC7BD1AF0() { return invoke<Any>(0xC7BD1AF0); } // 0xC7BD1AF0
	static Any _0x22BE2423(Any p0) { return invoke<Any>(0x22BE2423, p0); } // 0x22BE2423
	static void CLEAR_REPLAY_STATS() { invoke<Void>(0xC47DFF02); } // 0xC47DFF02
	static Any _0xF62B3C48() { return invoke<Any>(0xF62B3C48); } // 0xF62B3C48
	static Any _0x3589452B() { return invoke<Any>(0x3589452B); } // 0x3589452B
	static Any _0x144AAF22() { return invoke<Any>(0x144AAF22); } // 0x144AAF22
	static BOOL IS_MEMORY_CARD_IN_USE() { return invoke<BOOL>(0x40CE4DFD); } // 0x40CE4DFD
	static void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float* StartPositionX, float* StartPositionY, float* StartPositionZ, float* HitPositionX, float* HitPositionY, float* HitPositionZ, Any p6, Any p7, Hash WeaponHash, Ped PedHandle, Any p10, Any p11, float Speed) { invoke<Void>(0xCB7415AC, StartPositionX, StartPositionY, StartPositionZ, HitPositionX, HitPositionY, HitPositionZ, p6, p7, WeaponHash, PedHandle, p10, p11, Speed); } // 0xCB7415AC
	static void _0x52ACCB7B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { invoke<Void>(0x52ACCB7B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0x52ACCB7B
	static void GET_MODEL_DIMENSIONS(Entity Entity, float* Minimum, float* Maximum) { invoke<Void>(0x91ABB8E0, Entity, Minimum, Maximum); } // 0x91ABB8E0
	static void SET_FAKE_WANTED_LEVEL(Any p0) { invoke<Void>(0x85B1C9FA, p0); } // 0x85B1C9FA
	static Any _0x0022A430() { return invoke<Any>(0x0022A430); } // 0x0022A430
	static BOOL IS_BIT_SET(int var, int bit) { return invoke<BOOL>(0x902E26AC, var, bit); } // 0x902E26AC
	static void USING_MISSION_CREATOR(Any p0) { invoke<Void>(0x20AB0B6B, p0); } // 0x20AB0B6B
	static void _0x082BA6F2(Any p0) { invoke<Void>(0x082BA6F2, p0); } // 0x082BA6F2
	static void SET_MINIGAME_IN_PROGRESS(Any p0) { invoke<Void>(0x348B9046, p0); } // 0x348B9046
	static BOOL IS_MINIGAME_IN_PROGRESS() { return invoke<BOOL>(0x53A95E13); } // 0x53A95E13
	static BOOL IS_THIS_A_MINIGAME_SCRIPT() { return invoke<BOOL>(0x7605EF6F); } // 0x7605EF6F
	static BOOL IS_SNIPER_INVERTED() { return invoke<BOOL>(0x5C3BF51B); } // 0x5C3BF51B
	static Any GET_CURRENT_LANGUAGE() { return invoke<Any>(0x761BE00B); } // 0x761BE00B
	static Any _0xBAF17315() { return invoke<Any>(0xBAF17315); } // 0xBAF17315
	static Any GET_PROFILE_SETTING(int p0) { return invoke<Any>(0xD374BEBC, p0); } // 0xD374BEBC
	static BOOL ARE_STRINGS_EQUAL(char* string1, char* string2) { return invoke<BOOL>(0x877C0BC5, string1, string2); } // 0x877C0BC5
	static Any COMPARE_STRINGS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xFE25A58F, p0, p1, p2, p3); } // 0xFE25A58F
	static Any ABSI(Any p0) { return invoke<Any>(0xB44677C5, p0); } // 0xB44677C5
	static Any ABSF(Any p0) { return invoke<Any>(0xAF6F6E0B, p0); } // 0xAF6F6E0B
	static BOOL IS_SNIPER_BULLET_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x0483715C, p0, p1, p2, p3, p4, p5); } // 0x0483715C
	static BOOL IS_PROJECTILE_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0x78E1A557, p0, p1, p2, p3, p4, p5, p6); } // 0x78E1A557
	static BOOL IS_PROJECTILE_TYPE_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x2B73BCF6, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2B73BCF6
	static BOOL IS_PROJECTILE_TYPE_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0xD1AE2681, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD1AE2681
	static Any _0xBE81F1E2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xBE81F1E2, p0, p1, p2, p3, p4, p5); } // 0xBE81F1E2
	static Any _0x1A40454B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x1A40454B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x1A40454B
	static Any _0x6BDE5CE4(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x6BDE5CE4, p0, p1, p2, p3, p4); } // 0x6BDE5CE4
	static Any _0x507BC6F7(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x507BC6F7, p0, p1, p2, p3, p4, p5); } // 0x507BC6F7
	static BOOL IS_BULLET_IN_ANGLED_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0xE2DB58F7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xE2DB58F7
	static BOOL IS_BULLET_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xB54F46CA, p0, p1, p2, p3, p4); } // 0xB54F46CA
	static BOOL IS_BULLET_IN_BOX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xAB73ED26, p0, p1, p2, p3, p4, p5, p6); } // 0xAB73ED26
	static BOOL HAS_BULLET_IMPACTED_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x902BC7D9, p0, p1, p2, p3, p4, p5); } // 0x902BC7D9
	static BOOL HAS_BULLET_IMPACTED_IN_BOX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x2C2618CC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2C2618CC
	static BOOL IS_ORBIS_VERSION() { return invoke<BOOL>(0x40282018); } // 0x40282018
	static BOOL IS_DURANGO_VERSION() { return invoke<BOOL>(0x46FB06A5); } // 0x46FB06A5
	static BOOL IS_XBOX360_VERSION() { return invoke<BOOL>(0x24005CC8); } // 0x24005CC8
	static BOOL IS_PS3_VERSION() { return invoke<BOOL>(0x4C0D5303); } // 0x4C0D5303
	static BOOL IS_PC_VERSION() { return invoke<BOOL>(0x4D5D9EE3); } // 0x4D5D9EE3
	static BOOL IS_AUSSIE_VERSION() { return invoke<BOOL>(0x944BA1DC); } // 0x944BA1DC
	static BOOL IS_STRING_NULL(Any p0) { return invoke<BOOL>(0x8E71E00F, p0); } // 0x8E71E00F
	static BOOL IS_STRING_NULL_OR_EMPTY(char* string) { return invoke<BOOL>(0x42E9F2CA, string); } // 0x42E9F2CA
	static BOOL STRING_TO_INT(char* string, int* ToStore) { return invoke<BOOL>(0x590A8160, string, ToStore); } // 0x590A8160
	static void SET_BITS_IN_RANGE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x32094719, p0, p1, p2, p3); } // 0x32094719
	static Any GET_BITS_IN_RANGE(Any p0, Any p1, Any p2) { return invoke<Any>(0xCA03A1E5, p0, p1, p2); } // 0xCA03A1E5
	static Any ADD_STUNT_JUMP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return invoke<Any>(0xB630E5FF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0xB630E5FF
	static Any ADD_STUNT_JUMP_ANGLED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18) { return invoke<Any>(0xB9B7E777, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // 0xB9B7E777
	static void DELETE_STUNT_JUMP(Any p0) { invoke<Void>(0x840CB5DA, p0); } // 0x840CB5DA
	static void ENABLE_STUNT_JUMP_SET(Any p0) { invoke<Void>(0x9D1E7785, p0); } // 0x9D1E7785
	static void DISABLE_STUNT_JUMP_SET(Any p0) { invoke<Void>(0x644C9FA4, p0); } // 0x644C9FA4
	static void _0x3C806A2D(Any p0) { invoke<Void>(0x3C806A2D, p0); } // 0x3C806A2D
	static BOOL IS_STUNT_JUMP_IN_PROGRESS() { return invoke<BOOL>(0xF477D0B1); } // 0xF477D0B1
	static Any _0x021636EE() { return invoke<Any>(0x021636EE); } // 0x021636EE
	static Any _0x006F9BA2() { return invoke<Any>(0x006F9BA2); } // 0x006F9BA2
	static void CANCEL_STUNT_JUMP() { invoke<Void>(0xF43D9821); } // 0xF43D9821
	static void SET_GAME_PAUSED(BOOL Paused) { invoke<Void>(0x8230FF6C, Paused); } // 0x8230FF6C
	static void SET_THIS_SCRIPT_CAN_BE_PAUSED(Any p0) { invoke<Void>(0xA0C3CE29, p0); } // 0xA0C3CE29
	static void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(Any p0) { invoke<Void>(0xD06F1720, p0); } // 0xD06F1720
	static Any _0xFF6191E1(Any p0, Any p1) { return invoke<Any>(0xFF6191E1, p0, p1); } // 0xFF6191E1
	static void _0x721B2492(Any p0) { invoke<Void>(0x721B2492, p0); } // 0x721B2492
	static void _0xE202879D(Any p0) { invoke<Void>(0xE202879D, p0); } // 0xE202879D
	static BOOL IS_FRONTEND_FADING() { return invoke<BOOL>(0x8FF6232C); } // 0x8FF6232C
	static void POPULATE_NOW() { invoke<Void>(0x72C20700); } // 0x72C20700
	static Any GET_INDEX_OF_CURRENT_LEVEL() { return invoke<Any>(0x6F203C6E); } // 0x6F203C6E
	static void SET_GRAVITY_LEVEL(Any p0) { invoke<Void>(0x2D833F4A, p0); } // 0x2D833F4A
	static void START_SAVE_DATA(Any p0, Any p1, Any p2) { invoke<Void>(0x881A694D, p0, p1, p2); } // 0x881A694D
	static void STOP_SAVE_DATA() { invoke<Void>(0x3B1C07C8); } // 0x3B1C07C8
	static Any _0x9EF0BC64(Any p0) { return invoke<Any>(0x9EF0BC64, p0); } // 0x9EF0BC64
	static void REGISTER_INT_TO_SAVE(Any p0, Any p1) { invoke<Void>(0xB930956F, p0, p1); } // 0xB930956F
	static void _0x9B38374A(Any p0, Any p1) { invoke<Void>(0x9B38374A, p0, p1); } // 0x9B38374A
	static void REGISTER_FLOAT_TO_SAVE(Any p0, Any p1) { invoke<Void>(0xDB06F7AD, p0, p1); } // 0xDB06F7AD
	static void REGISTER_BOOL_TO_SAVE(Any p0, Any p1) { invoke<Void>(0x5417E0E0, p0, p1); } // 0x5417E0E0
	static void REGISTER_TEXT_LABEL_TO_SAVE(Any p0, Any p1) { invoke<Void>(0x284352C4, p0, p1); } // 0x284352C4
	static void _0xE2089749(Any p0, Any p1) { invoke<Void>(0xE2089749, p0, p1); } // 0xE2089749
	static void _0xF91B8C33(Any p0, Any p1) { invoke<Void>(0xF91B8C33, p0, p1); } // 0xF91B8C33
	static void _0x74E8FAD9(Any p0, Any p1) { invoke<Void>(0x74E8FAD9, p0, p1); } // 0x74E8FAD9
	static void _0x6B4335DD(Any p0, Any p1) { invoke<Void>(0x6B4335DD, p0, p1); } // 0x6B4335DD
	static void _0xFB45728E(Any p0, Any p1, Any p2) { invoke<Void>(0xFB45728E, p0, p1, p2); } // 0xFB45728E
	static void STOP_SAVE_STRUCT() { invoke<Void>(0xC2624A28); } // 0xC2624A28
	static void _0x893A342C(Any p0, Any p1, Any p2) { invoke<Void>(0x893A342C, p0, p1, p2); } // 0x893A342C
	static void STOP_SAVE_ARRAY() { invoke<Void>(0x0CAD8217); } // 0x0CAD8217
	static void _0x0B710A51(Any p0, Any p1) { invoke<Void>(0x0B710A51, p0, p1); } // 0x0B710A51
	static void _0xE0F0684F(Any p0, Any p1) { invoke<Void>(0xE0F0684F, p0, p1); } // 0xE0F0684F
	static Any _0x3CE5BF6B(Any p0) { return invoke<Any>(0x3CE5BF6B, p0); } // 0x3CE5BF6B
	static Any CREATE_INCIDENT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xFC5FF7B3, p0, p1, p2, p3, p4, p5, p6); } // 0xFC5FF7B3
	static Any CREATE_INCIDENT_WITH_ENTITY(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xBBC35B03, p0, p1, p2, p3, p4); } // 0xBBC35B03
	static void DELETE_INCIDENT(Any p0) { invoke<Void>(0x212BD0DC, p0); } // 0x212BD0DC
	static BOOL IS_INCIDENT_VALID(Any p0) { return invoke<BOOL>(0x31FD0BA4, p0); } // 0x31FD0BA4
	static void _0x0242D88E(Any p0, Any p1, Any p2) { invoke<Void>(0x0242D88E, p0, p1, p2); } // 0x0242D88E
	static void _0x1F38102E(Any p0, Any p1) { invoke<Void>(0x1F38102E, p0, p1); } // 0x1F38102E
	static Any FIND_SPAWN_POINT_IN_DIRECTION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x71AEFD77, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x71AEFD77
	static Any _0x42BF09B3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x42BF09B3, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x42BF09B3
	static void _0xFBDBE374(Any p0, Any p1) { invoke<Void>(0xFBDBE374, p0, p1); } // 0xFBDBE374
	static void ENABLE_TENNIS_MODE(Any p0, Any p1, Any p2) { invoke<Void>(0x0BD3F9EC, p0, p1, p2); } // 0x0BD3F9EC
	static BOOL IS_TENNIS_MODE(Any p0) { return invoke<BOOL>(0x04A947BA, p0); } // 0x04A947BA
	static void _0xC20A7D2B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xC20A7D2B, p0, p1, p2, p3, p4, p5); } // 0xC20A7D2B
	static Any _0x8501E727(Any p0) { return invoke<Any>(0x8501E727, p0); } // 0x8501E727
	static Any _0x1A332D2D(Any p0) { return invoke<Any>(0x1A332D2D, p0); } // 0x1A332D2D
	static void _0x0C8865DF(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x0C8865DF, p0, p1, p2, p3, p4, p5); } // 0x0C8865DF
	static void _0x49F977A9(Any p0, Any p1, Any p2) { invoke<Void>(0x49F977A9, p0, p1, p2); } // 0x49F977A9
	static void _0x6F009E33(Any p0, Any p1, Any p2) { invoke<Void>(0x6F009E33, p0, p1, p2); } // 0x6F009E33
	static void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE() { invoke<Void>(0xDA65ECAA); } // 0xDA65ECAA
	static void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(Any p0) { invoke<Void>(0x6283BE32, p0); } // 0x6283BE32
	static void RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0) { invoke<Void>(0x1479E85A, p0); } // 0x1479E85A
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0, Any p1) { invoke<Void>(0xABADB709, p0, p1); } // 0xABADB709
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x1C996BCD, p0, p1); } // 0x1C996BCD
	static Any _0xF557BAF9(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xF557BAF9, p0, p1, p2, p3, p4, p5, p6); } // 0xF557BAF9
	static void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(Any p0) { invoke<Void>(0xA8D2FB92, p0); } // 0xA8D2FB92
	static void RESET_DISPATCH_SPAWN_BLOCKING_AREAS() { invoke<Void>(0x9A17F835); } // 0x9A17F835
	static void _0xE0C9307E() { invoke<Void>(0xE0C9307E); } // 0xE0C9307E
	static void _0xA0D8C749(Any p0, Any p1) { invoke<Void>(0xA0D8C749, p0, p1); } // 0xA0D8C749
	static void _0x24A4E0B2(Any p0, Any p1, Any p2) { invoke<Void>(0x24A4E0B2, p0, p1, p2); } // 0x24A4E0B2
	static void _0x66C3C59C() { invoke<Void>(0x66C3C59C); } // 0x66C3C59C
	static void _0xD9660339(Any p0) { invoke<Void>(0xD9660339, p0); } // 0xD9660339
	static void _0xD2688412(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { invoke<Void>(0xD2688412, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xD2688412
	static void DISPLAY_ONSCREEN_KEYBOARD(BOOL p0, char* windowTitle, char* p2, char* defaultText, char* defaultConcat1, char* defaultConcat2, char* defaultConcat3, int maxInputLength) { invoke<Void>(0xAD99F2CE, p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, maxInputLength); } // 0xAD99F2CE
	static int UPDATE_ONSCREEN_KEYBOARD() { return invoke<int>(0x23D0A1CE); } // 0x23D0A1CE
	static char* GET_ONSCREEN_KEYBOARD_RESULT() { return invoke<char*>(0x44828FB3); } // 0x44828FB3
	static void _0x3301EA47(Any p0) { invoke<Void>(0x3301EA47, p0); } // 0x3301EA47
	static void _0x42B484ED(Any p0, Any p1) { invoke<Void>(0x42B484ED, p0, p1); } // 0x42B484ED
	static void _0x8F60366E(Any p0, Any p1) { invoke<Void>(0x8F60366E, p0, p1); } // 0x8F60366E
	static void SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0x2EAFA1D1, player); } // 0x2EAFA1D1
	static void SET_FIRE_AMMO_THIS_FRAME(Player player) { invoke<Void>(0x7C18FC8A, player); } // 0x7C18FC8A
	static void SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player) { invoke<Void>(0x96663D56, player); } // 0x96663D56
	static void SET_SUPER_JUMP_THIS_FRAME(Player player) { invoke<Void>(0x86745EF3, player); } // 0x86745EF3
	static Any _0xC3C10FCC() { return invoke<Any>(0xC3C10FCC); } // 0xC3C10FCC
	static void _0x054EC103() { invoke<Void>(0x054EC103); } // 0x054EC103
	static Any _0x46B5A15C() { return invoke<Any>(0x46B5A15C); } // 0x46B5A15C
	static void _0x5D209F25() { invoke<Void>(0x5D209F25); } // 0x5D209F25
	static void _0x2D33F15A(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x2D33F15A, p0, p1, p2, p3); } // 0x2D33F15A
	static void _0xDF99925C() { invoke<Void>(0xDF99925C); } // 0xDF99925C
	static void _0xA27F4472(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA27F4472, p0, p1, p2, p3); } // 0xA27F4472
	static Any _0x07FF553F(Any p0, Any p1, Any p2) { return invoke<Any>(0x07FF553F, p0, p1, p2); } // 0x07FF553F
}

namespace PED
{
	static Ped CREATE_PED(int type, Hash pedHash, float x, float y, float z, float heading, BOOL networkHandle, BOOL returnPEDHandle) { return invoke<Ped>(0x0389EF71, type, pedHash, x, y, z, heading, networkHandle, returnPEDHandle); } // 0x0389EF71
	static void DELETE_PED(Ped* ped) { invoke<Void>(0x13EFB9A0, ped); } // 0x13EFB9A0
	static Ped CLONE_PED(Ped Priest, float Heading, BOOL networkhandle, BOOL createpedhandle) { return invoke<Ped>(0x8C8A8D6E, Priest, Heading, networkhandle, createpedhandle); } // 0x8C8A8D6E
	static void _0xFC70EEC7(Ped GamerHandle, Ped* pedHandle) { invoke<Void>(0xFC70EEC7, GamerHandle, pedHandle); } // 0xFC70EEC7
	static BOOL IS_PED_IN_VEHICLE(Ped pedHandle, Vehicle vehicleHandle, BOOL atGetIn) { return invoke<BOOL>(0x7DA6BC83, pedHandle, vehicleHandle, atGetIn); } // 0x7DA6BC83
	static BOOL IS_PED_IN_MODEL(Ped ped, Hash vehicleModel) { return invoke<BOOL>(0xA6438D4B, ped, vehicleModel); } // 0xA6438D4B
	static BOOL IS_PED_IN_ANY_VEHICLE(Ped pedHandle, BOOL atGetIn) { return invoke<BOOL>(0x3B0171EE, pedHandle, atGetIn); } // 0x3B0171EE
	static BOOL IS_COP_PED_IN_AREA_3D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0xB98DB96B, p0, p1, p2, p3, p4, p5); } // 0xB98DB96B
	static BOOL IS_PED_INJURED(Ped ped) { return invoke<BOOL>(0x2530A087, ped); } // 0x2530A087
	static BOOL IS_PED_HURT(Any p0) { return invoke<BOOL>(0x69DFA0AF, p0); } // 0x69DFA0AF
	static BOOL IS_PED_FATALLY_INJURED(Ped ped) { return invoke<BOOL>(0xBADA0093, ped); } // 0xBADA0093
	static BOOL _IS_PED_DEAD(Ped pedHandle, BOOL p1) { return invoke<BOOL>(0xCBDB7739, pedHandle, p1); } // 0xCBDB7739
	static BOOL IS_CONVERSATION_PED_DEAD(Any p0) { return invoke<BOOL>(0x1FA39EFE, p0); } // 0x1FA39EFE
	static BOOL IS_PED_AIMING_FROM_COVER(Player* p0) { return invoke<BOOL>(0xDEBAB2AF, p0); } // 0xDEBAB2AF
	static BOOL IS_PED_RELOADING(Ped ped) { return invoke<BOOL>(0x961E1745, ped); } // 0x961E1745
	static BOOL IS_PED_A_PLAYER(Ped ped) { return invoke<BOOL>(0x404794CA, ped); } // 0x404794CA
	static Any CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, Any p4, Any p5) { return invoke<Any>(0x3000F092, vehicle, pedType, modelHash, seat, p4, p5); } // 0x3000F092
	static void SET_PED_DESIRED_HEADING(Any p0, Any p1) { invoke<Void>(0x961458F9, p0, p1); } // 0x961458F9
	static void _0x290421BE(Any p0) { invoke<Void>(0x290421BE, p0); } // 0x290421BE
	static BOOL IS_PED_FACING_PED(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x0B775838, p0, p1, p2); } // 0x0B775838
	static BOOL IS_PED_IN_MELEE_COMBAT(Ped ped) { return invoke<BOOL>(0xFD7814A5, ped); } // 0xFD7814A5
	static BOOL IS_PED_STOPPED(Ped ped) { return invoke<BOOL>(0xA0DC0B87, ped); } // 0xA0DC0B87
	static BOOL IS_PED_SHOOTING_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0x741BF04F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x741BF04F
	static BOOL IS_ANY_PED_SHOOTING_IN_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x91833867, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x91833867
	static BOOL IS_PED_SHOOTING(Ped ped) { return invoke<BOOL>(0xE7C3405E, ped); } // 0xE7C3405E
	static void SET_PED_ACCURACY(Ped ped, int accuracy) { invoke<Void>(0x6C17122E, ped, accuracy); } // 0x6C17122E
	static Any GET_PED_ACCURACY(Any p0) { return invoke<Any>(0x0A2A0AA0, p0); } // 0x0A2A0AA0
	static BOOL IS_PED_MODEL(Ped pedHandle, Hash modelHash) { return invoke<BOOL>(0x5F1DDFCB, pedHandle, modelHash); } // 0x5F1DDFCB
	static void EXPLODE_PED_HEAD(Ped ped, Hash WeaponHash) { invoke<Void>(0x05CC1380, ped, WeaponHash); } // 0x05CC1380
	static void REMOVE_PED_ELEGANTLY(Ped PedHandle) { invoke<Void>(0x4FFB8C6C, PedHandle); } // 0x4FFB8C6C
	static void ADD_ARMOUR_TO_PED(Ped PedHandle, int Amount) { invoke<Void>(0xF686B26E, PedHandle, Amount); } // 0xF686B26E
	static void SET_PED_ARMOUR(Any p0, Any p1) { invoke<Void>(0x4E3A0CC4, p0, p1); } // 0x4E3A0CC4
	static void SET_PED_INTO_VEHICLE(Ped PedHandle, Vehicle VehicleHandle, int SeatIndex) { invoke<Void>(0x07500C79, PedHandle, VehicleHandle, SeatIndex); } // 0x07500C79
	static void _0x58A80BD5(Any p0, Any p1) { invoke<Void>(0x58A80BD5, p0, p1); } // 0x58A80BD5
	static BOOL CAN_CREATE_RANDOM_PED(Any p0) { return invoke<BOOL>(0xF9ABE88F, p0); } // 0xF9ABE88F
	static Ped CREATE_RANDOM_PED(float X, float Y, float Z) { return invoke<Ped>(0x5A949543, X, Y, Z); } // 0x5A949543
	static Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicleHandle, BOOL p1) { return invoke<Ped>(0xB927CE9A, vehicleHandle, p1); } // 0xB927CE9A
	static BOOL CAN_CREATE_RANDOM_DRIVER() { return invoke<BOOL>(0x99861609); } // 0x99861609
	static Any _0x7018BE31() { return invoke<Any>(0x7018BE31); } // 0x7018BE31
	static void SET_PED_MOVE_ANIMS_BLEND_OUT(Any p0) { invoke<Void>(0x20E01957, p0); } // 0x20E01957
	static void SET_PED_CAN_BE_DRAGGED_OUT(Any p0, Any p1) { invoke<Void>(0xAA7F1131, p0, p1); } // 0xAA7F1131
	static void _0x6CD58238(Any p0) { invoke<Void>(0x6CD58238, p0); } // 0x6CD58238
	static BOOL IS_PED_MALE(Any p0) { return invoke<BOOL>(0x90950455, p0); } // 0x90950455
	static BOOL IS_PED_HUMAN(Any p0) { return invoke<BOOL>(0x194BB7B0, p0); } // 0x194BB7B0
	static Vehicle GET_VEHICLE_PED_IS_IN(Ped pedHandle, BOOL getLastVehicle) { return invoke<Vehicle>(0xAFE92319, pedHandle, getLastVehicle); } // 0xAFE92319
	static void RESET_PED_LAST_VEHICLE(Any p0) { invoke<Void>(0x5E3B5942, p0); } // 0x5E3B5942
	static void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(Any p0) { invoke<Void>(0x039C82BB, p0); } // 0x039C82BB
	static void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(Any p0, Any p1) { invoke<Void>(0x2909ABF0, p0, p1); } // 0x2909ABF0
	static void _0xB48C0C04() { invoke<Void>(0xB48C0C04); } // 0xB48C0C04
	static void _0x25EA2AA5(Any p0, Any p1, Any p2) { invoke<Void>(0x25EA2AA5, p0, p1, p2); } // 0x25EA2AA5
	static void SET_PED_NON_CREATION_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x7A97283F, p0, p1, p2, p3, p4, p5); } // 0x7A97283F
	static void CLEAR_PED_NON_CREATION_AREA() { invoke<Void>(0x6F7043A3); } // 0x6F7043A3
	static void _0x8C555ADD() { invoke<Void>(0x8C555ADD); } // 0x8C555ADD
	static BOOL IS_PED_ON_MOUNT(Any p0) { return invoke<BOOL>(0x43103006, p0); } // 0x43103006
	static Any GET_MOUNT(Any p0) { return invoke<Any>(0xDD31EC4E, p0); } // 0xDD31EC4E
	static BOOL IS_PED_ON_VEHICLE(Any p0) { return invoke<BOOL>(0xA1AE7CC7, p0); } // 0xA1AE7CC7
	static BOOL IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle specificVehicle) { return invoke<BOOL>(0x63CB4603, ped, specificVehicle); } // 0x63CB4603
	static void SET_PED_MONEY(Ped pedHandle, int amount) { invoke<Void>(0x40D90BF2, pedHandle, amount); } // 0x40D90BF2
	static Any GET_PED_MONEY(Ped pedHandle) { return invoke<Any>(0xEB3C4C7E, pedHandle); } // 0xEB3C4C7E
	static void _0xD41C9AED(Any p0, Any p1) { invoke<Void>(0xD41C9AED, p0, p1); } // 0xD41C9AED
	static void _0x30B98369(Any p0) { invoke<Void>(0x30B98369, p0); } // 0x30B98369
	static void _0x02A080C8(Any p0) { invoke<Void>(0x02A080C8, p0); } // 0x02A080C8
	static void SET_PED_SUFFERS_CRITICAL_HITS(Any p0, Any p1) { invoke<Void>(0x6F6FC7E6, p0, p1); } // 0x6F6FC7E6
	static void _0x1572022A(Any p0, Any p1) { invoke<Void>(0x1572022A, p0, p1); } // 0x1572022A
	static BOOL IS_PED_SITTING_IN_VEHICLE(Any p0, Any p1) { return invoke<BOOL>(0xDDDE26FA, p0, p1); } // 0xDDDE26FA
	static BOOL IS_PED_SITTING_IN_ANY_VEHICLE(Ped Ped) { return invoke<BOOL>(0x0EA9CA03, Ped); } // 0x0EA9CA03
	static BOOL IS_PED_ON_FOOT(Ped Ped) { return invoke<BOOL>(0xC60D0785, Ped); } // 0xC60D0785
	static BOOL IS_PED_ON_ANY_BIKE(Any p0) { return invoke<BOOL>(0x4D885B2E, p0); } // 0x4D885B2E
	static BOOL IS_PED_PLANTING_BOMB(Any p0) { return invoke<BOOL>(0x0EDAC574, p0); } // 0x0EDAC574
	static vec3_t GET_DEAD_PED_PICKUP_COORDS(Any p0, Any p1, Any p2) { return invoke<vec3_t>(0x129F9DC1, p0, p1, p2); } // 0x129F9DC1
	static BOOL IS_PED_IN_ANY_BOAT(Any p0) { return invoke<BOOL>(0x1118A947, p0); } // 0x1118A947
	static BOOL IS_PED_IN_ANY_SUB(Any p0) { return invoke<BOOL>(0xE65F8059, p0); } // 0xE65F8059
	static BOOL IS_PED_IN_ANY_HELI(Any p0) { return invoke<BOOL>(0x7AB5523B, p0); } // 0x7AB5523B
	static BOOL IS_PED_IN_ANY_PLANE(Any p0) { return invoke<BOOL>(0x51BBCE7E, p0); } // 0x51BBCE7E
	static BOOL IS_PED_IN_FLYING_VEHICLE(Any p0) { return invoke<BOOL>(0xCA072485, p0); } // 0xCA072485
	static void SET_PED_DIES_IN_WATER(Any p0, Any p1) { invoke<Void>(0x604C872B, p0, p1); } // 0x604C872B
	static void SET_PED_DIES_IN_SINKING_VEHICLE(Any p0, Any p1) { invoke<Void>(0x8D4D9ABB, p0, p1); } // 0x8D4D9ABB
	static int GET_PED_ARMOUR(Ped PedHandle) { return invoke<int>(0x2CE311A7, PedHandle); } // 0x2CE311A7
	static void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Any p0, Any p1) { invoke<Void>(0xB014A09C, p0, p1); } // 0xB014A09C
	static void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x5DB7B3A9, p0, p1); } // 0x5DB7B3A9
	static Any GET_PED_LAST_DAMAGE_BONE(Any p0, Any p1) { return invoke<Any>(0xAB933841, p0, p1); } // 0xAB933841
	static void CLEAR_PED_LAST_DAMAGE_BONE(Any p0) { invoke<Void>(0x56CB715E, p0); } // 0x56CB715E
	static void SET_AI_WEAPON_DAMAGE_MODIFIER(Any p0) { invoke<Void>(0x516E30EE, p0); } // 0x516E30EE
	static void RESET_AI_WEAPON_DAMAGE_MODIFIER() { invoke<Void>(0x6E965420); } // 0x6E965420
	static void _0x0F9A401F(Any p0) { invoke<Void>(0x0F9A401F, p0); } // 0x0F9A401F
	static void _0x97886238() { invoke<Void>(0x97886238); } // 0x97886238
	static void _0xCC9D7F1A(Any p0, Any p1) { invoke<Void>(0xCC9D7F1A, p0, p1); } // 0xCC9D7F1A
	static void SET_PED_CAN_BE_TARGETTED(Any p0, Any p1) { invoke<Void>(0x75C49F74, p0, p1); } // 0x75C49F74
	static void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Any p0, Any p1, Any p2) { invoke<Void>(0xB103A8E1, p0, p1, p2); } // 0xB103A8E1
	static void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Any p0, Any p1, Any p2) { invoke<Void>(0xD050F490, p0, p1, p2); } // 0xD050F490
	static void _0x7DA12905(Any p0, Any p1) { invoke<Void>(0x7DA12905, p0, p1); } // 0x7DA12905
	static void SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(Any p0, Any p1) { invoke<Void>(0x7F67671D, p0, p1); } // 0x7F67671D
	static BOOL IS_PED_IN_ANY_POLICE_VEHICLE(Any p0) { return invoke<BOOL>(0x84FA790D, p0); } // 0x84FA790D
	static void _0xA819680B(Any p0) { invoke<Void>(0xA819680B, p0); } // 0xA819680B
	static Any _0xCD71F11B(Ped ped) { return invoke<Any>(0xCD71F11B, ped); } // 0xCD71F11B
	static BOOL IS_PED_FALLING(Ped PedHandle) { return invoke<BOOL>(0xABF77334, PedHandle); } // 0xABF77334
	static BOOL IS_PED_JUMPING(Ped Ped) { return invoke<BOOL>(0x07E5BC0E, Ped); } // 0x07E5BC0E
	static BOOL IS_PED_CLIMBING(Ped Ped) { return invoke<BOOL>(0xBCE03D35, Ped); } // 0xBCE03D35
	static Any _0xC3169BDA(Any p0) { return invoke<Any>(0xC3169BDA, p0); } // 0xC3169BDA
	static BOOL IS_PED_DIVING(Any p0) { return invoke<BOOL>(0x7BC5BF3C, p0); } // 0x7BC5BF3C
	static Any _0xB19215F6(Any p0) { return invoke<Any>(0xB19215F6, p0); } // 0xB19215F6
	static Any GET_PED_PARACHUTE_STATE(Any p0) { return invoke<Any>(0x7D4BC475, p0); } // 0x7D4BC475
	static Any _0x01F3B035(Any p0) { return invoke<Any>(0x01F3B035, p0); } // 0x01F3B035
	static void SET_PED_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0x5AEFEC3A, p0, p1); } // 0x5AEFEC3A
	static void GET_PED_PARACHUTE_TINT_INDEX(Any p0, Any p1) { invoke<Void>(0xE9E7FAC5, p0, p1); } // 0xE9E7FAC5
	static void _0x177EFC79(Any p0, Any p1) { invoke<Void>(0x177EFC79, p0, p1); } // 0x177EFC79
	static void SET_PED_DUCKING(Any p0, Any p1) { invoke<Void>(0xB90353D7, p0, p1); } // 0xB90353D7
	static BOOL IS_PED_DUCKING(Any p0) { return invoke<BOOL>(0x9199C77D, p0); } // 0x9199C77D
	static BOOL IS_PED_IN_ANY_TAXI(Any p0) { return invoke<BOOL>(0x16FD386C, p0); } // 0x16FD386C
	static void SET_PED_ID_RANGE(Any p0, Any p1) { invoke<Void>(0xEF3B4ED9, p0, p1); } // 0xEF3B4ED9
	static void _0x9A2180FF(Any p0, Any p1) { invoke<Void>(0x9A2180FF, p0, p1); } // 0x9A2180FF
	static void _0xF30658D2(Any p0, Any p1) { invoke<Void>(0xF30658D2, p0, p1); } // 0xF30658D2
	static void _0x43709044(Any p0) { invoke<Void>(0x43709044, p0); } // 0x43709044
	static void SET_PED_SEEING_RANGE(Any p0, float p1) { invoke<Void>(0x4BD72FE8, p0, p1); } // 0x4BD72FE8
	static void SET_PED_HEARING_RANGE(Any p0, Any p1) { invoke<Void>(0xB32087E0, p0, p1); } // 0xB32087E0
	static void SET_PED_VISUAL_FIELD_MIN_ANGLE(Any p0, Any p1) { invoke<Void>(0x72E2E18B, p0, p1); } // 0x72E2E18B
	static void SET_PED_VISUAL_FIELD_MAX_ANGLE(Any p0, Any p1) { invoke<Void>(0x0CEA0F9A, p0, p1); } // 0x0CEA0F9A
	static void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Any p0, Any p1) { invoke<Void>(0x5CC2F1B8, p0, p1); } // 0x5CC2F1B8
	static void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Any p0, Any p1) { invoke<Void>(0x39D9102F, p0, p1); } // 0x39D9102F
	static void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Any p0, float p1) { invoke<Void>(0xFDF2F7C2, p0, p1); } // 0xFDF2F7C2
	static void _0xE57202A1(Any p0, Any p1) { invoke<Void>(0xE57202A1, p0, p1); } // 0xE57202A1
	static void SET_PED_STEALTH_MOVEMENT(Any p0, Any p1, Any p2) { invoke<Void>(0x67E28E1D, p0, p1, p2); } // 0x67E28E1D
	static Any GET_PED_STEALTH_MOVEMENT(Any p0) { return invoke<Any>(0x40321B83, p0); } // 0x40321B83
	static Any CREATE_GROUP(int Zombies) { return invoke<Any>(0x8DC0368D, Zombies); } // 0x8DC0368D
	static void SET_PED_AS_GROUP_LEADER(Ped PedHandle, int Zombies) { invoke<Void>(0x7265BEA2, PedHandle, Zombies); } // 0x7265BEA2
	static void SET_PED_AS_GROUP_MEMBER(Ped PedHandle, int groupId) { invoke<Void>(0x0EE13F92, PedHandle, groupId); } // 0x0EE13F92
	static void _0xD0D8BDBC(Any p0, Any p1, Any p2) { invoke<Void>(0xD0D8BDBC, p0, p1, p2); } // 0xD0D8BDBC
	static void REMOVE_GROUP(int Group) { invoke<Void>(0x48D72B88, Group); } // 0x48D72B88
	static void REMOVE_PED_FROM_GROUP(Ped PedHandle) { invoke<Void>(0x82697713, PedHandle); } // 0x82697713
	static BOOL IS_PED_GROUP_MEMBER(Ped PedHandle, int Group) { return invoke<BOOL>(0x876D5363, PedHandle, Group); } // 0x876D5363
	static Any _0x9678D4FF(Any p0) { return invoke<Any>(0x9678D4FF, p0); } // 0x9678D4FF
	static void SET_GROUP_SEPARATION_RANGE(Any p0, Any p1) { invoke<Void>(0x7B820CD5, p0, p1); } // 0x7B820CD5
	static void _0x2F0D0973(Any p0, Any p1) { invoke<Void>(0x2F0D0973, p0, p1); } // 0x2F0D0973
	static BOOL IS_PED_PRONE(Any p0) { return invoke<BOOL>(0x02C2A6C3, p0); } // 0x02C2A6C3
	static BOOL IS_PED_IN_COMBAT(Any p0, Any p1) { return invoke<BOOL>(0xFE027CB5, p0, p1); } // 0xFE027CB5
	static Any _0xCCD525E1(Any p0, Any p1) { return invoke<Any>(0xCCD525E1, p0, p1); } // 0xCCD525E1
	static BOOL IS_PED_DOING_DRIVEBY(Any p0) { return invoke<BOOL>(0xAC3CEB9C, p0); } // 0xAC3CEB9C
	static BOOL IS_PED_JACKING(Any p0) { return invoke<BOOL>(0x3B321816, p0); } // 0x3B321816
	static BOOL IS_PED_BEING_JACKED(Any p0) { return invoke<BOOL>(0xD45D605C, p0); } // 0xD45D605C
	static BOOL IS_PED_BEING_STUNNED(Any p0, Any p1) { return invoke<BOOL>(0x0A66CE30, p0, p1); } // 0x0A66CE30
	static Any GET_PEDS_JACKER(Any p0) { return invoke<Any>(0xDE1DBB59, p0); } // 0xDE1DBB59
	static Any GET_JACK_TARGET(Any p0) { return invoke<Any>(0x1D196361, p0); } // 0x1D196361
	static BOOL IS_PED_FLEEING(Any p0) { return invoke<BOOL>(0x85D813C6, p0); } // 0x85D813C6
	static BOOL IS_PED_IN_COVER(Any p0, Any p1) { return invoke<BOOL>(0x972C5A8B, p0, p1); } // 0x972C5A8B
	static BOOL IS_PED_IN_COVER_FACING_LEFT(Any p0) { return invoke<BOOL>(0xB89DBB80, p0); } // 0xB89DBB80
	static BOOL IS_PED_GOING_INTO_COVER(Any p0) { return invoke<BOOL>(0xA3589628, p0); } // 0xA3589628
	static Any SET_PED_PINNED_DOWN(Any p0, Any p1, Any p2) { return invoke<Any>(0xCC78999D, p0, p1, p2); } // 0xCC78999D
	static Any _0xACF162E0(Any p0) { return invoke<Any>(0xACF162E0, p0); } // 0xACF162E0
	static Any _0x99968B37(Any p0) { return invoke<Any>(0x99968B37, p0); } // 0x99968B37
	static Any _0x84ADF9EB(Any p0) { return invoke<Any>(0x84ADF9EB, p0); } // 0x84ADF9EB
	static Any GET_PED_CAUSE_OF_DEATH(Any p0) { return invoke<Any>(0x63458C27, p0); } // 0x63458C27
	static Any GET_PED_TIME_OF_DEATH(Any p0) { return invoke<Any>(0xDF6D5D54, p0); } // 0xDF6D5D54
	static Any _0xEF0B78E6(Any p0) { return invoke<Any>(0xEF0B78E6, p0); } // 0xEF0B78E6
	static Any _0xFB18CB19(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xFB18CB19, p0, p1, p2, p3, p4); } // 0xFB18CB19
	static void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Any p0, Any p1) { invoke<Void>(0x423B7BA2, p0, p1); } // 0x423B7BA2
	static void SET_PED_RELATIONSHIP_GROUP_HASH(Ped pedHandle, Any groupHandle) { invoke<Void>(0x79F8C18C, pedHandle, groupHandle); } // 0x79F8C18C
	static void SET_RELATIONSHIP_BETWEEN_GROUPS(int RelationStatus, Any Group1, Any Group2) { invoke<Void>(0xD4A215BA, RelationStatus, Group1, Group2); } // 0xD4A215BA
	static void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int RelationStatus, Any Group1, Any Group2) { invoke<Void>(0x994B8C2D, RelationStatus, Group1, Group2); } // 0x994B8C2D
	static Any ADD_RELATIONSHIP_GROUP(char* crewName, Any p1) { return invoke<Any>(0x8B635546, crewName, p1); } // 0x8B635546
	static void REMOVE_RELATIONSHIP_GROUP(Any p0) { invoke<Void>(0x4A1DC59A, p0); } // 0x4A1DC59A
	static int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2) { return invoke<int>(0xE254C39C, ped1, ped2); } // 0xE254C39C
	static Any GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Any p0) { return invoke<Any>(0x714BD6E4, p0); } // 0x714BD6E4
	static Any GET_PED_RELATIONSHIP_GROUP_HASH(Player playerId) { return invoke<Any>(0x354F283C, playerId); } // 0x354F283C
	static int GET_RELATIONSHIP_BETWEEN_GROUPS(Any p0, Any p1) { return invoke<int>(0x4E372FE2, p0, p1); } // 0x4E372FE2
	static void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Any p0, Any p1) { invoke<Void>(0x7FDDC0A6, p0, p1); } // 0x7FDDC0A6
	static void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Any p0, Any p1, Any p2) { invoke<Void>(0xD78AC46C, p0, p1, p2); } // 0xD78AC46C
	static BOOL IS_PED_RESPONDING_TO_EVENT(Any p0, Any p1) { return invoke<BOOL>(0x7A877554, p0, p1); } // 0x7A877554
	static void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash) { invoke<Void>(0xB4629D66, ped, patternHash); } // 0xB4629D66
	static void SET_PED_SHOOT_RATE(Ped ped, int shootRate) { invoke<Void>(0xFB301746, ped, shootRate); } // 0xFB301746
	static void SET_COMBAT_FLOAT(Any p0, Any p1, Any p2) { invoke<Void>(0xD8B7637C, p0, p1, p2); } // 0xD8B7637C
	static Any GET_COMBAT_FLOAT(Any p0, Any p1) { return invoke<Any>(0x511D7EF8, p0, p1); } // 0x511D7EF8
	static void GET_GROUP_SIZE(Any p0, Any p1, Any p2) { invoke<Void>(0xF7E1A691, p0, p1, p2); } // 0xF7E1A691
	static BOOL DOES_GROUP_EXIST(int Group) { return invoke<BOOL>(0x935C978D, Group); } // 0x935C978D
	static int GET_PED_GROUP_INDEX(Ped pedHandle) { return invoke<int>(0x134E0785, pedHandle); } // 0x134E0785
	static BOOL IS_PED_IN_GROUP(Ped pedHandle) { return invoke<BOOL>(0x836D9795, pedHandle); } // 0x836D9795
	static Any _0xDE7442EE(Any p0) { return invoke<Any>(0xDE7442EE, p0); } // 0xDE7442EE
	static void SET_GROUP_FORMATION(int group, int formationType) { invoke<Void>(0x08FAC739, group, formationType); } // 0x08FAC739
	static void SET_GROUP_FORMATION_SPACING(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB1E086FF, p0, p1, p2, p3); } // 0xB1E086FF
	static void _0x267FCEAD(Any p0) { invoke<Void>(0x267FCEAD, p0); } // 0x267FCEAD
	static Vehicle GET_VEHICLE_PED_IS_USING(Ped PedHandle) { return invoke<Vehicle>(0x6DE3AADA, PedHandle); } // 0x6DE3AADA
	static Any SET_EXCLUSIVE_PHONE_RELATIONSHIPS(Any p0) { return invoke<Any>(0x56E0C163, p0); } // 0x56E0C163
	static void SET_PED_GRAVITY(Any p0, Any p1) { invoke<Void>(0x3CA16652, p0, p1); } // 0x3CA16652
	static void APPLY_DAMAGE_TO_PED(Ped pedHandle, Any damageAmount, BOOL p2) { invoke<Void>(0x4DC27FCF, pedHandle, damageAmount, p2); } // 0x4DC27FCF
	static void SET_PED_ALLOWED_TO_DUCK(Any p0, Any p1) { invoke<Void>(0xC4D122F8, p0, p1); } // 0xC4D122F8
	static void SET_PED_NEVER_LEAVES_GROUP(Ped PedHandle, int Group) { invoke<Void>(0x0E038813, PedHandle, Group); } // 0x0E038813
	static Any GET_PED_TYPE(Ped PedHandle) { return invoke<Any>(0xB1460D43, PedHandle); } // 0xB1460D43
	static void SET_PED_AS_COP(int PedHandle, BOOL Toggle) { invoke<Void>(0x84E7DE9F, PedHandle, Toggle); } // 0x84E7DE9F
	static void SET_PED_MAX_HEALTH(Any p0, Any p1) { invoke<Void>(0x5533F60B, p0, p1); } // 0x5533F60B
	static Any GET_PED_MAX_HEALTH(Any p0) { return invoke<Any>(0xA45B6C8D, p0); } // 0xA45B6C8D
	static void SET_PED_MAX_TIME_IN_WATER(Any p0, Any p1) { invoke<Void>(0xFE0A106B, p0, p1); } // 0xFE0A106B
	static void SET_PED_MAX_TIME_UNDERWATER(Any p0, Any p1) { invoke<Void>(0x082EF240, p0, p1); } // 0x082EF240
	static void _0x373CC405(Any p0, Any p1) { invoke<Void>(0x373CC405, p0, p1); } // 0x373CC405
	static void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped PedHandle, int p1) { invoke<Void>(0x8A251612, PedHandle, p1); } // 0x8A251612
	static Any _0xC9D098B3(Any p0) { return invoke<Any>(0xC9D098B3, p0); } // 0xC9D098B3
	static void KNOCK_PED_OFF_VEHICLE(Ped PedHandle) { invoke<Void>(0xACDD0674, PedHandle); } // 0xACDD0674
	static void SET_PED_COORDS_NO_GANG(Ped ped, float XCoord, float YCoord, float ZCoord) { invoke<Void>(0x9561AD98, ped, XCoord, YCoord, ZCoord); } // 0x9561AD98
	static Any GET_PED_AS_GROUP_MEMBER(Any p0, Any p1) { return invoke<Any>(0x9AA3CC8C, p0, p1); } // 0x9AA3CC8C
	static void SET_PED_KEEP_TASK(Ped ped, BOOL Toggle) { invoke<Void>(0xA7EC79CE, ped, Toggle); } // 0xA7EC79CE
	static void _0x397F06E3(Any p0, Any p1) { invoke<Void>(0x397F06E3, p0, p1); } // 0x397F06E3
	static BOOL IS_PED_SWIMMING(Any p0) { return invoke<BOOL>(0x7AB43DB8, p0); } // 0x7AB43DB8
	static BOOL IS_PED_SWIMMING_UNDER_WATER(Any p0) { return invoke<BOOL>(0x0E8D524F, p0); } // 0x0E8D524F
	static void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float XCoord, float YCoord, float ZCoord) { invoke<Void>(0xD66AE1D3, ped, XCoord, YCoord, ZCoord); } // 0xD66AE1D3
	static void SET_PED_DIES_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x6FE1E440, p0, p1); } // 0x6FE1E440
	static void SET_CREATE_RANDOM_COPS(Any p0) { invoke<Void>(0x23441648, p0); } // 0x23441648
	static void _0x82E548CC(Any p0) { invoke<Void>(0x82E548CC, p0); } // 0x82E548CC
	static void _0xEDC31475(Any p0) { invoke<Void>(0xEDC31475, p0); } // 0xEDC31475
	static BOOL CAN_CREATE_RANDOM_COPS() { return invoke<BOOL>(0xAA73DAD9); } // 0xAA73DAD9
	static void SET_PED_AS_ENEMY(Ped pedHandle, BOOL p1) { invoke<Void>(0xAE620A1B, pedHandle, p1); } // 0xAE620A1B
	static void SET_PED_CAN_SMASH_GLASS(Any p0, Any p1, Any p2) { invoke<Void>(0x149C60A8, p0, p1, p2); } // 0x149C60A8
	static BOOL IS_PED_IN_ANY_TRAIN(Any p0) { return invoke<BOOL>(0x759EF63A, p0); } // 0x759EF63A
	static BOOL IS_PED_GETTING_INTO_A_VEHICLE(int playerID) { return invoke<BOOL>(0x90E805AC, playerID); } // 0x90E805AC
	static BOOL IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Any p0) { return invoke<BOOL>(0x46828B4E, p0); } // 0x46828B4E
	static void SET_ENABLE_HANDCUFFS(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xAC9BBA23, PedHandle, Toggle); } // 0xAC9BBA23
	static void SET_ENABLE_BOUND_ANKLES(Any p0, Any p1) { invoke<Void>(0x9208D689, p0, p1); } // 0x9208D689
	static void _0x7BF61471(Any p0, Any p1) { invoke<Void>(0x7BF61471, p0, p1); } // 0x7BF61471
	static void SET_CAN_ATTACK_FRIENDLY(Player p0, Ped p1, Any p2) { invoke<Void>(0x47C60963, p0, p1, p2); } // 0x47C60963
	static Any GET_PED_ALERTNESS(Any p0) { return invoke<Any>(0xF83E4DAF, p0); } // 0xF83E4DAF
	static void SET_PED_ALERTNESS(Any p0, Any p1) { invoke<Void>(0x2C32D9AE, p0, p1); } // 0x2C32D9AE
	static void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x89AD49FF, p0, p1); } // 0x89AD49FF
	static void SET_PED_MOVEMENT_CLIPSET(Any p0, char* p1, Any p2) { invoke<Void>(0xA817CDEB, p0, p1, p2); } // 0xA817CDEB
	static void RESET_PED_MOVEMENT_CLIPSET(Any p0, Any p1) { invoke<Void>(0xB83CEE93, p0, p1); } // 0xB83CEE93
	static void SET_PED_STRAFE_CLIPSET(Any p0, Any p1) { invoke<Void>(0x0BACF010, p0, p1); } // 0x0BACF010
	static void RESET_PED_STRAFE_CLIPSET(Any p0) { invoke<Void>(0xF1967A12, p0); } // 0xF1967A12
	static void SET_PED_WEAPON_MOVEMENT_CLIPSET(Any p0, Any p1) { invoke<Void>(0xF8BE54DC, p0, p1); } // 0xF8BE54DC
	static void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Any p0) { invoke<Void>(0xC60C9ACD, p0); } // 0xC60C9ACD
	static void _0xD4C73595(Any p0, Any p1) { invoke<Void>(0xD4C73595, p0, p1); } // 0xD4C73595
	static void _0xAEC9163B(Any p0) { invoke<Void>(0xAEC9163B, p0); } // 0xAEC9163B
	static void SET_PED_IN_VEHICLE_CONTEXT(Any p0, Any p1) { invoke<Void>(0x27F25C0E, p0, p1); } // 0x27F25C0E
	static void RESET_PED_IN_VEHICLE_CONTEXT(Any p0) { invoke<Void>(0x3C94D88A, p0); } // 0x3C94D88A
	static Any _0x3C30B447(Any p0, Any p1, Any p2) { return invoke<Any>(0x3C30B447, p0, p1, p2); } // 0x3C30B447
	static void _0x895E1D67(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x895E1D67, p0, p1, p2, p3, p4); } // 0x895E1D67
	static void _0x5736FB23(Any p0, Any p1) { invoke<Void>(0x5736FB23, p0, p1); } // 0x5736FB23
	static void SET_PED_ALTERNATE_MOVEMENT_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xBA84FD8C, p0, p1, p2, p3, p4, p5); } // 0xBA84FD8C
	static void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Any p0, Any p1, Any p2) { invoke<Void>(0x7A7F5BC3, p0, p1, p2); } // 0x7A7F5BC3
	static void SET_PED_GESTURE_GROUP(Any p0, Any p1) { invoke<Void>(0x170DA109, p0, p1); } // 0x170DA109
	static vec3_t _0xC59D4268(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<vec3_t>(0xC59D4268, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xC59D4268
	static vec3_t _0x5F7789E6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<vec3_t>(0x5F7789E6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x5F7789E6
	static int GET_PED_DRAWABLE_VARIATION(Ped pedID, int componentID) { return invoke<int>(0x29850FE2, pedID, componentID); } // 0x29850FE2
	static int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped pedID, int componentID) { return invoke<int>(0x9754C27D, pedID, componentID); } // 0x9754C27D
	static int GET_PED_TEXTURE_VARIATION(Ped pedID, int componentID) { return invoke<int>(0xC0A8590A, pedID, componentID); } // 0xC0A8590A
	static int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped pedID, int componentID, int drawableID) { return invoke<int>(0x83D9FBE7, pedID, componentID, drawableID); } // 0x83D9FBE7
	static int _0xC9780B95(Any p0, Any p1) { return invoke<int>(0xC9780B95, p0, p1); } // 0xC9780B95
	static Any REMOVE_NIGHTVISION_MELEE(Any p0, Any p1, Any p2) { return invoke<Any>(0x4892B882, p0, p1, p2); } // 0x4892B882
	static int GET_PED_PALETTE_VARIATION(Any p0, Any p1) { return invoke<int>(0xEF1BC082, p0, p1); } // 0xEF1BC082
	static BOOL IS_PED_COMPONENT_VARIATION_VALID(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x952ABD9A, p0, p1, p2, p3); } // 0x952ABD9A
	static void SET_PED_COMPONENT_VARIATION(Ped PedHandle, int componentID, int drawableID, int textureID, int paletteID) { invoke<Void>(0xD4F7B05C, PedHandle, componentID, drawableID, textureID, paletteID); } // 0xD4F7B05C
	static void SET_PED_RANDOM_COMPONENT_VARIATION(Ped pedHandle, BOOL p1) { invoke<Void>(0x4111BA46, pedHandle, p1); } // 0x4111BA46
	static void SET_PED_RANDOM_PROPS(Ped PedHandle) { invoke<Void>(0xE3318E0E, PedHandle); } // 0xE3318E0E
	static void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped PedHandle) { invoke<Void>(0xC866A984, PedHandle); } // 0xC866A984
	static void SET_PED_BLEND_FROM_PARENTS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x837BD370, p0, p1, p2, p3, p4); } // 0x837BD370
	static void _0xC21C8A56(Any p0) { invoke<Void>(0xC21C8A56, p0); } // 0xC21C8A56
	static void _0x5D2FC042(Any p0, Any p1, Any p2) { invoke<Void>(0x5D2FC042, p0, p1, p2); } // 0x5D2FC042
	static void SET_PED_HEAD_BLEND_DATA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x60746B88, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x60746B88
	static void UPDATE_PED_HEAD_BLEND_DATA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5CB76219, p0, p1, p2, p3); } // 0x5CB76219
	static void SET_PED_HEAD_OVERLAY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD28DBA90, p0, p1, p2, p3); } // 0xD28DBA90
	static Any _0xFF43C18D(Any p0) { return invoke<Any>(0xFF43C18D, p0); } // 0xFF43C18D
	static BOOL HAS_PED_HEAD_BLEND_FINISHED(Any p0) { return invoke<BOOL>(0x2B1BD9C5, p0); } // 0x2B1BD9C5
	static void _0x894314A4(Any p0) { invoke<Void>(0x894314A4, p0); } // 0x894314A4
	static void _0x57E5B3F9(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x57E5B3F9, p0, p1, p2, p3, p4); } // 0x57E5B3F9
	static void _0xC6F36292(Any p0) { invoke<Void>(0xC6F36292, p0); } // 0xC6F36292
	static Any _0x211DEFEC(Any p0) { return invoke<Any>(0x211DEFEC, p0); } // 0x211DEFEC
	static Any _0x095D3BD8(Any p0) { return invoke<Any>(0x095D3BD8, p0); } // 0x095D3BD8
	static void _0x45F3BDFB(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x45F3BDFB, p0, p1, p2, p3); } // 0x45F3BDFB
	static Any _0xC6517D52(Any p0) { return invoke<Any>(0xC6517D52, p0); } // 0xC6517D52
	static void _0x6435F67F(Any p0) { invoke<Void>(0x6435F67F, p0); } // 0x6435F67F
	static void _0xC0E23671(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC0E23671, p0, p1, p2, p3); } // 0xC0E23671
	static Any _0x3B0CA391(Any p0) { return invoke<Any>(0x3B0CA391, p0); } // 0x3B0CA391
	static void _0xFD103BA7(Any p0) { invoke<Void>(0xFD103BA7, p0); } // 0xFD103BA7
	static Any GET_PED_PROP_INDEX(Ped PedHandle, int ComponentID) { return invoke<Any>(0x746DDAC0, PedHandle, ComponentID); } // 0x746DDAC0
	static void SET_PED_PROP_INDEX(Ped PedHandle, int ComponentID, int drawableID, int TextureID, int PaletteID) { invoke<Void>(0x0829F2E2, PedHandle, ComponentID, drawableID, TextureID, PaletteID); } // 0x0829F2E2
	static void KNOCK_OFF_PED_PROP(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x08D8B180, p0, p1, p2, p3, p4); } // 0x08D8B180
	static void CLEAR_PED_PROP(Ped PedHandle, int PropID) { invoke<Void>(0x2D23D743, PedHandle, PropID); } // 0x2D23D743
	static void CLEAR_ALL_PED_PROPS(Ped PedHandle) { invoke<Void>(0x81DF8B43, PedHandle); } // 0x81DF8B43
	static Any GET_PED_PROP_TEXTURE_INDEX(Any p0, Any p1) { return invoke<Any>(0x922A6653, p0, p1); } // 0x922A6653
	static void _0x7BCD8991(Any p0) { invoke<Void>(0x7BCD8991, p0); } // 0x7BCD8991
	static void _0x080275EE(Any p0) { invoke<Void>(0x080275EE, p0); } // 0x080275EE
	static void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Any p0, Any p1) { invoke<Void>(0xDFE34E4A, p0, p1); } // 0xDFE34E4A
	static void SET_PED_BOUNDS_ORIENTATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xCFA20D68, p0, p1, p2, p3, p4, p5); } // 0xCFA20D68
	static void REGISTER_TARGET(Any p0, Any p1) { invoke<Void>(0x50A95442, p0, p1); } // 0x50A95442
	static void REGISTER_HATED_TARGETS_AROUND_PED(Ped PedHandle, float AreaToAttack) { invoke<Void>(0x7F87559E, PedHandle, AreaToAttack); } // 0x7F87559E
	static Ped GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int p6) { return invoke<Ped>(0xDC8239EB, x, y, z, xRadius, yRadius, zRadius, p6); } // 0xDC8239EB
	static Ped GET_CLOSEST_PED(float x, float y, float z, float Radius, BOOL p4, BOOL p5, int handle, BOOL p7, BOOL p8, int p9) { return invoke<Ped>(0x8F6C1F55, x, y, z, Radius, p4, p5, handle, p7, p8, p9); } // 0x8F6C1F55
	static void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(Any p0) { invoke<Void>(0x85615FD0, p0); } // 0x85615FD0
	static Any _0x18DD76A1(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0x18DD76A1, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x18DD76A1
	static void _0x6D55B3B3(Any p0, Any p1) { invoke<Void>(0x6D55B3B3, p0, p1); } // 0x6D55B3B3
	static void SET_DRIVER_ABILITY(Any p0, Any p1) { invoke<Void>(0xAAD4012C, p0, p1); } // 0xAAD4012C
	static void SET_DRIVER_AGGRESSIVENESS(Any p0, Any p1) { invoke<Void>(0x8B02A8FB, p0, p1); } // 0x8B02A8FB
	static BOOL CAN_PED_RAGDOLL(Any p0) { return invoke<BOOL>(0xC0EFB7A3, p0); } // 0xC0EFB7A3
	static Any SET_PED_TO_RAGDOLL(Ped ped, int Xforce, int Yforce, int Zforce, BOOL p4, BOOL p5, BOOL p6) { return invoke<Any>(0x83CB5052, ped, Xforce, Yforce, Zforce, p4, p5, p6); } // 0x83CB5052
	static Any SET_PED_TO_RAGDOLL_WITH_FALL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return invoke<Any>(0xFA12E286, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 0xFA12E286
	static void SET_PED_RAGDOLL_ON_COLLISION(Ped PedHandle, BOOL Toggle) { invoke<Void>(0x2654A0F4, PedHandle, Toggle); } // 0x2654A0F4
	static BOOL IS_PED_RAGDOLL(Any p0) { return invoke<BOOL>(0xC833BBE1, p0); } // 0xC833BBE1
	static BOOL IS_PED_RUNNING_RAGDOLL_TASK(Any p0) { return invoke<BOOL>(0x44A153F2, p0); } // 0x44A153F2
	static void SET_PED_RAGDOLL_FORCE_FALL(Ped ped) { invoke<Void>(0x20A5BDE0, ped); } // 0x20A5BDE0
	static void RESET_PED_RAGDOLL_TIMER(Any p0) { invoke<Void>(0xF2865370, p0); } // 0xF2865370
	static void SET_PED_CAN_RAGDOLL(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xCF1384C4, PedHandle, Toggle); } // 0xCF1384C4
	static BOOL IS_PED_RUNNING_MOBILE_PHONE_TASK(Any p0) { return invoke<BOOL>(0xFB2AFED1, p0); } // 0xFB2AFED1
	static Any _0x97353375(Any p0) { return invoke<Any>(0x97353375, p0); } // 0x97353375
	static void _0x9C8F830D(Any p0, Any p1) { invoke<Void>(0x9C8F830D, p0, p1); } // 0x9C8F830D
	static void _0x77CBA290(Any p0, Any p1) { invoke<Void>(0x77CBA290, p0, p1); } // 0x77CBA290
	static void SET_PED_ANGLED_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x3EFBDD9B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x3EFBDD9B
	static void SET_PED_SPHERE_DEFENSIVE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xBD96D8E8, p0, p1, p2, p3, p4, p5, p6); } // 0xBD96D8E8
	static void _0x40638BDC(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x40638BDC, p0, p1, p2, p3, p4, p5, p6); } // 0x40638BDC
	static void _0x4763B2C6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x4763B2C6, p0, p1, p2, p3, p4, p5, p6); } // 0x4763B2C6
	static void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x74BDA7CE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x74BDA7CE
	static void _0xB66B0C9A(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xB66B0C9A, p0, p1, p2, p3, p4); } // 0xB66B0C9A
	static void REMOVE_PED_DEFENSIVE_AREA(Any p0, Any p1) { invoke<Void>(0x34AAAFA5, p0, p1); } // 0x34AAAFA5
	static vec3_t GET_PED_DEFENSIVE_AREA_POSITION(Any p0, Any p1) { return invoke<vec3_t>(0xCB65198D, p0, p1); } // 0xCB65198D
	static void _0xF3B7EFBF(Any p0, Any p1) { invoke<Void>(0xF3B7EFBF, p0, p1); } // 0xF3B7EFBF
	static void _0xA0134498(Any p0) { invoke<Void>(0xA0134498, p0); } // 0xA0134498
	static void REVIVE_INJURED_PED(Any p0) { invoke<Void>(0x14D3E6E3, p0); } // 0x14D3E6E3
	static void RESURRECT_PED(Any p0) { invoke<Void>(0xA4B82097, p0); } // 0xA4B82097
	static void SET_PED_NAME_DEBUG(Any p0, Any p1) { invoke<Void>(0x20D6273E, p0, p1); } // 0x20D6273E
	static vec3_t GET_PED_EXTRACTED_DISPLACEMENT(Any p0, Any p1) { return invoke<vec3_t>(0x5231F901, p0, p1); } // 0x5231F901
	static void SET_PED_DIES_WHEN_INJURED(Ped ped, BOOL toggle) { invoke<Void>(0xE94E24D4, ped, toggle); } // 0xE94E24D4
	static void SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, BOOL toggle) { invoke<Void>(0x4CAD1A4A, ped, toggle); } // 0x4CAD1A4A
	static void _0x141CC936(Any p0, Any p1) { invoke<Void>(0x141CC936, p0, p1); } // 0x141CC936
	static void RESET_PED_VISIBLE_DAMAGE(Ped ped) { invoke<Void>(0xC4BC4841, ped); } // 0xC4BC4841
	static void _0x1E54DB12(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x1E54DB12, p0, p1, p2, p3, p4); } // 0x1E54DB12
	static void APPLY_PED_BLOOD(Ped ped, int i1, float f1, float f2, float f3, char* s1) { invoke<Void>(0x376CE3C0, ped, i1, f1, f2, f3, s1); } // 0x376CE3C0
	static void _0x8F3F3A9C(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x8F3F3A9C, p0, p1, p2, p3, p4); } // 0x8F3F3A9C
	static void _0xFC13CE80(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xFC13CE80, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFC13CE80
	static void APPLY_PED_DAMAGE_DECAL(Ped p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, BOOL p8, char* p9) { invoke<Void>(0x8A13A41F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x8A13A41F
	static void APPLY_PED_DAMAGE_PACK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x208D0CB8, p0, p1, p2, p3); } // 0x208D0CB8
	static void CLEAR_PED_BLOOD_DAMAGE(Ped PedHandle) { invoke<Void>(0xF7ADC960, PedHandle); } // 0xF7ADC960
	static void _0xF210BE69(Ped p0, int p1) { invoke<Void>(0xF210BE69, p0, p1); } // 0xF210BE69
	static void _0x0CB6C4ED(Any p0, Any p1, Any p2) { invoke<Void>(0x0CB6C4ED, p0, p1, p2); } // 0x0CB6C4ED
	static void _0x70AA5B7D(Any p0, Any p1, Any p2) { invoke<Void>(0x70AA5B7D, p0, p1, p2); } // 0x70AA5B7D
	static Any _0x47187F7F(Any p0) { return invoke<Any>(0x47187F7F, p0); } // 0x47187F7F
	static void CLEAR_PED_WETNESS(Ped ped) { invoke<Void>(0x629F15BD, ped); } // 0x629F15BD
	static void SET_PED_WETNESS_HEIGHT(Ped ped, float height) { invoke<Void>(0x7B33289A, ped, height); } // 0x7B33289A
	static void SET_PED_WETNESS_ENABLED_THIS_FRAME(Any p0) { invoke<Void>(0xBDE749F7, p0); } // 0xBDE749F7
	static void _0xA993915F(Ped ped) { invoke<Void>(0xA993915F, ped); } // 0xA993915F
	static void SET_PED_SWEAT(Ped ped, float sweat) { invoke<Void>(0x76A1DB9F, ped, sweat); } // 0x76A1DB9F
	static void _0x70559AC7(Ped ped, Hash ShirtType, Hash ShirtDecal) { invoke<Void>(0x70559AC7, ped, ShirtType, ShirtDecal); } // 0x70559AC7
	static Any _0x3543019E(Any p0, Any p1) { return invoke<Any>(0x3543019E, p0, p1); } // 0x3543019E
	static void CLEAR_PED_DECORATIONS(Ped PedHandle) { invoke<Void>(0xD4496BF3, PedHandle); } // 0xD4496BF3
	static void _0xEFD58EB9(Any p0) { invoke<Void>(0xEFD58EB9, p0); } // 0xEFD58EB9
	static BOOL WAS_PED_SKELETON_UPDATED(Any p0) { return invoke<BOOL>(0xF7E2FBAD, p0); } // 0xF7E2FBAD
	static vec3_t GET_PED_BONE_COORDS(Ped ped, int i1, float f1, float f2, float f3) { return invoke<vec3_t>(0x4579CAB1, ped, i1, f1, f2, f3); } // 0x4579CAB1
	static void CREATE_NM_MESSAGE(Any p0, Any p1) { invoke<Void>(0x1CFBFD4B, p0, p1); } // 0x1CFBFD4B
	static void GIVE_PED_NM_MESSAGE(Any p0) { invoke<Void>(0x737C3689, p0); } // 0x737C3689
	static Any ADD_SCENARIO_BLOCKING_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xA38C0234, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA38C0234
	static void REMOVE_SCENARIO_BLOCKING_AREAS() { invoke<Void>(0x4DDF845F); } // 0x4DDF845F
	static void REMOVE_SCENARIO_BLOCKING_AREA(Any p0, Any p1) { invoke<Void>(0x4483EF06, p0, p1); } // 0x4483EF06
	static void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x80EAD297, p0, p1, p2, p3, p4); } // 0x80EAD297
	static BOOL IS_PED_USING_SCENARIO(Any p0, Any p1) { return invoke<BOOL>(0x0F65B0D4, p0, p1); } // 0x0F65B0D4
	static BOOL IS_PED_USING_ANY_SCENARIO(Any p0) { return invoke<BOOL>(0x195EF5B7, p0); } // 0x195EF5B7
	static Any _0x59DE73AC(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x59DE73AC, p0, p1, p2, p3); } // 0x59DE73AC
	static void _0xC08FE5F6(Any p0, Any p1) { invoke<Void>(0xC08FE5F6, p0, p1); } // 0xC08FE5F6
	static Any _0x58C0F6CF(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x58C0F6CF, p0, p1, p2, p3); } // 0x58C0F6CF
	static Any _0x761F8F48(Any p0, Any p1) { return invoke<Any>(0x761F8F48, p0, p1); } // 0x761F8F48
	static void _0x033F43FA(Any p0) { invoke<Void>(0x033F43FA, p0); } // 0x033F43FA
	static void _0x4C684C81(Any p0) { invoke<Void>(0x4C684C81, p0); } // 0x4C684C81
	static Any _0x7B4C3E6F(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x7B4C3E6F, p0, p1, p2, p3); } // 0x7B4C3E6F
	static void _0x5BC276AE(Any p0, Any p1) { invoke<Void>(0x5BC276AE, p0, p1); } // 0x5BC276AE
	static void PLAY_FACIAL_ANIM(Any p0, Any p1, Any p2) { invoke<Void>(0x1F6CCDDE, p0, p1, p2); } // 0x1F6CCDDE
	static void SET_FACIAL_IDLE_ANIM_OVERRIDE(Any p0, Any p1, Any p2) { invoke<Void>(0x9BA19C13, p0, p1, p2); } // 0x9BA19C13
	static void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Any p0) { invoke<Void>(0x5244F4E2, p0); } // 0x5244F4E2
	static void SET_PED_CAN_PLAY_GESTURE_ANIMS(Any p0, Any p1) { invoke<Void>(0xE131E3B3, p0, p1); } // 0xE131E3B3
	static void SET_PED_CAN_PLAY_VISEME_ANIMS(Any p0, Any p1, Any p2) { invoke<Void>(0xA2FDAF27, p0, p1, p2); } // 0xA2FDAF27
	static void _0xADB2511A(Any p0, Any p1) { invoke<Void>(0xADB2511A, p0, p1); } // 0xADB2511A
	static void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Any p0, Any p1) { invoke<Void>(0xF8053081, p0, p1); } // 0xF8053081
	static void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Any p0, Any p1) { invoke<Void>(0x5720A5DD, p0, p1); } // 0x5720A5DD
	static void _0xB7CD0A49(Any p0) { invoke<Void>(0xB7CD0A49, p0); } // 0xB7CD0A49
	static void _0x343B4DE0(Any p0, Any p1) { invoke<Void>(0x343B4DE0, p0, p1); } // 0x343B4DE0
	static void SET_PED_CAN_HEAD_IK(Any p0, Any p1) { invoke<Void>(0xD3B04476, p0, p1); } // 0xD3B04476
	static void SET_PED_CAN_LEG_IK(Any p0, Any p1) { invoke<Void>(0x9955BC6F, p0, p1); } // 0x9955BC6F
	static void _0x8E5D4EAB(Any p0, Any p1) { invoke<Void>(0x8E5D4EAB, p0, p1); } // 0x8E5D4EAB
	static void _0x7B0040A8(Any p0, Any p1) { invoke<Void>(0x7B0040A8, p0, p1); } // 0x7B0040A8
	static void _0x0FDA62DE(Any p0, Any p1) { invoke<Void>(0x0FDA62DE, p0, p1); } // 0x0FDA62DE
	static void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Any p0, Any p1) { invoke<Void>(0x584C5178, p0, p1); } // 0x584C5178
	static BOOL IS_PED_HEADTRACKING_PED(Any p0, Any p1) { return invoke<BOOL>(0x2A5DF721, p0, p1); } // 0x2A5DF721
	static BOOL IS_PED_HEADTRACKING_ENTITY(Any p0, Any p1) { return invoke<BOOL>(0x233C9ACF, p0, p1); } // 0x233C9ACF
	static void SET_PED_PRIMARY_LOOKAT(Any p0, Any p1) { invoke<Void>(0x6DEF6F1C, p0, p1); } // 0x6DEF6F1C
	static void _0xFC942D7C(Any p0, Any p1) { invoke<Void>(0xFC942D7C, p0, p1); } // 0xFC942D7C
	static void _0x89EEE07B(Any p0, Any p1) { invoke<Void>(0x89EEE07B, p0, p1); } // 0x89EEE07B
	static void SET_PED_CONFIG_FLAG(Any p0, Any p1, Any p2) { invoke<Void>(0x9CFBE10D, p0, p1, p2); } // 0x9CFBE10D
	static void SET_PED_RESET_FLAG(Any p0, Any p1, Any p2) { invoke<Void>(0xCFF6FF66, p0, p1, p2); } // 0xCFF6FF66
	static Any GET_PED_CONFIG_FLAG(Any p0, Any p1, Any p2) { return invoke<Any>(0xABE98267, p0, p1, p2); } // 0xABE98267
	static Any GET_PED_RESET_FLAG(Any p0, Any p1) { return invoke<Any>(0x2FC10D11, p0, p1); } // 0x2FC10D11
	static void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Any p0, Any p1) { invoke<Void>(0x2AB3670B, p0, p1); } // 0x2AB3670B
	static void SET_PED_CAN_EVASIVE_DIVE(Any p0, Any p1) { invoke<Void>(0x542FEB4D, p0, p1); } // 0x542FEB4D
	static BOOL IS_PED_EVASIVE_DIVING(Any p0, Any p1) { return invoke<BOOL>(0xD82829DC, p0, p1); } // 0xD82829DC
	static void SET_PED_SHOOTS_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xFD64EAE5, p0, p1, p2, p3, p4); } // 0xFD64EAE5
	static void SET_PED_MODEL_IS_SUPPRESSED(Any p0, Any p1) { invoke<Void>(0x7820CA43, p0, p1); } // 0x7820CA43
	static void STOP_ANY_PED_MODEL_BEING_SUPPRESSED() { invoke<Void>(0x5AD7DC55); } // 0x5AD7DC55
	static void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Any p0, Any p1) { invoke<Void>(0x6FD9A7CD, p0, p1); } // 0x6FD9A7CD
	static void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, BOOL Toggle) { invoke<Void>(0xE9B97A2B, ped, Toggle); } // 0xE9B97A2B
	static void _0xFF1F6AEB(Any p0, Any p1) { invoke<Void>(0xFF1F6AEB, p0, p1); } // 0xFF1F6AEB
	static void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Any p0, Any p1) { invoke<Void>(0xE9BD733A, p0, p1); } // 0xE9BD733A
	static void GIVE_PED_HELMET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1862A461, p0, p1, p2, p3); } // 0x1862A461
	static void REMOVE_PED_HELMET(Any p0, Any p1) { invoke<Void>(0x2086B1F0, p0, p1); } // 0x2086B1F0
	static void SET_PED_HELMET(Any p0, Any p1) { invoke<Void>(0xED366E53, p0, p1); } // 0xED366E53
	static void SET_PED_HELMET_FLAG(Any p0, Any p1) { invoke<Void>(0x12677780, p0, p1); } // 0x12677780
	static void SET_PED_HELMET_PROP_INDEX(Any p0, Any p1) { invoke<Void>(0xA316D13F, p0, p1); } // 0xA316D13F
	static void SET_PED_HELMET_TEXTURE_INDEX(Any p0, Any p1) { invoke<Void>(0x5F6C3328, p0, p1); } // 0x5F6C3328
	static BOOL IS_PED_WEARING_HELMET(Ped PedHandle) { return invoke<BOOL>(0x0D680D49, PedHandle); } // 0x0D680D49
	static void _0x24A1284E(Any p0) { invoke<Void>(0x24A1284E, p0); } // 0x24A1284E
	static Any _0x8A3A3116(Any p0) { return invoke<Any>(0x8A3A3116, p0); } // 0x8A3A3116
	static Any _0x74EB662D(Any p0) { return invoke<Any>(0x74EB662D, p0); } // 0x74EB662D
	static Any _0xFFF149FE(Any p0) { return invoke<Any>(0xFFF149FE, p0); } // 0xFFF149FE
	static void SET_PED_TO_LOAD_COVER(Any p0, Any p1) { invoke<Void>(0xCF94BA97, p0, p1); } // 0xCF94BA97
	static void SET_PED_CAN_COWER_IN_COVER(Any p0, Any p1) { invoke<Void>(0x5194658B, p0, p1); } // 0x5194658B
	static void SET_PED_CAN_PEEK_IN_COVER(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xC1DAE216, PedHandle, Toggle); } // 0xC1DAE216
	static void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Any p0, Any p1) { invoke<Void>(0x7C563CD2, p0, p1); } // 0x7C563CD2
	static void SET_PED_LEG_IK_MODE(Any p0, Any p1) { invoke<Void>(0xFDDB042E, p0, p1); } // 0xFDDB042E
	static void SET_PED_MOTION_BLUR(Any p0, Any p1) { invoke<Void>(0xA211A128, p0, p1); } // 0xA211A128
	static void SET_PED_CAN_SWITCH_WEAPON(int PedID, BOOL CAN_SWITCH) { invoke<Void>(0xB5F8BA28, PedID, CAN_SWITCH); } // 0xB5F8BA28
	static void SET_PED_DIES_INSTANTLY_IN_WATER(Ped PedHandle, BOOL Toggle) { invoke<Void>(0xFE2554FC, PedHandle, Toggle); } // 0xFE2554FC
	static void _0x77BB7CB8(Any p0, Any p1) { invoke<Void>(0x77BB7CB8, p0, p1); } // 0x77BB7CB8
	static void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Any p0) { invoke<Void>(0x4AC3421E, p0); } // 0x4AC3421E
	static void SET_SCRIPTED_ANIM_SEAT_OFFSET(Any p0, Any p1) { invoke<Void>(0x7CEFFA45, p0, p1); } // 0x7CEFFA45
	static void SET_PED_COMBAT_MOVEMENT(Any p0, Any p1) { invoke<Void>(0x12E62F9E, p0, p1); } // 0x12E62F9E
	static Any GET_PED_COMBAT_MOVEMENT(Any p0) { return invoke<Any>(0xF3E7730E, p0); } // 0xF3E7730E
	static void SET_PED_COMBAT_ABILITY(Ped ped, int p1) { invoke<Void>(0x6C23D329, ped, p1); } // 0x6C23D329
	static void SET_PED_COMBAT_RANGE(Ped ped, float range) { invoke<Void>(0x8818A959, ped, range); } // 0x8818A959
	static Any GET_PED_COMBAT_RANGE(Any p0) { return invoke<Any>(0x9B9B7163, p0); } // 0x9B9B7163
	static void SET_PED_COMBAT_ATTRIBUTES(Any p0, Any p1, Any p2) { invoke<Void>(0x81D64248, p0, p1, p2); } // 0x81D64248
	static void SET_PED_TARGET_LOSS_RESPONSE(Any p0, Any p1) { invoke<Void>(0xCFA613FF, p0, p1); } // 0xCFA613FF
	static Any _0x139C0875(Any p0) { return invoke<Any>(0x139C0875, p0); } // 0x139C0875
	static BOOL IS_PED_PERFORMING_STEALTH_KILL(Any p0) { return invoke<BOOL>(0x9ADD7B21, p0); } // 0x9ADD7B21
	static BOOL _0x9BE7C860(Ped PedHandle) { return invoke<BOOL>(0x9BE7C860, PedHandle); } // 0x9BE7C860
	static BOOL IS_PED_BEING_STEALTH_KILLED(Any p0) { return invoke<BOOL>(0xD044C8AF, p0); } // 0xD044C8AF
	static Any _0xAFEC26A4(Any p0) { return invoke<Any>(0xAFEC26A4, p0); } // 0xAFEC26A4
	static BOOL WAS_PED_KILLED_BY_STEALTH(Any p0) { return invoke<BOOL>(0x2EA4B54E, p0); } // 0x2EA4B54E
	static BOOL WAS_PED_KILLED_BY_TAKEDOWN(Any p0) { return invoke<BOOL>(0xBDD3CE69, p0); } // 0xBDD3CE69
	static Any _0x3993092B(Any p0) { return invoke<Any>(0x3993092B, p0); } // 0x3993092B
	static void SET_PED_FLEE_ATTRIBUTES(Any p0, Any p1, Any p2) { invoke<Void>(0xA717A875, p0, p1, p2); } // 0xA717A875
	static void SET_PED_COWER_HASH(Any p0, Any p1) { invoke<Void>(0x16F30DF4, p0, p1); } // 0x16F30DF4
	static void _0xA6F2C057(Any p0, Any p1) { invoke<Void>(0xA6F2C057, p0, p1); } // 0xA6F2C057
	static void SET_PED_STEERS_AROUND_PEDS(Ped ped, BOOL DoesSteer) { invoke<Void>(0x797CAE4F, ped, DoesSteer); } // 0x797CAE4F
	static void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, BOOL DoesSteer) { invoke<Void>(0x3BD9B0A6, ped, DoesSteer); } // 0x3BD9B0A6
	static void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, BOOL DoesSteer) { invoke<Void>(0x533C0651, ped, DoesSteer); } // 0x533C0651
	static void _0x2276DE0D(Any p0, Any p1) { invoke<Void>(0x2276DE0D, p0, p1); } // 0x2276DE0D
	static void _0x59C52BE6(Any p0) { invoke<Void>(0x59C52BE6, p0); } // 0x59C52BE6
	static void _0x1D87DDC1(Any p0, Any p1) { invoke<Void>(0x1D87DDC1, p0, p1); } // 0x1D87DDC1
	static void _0xB52BA5F5(Any p0) { invoke<Void>(0xB52BA5F5, p0); } // 0xB52BA5F5
	static BOOL IS_ANY_PED_NEAR_POINT(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xFBD9B050, p0, p1, p2, p3); } // 0xFBD9B050
	static void _0x187B9070(Any p0, Any p1, Any p2) { invoke<Void>(0x187B9070, p0, p1, p2); } // 0x187B9070
	static Any _0x45037B9B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x45037B9B, p0, p1, p2, p3, p4); } // 0x45037B9B
	static void _0x840D24D3(Any p0) { invoke<Void>(0x840D24D3, p0); } // 0x840D24D3
	static void GET_PED_FLOOD_INVINCIBILITY(Any p0, Any p1) { invoke<Void>(0x31C31DAA, p0, p1); } // 0x31C31DAA
	static void _0x9194DB71(Any p0, Any p1) { invoke<Void>(0x9194DB71, p0, p1); } // 0x9194DB71
	static BOOL IS_TRACKED_PED_VISIBLE(Any p0) { return invoke<BOOL>(0x33248CC1, p0); } // 0x33248CC1
	static Any _0x5B1B70AA(Any p0) { return invoke<Any>(0x5B1B70AA, p0); } // 0x5B1B70AA
	static BOOL IS_PED_TRACKED(Any p0) { return invoke<BOOL>(0x7EB613D9, p0); } // 0x7EB613D9
	static BOOL HAS_PED_RECEIVED_EVENT(Any p0, Any p1) { return invoke<BOOL>(0xECD73DB0, p0, p1); } // 0xECD73DB0
	static Any _0x74A0F291(Any p0, Any p1) { return invoke<Any>(0x74A0F291, p0, p1); } // 0x74A0F291
	static Any GET_PED_BONE_INDEX(Ped PedHandle, int BoneIndex) { return invoke<Any>(0x259C6BA2, PedHandle, BoneIndex); } // 0x259C6BA2
	static Any GET_PED_RAGDOLL_BONE_INDEX(Any p0, Any p1) { return invoke<Any>(0x849F0716, p0, p1); } // 0x849F0716
	static void SET_PED_ENVEFF_SCALE(Any p0, Any p1) { invoke<Void>(0xFC1CFC27, p0, p1); } // 0xFC1CFC27
	static Any GET_PED_ENVEFF_SCALE(Any p0) { return invoke<Any>(0xA3421E39, p0); } // 0xA3421E39
	static void SET_ENABLE_PED_ENVEFF_SCALE(Any p0, Any p1) { invoke<Void>(0xC70F4A84, p0, p1); } // 0xC70F4A84
	static void _0x3B882533(Any p0, Any p1) { invoke<Void>(0x3B882533, p0, p1); } // 0x3B882533
	static void _0x87A0C174(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x87A0C174, p0, p1, p2, p3); } // 0x87A0C174
	static void _0x7BD26837(Any p0, Any p1) { invoke<Void>(0x7BD26837, p0, p1); } // 0x7BD26837
	static void _0x98E29ED0(Any p0, Any p1) { invoke<Void>(0x98E29ED0, p0, p1); } // 0x98E29ED0
	static Any _0xD315978E(Any p0) { return invoke<Any>(0xD315978E, p0); } // 0xD315978E
	static Any CREATE_SYNCHRONIZED_SCENE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xFFDDF8FA, p0, p1, p2, p3, p4, p5, p6); } // 0xFFDDF8FA
	static Any _0xF3876894(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xF3876894, p0, p1, p2, p3, p4); } // 0xF3876894
	static BOOL IS_SYNCHRONIZED_SCENE_RUNNING(Any p0) { return invoke<BOOL>(0x57A282F1, p0); } // 0x57A282F1
	static void SET_SYNCHRONIZED_SCENE_ORIGIN(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x2EC2A0B2, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x2EC2A0B2
	static void SET_SYNCHRONIZED_SCENE_PHASE(Any p0, Any p1) { invoke<Void>(0xF5AB0D98, p0, p1); } // 0xF5AB0D98
	static Any GET_SYNCHRONIZED_SCENE_PHASE(Any p0) { return invoke<Any>(0xB0B2C852, p0); } // 0xB0B2C852
	static void SET_SYNCHRONIZED_SCENE_RATE(Any p0, Any p1) { invoke<Void>(0xF10112FD, p0, p1); } // 0xF10112FD
	static Any GET_SYNCHRONIZED_SCENE_RATE(Any p0) { return invoke<Any>(0x89365F0D, p0); } // 0x89365F0D
	static void SET_SYNCHRONIZED_SCENE_LOOPED(Any p0, Any p1) { invoke<Void>(0x32ED9F82, p0, p1); } // 0x32ED9F82
	static BOOL IS_SYNCHRONIZED_SCENE_LOOPED(Any p0) { return invoke<BOOL>(0x47D87A84, p0); } // 0x47D87A84
	static void _0x2DE48DA1(Any p0, Any p1) { invoke<Void>(0x2DE48DA1, p0, p1); } // 0x2DE48DA1
	static Any _0x72CF2514(Any p0) { return invoke<Any>(0x72CF2514, p0); } // 0x72CF2514
	static void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0xE9BA6189, p0, p1, p2); } // 0xE9BA6189
	static void DETACH_SYNCHRONIZED_SCENE(Any p0) { invoke<Void>(0x52A1CAB2, p0); } // 0x52A1CAB2
	static void _0xBF7F9035(Any p0) { invoke<Void>(0xBF7F9035, p0); } // 0xBF7F9035
	static Any FORCE_PED_MOTION_STATE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x164DDEFF, p0, p1, p2, p3, p4); } // 0x164DDEFF
	static void SET_PED_MAX_MOVE_BLEND_RATIO(Any p0, Any p1) { invoke<Void>(0xEAD0269A, p0, p1); } // 0xEAD0269A
	static void SET_PED_MIN_MOVE_BLEND_RATIO(Any p0, Any p1) { invoke<Void>(0x383EC364, p0, p1); } // 0x383EC364
	static void SET_PED_MOVE_RATE_OVERRIDE(Any p0, Any p1) { invoke<Void>(0x900008C6, p0, p1); } // 0x900008C6
	static Any _0x79543043(Any p0, Any p1) { return invoke<Any>(0x79543043, p0, p1); } // 0x79543043
	static int GET_PED_NEARBY_VEHICLES(Ped PedHandle, int* sizeAndVehs) { return invoke<int>(0xCB716F68, PedHandle, sizeAndVehs); } // 0xCB716F68
	static int GET_PED_NEARBY_PEDS(Ped PedHandle, int* PToArray, int p2) { return invoke<int>(0x4D3325F4, PedHandle, PToArray, p2); } // 0x4D3325F4
	static Any _0xF9FB4B71(Any p0) { return invoke<Any>(0xF9FB4B71, p0); } // 0xF9FB4B71
	static BOOL IS_PED_USING_ACTION_MODE(Any p0) { return invoke<BOOL>(0x5AE7EDA2, p0); } // 0x5AE7EDA2
	static void SET_PED_USING_ACTION_MODE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x8802F696, p0, p1, p2, p3); } // 0x8802F696
	static void SET_PED_CAPSULE(Any p0, Any p1) { invoke<Void>(0xB153E1B9, p0, p1); } // 0xB153E1B9
	static Any REGISTER_PEDHEADSHOT(Any p0) { return invoke<Any>(0xFFE2667B, p0); } // 0xFFE2667B
	static Any _0x4DD03628(Any p0) { return invoke<Any>(0x4DD03628, p0); } // 0x4DD03628
	static void UNREGISTER_PEDHEADSHOT(Any p0) { invoke<Void>(0x0879AE45, p0); } // 0x0879AE45
	static BOOL IS_PEDHEADSHOT_VALID(Any p0) { return invoke<BOOL>(0x0B1080C4, p0); } // 0x0B1080C4
	static BOOL IS_PEDHEADSHOT_READY(Any p0) { return invoke<BOOL>(0x761CD02E, p0); } // 0x761CD02E
	static Any GET_PEDHEADSHOT_TXD_STRING(Any p0) { return invoke<Any>(0x76D28E96, p0); } // 0x76D28E96
	static void SET_PEDHEADSHOT_CUSTOM_LIGHTING(Any p0) { invoke<Void>(0xAB688DAB, p0); } // 0xAB688DAB
	static void SET_PEDHEADSHOT_CUSTOM_LIGHT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xF48A9155, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF48A9155
	static Any _0x10F2C023(Any p0) { return invoke<Any>(0x10F2C023, p0); } // 0x10F2C023
	static void _0x0DBB2FA7(Any p0) { invoke<Void>(0x0DBB2FA7, p0); } // 0x0DBB2FA7
	static Any _0x810158F8() { return invoke<Any>(0x810158F8); } // 0x810158F8
	static Any _0x05023F8F() { return invoke<Any>(0x05023F8F); } // 0x05023F8F
	static Any _0xAA39FD6C() { return invoke<Any>(0xAA39FD6C); } // 0xAA39FD6C
	static void _0xEF9142DB(Any p0, Any p1) { invoke<Void>(0xEF9142DB, p0, p1); } // 0xEF9142DB
	static void _0x0688DE64(Any p0) { invoke<Void>(0x0688DE64, p0); } // 0x0688DE64
	static void _0x909A1D76(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x909A1D76, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x909A1D76
	static void _0x4AAD0ECB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x4AAD0ECB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4AAD0ECB
	static void _0x492C9E46() { invoke<Void>(0x492C9E46); } // 0x492C9E46
	static Any _0x814A28F4() { return invoke<Any>(0x814A28F4); } // 0x814A28F4
	static Any _0x0B60D2BA() { return invoke<Any>(0x0B60D2BA); } // 0x0B60D2BA
	static Any _0x6B83ABDF() { return invoke<Any>(0x6B83ABDF); } // 0x6B83ABDF
	static Any _0xF46B4DC8() { return invoke<Any>(0xF46B4DC8); } // 0xF46B4DC8
	static void _0x36A4AC65(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x36A4AC65, p0, p1, p2, p3); } // 0x36A4AC65
	static void _0xBA699DDF(Any p0, Any p1) { invoke<Void>(0xBA699DDF, p0, p1); } // 0xBA699DDF
	static void SET_IK_TARGET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x6FE5218C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x6FE5218C
	static void _0xFB4000DC(Any p0) { invoke<Void>(0xFB4000DC, p0); } // 0xFB4000DC
	static void REQUEST_ACTION_MODE_ASSET(Any p0) { invoke<Void>(0x572BA553, p0); } // 0x572BA553
	static BOOL HAS_ACTION_MODE_ASSET_LOADED(Any p0) { return invoke<BOOL>(0xF7EB2BF1, p0); } // 0xF7EB2BF1
	static void REMOVE_ACTION_MODE_ASSET(Any p0) { invoke<Void>(0x3F480F92, p0); } // 0x3F480F92
	static void REQUEST_STEALTH_MODE_ASSET(Any p0) { invoke<Void>(0x280A004A, p0); } // 0x280A004A
	static BOOL HAS_STEALTH_MODE_ASSET_LOADED(Any p0) { return invoke<BOOL>(0x39245667, p0); } // 0x39245667
	static void REMOVE_STEALTH_MODE_ASSET(Any p0) { invoke<Void>(0x8C0B243A, p0); } // 0x8C0B243A
	static void SET_PED_LOD_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x1D2B5C70, p0, p1); } // 0x1D2B5C70
	static void _0x2F9550C2(Any p0, Any p1, Any p2) { invoke<Void>(0x2F9550C2, p0, p1, p2); } // 0x2F9550C2
	static void _0x37DBC2AD(Any p0, Any p1) { invoke<Void>(0x37DBC2AD, p0, p1); } // 0x37DBC2AD
	static void _0xC0F1BC91(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xC0F1BC91, p0, p1, p2, p3); } // 0xC0F1BC91
	static Any _0x1A464167(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x1A464167, p0, p1, p2, p3, p4); } // 0x1A464167
	static Any _0xD0567D41(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xD0567D41, p0, p1, p2, p3, p4, p5); } // 0xD0567D41
	static void _0x4BBE5E2C(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4BBE5E2C, p0, p1, p2, p3, p4); } // 0x4BBE5E2C
	static void _0xA89A53F2(Any p0) { invoke<Void>(0xA89A53F2, p0); } // 0xA89A53F2
}

namespace NETWORK
{
	static bool _0x99F58A07(int ped, int player) { return invoke<bool>(0x99F58A07, ped, player); };
	static Any NETWORK_IS_SIGNED_IN() { return invoke<Any>(0xADD0B40F); } // 0xADD0B40F
	static Any NETWORK_IS_SIGNED_ONLINE() { return invoke<Any>(0x6E5BDCE2); } // 0x6E5BDCE2
	static Any _0x3FB40673() { return invoke<Any>(0x3FB40673); } // 0x3FB40673
	static Any NETWORK_IS_CLOUD_AVAILABLE() { return invoke<Any>(0xC7FF5AFC); } // 0xC7FF5AFC
	static Any _0x66EC713F() { return invoke<Any>(0x66EC713F); } // 0x66EC713F
	static Any _0x358D1D77() { return invoke<Any>(0x358D1D77); } // 0x358D1D77
	static Any NETWORK_IS_HOST() { return invoke<Any>(0xE46AC10F); } // 0xE46AC10F
	static Any NETWORK_HAVE_ONLINE_PRIVILEGES() { return invoke<Any>(0xEF63BFDF); } // 0xEF63BFDF
	static Any _0x1F88819D(Any p0) { return invoke<Any>(0x1F88819D, p0); } // 0x1F88819D
	static Any _0x2D817A5E(Any p0, Any p1) { return invoke<Any>(0x2D817A5E, p0, p1); } // 0x2D817A5E
	static Any _0xBB54AA3D(Any p0, Any p1, Any p2) { return invoke<Any>(0xBB54AA3D, p0, p1, p2); } // 0xBB54AA3D
	static Any _0xA79E5B05(Any p0, Any p1, Any p2) { return invoke<Any>(0xA79E5B05, p0, p1, p2); } // 0xA79E5B05
	static Any _0xEB864288() { return invoke<Any>(0xEB864288); } // 0xEB864288
	static Any _0xAB07CBBE() { return invoke<Any>(0xAB07CBBE); } // 0xAB07CBBE
	static Any _0x60E1FEDF() { return invoke<Any>(0x60E1FEDF); } // 0x60E1FEDF
	static void NETWORK_BAIL() { invoke<Void>(0x87D79A04); } // 0x87D79A04
	static void _0x96E28FE2() { invoke<Void>(0x96E28FE2); } // 0x96E28FE2
	static Any _0xA520B982(Any p0) { return invoke<Any>(0xA520B982, p0); } // 0xA520B982
	static Any _0x05518C0F() { return invoke<Any>(0x05518C0F); } // 0x05518C0F
	static Any NETWORK_CAN_ENTER_MULTIPLAYER() { return invoke<Any>(0x4A23B9C9); } // 0x4A23B9C9
	static Any NETWORK_SESSION_ENTER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x543CD2BE, p0, p1, p2, p3, p4, p5); } // 0x543CD2BE
	static Any _0x4E53202A(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4E53202A, p0, p1, p2, p3); } // 0x4E53202A
	static Any _0xD7624E6B(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xD7624E6B, p0, p1, p2, p3, p4); } // 0xD7624E6B
	static Any _0x3F75CC38(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x3F75CC38, p0, p1, p2, p3); } // 0x3F75CC38
	static Any NETWORK_SESSION_HOST(Any p0, Any p1, Any p2) { return invoke<Any>(0x6716460F, p0, p1, p2); } // 0x6716460F
	static Any _0x8AC9EA19(Any p0, Any p1) { return invoke<Any>(0x8AC9EA19, p0, p1); } // 0x8AC9EA19
	static Any NETWORK_SESSION_HOST_FRIENDS_ONLY(Any p0, Any p1) { return invoke<Any>(0x26864403, p0, p1); } // 0x26864403
	static Any _0x56E75FE4() { return invoke<Any>(0x56E75FE4); } // 0x56E75FE4
	static Any _0xA95299B9() { return invoke<Any>(0xA95299B9); } // 0xA95299B9
	static Any _0x3D2C1916() { return invoke<Any>(0x3D2C1916); } // 0x3D2C1916
	static Any _0xDB67785D() { return invoke<Any>(0xDB67785D); } // 0xDB67785D
	static Any NETWORK_SESSION_END(Any p0, Any p1) { return invoke<Any>(0xBCACBEA2, p0, p1); } // 0xBCACBEA2
	static void NETWORK_SESSION_KICK_PLAYER(Any p0) { invoke<Void>(0x1E20138A, p0); } // 0x1E20138A
	static Any _0x8A559D26(Any p0) { return invoke<Any>(0x8A559D26, p0); } // 0x8A559D26
	static void _0x3C3E2AB6(Any p0) { invoke<Void>(0x3C3E2AB6, p0); } // 0x3C3E2AB6
	static void _0x5F29A7E0(Any p0, Any p1) { invoke<Void>(0x5F29A7E0, p0, p1); } // 0x5F29A7E0
	static Any _0x36EAD960(Any p0) { return invoke<Any>(0x36EAD960, p0); } // 0x36EAD960
	static void _0x5BE529F7(Any p0) { invoke<Void>(0x5BE529F7, p0); } // 0x5BE529F7
	static void _0x454C7B67(Any p0) { invoke<Void>(0x454C7B67, p0); } // 0x454C7B67
	static void _0xE5961511(Any p0) { invoke<Void>(0xE5961511, p0); } // 0xE5961511
	static void _0xAE396263(Any p0) { invoke<Void>(0xAE396263, p0); } // 0xAE396263
	static void _0x913FD7D6(Any p0) { invoke<Void>(0x913FD7D6, p0); } // 0x913FD7D6
	static void _0xB3D9A67F(Any p0) { invoke<Void>(0xB3D9A67F, p0); } // 0xB3D9A67F
	static void _0x6CC062FC(Any p0) { invoke<Void>(0x6CC062FC, p0); } // 0x6CC062FC
	static void _0x57F9BC83() { invoke<Void>(0x57F9BC83); } // 0x57F9BC83
	static void _0xF3768F90(Any p0) { invoke<Void>(0xF3768F90, p0); } // 0xF3768F90
	static void _0x0EC62629(Any p0, Any p1) { invoke<Void>(0x0EC62629, p0, p1); } // 0x0EC62629
	static void _0x5E557307() { invoke<Void>(0x5E557307); } // 0x5E557307
	static void _0x74E8C53E(Any p0, Any p1, Any p2) { invoke<Void>(0x74E8C53E, p0, p1, p2); } // 0x74E8C53E
	static void _0x959E43A3(Any p0) { invoke<Void>(0x959E43A3, p0); } // 0x959E43A3
	static Any _0x7771AB83(Any p0) { return invoke<Any>(0x7771AB83, p0); } // 0x7771AB83
	static Any _0xA13045D4(int p0, float p1, float p2, float p3) { return invoke<Any>(0xA13045D4, p0, p1, p2, p3); } // 0xA13045D4
	static Any NETWORK_IS_FINDING_GAMERS() { return invoke<Any>(0xA6DAA79F); } // 0xA6DAA79F
	static Any _0xBEDC4503() { return invoke<Any>(0xBEDC4503); } // 0xBEDC4503
	static Any NETWORK_GET_NUM_FOUND_GAMERS() { return invoke<Any>(0xF4B80C7E); } // 0xF4B80C7E
	static Any NETWORK_GET_FOUND_GAMER(int* p0, Any p1) { return invoke<Any>(0xA08C9141, p0, p1); } // 0xA08C9141
	static void NETWORK_CLEAR_FOUND_GAMERS() { invoke<Void>(0x6AA9A154); } // 0x6AA9A154
	static Any _0x42BD0780(Any* p0) { return invoke<Any>(0x42BD0780, p0); } // 0x42BD0780
	static Any _0xBEB98840() { return invoke<Any>(0xBEB98840); } // 0xBEB98840
	static Any _0x08029970() { return invoke<Any>(0x08029970); } // 0x08029970
	static Any _0xC871E745() { return invoke<Any>(0xC871E745); } // 0xC871E745
	static Any _0xB5ABC4B4(Any p0, Any p1) { return invoke<Any>(0xB5ABC4B4, p0, p1); } // 0xB5ABC4B4
	static void _0x3F7EDBBD() { invoke<Void>(0x3F7EDBBD); } // 0x3F7EDBBD
	static void NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED() { invoke<Void>(0x3D6360B5); } // 0x3D6360B5
	static void NETWORK_SESSION_CANCEL_INVITE() { invoke<Void>(0x20317535); } // 0x20317535
	static void _0x3FD49D3B() { invoke<Void>(0x3FD49D3B); } // 0x3FD49D3B
	static Any NETWORK_HAS_PENDING_INVITE() { return invoke<Any>(0x0C207D6E); } // 0x0C207D6E
	static Any _0xFBBAC350() { return invoke<Any>(0xFBBAC350); } // 0xFBBAC350
	static Any _0x0907A6BF() { return invoke<Any>(0x0907A6BF); } // 0x0907A6BF
	static Any _0x6A0BEA60() { return invoke<Any>(0x6A0BEA60); } // 0x6A0BEA60
	static void NETWORK_SESSION_GET_INVITER(Any p0) { invoke<Void>(0xE9C6B3FD, p0); } // 0xE9C6B3FD
	static Any _0x3EA9D44C() { return invoke<Any>(0x3EA9D44C); } // 0x3EA9D44C
	static void NETWORK_SUPPRESS_INVITE(Any p0) { invoke<Void>(0x323DC78C, p0); } // 0x323DC78C
	static void NETWORK_BLOCK_INVITES(Any p0) { invoke<Void>(0xD156FD1A, p0); } // 0xD156FD1A
	static void _0x32B7A076() { invoke<Void>(0x32B7A076); } // 0x32B7A076
	static void _0x0FCE995D(Any p0) { invoke<Void>(0x0FCE995D, p0); } // 0x0FCE995D
	static void _0xA639DCA2(Any p0) { invoke<Void>(0xA639DCA2, p0); } // 0xA639DCA2
	static Any _0x70ED476A() { return invoke<Any>(0x70ED476A); } // 0x70ED476A
	static void _0x50507BED() { invoke<Void>(0x50507BED); } // 0x50507BED
	static void NETWORK_SESSION_HOST_SINGLE_PLAYER(Any p0) { invoke<Void>(0xF3B1CA85, p0); } // 0xF3B1CA85
	static void NETWORK_SESSION_LEAVE_SINGLE_PLAYER() { invoke<Void>(0xC692F86A); } // 0xC692F86A
	static Any NETWORK_IS_GAME_IN_PROGRESS() { return invoke<Any>(0x09B88E3E); } // 0x09B88E3E
	static Any NETWORK_IS_SESSION_ACTIVE() { return invoke<Any>(0x715CB8C4); } // 0x715CB8C4
	static Any NETWORK_IS_IN_SESSION() { return invoke<Any>(0x4BC4105E); } // 0x4BC4105E
	static Any NETWORK_IS_SESSION_STARTED() { return invoke<Any>(0x9D854A37); } // 0x9D854A37
	static Any NETWORK_IS_SESSION_BUSY() { return invoke<Any>(0x8592152D); } // 0x8592152D
	static Any NETWORK_CAN_SESSION_END() { return invoke<Any>(0xE1FCCDBA); } // 0xE1FCCDBA
	static void _0x7017257D(Any p0) { invoke<Void>(0x7017257D, p0); } // 0x7017257D
	static Any _0x4977AC28() { return invoke<Any>(0x4977AC28); } // 0x4977AC28
	static void _0xE6EEF8AF(Any p0) { invoke<Void>(0xE6EEF8AF, p0); } // 0xE6EEF8AF
	static void _0x6BB93227(Any p0, Any p1) { invoke<Void>(0x6BB93227, p0, p1); } // 0x6BB93227
	static Any _0xE642F2FD() { return invoke<Any>(0xE642F2FD); } // 0xE642F2FD
	static void NETWORK_SESSION_VOICE_HOST() { invoke<Void>(0x345C2980); } // 0x345C2980
	static void NETWORK_SESSION_VOICE_LEAVE() { invoke<Void>(0xE566C7DA); } // 0xE566C7DA
	static void _0x9DFD89E6(int* p0) { invoke<Void>(0x9DFD89E6, p0); } // 0x9DFD89E6
	static void NETWORK_SET_KEEP_FOCUSPOINT(Any p0, Any p1) { invoke<Void>(0x075321B5, p0, p1); } // 0x075321B5
	static void _0x6EFC2FD0(Any p0) { invoke<Void>(0x6EFC2FD0, p0); } // 0x6EFC2FD0
	static Any _0x60AA4AA1() { return invoke<Any>(0x60AA4AA1); } // 0x60AA4AA1
	static Any _0x132CA01E() { return invoke<Any>(0x132CA01E); } // 0x132CA01E
	static Any NETWORK_SEND_TEXT_MESSAGE(char* Text, int FreeMemPointer) { return invoke<Any>(0xAFFEA720, Text, FreeMemPointer); } // 0xAFFEA720
	static void NETWORK_SET_ACTIVITY_SPECTATOR(Any p0) { invoke<Void>(0xFC9AD060, p0); } // 0xFC9AD060
	static Any NETWORK_IS_ACTIVITY_SPECTATOR() { return invoke<Any>(0xAF329720); } // 0xAF329720
	static void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(Any p0) { invoke<Void>(0x74E0BC0A, p0); } // 0x74E0BC0A
	static Any NETWORK_GET_ACTIVITY_PLAYER_NUM(Any p0) { return invoke<Any>(0x31F951FD, p0); } // 0x31F951FD
	static Any NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(Any p0) { return invoke<Any>(0x58F1DF7D, p0); } // 0x58F1DF7D
	static Any NETWORK_HOST_TRANSITION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x146764FB, p0, p1, p2, p3, p4, p5); } // 0x146764FB
	static Any _0x2FF65C0B(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x2FF65C0B, p0, p1, p2, p3); } // 0x2FF65C0B
	static Any _0x47D61C99(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x47D61C99, p0, p1, p2, p3); } // 0x47D61C99
	static Any _0x5CE60A11(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x5CE60A11, p0, p1, p2, p3, p4, p5); } // 0x5CE60A11
	static Any _0x0D7E5CF9() { return invoke<Any>(0x0D7E5CF9); } // 0x0D7E5CF9
	static void _0x36A5F2DA() { invoke<Void>(0x36A5F2DA); } // 0x36A5F2DA
	static Any _0x95FFACF8() { return invoke<Any>(0x95FFACF8); } // 0x95FFACF8
	static Any _0xB97A966B() { return invoke<Any>(0xB97A966B); } // 0xB97A966B
	static void _0x7EF353E1(Any p0) { invoke<Void>(0x7EF353E1, p0); } // 0x7EF353E1
	static void _0xF60986FC(Any p0) { invoke<Void>(0xF60986FC, p0); } // 0xF60986FC
	static void NETWORK_SET_TRANSITION_CREATOR_HANDLE(Any p0) { invoke<Void>(0x1DD01FE7, p0); } // 0x1DD01FE7
	static void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE() { invoke<Void>(0x8BB336F7); } // 0x8BB336F7
	static Any NETWORK_INVITE_GAMERS_TO_TRANSITION(Any p0, Any p1) { return invoke<Any>(0x5332E645, p0, p1); } // 0x5332E645
	static void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(Any p0) { invoke<Void>(0x17F1C69D, p0); } // 0x17F1C69D
	static Any NETWORK_LEAVE_TRANSITION() { return invoke<Any>(0x3A3599B7); } // 0x3A3599B7
	static Any NETWORK_LAUNCH_TRANSITION() { return invoke<Any>(0xE3570BA2); } // 0xE3570BA2
	static void _0xB59D74CA() { invoke<Void>(0xB59D74CA); } // 0xB59D74CA
	static Any NETWORK_DO_TRANSITION_TO_GAME(Any p0, Any p1) { return invoke<Any>(0x1B2114D2, p0, p1); } // 0x1B2114D2
	static Any NETWORK_DO_TRANSITION_TO_NEW_GAME(Any p0, Any p1, Any p2) { return invoke<Any>(0x58AFBE63, p0, p1, p2); } // 0x58AFBE63
	static Any NETWORK_DO_TRANSITION_TO_FREEMODE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xC7CB8ADF, p0, p1, p2, p3); } // 0xC7CB8ADF
	static Any NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xAD13375E, p0, p1, p2, p3, p4); } // 0xAD13375E
	static Any NETWORK_IS_TRANSITION_TO_GAME() { return invoke<Any>(0x17146B2B); } // 0x17146B2B
	static Any NETWORK_GET_TRANSITION_MEMBERS(Any p0, Any p1) { return invoke<Any>(0x31F19263, p0, p1); } // 0x31F19263
	static void _0xCEE79711(Any p0, Any p1) { invoke<Void>(0xCEE79711, p0, p1); } // 0xCEE79711
	static void _0xE0C28DB5(Any p0, Any p1, Any p2) { invoke<Void>(0xE0C28DB5, p0, p1, p2); } // 0xE0C28DB5
	static Any NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(void* p0, char* p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x468B0884, p0, p1, p2, p3, p4); } // 0x468B0884
	static Any NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(Any p0) { return invoke<Any>(0x03383F57, p0); } // 0x03383F57
	static Any NETWORK_IS_TRANSITION_HOST() { return invoke<Any>(0x0C0900BC); } // 0x0C0900BC
	static Any NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(Any p0) { return invoke<Any>(0x0E2854C4, p0); } // 0x0E2854C4
	static Any NETWORK_GET_TRANSITION_HOST(Any p0) { return invoke<Any>(0x73098D40, p0); } // 0x73098D40
	static Any NETWORK_IS_IN_TRANSITION() { return invoke<Any>(0xC3CDB626); } // 0xC3CDB626
	static Any NETWORK_IS_TRANSITION_STARTED() { return invoke<Any>(0x7917E111); } // 0x7917E111
	static Any NETWORK_IS_TRANSITION_BUSY() { return invoke<Any>(0xA357A2C6); } // 0xA357A2C6
	static Any _0x8262C70E() { return invoke<Any>(0x8262C70E); } // 0x8262C70E
	static void _0xC71E607B() { invoke<Void>(0xC71E607B); } // 0xC71E607B
	static void _0x82D32D07() { invoke<Void>(0x82D32D07); } // 0x82D32D07
	static Any _0xC901AA9F() { return invoke<Any>(0xC901AA9F); } // 0xC901AA9F
	static void _0xCCA9C022(Any p0) { invoke<Void>(0xCCA9C022, p0); } // 0xCCA9C022
	static void _0x1E5F6AEF(Any p0, Any p1) { invoke<Void>(0x1E5F6AEF, p0, p1); } // 0x1E5F6AEF
	static void _0x0532DDD2(Any p0) { invoke<Void>(0x0532DDD2, p0); } // 0x0532DDD2
	static Any NETWORK_HAS_PLAYER_STARTED_TRANSITION(Any p0) { return invoke<Any>(0x4ABD1E59, p0); } // 0x4ABD1E59
	static Any _0xCDEBCCE7(Any p0) { return invoke<Any>(0xCDEBCCE7, p0); } // 0xCDEBCCE7
	static Any NETWORK_JOIN_TRANSITION(Any p0) { return invoke<Any>(0xB054EC4B, p0); } // 0xB054EC4B
	static Any _0x4F41DF6B(Any p0) { return invoke<Any>(0x4F41DF6B, p0); } // 0x4F41DF6B
	static Any NETWORK_IS_ACTIVITY_SESSION() { return invoke<Any>(0x577DAA8A); } // 0x577DAA8A
	static void _0x18F03AFD(Any p0) { invoke<Void>(0x18F03AFD, p0); } // 0x18F03AFD
	static Any _0x8B99B72B(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x8B99B72B, p0, p1, p2, p3); } // 0x8B99B72B
	static Any _0x877C0E1C(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x877C0E1C, p0, p1, p2, p3); } // 0x877C0E1C
	static Any _0x5E832444(Any p0) { return invoke<Any>(0x5E832444, p0); } // 0x5E832444
	static Any _0x3FDA00F3() { return invoke<Any>(0x3FDA00F3); } // 0x3FDA00F3
	static Any NETWORK_ACCEPT_PRESENCE_INVITE(Any p0) { return invoke<Any>(0xE5DA4CED, p0); } // 0xE5DA4CED
	static Any _0x93C665FA(Any p0) { return invoke<Any>(0x93C665FA, p0); } // 0x93C665FA
	static Any _0xD50DF46C(Any p0) { return invoke<Any>(0xD50DF46C, p0); } // 0xD50DF46C
	static Any _0x19EC65D9(Any p0) { return invoke<Any>(0x19EC65D9, p0); } // 0x19EC65D9
	static Any NETWORK_GET_PRESENCE_INVITE_HANDLE(Any p0, Any p1) { return invoke<Any>(0xB2451429, p0, p1); } // 0xB2451429
	static Any _0xC5E0C989(Any p0) { return invoke<Any>(0xC5E0C989, p0); } // 0xC5E0C989
	static Any _0xA4302183(Any p0) { return invoke<Any>(0xA4302183, p0); } // 0xA4302183
	static Any _0x51B2D848(Any p0) { return invoke<Any>(0x51B2D848, p0); } // 0x51B2D848
	static Any _0x4677C656(Any p0) { return invoke<Any>(0x4677C656, p0); } // 0x4677C656
	static Any _0xF5E3401C(Any p0) { return invoke<Any>(0xF5E3401C, p0); } // 0xF5E3401C
	static Any _0x7D593B4C(Any p0) { return invoke<Any>(0x7D593B4C, p0); } // 0x7D593B4C
	static Any _0xE96CFE7D() { return invoke<Any>(0xE96CFE7D); } // 0xE96CFE7D
	static Any _0xAB969F00() { return invoke<Any>(0xAB969F00); } // 0xAB969F00
	static Any _0x3242F952() { return invoke<Any>(0x3242F952); } // 0x3242F952
	static void _0x9773F36A() { invoke<Void>(0x9773F36A); } // 0x9773F36A
	static void NETWORK_REMOVE_TRANSITION_INVITE(Any p0) { invoke<Void>(0xFDE84CB7, p0); } // 0xFDE84CB7
	static void _0xF7134E73() { invoke<Void>(0xF7134E73); } // 0xF7134E73
	static void _0xC47352E7() { invoke<Void>(0xC47352E7); } // 0xC47352E7
	static Any NETWORK_INVITE_GAMERS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x52FB8074, p0, p1, p2, p3); } // 0x52FB8074
	static Any _0xEC651BC0(Any p0) { return invoke<Any>(0xEC651BC0, p0); } // 0xEC651BC0
	static Any NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any p0) { return invoke<Any>(0x72BA00CE, p0); } // 0x72BA00CE
	static Any NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any p0) { return invoke<Any>(0xFD95899E, p0); } // 0xFD95899E
	static void _0x0808D4CC(Any p0, Any p1) { invoke<Void>(0x0808D4CC, p0, p1); } // 0x0808D4CC
	static void _0x11378777(Any p0) { invoke<Void>(0x11378777, p0); } // 0x11378777
	static Any FILLOUT_PM_PLAYER_LIST(Any p0, Any p1, Any p2) { return invoke<Any>(0xCE40F423, p0, p1, p2); } // 0xCE40F423
	static Any FILLOUT_PM_PLAYER_LIST_WITH_NAMES(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xB8DF604E, p0, p1, p2, p3); } // 0xB8DF604E
	static Any USING_NETWORK_WEAPONTYPE(Any p0) { return invoke<Any>(0xF49C1533, p0); } // 0xF49C1533
	static Any _0xA812B6CB() { return invoke<Any>(0xA812B6CB); } // 0xA812B6CB
	static Any _0xF30E5814(Any p0, Any p1) { return invoke<Any>(0xF30E5814, p0, p1); } // 0xF30E5814
	static Any _0xC6609191() { return invoke<Any>(0xC6609191); } // 0xC6609191
	static Any _0x51367B34(Any p0) { return invoke<Any>(0x51367B34, p0); } // 0x51367B34
	static Any NETWORK_IS_IN_PARTY() { return invoke<Any>(0xF9D7D67D); } // 0xF9D7D67D
	static Any NETWORK_IS_PARTY_MEMBER(Any p0) { return invoke<Any>(0x1D0C929D, p0); } // 0x1D0C929D
	static Any _0x9156EFC0() { return invoke<Any>(0x9156EFC0); } // 0x9156EFC0
	static Any _0x8FA6EE0E() { return invoke<Any>(0x8FA6EE0E); } // 0x8FA6EE0E
	static void _0x7F70C15A() { invoke<Void>(0x7F70C15A); } // 0x7F70C15A
	static void _0x8179C48A(Any p0) { invoke<Void>(0x8179C48A, p0); } // 0x8179C48A
	static void _0x41702C8A(Any p0) { invoke<Void>(0x41702C8A, p0); } // 0x41702C8A
	static Any _0x208DD848() { return invoke<Any>(0x208DD848); } // 0x208DD848
	static Any _0xF9B6426D(Any p0, Any p1) { return invoke<Any>(0xF9B6426D, p0, p1); } // 0xF9B6426D
	static Any NETWORK_PLAYER_IS_CHEATER() { return invoke<Any>(0xA51DC214); } // 0xA51DC214
	static Any _0x1720ABA6() { return invoke<Any>(0x1720ABA6); } // 0x1720ABA6
	static Any _0xA19708E3() { return invoke<Any>(0xA19708E3); } // 0xA19708E3
	static Any _0xF9A51B92(Any p0, Any p1, Any p2) { return invoke<Any>(0xF9A51B92, p0, p1, p2); } // 0xF9A51B92
	static Any _0x4C2C6B6A(Any p0, Any p1, Any p2) { return invoke<Any>(0x4C2C6B6A, p0, p1, p2); } // 0x4C2C6B6A
	static void _0x4818ACD0(Any p0, Any p1) { invoke<Void>(0x4818ACD0, p0, p1); } // 0x4818ACD0
	static void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(Any p0, Any p1, Any p2) { invoke<Void>(0x470810ED, p0, p1, p2); } // 0x470810ED
	static Any NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() { return invoke<Any>(0xD9BF6549); } // 0xD9BF6549
	static Any _0xCCD8C02D() { return invoke<Any>(0xCCD8C02D); } // 0xCCD8C02D
	static Any _0x3E25A3C5() { return invoke<Any>(0x3E25A3C5); } // 0x3E25A3C5
	static Any NETWORK_GET_SCRIPT_STATUS() { return invoke<Any>(0x2BE9235A); } // 0x2BE9235A
	static void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xDAF3B0AE, p0, p1); } // 0xDAF3B0AE
	static void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xBE3D32B4, p0, p1); } // 0xBE3D32B4
	static void _0xA71A1D2A() { invoke<Void>(0xA71A1D2A); } // 0xA71A1D2A
	static Any _0x0B739F53() { return invoke<Any>(0x0B739F53); } // 0x0B739F53
	static Any NETWORK_GET_PLAYER_INDEX(Ped PedHandle) { return invoke<Any>(0xBE1C1506, PedHandle); } // 0xBE1C1506
	static Any NETWORK_GET_PARTICIPANT_INDEX(Any p0) { return invoke<Any>(0xC4D91094, p0); } // 0xC4D91094
	static Any _0x40DBF464(Any p0) { return invoke<Any>(0x40DBF464, p0); } // 0x40DBF464
	static int NETWORK_GET_NUM_CONNECTED_PLAYERS() { return invoke<int>(0xF7952E62); } // 0xF7952E62
	static Any NETWORK_IS_PLAYER_CONNECTED(Any p0) { return invoke<Any>(0x168EE2C2, p0); } // 0x168EE2C2
	static Any _0xF4F13B06() { return invoke<Any>(0xF4F13B06); } // 0xF4F13B06
	static Any NETWORK_IS_PARTICIPANT_ACTIVE(Any p0) { return invoke<Any>(0x4E2C348B, p0); } // 0x4E2C348B
	static Any NETWORK_IS_PLAYER_ACTIVE(Any p0) { return invoke<Any>(0x43657B17, p0); } // 0x43657B17
	static Any NETWORK_IS_PLAYER_A_PARTICIPANT(Any p0) { return invoke<Any>(0xB08B6992, p0); } // 0xB08B6992
	static Any NET_BUT() { return invoke<Any>(0x6970BA94); } // 0x6970BA94
	static Any NETWORK_GET_HOST_OF_THIS_SCRIPT() { return invoke<Any>(0x89EA7B54); } // 0x89EA7B54
	static Any NETWORK_GET_HOST_OF_SCRIPT(char* gamemode, Any p1, Any p2) { return invoke<Any>(0x9C95D0BB, gamemode, p1, p2); } // 0x9C95D0BB
	static void NETWORK_SET_MISSION_FINISHED() { invoke<Void>(0x3083FAD7); } // 0x3083FAD7
	static Any NETWORK_IS_SCRIPT_ACTIVE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4A65250C, p0, p1, p2, p3); } // 0x4A65250C
	static Any _0x8F7D9F46(Any p0, Any p1, Any p2) { return invoke<Any>(0x8F7D9F46, p0, p1, p2); } // 0x8F7D9F46
	static Any _0xDB8B5D71() { return invoke<Any>(0xDB8B5D71); } // 0xDB8B5D71
	static Any _0xCEA55F4C(Any p0, Any p1, Any p2) { return invoke<Any>(0xCEA55F4C, p0, p1, p2); } // 0xCEA55F4C
	static void _0x8DCFE77D() { invoke<Void>(0x8DCFE77D); } // 0x8DCFE77D
	static void _0x331D9A27() { invoke<Void>(0x331D9A27); } // 0x331D9A27
	static Any PARTICIPANT_ID() { return invoke<Any>(0x9C35A221); } // 0x9C35A221
	static Any PARTICIPANT_ID_TO_INT() { return invoke<Any>(0x907498B0); } // 0x907498B0
	static Any NETWORK_GET_DESTROYER_OF_NETWORK_ID(Any p0, Any p1) { return invoke<Any>(0x4FCA6436, p0, p1); } // 0x4FCA6436
	static Any _0x28A45454(Any p0, Any p1, Any p2) { return invoke<Any>(0x28A45454, p0, p1, p2); } // 0x28A45454
	static Any NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Any p0, Any p1) { return invoke<Any>(0xA7E7E04F, p0, p1); } // 0xA7E7E04F
	static void NETWORK_RESURRECT_LOCAL_PLAYER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xF1F9D4B4, p0, p1, p2, p3, p4, p5); } // 0xF1F9D4B4
	static void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(Any p0) { invoke<Void>(0xFEA9B85C, p0); } // 0xFEA9B85C
	static Any NETWORK_IS_LOCAL_PLAYER_INVINCIBLE() { return invoke<Any>(0x8DE13B36); } // 0x8DE13B36
	static void _0x8D27280E(Any p0, Any p1) { invoke<Void>(0x8D27280E, p0, p1); } // 0x8D27280E
	static void _0xB72F086D(Any p0) { invoke<Void>(0xB72F086D, p0); } // 0xB72F086D
	static Any _0xEDA68956(Any p0) { return invoke<Any>(0xEDA68956, p0); } // 0xEDA68956
	static Any NETWORK_GET_NETWORK_ID_FROM_ENTITY(Any p0) { return invoke<Any>(0x9E35DAB6, p0); } // 0x9E35DAB6
	static Any NETWORK_GET_ENTITY_FROM_NETWORK_ID(Any p0) { return invoke<Any>(0x5B912C3F, p0); } // 0x5B912C3F
	static Any _0xD7F934F4(Any p0) { return invoke<Any>(0xD7F934F4, p0); } // 0xD7F934F4
	static Any NETWORK_GET_ENTITY_IS_LOCAL(Any p0) { return invoke<Any>(0x813353ED, p0); } // 0x813353ED
	static void _0x31A630A4(Any p0) { invoke<Void>(0x31A630A4, p0); } // 0x31A630A4
	static void _0x5C645F64(Any p0) { invoke<Void>(0x5C645F64, p0); } // 0x5C645F64
	static Any NETWORK_DOES_NETWORK_ID_EXIST(Any p0) { return invoke<Any>(0xB8D2C99E, p0); } // 0xB8D2C99E
	static Any NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(Any p0) { return invoke<Any>(0x1E2E3177, p0); } // 0x1E2E3177
	static Any NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netID) { return invoke<Any>(0x9262A60A, netID); } // 0x9262A60A
	static Any NETWORK_HAS_CONTROL_OF_NETWORK_ID(Entity entity) { return invoke<Any>(0x92E77D21, entity); } // 0x92E77D21
	static Any NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity) { return invoke<Any>(0xA05FEBD7, entity); } // 0xA05FEBD7
	static Any NETWORK_REQUEST_CONTROL_OF_DOOR(Any p0) { return invoke<Any>(0xF60DAAF6, p0); } // 0xF60DAAF6
	static Any NETWORK_HAS_CONTROL_OF_ENTITY(Entity Entity) { return invoke<Any>(0x005FD797, Entity); } // 0x005FD797
	static Any NETWORK_HAS_CONTROL_OF_PICKUP(Any p0) { return invoke<Any>(0xF7784FC8, p0); } // 0xF7784FC8
	static Any NETWORK_HAS_CONTROL_OF_DOOR(Any p0) { return invoke<Any>(0x136326EC, p0); } // 0x136326EC
	static Any VEH_TO_NET(Vehicle vehicle) { return invoke<Any>(0xF17634EB, vehicle); } // 0xF17634EB
	static Any PED_TO_NET(Ped ped) { return invoke<Any>(0x86A0B759, ped); } // 0x86A0B759
	static Any OBJ_TO_NET(Object object) { return invoke<Any>(0x1E05F29F, object); } // 0x1E05F29F
	static Any NET_TO_VEH(Any p0) { return invoke<Any>(0x7E02FAEA, p0); } // 0x7E02FAEA
	static Any NET_TO_PED(Any p0) { return invoke<Any>(0x87717DD4, p0); } // 0x87717DD4
	static Any NET_TO_OBJ(Any p0) { return invoke<Any>(0x27AA14D8, p0); } // 0x27AA14D8
	static Any NET_TO_ENT(Any p0) { return invoke<Any>(0x5E149683, p0); } // 0x5E149683
	static void NETWORK_GET_LOCAL_HANDLE(Any p0, Any p1) { invoke<Void>(0x08023B16, p0, p1); } // 0x08023B16
	static void NETWORK_HANDLE_FROM_USER_ID(char* p0, int* p1, Any p2) { invoke<Void>(0x74C2C1B7, p0, p1, p2); } // 0x74C2C1B7
	static void NETWORK_HANDLE_FROM_MEMBER_ID(char* p0, int* p1, Any p2) { invoke<Void>(0x9BFC9FE2, p0, p1, p2); } // 0x9BFC9FE2
	static void NETWORK_HANDLE_FROM_FRIEND(Any p0, Any p1, Any p2) { invoke<Void>(0x3B0BB3A3, p0, p1, p2); } // 0x3B0BB3A3
	static Any NETWORK_GAMERTAG_FROM_HANDLE_START(Any p0) { return invoke<Any>(0xEBA00C2A, p0); } // 0xEBA00C2A
	static Any NETWORK_GAMERTAG_FROM_HANDLE_PENDING() { return invoke<Any>(0xF000828E); } // 0xF000828E
	static Any NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED() { return invoke<Any>(0x89C2B5EA); } // 0x89C2B5EA
	static char* NETWORK_GET_GAMERTAG_FROM_HANDLE(int* p0) { return invoke<char*>(0xA18A1B26, p0); } // 0xA18A1B26
	static Any NETWORK_ARE_HANDLES_THE_SAME(Any p0, Any p1) { return invoke<Any>(0x45975AE3, p0, p1); } // 0x45975AE3
	static Any NETWORK_IS_HANDLE_VALID(int* p0, Any p1) { return invoke<Any>(0xF0996C6E, p0, p1); } // 0xF0996C6E
	static Any NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(Any p0) { return invoke<Any>(0x2E96EF1E, p0); } // 0x2E96EF1E
	static Any NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(Any p0) { return invoke<Any>(0x62EF0A63, p0); } // 0x62EF0A63
	static Any NETWORK_IS_GAMER_IN_MY_SESSION(Any p0) { return invoke<Any>(0x59127716, p0); } // 0x59127716
	static void NETWORK_SHOW_PROFILE_UI(Any p0) { invoke<Void>(0xF00A20B0, p0); } // 0xF00A20B0
	static Any NETWORK_GET_GAME_REGION() { return invoke<Any>(0xEE4D173E); } // 0xEE4D173E
	static Any NETWORK_PLAYER_GET_NAME(Any p0) { return invoke<Any>(0xCE48F260, p0); } // 0xCE48F260
	static Any _0x4EC0D983(Any p0, Any p1) { return invoke<Any>(0x4EC0D983, p0, p1); } // 0x4EC0D983
	static BOOL NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player) { return invoke<BOOL>(0xF6659045, player); } // 0xF6659045
	static Any _0xD265B049(Any p0) { return invoke<Any>(0xD265B049, p0); } // 0xD265B049
	static Any NETWORK_IS_INACTIVE_PROFILE(Any p0) { return invoke<Any>(0x95481343, p0); } // 0x95481343
	static Any NETWORK_GET_MAX_FRIENDS() { return invoke<Any>(0x048171BC); } // 0x048171BC
	static Any NETWORK_GET_FRIEND_COUNT() { return invoke<Any>(0xA396ACDE); } // 0xA396ACDE
	static char* NETWORK_GET_FRIEND_NAME(Any p0) { return invoke<char*>(0x97420B6D, p0); } // 0x97420B6D
	static Any NETWORK_IS_FRIEND_ONLINE(char* p0) { return invoke<Any>(0xE0A42430, p0); } // 0xE0A42430
	static Any NETWORK_IS_FRIEND_IN_SAME_TITLE(Any p0) { return invoke<Any>(0xC54365C2, p0); } // 0xC54365C2
	static Any NETWORK_IS_FRIEND_IN_MULTIPLAYER(Any p0) { return invoke<Any>(0x400BDDD9, p0); } // 0x400BDDD9
	static Any NETWORK_IS_FRIEND(Any p0) { return invoke<Any>(0x2DA4C282, p0); } // 0x2DA4C282
	static Any NETWORK_IS_PENDING_FRIEND(Any p0) { return invoke<Any>(0x5C85FF81, p0); } // 0x5C85FF81
	static Any NETWORK_IS_ADDING_FRIEND() { return invoke<Any>(0xBB7EC8C4); } // 0xBB7EC8C4
	static Any NETWORK_ADD_FRIEND(Any p0, Any p1) { return invoke<Any>(0x20E5B3EE, p0, p1); } // 0x20E5B3EE
	static Any CLEAR_PLAYER_BAILED_FROM_PLAYERICLE(Any p0) { return invoke<Any>(0x94AE7172, p0); } // 0x94AE7172
	static Any GET_OBJ_ENTITY(Any p0) { return invoke<Any>(0xB802B671, p0); } // 0xB802B671
	static Any NETWORK_CAN_SET_WAYPOINT() { return invoke<Any>(0x009E68F3); } // 0x009E68F3
	static Any _0x5C0AB2A9(Any p0) { return invoke<Any>(0x5C0AB2A9, p0); } // 0x5C0AB2A9
	static Any _0x9A176B6E() { return invoke<Any>(0x9A176B6E); } // 0x9A176B6E
	static Any NETWORK_HAS_HEADSET() { return invoke<Any>(0xA7DC5657); } // 0xA7DC5657
	static void _0x5C05B7E1(Any p0) { invoke<Void>(0x5C05B7E1, p0); } // 0x5C05B7E1
	static Any VEHICLE_NET_ATTACH_CHAR_TO_CHAR_PHYSICALLY() { return invoke<Any>(0xAC00A5BE); } // 0xAC00A5BE
	static Any NETWORK_GAMER_HAS_HEADSET(Any p0) { return invoke<Any>(0xD036DA4A, p0); } // 0xD036DA4A
	static Any NETWORK_IS_GAMER_TALKING(Any p0) { return invoke<Any>(0x99B58DBC, p0); } // 0x99B58DBC
	static Any NETWORK_CAN_COMMUNICATE_WITH_GAMER(Any p0) { return invoke<Any>(0xD05EB7F6, p0); } // 0xD05EB7F6
	static Any NETWORK_IS_GAMER_MUTED_BY_ME(Any p0) { return invoke<Any>(0x001B4046, p0); } // 0x001B4046
	static Any _0x7685B333(Any p0) { return invoke<Any>(0x7685B333, p0); } // 0x7685B333
	static Any _0x3FDCC8D7(Any p0) { return invoke<Any>(0x3FDCC8D7, p0); } // 0x3FDCC8D7
	static Any _0xD19B312C(Any p0) { return invoke<Any>(0xD19B312C, p0); } // 0xD19B312C
	static Any NETWORK_IS_PLAYER_TALKING(Any p0) { return invoke<Any>(0xDA9FD9DB, p0); } // 0xDA9FD9DB
	static Any NETWORK_PLAYER_HAS_HEADSET(Any p0) { return invoke<Any>(0x451FB6B6, p0); } // 0x451FB6B6
	static Any NETWORK_IS_PLAYER_MUTED_BY_ME(Any p0) { return invoke<Any>(0x7A21050E, p0); } // 0x7A21050E
	static Any NETWORK_AM_I_MUTED_BY_PLAYER(Any p0) { return invoke<Any>(0xE128F2B0, p0); } // 0xE128F2B0
	static Any NETWORK_IS_PLAYER_BLOCKED_BY_ME(Any p0) { return invoke<Any>(0xAE4F4560, p0); } // 0xAE4F4560
	static Any NETWORK_AM_I_BLOCKED_BY_PLAYER(Any p0) { return invoke<Any>(0x953EF45E, p0); } // 0x953EF45E
	static Any NETWORK_GET_PLAYER_LOUDNESS(Any p0) { return invoke<Any>(0xF2F67014, p0); } // 0xF2F67014
	static void NETWORK_SET_TALKER_PROXIMITY(Any p0) { invoke<Void>(0x67555C66, p0); } // 0x67555C66
	static Any NETWORK_GET_TALKER_PROXIMITY() { return invoke<Any>(0x19991ADD); } // 0x19991ADD
	static void NETWORK_SET_VOICE_ACTIVE(Any p0) { invoke<Void>(0x8011247F, p0); } // 0x8011247F
	static void _0x1A3EA6CD(Any p0) { invoke<Void>(0x1A3EA6CD, p0); } // 0x1A3EA6CD
	static void _0xCAB21090(Any p0) { invoke<Void>(0xCAB21090, p0); } // 0xCAB21090
	static void NETWORK_SET_TEAM_ONLY_CHAT(Any p0) { invoke<Void>(0x3813019A, p0); } // 0x3813019A
	static void _0xC8CC9E75(Any p0, Any p1) { invoke<Void>(0xC8CC9E75, p0, p1); } // 0xC8CC9E75
	static void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(Any p0) { invoke<Void>(0xA0FD42D3, p0); } // 0xA0FD42D3
	static void _0xC9DDA85B(Any p0) { invoke<Void>(0xC9DDA85B, p0); } // 0xC9DDA85B
	static void _0xD33AFF79(Any p0) { invoke<Void>(0xD33AFF79, p0); } // 0xD33AFF79
	static void _0x4FFEFE43(Any p0) { invoke<Void>(0x4FFEFE43, p0); } // 0x4FFEFE43
	static void _0x74EE2D8B(Any p0, Any p1) { invoke<Void>(0x74EE2D8B, p0, p1); } // 0x74EE2D8B
	static void _0x2F98B405(Any p0) { invoke<Void>(0x2F98B405, p0); } // 0x2F98B405
	static void _0x95F1C60D(Any p0, Any p1) { invoke<Void>(0x95F1C60D, p0, p1); } // 0x95F1C60D
	static void _0x6C344AE3(Any p0, Any p1) { invoke<Void>(0x6C344AE3, p0, p1); } // 0x95F1C60D
	static void _0x1BCD3DDF(Any p0) { invoke<Void>(0x1BCD3DDF, p0); } // 0x1BCD3DDF
	static void NETWORK_SET_VOICE_CHANNEL(Any p0) { invoke<Void>(0x3974879F, p0); } // 0x3974879F
	static void _0x9ECF722A() { invoke<Void>(0x9ECF722A); } // 0x9ECF722A
	static void IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0xF1E84832, p0, p1, p2); } // 0xF1E84832
	static void _0x7F9B9052() { invoke<Void>(0x7F9B9052); } // 0x7F9B9052
	static void _0x7BBEA8CF(Any p0) { invoke<Void>(0x7BBEA8CF, p0); } // 0x7BBEA8CF
	static void _0xE797A4B6(Any p0) { invoke<Void>(0xE797A4B6, p0); } // 0xE797A4B6
	static void _0x92268BB5(int player, float* p1, float* p2) { invoke<Void>(0x92268BB5, player, p1, p2); } // 0x92268BB5
	static void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { invoke<Void>(0x92B7351C); } // 0x92B7351C
	static void NETWORK_SET_FRIENDLY_FIRE_OPTION(Any p0) { invoke<Void>(0x6BAF95FA, p0); } // 0x6BAF95FA
	static void NETWORK_SET_RICH_PRESENCE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x932A6CED, p0, p1, p2, p3); } // 0x932A6CED
	static void _0x017E6777(int p0, char* p1) { invoke<Void>(0x017E6777, p0, p1); } // 0x017E6777
	static Any _0xE1F86C6A() { return invoke<Any>(0xE1F86C6A); } // 0xE1F86C6A
	//static void _0xBE6A30C3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xBE6A30C3, p0, p1, p2, p3, p4, p5); } // 0xBE6A30C3
	//static void _0x22E03AD0(Any p0, Any p1) { invoke<Void>(0x22E03AD0, p0, p1); } // 0x22E03AD0
	static void _0xCEAE5AFC(Any p0) { invoke<Void>(0xCEAE5AFC, p0); } // 0xCEAE5AFC
	static Any _0xF5F4BD95() { return invoke<Any>(0xF5F4BD95); } // 0xF5F4BD95
	static void _0xF633805A(Any p0, Any p1, Any p2) { invoke<Void>(0xF633805A, p0, p1, p2); } // 0xF633805A
	static Any _0x807B3450() { return invoke<Any>(0x807B3450); } // 0x807B3450
	static Any _0x3369DD1F(Any p0, Any p1) { return invoke<Any>(0x3369DD1F, p0, p1); } // 0x3369DD1F
	static Any NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(Any p0) { return invoke<Any>(0x8E8CB520, p0); } // 0x8E8CB520
	static Any NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(Any p0) { return invoke<Any>(0x1FDB590F, p0); } // 0x1FDB590F
	static Any _0x83ED8E08() { return invoke<Any>(0x83ED8E08); } // 0x83ED8E08
	static Any _0x40202867(Any p0) { return invoke<Any>(0x40202867, p0); } // 0x40202867
	static Any NETWORK_CLAN_GET_MEMBERSHIP_COUNT(Any p0) { return invoke<Any>(0x25924010, p0); } // 0x25924010
	static Any NETWORK_CLAN_GET_MEMBERSHIP_VALID(Any p0, Any p1) { return invoke<Any>(0x48914F6A, p0, p1); } // 0x48914F6A
	static Any NETWORK_CLAN_GET_MEMBERSHIP(Any p0, Any p1, Any p2) { return invoke<Any>(0xCDC4A590, p0, p1, p2); } // 0xCDC4A590
	static Any NETWORK_CLAN_JOIN(Any p0) { return invoke<Any>(0x79C916C5, p0); } // 0x79C916C5
	static Any _0xBDA90BAC(Any p0, Any p1) { return invoke<Any>(0xBDA90BAC, p0, p1); } // 0xBDA90BAC
	static Any _0x8E952B12(Any p0, Any p1) { return invoke<Any>(0x8E952B12, p0, p1); } // 0x8E952B12
	static Any _0x966C90FD() { return invoke<Any>(0x966C90FD); } // 0x966C90FD
	static Any _0xBA672146(Any p0, Any p1) { return invoke<Any>(0xBA672146, p0, p1); } // 0xBA672146
	static Any _0x7963FA4D(Any p0) { return invoke<Any>(0x7963FA4D, p0); } // 0x7963FA4D
	static Any _0x88B13CDC(Any p0, Any p1) { return invoke<Any>(0x88B13CDC, p0, p1); } // 0x88B13CDC
	static void _0xD6E3D5EA(Any p0) { invoke<Void>(0xD6E3D5EA, p0); } // 0xD6E3D5EA
	static Any _0xE22445DA() { return invoke<Any>(0xE22445DA); } // 0xE22445DA
	static void _0x455DDF5C() { invoke<Void>(0x455DDF5C); } // 0x455DDF5C
	static Any _0x89DB0EC7(Any p0, Any p1) { return invoke<Any>(0x89DB0EC7, p0, p1); } // 0x89DB0EC7
	static Any _0xA4EF02F3() { return invoke<Any>(0xA4EF02F3); } // 0xA4EF02F3
	static Any _0x068A054E() { return invoke<Any>(0x068A054E); } // 0x068A054E
	static Any _0x9B8631EB(Any p0, Any p1) { return invoke<Any>(0x9B8631EB, p0, p1); } // 0x9B8631EB
	static void SET_NETWORK_ID_CAN_MIGRATE(Any p0, Any p1) { invoke<Void>(0x47C8E5FF, p0, p1); } // 0x47C8E5FF
	static void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int NetID, BOOL DoesExist) { invoke<Void>(0x68D486B2, NetID, DoesExist); } // 0x68D486B2
	static void _0x4D15FDB1(Any p0, Any p1, Any p2) { invoke<Void>(0x4D15FDB1, p0, p1, p2); } // 0x4D15FDB1
	static void NETWORK_SET_ENTITY_CAN_BLEND(Any p0, Any p1) { invoke<Void>(0xDE8C0DB8, p0, p1); } // 0xDE8C0DB8
	static void _0x09CBC4B0(Any p0, Any p1) { invoke<Void>(0x09CBC4B0, p0, p1); } // 0x09CBC4B0
	static void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0x199E75EF, p0, p1, p2); } // 0x199E75EF
	static void _0x00AE4E17(Any p0, Any p1) { invoke<Void>(0x00AE4E17, p0, p1); } // 0x00AE4E17
	static Any _0xEA5176C0(Any p0) { return invoke<Any>(0xEA5176C0, p0); } // 0xEA5176C0
	static void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(Any p0, Any p1) { invoke<Void>(0x59F3479B, p0, p1); } // 0x59F3479B
	static void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(Any p0) { invoke<Void>(0x764F6222, p0); } // 0x764F6222
	static void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(Any p0) { invoke<Void>(0x324B56DB, p0); } // 0x324B56DB
	static void SET_PLAYER_INVISIBLE_LOCALLY(Any p0, Any p1) { invoke<Void>(0x18227209, p0, p1); } // 0x18227209
	static void SET_PLAYER_VISIBLE_LOCALLY(Any p0, Any p1) { invoke<Void>(0xBA2BB4B4, p0, p1); } // 0xBA2BB4B4
	static void FADE_OUT_LOCAL_PLAYER(Any p0) { invoke<Void>(0x8FA7CEBD, p0); } // 0x8FA7CEBD
	static void NETWORK_FADE_OUT_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0x47EDEE56, p0, p1, p2); } // 0x47EDEE56
	static void NETWORK_FADE_IN_ENTITY(Any p0, Any p1) { invoke<Void>(0x9B9FCD02, p0, p1); } // 0x9B9FCD02
	static BOOL IS_PLAYER_IN_CUTSCENE(Any p0) { return invoke<BOOL>(0xE0A619BD, p0); } // 0xE0A619BD
	static void SET_ENTITY_VISIBLE_IN_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0xDBFB067B, p0, p1, p2); } // 0xDBFB067B
	static void SET_ENTITY_LOCALLY_INVISIBLE(Any p0) { invoke<Void>(0x51ADCC5F, p0); } // 0x51ADCC5F
	static void SET_ENTITY_LOCALLY_VISIBLE(Any p0) { invoke<Void>(0x235A57B3, p0); } // 0x235A57B3
	static BOOL IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(Any p0) { return invoke<BOOL>(0x597063BA, p0); } // 0x597063BA
	static void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(Any p0, Any p1) { invoke<Void>(0x95D07BA5, p0, p1); } // 0x95D07BA5
	static BOOL IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x23C5274E, p0, p1, p2, p3); } // 0x23C5274E
	static BOOL IS_SPHERE_VISIBLE_TO_PLAYER(int player, float x, float y, float z, float radius) { return invoke<BOOL>(0xE9FCFB32, player, x, y, z, radius); } // 0xE9FCFB32
	static void RESERVE_NETWORK_MISSION_OBJECTS(Any p0) { invoke<Void>(0x391DF4F3, p0); } // 0x391DF4F3
	static void RESERVE_NETWORK_MISSION_PEDS(Any p0) { invoke<Void>(0x54998C37, p0); } // 0x54998C37
	static void RESERVE_NETWORK_MISSION_VEHICLES(Any p0) { invoke<Void>(0x5062875E, p0); } // 0x5062875E
	static BOOL CAN_REGISTER_MISSION_OBJECTS(Any p0) { return invoke<BOOL>(0x7F85DFDE, p0); } // 0x7F85DFDE
	static BOOL CAN_REGISTER_MISSION_PEDS(Any p0) { return invoke<BOOL>(0xCCAA5CE9, p0); } // 0xCCAA5CE9
	static BOOL CAN_REGISTER_MISSION_VEHICLES(Any p0) { return invoke<BOOL>(0x818B6830, p0); } // 0x818B6830
	static BOOL CAN_REGISTER_MISSION_ENTITIES(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x83794008, p0, p1, p2, p3); } // 0x83794008
	static Any GET_NUM_RESERVED_MISSION_OBJECTS(Any p0) { return invoke<Any>(0x16A80CD6, p0); } // 0x16A80CD6
	static Any GET_NUM_RESERVED_MISSION_PEDS(Any p0) { return invoke<Any>(0x6C25975C, p0); } // 0x6C25975C
	static Any GET_NUM_RESERVED_MISSION_VEHICLES(Any p0) { return invoke<Any>(0xA9A308F3, p0); } // 0xA9A308F3
	static Any _0x603FA104(Any p0) { return invoke<Any>(0x603FA104, p0); } // 0x603FA104
	static Any _0xD8FEC4F8(Any p0) { return invoke<Any>(0xD8FEC4F8, p0); } // 0xD8FEC4F8
	static Any _0x20527695(Any p0) { return invoke<Any>(0x20527695, p0); } // 0x20527695
	static Any _0x8687E285() { return invoke<Any>(0x8687E285); } // 0x8687E285
	static Any _0x744AC008() { return invoke<Any>(0x744AC008); } // 0x744AC008
	static Any _0xC3A12135() { return invoke<Any>(0xC3A12135); } // 0xC3A12135
	static Any _0x6A036061() { return invoke<Any>(0x6A036061); } // 0x6A036061
	static Any GET_NETWORK_TIME() { return invoke<Any>(0x998103C2); } // 0x998103C2
	static Any _0x98AA48E5() { return invoke<Any>(0x98AA48E5); } // 0x98AA48E5
	static Any _0x4538C4A2() { return invoke<Any>(0x4538C4A2); } // 0x4538C4A2
	static Any GET_TIME_OFFSET(Any p0, Any p1) { return invoke<Any>(0x2E079AE6, p0, p1); } // 0x2E079AE6
	static Any _0x50EF8FC6(Any p0, Any p1) { return invoke<Any>(0x50EF8FC6, p0, p1); } // 0x50EF8FC6
	static Any _0xBBB6DF61(Any p0, Any p1) { return invoke<Any>(0xBBB6DF61, p0, p1); } // 0xBBB6DF61
	static Any _0x8B4D1C06(Any p0, Any p1) { return invoke<Any>(0x8B4D1C06, p0, p1); } // 0x8B4D1C06
	static Any GET_TIME_DIFFERENCE(Any p0, Any p1) { return invoke<Any>(0x5666A837, p0, p1); } // 0x5666A837
	static Any _0x8218944E(Any p0) { return invoke<Any>(0x8218944E, p0); } // 0x8218944E
	static Any _0xF2FDF2E0() { return invoke<Any>(0xF2FDF2E0); } // 0xF2FDF2E0
	static void _0xBB7CCE49(Any p0, Any p1) { invoke<Void>(0xBB7CCE49, p0, p1); } // 0xBB7CCE49
	static void NETWORK_SET_IN_SPECTATOR_MODE(Any p0, Any p1) { invoke<Void>(0x5C4C8458, p0, p1); } // 0x5C4C8458
	static void _0x54058F5F(Any p0, Any p1, Any p2) { invoke<Void>(0x54058F5F, p0, p1, p2); } // 0x54058F5F
	static void _0xA7E36020(Any p0) { invoke<Void>(0xA7E36020, p0); } // 0xA7E36020
	static void _0x64235620(Any p0, Any p1) { invoke<Void>(0x64235620, p0, p1); } // 0x64235620
	static Any NETWORK_IS_IN_SPECTATOR_MODE() { return invoke<Any>(0x3EAD9DB8); } // 0x3EAD9DB8
	static void NETWORK_SET_IN_MP_CUTSCENE(Any p0, Any p1, Any p2) { invoke<Void>(0x8434CB43, p0, p1, p2); } // 0x8434CB43
	static Any NETWORK_IS_IN_MP_CUTSCENE() { return invoke<Any>(0x4BB33316); } // 0x4BB33316
	static Any NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Any p0) { return invoke<Any>(0x56F961E4, p0); } // 0x56F961E4
	static void SET_NETWORK_VEHICLE_RESPOT_TIMER(Any p0, Any p1) { invoke<Void>(0x2C30912D, p0, p1); } // 0x2C30912D
	static void _0xEA235081(Any p0, Any p1) { invoke<Void>(0xEA235081, p0, p1); } // 0xEA235081
	static void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(Any p0) { invoke<Void>(0x4DD46DAE, p0); } // 0x4DD46DAE
	//static Any NETWORK_CREATE_SYNCHRONISED_SCENE(float p0, float p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xB06FE3FE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xB06FE3FE
	//static void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Any p0, Any p1, char *p2, char *p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xB386713E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xB386713E
	static Any NETWORK_CREATE_SYNCHRONISED_SCENE(float p0, float p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, float p9, float p10, float p11) { return invoke<Any>(0xB06FE3FE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xB06FE3FE
	static void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Any p0, Any p1, char* p2, char* p3, float p4, float p5, int p6, Any p7, float p8) { invoke<Void>(0xB386713E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xB386713E
	static void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, char* animDict, char* animName, float speed, float speedMultiplier, int flag) { invoke<Void>(0x10DD636C, entity, netScene, animDict, animName, speed, speedMultiplier, flag); } // 0x10DD636C
	static void _0xBFFE8B5C(Any p0, Any p1, Any p2) { invoke<Void>(0xBFFE8B5C, p0, p1, p2); } // 0xBFFE8B5C
	static void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(Any p0, Any p1, Any p2) { invoke<Void>(0x3FE5B222, p0, p1, p2); } // 0x3FE5B222
	static void NETWORK_START_SYNCHRONISED_SCENE(Any p0) { invoke<Void>(0xA9DFDC40, p0); } // 0xA9DFDC40
	static void NETWORK_STOP_SYNCHRONISED_SCENE(Any p0) { invoke<Void>(0x97B1CDF6, p0); } // 0x97B1CDF6
	static Any _0x16AED87B(Any p0) { return invoke<Any>(0x16AED87B, p0); } // 0x16AED87B
	static Any _0x0679CE71(Any p0, Any p1) { return invoke<Any>(0x0679CE71, p0, p1); } // 0x0679CE71
	static Any _0xC62E77B3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<Any>(0xC62E77B3, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xC62E77B3
	static Any _0x74D6B13C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<Any>(0x74D6B13C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x74D6B13C
	static Any _0x90700C7D(Any p0) { return invoke<Any>(0x90700C7D, p0); } // 0x90700C7D
	static void _0x44BFB619() { invoke<Void>(0x44BFB619); } // 0x44BFB619
	static void NETWORK_GET_RESPAWN_RESULT(Any p0, Any p1, Any p2) { invoke<Void>(0xDDFE9FBC, p0, p1, p2); } // 0xDDFE9FBC
	static Any _0x03287FD2(Any p0) { return invoke<Any>(0x03287FD2, p0); } // 0x03287FD2
	static void _0x408A9436() { invoke<Void>(0x408A9436); } // 0x408A9436
	static void _0xFFB2ADA1(Any p0, Any p1) { invoke<Void>(0xFFB2ADA1, p0, p1); } // 0xFFB2ADA1
	static void NETWORK_END_TUTORIAL_SESSION() { invoke<Void>(0xBA57E53E); } // 0xBA57E53E
	static Any NETWORK_IS_IN_TUTORIAL_SESSION() { return invoke<Any>(0x34DD7B28); } // 0x34DD7B28
	static Any _0x755A2B3E() { return invoke<Any>(0x755A2B3E); } // 0x755A2B3E
	static Any _0xA003C40B() { return invoke<Any>(0xA003C40B); } // 0xA003C40B
	static Any _0x5E1020CC(Any p0) { return invoke<Any>(0x5E1020CC, p0); } // 0x5E1020CC
	static Any _0xE66A0B40(Any p0, Any p1) { return invoke<Any>(0xE66A0B40, p0, p1); } // 0xE66A0B40
	static void _0x72052DB3(Any p0, Any p1) { invoke<Void>(0x72052DB3, p0, p1); } // 0x72052DB3
	static Any _0xB0313590(Any p0) { return invoke<Any>(0xB0313590, p0); } // 0xB0313590
	static void NETWORK_OVERRIDE_CLOCK_TIME(int Hours, int Minutes, int Seconds) { invoke<Void>(0xC077BCD6, Hours, Minutes, Seconds); } // 0xC077BCD6
	static void _0xC4AEAF49() { invoke<Void>(0xC4AEAF49); } // 0xC4AEAF49
	static Any _0x2465296D() { return invoke<Any>(0x2465296D); } // 0x2465296D
	static Any NETWORK_ADD_ENTITY_AREA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x51030E5B, p0, p1, p2, p3, p4, p5); } // 0x51030E5B
	static Any _0x4C2C2B12(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x4C2C2B12, p0, p1, p2, p3, p4, p5); } // 0x4C2C2B12
	static Any NETWORK_REMOVE_ENTITY_AREA(Any p0) { return invoke<Any>(0xEAB97F25, p0); } // 0xEAB97F25
	static Any _0x69956127(Any p0) { return invoke<Any>(0x69956127, p0); } // 0x69956127
	static Any _0xCB1CD6D3(Any p0) { return invoke<Any>(0xCB1CD6D3, p0); } // 0xCB1CD6D3
	static Any _0xC6D53AA0(Any p0) { return invoke<Any>(0xC6D53AA0, p0); } // 0xC6D53AA0
	static void _0x155465EE(Any p0, Any p1) { invoke<Void>(0x155465EE, p0, p1); } // 0x155465EE
	static Any _0x29532731() { return invoke<Any>(0x29532731); } // 0x29532731
	static void _0xD760CAD5() { invoke<Void>(0xD760CAD5); } // 0xD760CAD5
	static Any _0x231CFD12() { return invoke<Any>(0x231CFD12); } // 0x231CFD12
	static Any NETWORK_DOES_TUNABLE_EXIST(Any p0, Any p1) { return invoke<Any>(0x9FCE9C9A, p0, p1); } // 0x9FCE9C9A
	static Any _0xE4B3726A(Any p0, Any p1, Any p2) { return invoke<Any>(0xE4B3726A, p0, p1, p2); } // 0xE4B3726A
	static Any _0x41E8912A(Any p0, Any p1, Any p2) { return invoke<Any>(0x41E8912A, p0, p1, p2); } // 0x41E8912A
	static Any _0x8A04E1FE(Any p0, Any p1) { return invoke<Any>(0x8A04E1FE, p0, p1); } // 0x8A04E1FE
	static Any _0xA78571CA(Any p0) { return invoke<Any>(0xA78571CA, p0); } // 0xA78571CA
	static Any _0x053BB329() { return invoke<Any>(0x053BB329); } // 0x053BB329
	static void NETWORK_RESET_BODY_TRACKER() { invoke<Void>(0x3914463F); } // 0x3914463F
	static Any _0x17CBC608() { return invoke<Any>(0x17CBC608); } // 0x17CBC608
	static Any _0xBFAA349B(Any p0) { return invoke<Any>(0xBFAA349B, p0); } // 0xBFAA349B
	static Any _0xBEB7281A(Any p0, Any p1) { return invoke<Any>(0xBEB7281A, p0, p1); } // 0xBEB7281A
	static Any NETWORK_EXPLODE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x0E1B38AE, p0, p1, p2, p3); } // 0x0E1B38AE
	static void _0xBC54371B(Any p0) { invoke<Void>(0xBC54371B, p0); } // 0xBC54371B
	static void _0x644141C5(int p0, float p1, float p2, float p3, float p4) { invoke<Void>(0x644141C5, p0, p1, p2, p3, p4); } // 0x644141C5
	static void NETWORK_SET_PROPERTY_ID(Any p0) { invoke<Void>(0x5A74E873, p0); } // 0x5A74E873
	static void _0x38BC35C8() { invoke<Void>(0x38BC35C8); } // 0x38BC35C8
	static void _0x53C9563C(Any p0) { invoke<Void>(0x53C9563C, p0); } // 0x53C9563C
	static void _0x6B97075B(Any p0) { invoke<Void>(0x6B97075B, p0); } // 0x6B97075B
	static Any _0x965EA007() { return invoke<Any>(0x965EA007); } // 0x965EA007
	static Any _0xEEFC8A55() { return invoke<Any>(0xEEFC8A55); } // 0xEEFC8A55
	static void _0x866D1B67(Any p0) { invoke<Void>(0x866D1B67, p0); } // 0x866D1B67
	static Any _0xED4A272F() { return invoke<Any>(0xED4A272F); } // 0xED4A272F
	static Any _0x4ACF110C(Any p0) { return invoke<Any>(0x4ACF110C, p0); } // 0x4ACF110C
	static Any _0x1AA3A0D5(Any p0) { return invoke<Any>(0x1AA3A0D5, p0); } // 0x1AA3A0D5
	static Any _0x37877757(Any p0) { return invoke<Any>(0x37877757, p0); } // 0x37877757
	static Any _0x1CF89DA5(Any p0) { return invoke<Any>(0x1CF89DA5, p0); } // 0x1CF89DA5
	static Any _0x16E53875(Any p0, Any p1) { return invoke<Any>(0x16E53875, p0, p1); } // 0x16E53875
	static void _0x365C50EE(Any p0, Any p1) { invoke<Void>(0x365C50EE, p0, p1); } // 0x365C50EE
	static Any _0x25E2DBA9() { return invoke<Any>(0x25E2DBA9); } // 0x25E2DBA9
	static void SET_STORE_ENABLED(Any p0) { invoke<Void>(0xC1F6443B, p0); } // 0xC1F6443B
	static Any _0x1FDC75DC(Any p0) { return invoke<Any>(0x1FDC75DC, p0); } // 0x1FDC75DC
	static void _0xCA7A0A49() { invoke<Void>(0xCA7A0A49); } // 0xCA7A0A49
	static Any _0x44A58B0A(Any p0) { return invoke<Any>(0x44A58B0A, p0); } // 0x44A58B0A
	static Any _0xD32FA11F() { return invoke<Any>(0xD32FA11F); } // 0xD32FA11F
	static void _0xA7FA70AE() { invoke<Void>(0xA7FA70AE); } // 0xA7FA70AE
	static void _0xCC7DCE24() { invoke<Void>(0xCC7DCE24); } // 0xCC7DCE24
	static Any _0x70F6D3AD() { return invoke<Any>(0x70F6D3AD); } // 0x70F6D3AD
	static Any _0x2B7B57B3(Any p0) { return invoke<Any>(0x2B7B57B3, p0); } // 0x2B7B57B3
	static Any _0xBAF52DD8(Any p0) { return invoke<Any>(0xBAF52DD8, p0); } // 0xBAF52DD8
	static Any _0x9B9AFFF1(Any p0) { return invoke<Any>(0x9B9AFFF1, p0); } // 0x9B9AFFF1
	static void _0xC38E9DB0() { invoke<Void>(0xC38E9DB0); } // 0xC38E9DB0
	static Any _0x32A4EB22() { return invoke<Any>(0x32A4EB22); } // 0x32A4EB22
	static Any _0x9262744C() { return invoke<Any>(0x9262744C); } // 0x9262744C
	static Any _0x08243B79(Any p0, Any p1) { return invoke<Any>(0x08243B79, p0, p1); } // 0x08243B79
	static Any _0x798D6C27() { return invoke<Any>(0x798D6C27); } // 0x798D6C27
	static Any _0xE69E8D0D() { return invoke<Any>(0xE69E8D0D); } // 0xE69E8D0D
	static Any _0x742075FE() { return invoke<Any>(0x742075FE); } // 0x742075FE
	static Any _0xCE569932() { return invoke<Any>(0xCE569932); } // 0xCE569932
	static Any _0x82146BE9() { return invoke<Any>(0x82146BE9); } // 0x82146BE9
	static void _0x133FF2D5() { invoke<Void>(0x133FF2D5); } // 0x133FF2D5
	static Any _0xCBA7242F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xCBA7242F, p0, p1, p2, p3, p4, p5); } // 0xCBA7242F
	static Any _0xDED82A6E(Any p0, Any p1, Any p2) { return invoke<Any>(0xDED82A6E, p0, p1, p2); } // 0xDED82A6E
	static Any _0x40CF0783(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x40CF0783, p0, p1, p2, p3); } // 0x40CF0783
	static Any _0x4609D596(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4609D596, p0, p1, p2, p3); } // 0x4609D596
	static Any _0x4C2C0D1F(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4C2C0D1F, p0, p1, p2, p3); } // 0x4C2C0D1F
	static Any _0x9EFBD5D1(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x9EFBD5D1, p0, p1, p2, p3); } // 0x9EFBD5D1
	static Any _0xA6D8B798(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xA6D8B798, p0, p1, p2, p3, p4); } // 0xA6D8B798
	static Any _0x67E74842(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x67E74842, p0, p1, p2, p3, p4); } // 0x67E74842
	static Any SET_BALANCE_ADD_MACHINE(Any p0, Any p1) { return invoke<Any>(0xE123C7AC, p0, p1); } // 0xE123C7AC
	static Any SET_BALANCE_ADD_MACHINES(Any p0, Any p1, Any p2) { return invoke<Any>(0x22C33603, p0, p1, p2); } // 0x22C33603
	static Any _0x37F5BD93(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x37F5BD93, p0, p1, p2, p3); } // 0x37F5BD93
	static Any _0x1CFB3F51(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x1CFB3F51, p0, p1, p2, p3); } // 0x1CFB3F51
	static Any _0x87D1E6BD(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x87D1E6BD, p0, p1, p2, p3); } // 0x87D1E6BD
	static void _0x021D5A94() { invoke<Void>(0x021D5A94); } // 0x021D5A94
	static Any _0x4908A514() { return invoke<Any>(0x4908A514); } // 0x4908A514
	static Any _0x50296140() { return invoke<Any>(0x50296140); } // 0x50296140
	static Any _0x3970B0DA() { return invoke<Any>(0x3970B0DA); } // 0x3970B0DA
	static Any _0xC1487110() { return invoke<Any>(0xC1487110); } // 0xC1487110
	static Any _0xCC2356E3() { return invoke<Any>(0xCC2356E3); } // 0xCC2356E3
	static Any _0x2DE69817() { return invoke<Any>(0x2DE69817); } // 0x2DE69817
	static Any _0x81BD8D3B() { return invoke<Any>(0x81BD8D3B); } // 0x81BD8D3B
	static Any _0x8E1D8F78() { return invoke<Any>(0x8E1D8F78); } // 0x8E1D8F78
	static void _0x0D35DD93() { invoke<Void>(0x0D35DD93); } // 0x0D35DD93
	static Any _0x8F3137E6(Any p0) { return invoke<Any>(0x8F3137E6, p0); } // 0x8F3137E6
	static Any _0xB9137BA7(Any p0) { return invoke<Any>(0xB9137BA7, p0); } // 0xB9137BA7
	static Any _0x9FEEAA9C(Any p0) { return invoke<Any>(0x9FEEAA9C, p0); } // 0x9FEEAA9C
	static Any _0x5E8A7559(Any p0) { return invoke<Any>(0x5E8A7559, p0); } // 0x5E8A7559
	static Any _0x331AEABF(Any p0) { return invoke<Any>(0x331AEABF, p0); } // 0x331AEABF
	static Any _0x0E5E8E5C(Any p0) { return invoke<Any>(0x0E5E8E5C, p0); } // 0x0E5E8E5C
	static Any _0xA5A0C695(Any p0) { return invoke<Any>(0xA5A0C695, p0); } // 0xA5A0C695
	static Any _0x91534C6E(Any p0) { return invoke<Any>(0x91534C6E, p0); } // 0x91534C6E
	static Any _0x744A9EA5(Any p0, Any p1) { return invoke<Any>(0x744A9EA5, p0, p1); } // 0x744A9EA5
	static void _0xA19A238D(Any p0, Any p1) { invoke<Void>(0xA19A238D, p0, p1); } // 0xA19A238D
	static Any _0xFF7D44E6(Any p0, Any p1) { return invoke<Any>(0xFF7D44E6, p0, p1); } // 0xFF7D44E6
	static Any _0xA2C5BD9D(Any p0) { return invoke<Any>(0xA2C5BD9D, p0); } // 0xA2C5BD9D
	static Any _0xA850DDE1(Any p0) { return invoke<Any>(0xA850DDE1, p0); } // 0xA850DDE1
	static Any _0x8F6754AE(Any p0) { return invoke<Any>(0x8F6754AE, p0); } // 0x8F6754AE
	static Any _0x1E34953F(Any p0, Any p1) { return invoke<Any>(0x1E34953F, p0, p1); } // 0x1E34953F
	static Any _0x771FE190(Any p0, Any p1) { return invoke<Any>(0x771FE190, p0, p1); } // 0x771FE190
	static Any _0x3276D9D3(Any p0, Any p1) { return invoke<Any>(0x3276D9D3, p0, p1); } // 0x3276D9D3
	static Any _0x41A0FB02(Any p0, Any p1) { return invoke<Any>(0x41A0FB02, p0, p1); } // 0x41A0FB02
	static Any _0x11DC0F27(Any p0) { return invoke<Any>(0x11DC0F27, p0); } // 0x11DC0F27
	static Any _0x0DEB3F5A(Any p0) { return invoke<Any>(0x0DEB3F5A, p0); } // 0x0DEB3F5A
	static Any _0x84315226(Any p0, Any p1) { return invoke<Any>(0x84315226, p0, p1); } // 0x84315226
	static Any _0x38FC2EEB(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x38FC2EEB, p0, p1, p2, p3, p4); } // 0x38FC2EEB
	static Any _0x1C4F9FDB(Any p0) { return invoke<Any>(0x1C4F9FDB, p0); } // 0x1C4F9FDB
	static Any _0xA69AE16C(Any p0) { return invoke<Any>(0xA69AE16C, p0); } // 0xA69AE16C
	static Any _0xF50BC67A(Any p0) { return invoke<Any>(0xF50BC67A, p0); } // 0xF50BC67A
	static Any _0xB3BBD241(Any p0) { return invoke<Any>(0xB3BBD241, p0); } // 0xB3BBD241
	static Any _0x70A2845C(Any p0, Any p1) { return invoke<Any>(0x70A2845C, p0, p1); } // 0x70A2845C
	static Any _0x346B506C(Any p0) { return invoke<Any>(0x346B506C, p0); } // 0x346B506C
	static void _0x0095DB71() { invoke<Void>(0x0095DB71); } // 0x0095DB71
	static Any _0xAD334B40(Any p0, Any p1, Any p2) { return invoke<Any>(0xAD334B40, p0, p1, p2); } // 0xAD334B40
	static Any _0x980D45D7(Any p0, Any p1, Any p2) { return invoke<Any>(0x980D45D7, p0, p1, p2); } // 0x980D45D7
	static Any _0x48CCC328(Any p0, Any p1, Any p2) { return invoke<Any>(0x48CCC328, p0, p1, p2); } // 0x48CCC328
	static Any _0x8E664EFD() { return invoke<Any>(0x8E664EFD); } // 0x8E664EFD
	static Any _0x611E0BE2() { return invoke<Any>(0x611E0BE2); } // 0x611E0BE2
	static Any _0xF0211AC1() { return invoke<Any>(0xF0211AC1); } // 0xF0211AC1
	static Any _0x1F0DD8AF() { return invoke<Any>(0x1F0DD8AF); } // 0x1F0DD8AF
	static void _0x405ECA16() { invoke<Void>(0x405ECA16); } // 0x405ECA16
	static Any _0x9567392B(Any p0, Any p1) { return invoke<Any>(0x9567392B, p0, p1); } // 0x9567392B
	static Any _0xF79FFF3C() { return invoke<Any>(0xF79FFF3C); } // 0xF79FFF3C
	static Any _0xA7F3F82B() { return invoke<Any>(0xA7F3F82B); } // 0xA7F3F82B
	static Any _0x410C61D1() { return invoke<Any>(0x410C61D1); } // 0x410C61D1
	static Any _0x0D4F845D(Any p0) { return invoke<Any>(0x0D4F845D, p0); } // 0x0D4F845D
	static void _0xE13C1F7F() { invoke<Void>(0xE13C1F7F); } // 0xE13C1F7F
	static void _0x213C6D36(Any p0) { invoke<Void>(0x213C6D36, p0); } // 0x213C6D36
	static void _0x511E6F50(Any p0) { invoke<Void>(0x511E6F50, p0); } // 0x511E6F50
	static Any _0xB4668B23(Any p0) { return invoke<Any>(0xB4668B23, p0); } // 0xB4668B23
	static Any _0x30B51753(Any p0, Any p1, Any p2) { return invoke<Any>(0x30B51753, p0, p1, p2); } // 0x30B51753
	static Any _0x02DAD93F() { return invoke<Any>(0x02DAD93F); } // 0x02DAD93F
	static Any _0x2D947814(Any p0) { return invoke<Any>(0x2D947814, p0); } // 0x2D947814
	static Any _0x37A28C26() { return invoke<Any>(0x37A28C26); } // 0x37A28C26
	static Any _0x11E8B5CD() { return invoke<Any>(0x11E8B5CD); } // 0x11E8B5CD
	static Any _0x429AEAB3() { return invoke<Any>(0x429AEAB3); } // 0x429AEAB3
	static Any TEXTURE_DOWNLOAD_REQUEST(int PlayerHandle, char* FilePath, char* Name, BOOL p3) { return invoke<Any>(0xAD546CC3, PlayerHandle, FilePath, Name, p3); } // 0xAD546CC3
	static Any _0x1856D008(Any p0, Any p1, Any p2) { return invoke<Any>(0x1856D008, p0, p1, p2); } // 0x1856D008
	static Any _0x68C9AF69(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x68C9AF69, p0, p1, p2, p3, p4, p5); } // 0x68C9AF69
	static void TEXTURE_DOWNLOAD_RELEASE(Any p0) { invoke<Void>(0xEE8D9E70, p0); } // 0xEE8D9E70
	static Any _0xE4547765(Any p0) { return invoke<Any>(0xE4547765, p0); } // 0xE4547765
	static Any TEXTURE_DOWNLOAD_GET_NAME(Any p0) { return invoke<Any>(0xA40EF65A, p0); } // 0xA40EF65A
	static Any _0x03225BA3(Any p0) { return invoke<Any>(0x03225BA3, p0); } // 0x03225BA3
	static Any _0x4DEBC227() { return invoke<Any>(0x4DEBC227); } // 0x4DEBC227
	static Any _0x5C065D55() { return invoke<Any>(0x5C065D55); } // 0x5C065D55
	static Any _0x0CA1167F() { return invoke<Any>(0x0CA1167F); } // 0x0CA1167F
	static Any _0x424C6E27() { return invoke<Any>(0x424C6E27); } // 0x424C6E27
	static Any _0xD3BBE42F() { return invoke<Any>(0xD3BBE42F); } // 0xD3BBE42F
	static Any _0xBDBB5948() { return invoke<Any>(0xBDBB5948); } // 0xBDBB5948
	static Any _0x97287D68() { return invoke<Any>(0x97287D68); } // 0x97287D68
	static Any _0xC6EA802E() { return invoke<Any>(0xC6EA802E); } // 0xC6EA802E
	static Any _0xFD261E30(Any p0) { return invoke<Any>(0xFD261E30, p0); } // 0xFD261E30
	static Any _0x8570DD34(Any p0, Any p1, Any p2) { return invoke<Any>(0x8570DD34, p0, p1, p2); } // 0x8570DD34
	static void _0x273C6180() { invoke<Void>(0x273C6180); } // 0x273C6180
	static void _0x371BBA08() { invoke<Void>(0x371BBA08); } // 0x371BBA08
	static void _0xA100CC97(Any p0) { invoke<Void>(0xA100CC97, p0); } // 0xA100CC97
	static void _0xBB2D33D3(Any p0, Any p1) { invoke<Void>(0xBB2D33D3, p0, p1); } // 0xBB2D33D3
}
