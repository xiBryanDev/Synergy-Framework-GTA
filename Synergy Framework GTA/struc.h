#pragma once
#define JOIN_HELPER(x, y) x##y
#define JOIN(x, y) JOIN_HELPER(x, y)
#define TYPE_PAD(size) char JOIN(_pad_, __COUNTER__)[size]
#define TYPE_VARIADIC_BEGIN(name) name { union {
#define TYPE_BEGIN(name, size) name { union { TYPE_PAD(size)
#define TYPE_END(...) }; } __VA_ARGS__
#define TYPE_FIELD(field, offset) struct { TYPE_PAD(offset); field; }
#define TYPE_FZERO(field, offset) struct { field; }


TYPE_BEGIN(struct CObjModelInfo, 0xFFF);
TYPE_FIELD(unsigned int modelType, 0x1B8);
TYPE_END();


#define PAD(x,s) char unk##x[s]

struct GtaThread {
	void* classData;//0x0
	unsigned int threadID;//0x4
	unsigned int nameHash;//0x8
	//unsigned char unk1[0x5C];//0xC
	PAD(0, 0x54 - 0xC);//0xC
	void* localDataPointer;//0x54
	PAD(1, 0x68 - 0x58);//0x58
	char threadName[0x4 * 6];//0x68
	//30CGameScriptHandlerNetComponent is 0xAC
	/*
	virtual void unkfunc1();//0x0
	virtual void unkfunc2();//0x4
	virtual void unkfunc3();//0x8
	virtual void unkfunc4();//0xC
	virtual void unkfunc5();//0x10
	virtual void terminate_thread();//0x14
	*/


};


struct ClassData {//this would be the 0x19...
	unsigned int base;

	unsigned int getClassDataAddress() {
		return (unsigned int)&base;
	}

	//alternate us using the typedef fnptr and doing fnptr call(unsigned int offset)...
	template <typename T>
	T(*call(unsigned int offset))(...) {//currently untested
		unsigned int __opd_s = *(volatile unsigned int*)(getClassDataAddress() + offset);
		T(*func)(...) = (T(*)(...)) & __opd_s;
		return func;
	}
	/*template <typename RET>
	fnptr<RET> call(unsigned int offset) {
	unsigned int opd_s = *(volatile unsigned int*)(getClassDataAddress()+offset);
	fnptr<RET> func = fnptr&opd_s;
	return func;
	}*/
};

struct CNonPhysicalPlayerData {
	ClassData* classData;//0x0
	unsigned int unk1;//0x4
	unsigned int playerIndex;//0x8
};
#define PAD(x,s) char unk##x[s]

struct CPlayerInfo {//this is at offset 0xBD0 from entity class, such as CPed
	ClassData* classData;//0x0
	unsigned char unk1[0x4 * 3];//0x4
	char name[0x4 * 5];//0x10
	char region[0x4 * 2];//0x24
	PAD(2, 0x40 - 0x2C);//0x2C
	uint64_t uuid;//0x40
	PAD(3, 0x160 - 0x48);//0x48
	void* cPed;//0x160  this is the CPed of the player
	//spoofed name is at 0x84 (0x10 + 0x74)
};

struct CNetGamePlayer {
	ClassData* classData;//0x0
	unsigned int unk1;//0x4
	CNonPhysicalPlayerData* nonPhysicalPlayerData;//0x8
	unsigned char unk2[0xC];//0xC
	unsigned int unk3;//0x18
	unsigned char unk4[0xD];//0x1C
	unsigned char playerIndex;//0x29   0 through 17 ya know
	unsigned char unk41[0x38 - 0x2A];//0x2A
	unsigned int team;//0x38
	unsigned int unk5;//0x3C
	CNetGamePlayer* myCNetgamePlayer;//0x40
	unsigned char unk6[0x4 * 3];//0x44
	CNetGamePlayer* myCNetgamePlayer1;//0x50
	unsigned char unk7[0x4 * 3];//0x54
	CNetGamePlayer* myCNetgamePlayer2;//0x60
	unsigned char unk8[0x4 * 5];//0x64
	CPlayerInfo* playerInfo;//0x78
	unsigned char unk9[0xF4];//0x7C
	unsigned char unk10[0x1];//0x170
	unsigned char rockstarDev;//0x171
	unsigned char rockstarQA;//0x172
	unsigned char isCheater;//0x173
	unsigned char unk12[0xFFFFFF];//0x174 just here to note that it's not at 0x174

