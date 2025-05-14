#include "stdafx.h"


namespace scheduler
{
	enum pipeline
	{
		// Asynchronuous pipeline, disconnected from the game
		async,

		// The game's rendering pipeline
		renderer,

		aimbot,

		hud,

		respawn,

		count
	};


	extern bool bypassTime1;
	void loop(pipeline thread, void(*handler)(), int interval = 0);
	void once(pipeline thread, void(*handler)(), int interval = 0);
	void remove(pipeline thread, void(*handler)());
	bool IS_PLAYER_ONLINE();
	void start();
	void stop();
}
extern	bool timer;
class thread
{
public:
	sys_ppu_thread_t id = SYS_PPU_THREAD_ID_INVALID;

	thread() = default;

	thread(void(*callback)(), int priority = 1000, int stackSize = 2048, const char* name = "", int flag = SYS_PPU_THREAD_CREATE_JOINABLE)
	{
		sys_ppu_thread_create(&id, [](uint64_t arg) -> void
			{
				if (arg)
					reinterpret_cast<void(*)()>((uint32_t)arg)();

				sys_ppu_thread_exit(0);

			}, reinterpret_cast<uint64_t>(callback), priority, stackSize, flag, name);
	}

	bool running()
	{
		return (id != SYS_PPU_THREAD_ID_INVALID);
	}

	bool join()
	{
		if (!running())
			return false;

		uint64_t exitCode;
		return sys_ppu_thread_join(id, &exitCode) == CELL_OK;
	}
};