	//offset 0xBE is crew name
	//offset 0xD7 is crew tag
	void* getWeirdNetInfo() {
		return classData->call<void*>(0x1C)(this);//this returns CPlayerInfo + 0x10
	}
};

struct CGameScriptId {
	ClassData* classData;//0x0
	unsigned int unk1;
	char scriptName[0x4 * 0x8];//max size, but might be less
};



struct CGameScriptHandlerNetComponent {//this is used for setting memory in script to be shared
	ClassData* classData;//0x0
	void* cGameScriptHandlerNetwork;//0x4
	unsigned int unk1;//0x8  -- used in some places
	//0x34 is a cnetgameplayer
	int getHost() {
		unsigned int unkStruct = *(unsigned int*)((unsigned int)this + 0x1C);
		if (unkStruct == 0)
			return -1;
		CNetGamePlayer* p = (CNetGamePlayer*)*(int*)(unkStruct + 0x8);
		return p->playerIndex;
	}
};
struct CGameScriptHandlerNetwork {
	ClassData* classData;//0x0
	unsigned char unk1[0x8];//0x4
	void* gtaThread;//0xC
	unsigned char unk2[0x14];//0x10
	CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponentSyncOne;//0x24   this one is used in CGameScriptHandlerNetComponent__setMemorySyncPlayers and CGameScriptHandlerNetComponent__setMemorySyncHost as r3
	unsigned char unk3[0x30];//0x28
	CGameScriptHandlerNetComponent* cGameScriptHandlerNetComponent;//0x58
	unsigned char unk4[0x10];//0x5C
	CGameScriptId cGameScriptId;//0x6C         //0x38 - //this may be bigger in size, unsure 
};

template <typename T>
class ArrayList {
private:
	T* arr;
	int size;
	int count;

	void resize(int newSize) {
		T* tmpArray = arr;
		size = newSize;
		//arr = (T*)_malloc(newSize * sizeof(T));
		//arr = (T*)call<char*>(0x10310)(newSize * sizeof(T));//gta malloc
		arr = (T*)0x10030000;
		if (tmpArray != 0) {
			memcpy(arr, tmpArray, sizeof(T)* count);//copy old values over
			//_free(tmpArray);
		}
	}
	void grow() {
		resize(size * 2);//double in size 
	}
public:
	ArrayList() {
		arr = 0;
		size = 0;
		count = 0;
		resize(1);
	}
	~ArrayList() {
		//printf("\n\n\n\n\n\n\n\n\n\nDESTRUCTOR OF ARRAYLIST CALLED!\n\n\n\n\n\n\n\n\n");
		//_free(arr);
	}
	int indexOf(T entity) {
		for (int i = 0; i < count; i++) {
			if (entity.equals(arr[i])) {
				return i;
			}
		}
		return -1;
	}

	int getCount() {
		return count;
	}

	void clear() {
		count = 0;
	}

	T* get(int index) {
		return &arr[index];
	}

	void add(T entity) {

		int i = indexOf(entity);
		if (i != -1)
			return;//do not add, already in array

		if (count == size)
			grow();
		memcpy((void*)&arr[count], (void*)&entity, sizeof(entity));
		count++;
	}

	int remove(T entity) {

		int i = indexOf(entity);
		if (i == -1)
			return -1;//not found


		memcpy(&arr[i], &arr[i + 1], sizeof(T)* (count - i - 1));


		count--;

		return i;
	}
};

class StackFrame {
private:
	void* stack;
	unsigned int size;
public:
	StackFrame(void* _stack, unsigned int _size) :
		stack(_stack), size(_size)
	{

	}
	void* get(unsigned int offset) {
		return (void*)((unsigned int)stack + (size - offset));
	}
	template <typename T>
	void setArg(unsigned int offset, T value) {
		*(T*)get(offset) = value;
	}
	template <typename T>
	T getArg(unsigned int offset) {
		return *(T*)get(offset);
	}
};