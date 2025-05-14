#include "scheduler.h"
#include "menu.h"
#include "animation.h"
#include "Native.h"
#include "frz.h"
#define I_AM_ONLINE (*(char*)0x223F0C0)

bool timer;
namespace scheduler
{
	static constexpr int taskStackMax = (30);




	struct task
	{
		void(*handler)();
		int interval;
		int lastCall;
		bool temporary;
	};

	struct task_pipeline
	{
		task stack[taskStackMax];

		void add(void(*handler)(), int interval, bool temporary)
		{
			for (int i = 0; i < taskStackMax; i++)
			{
				if (stack[i].handler)
					continue;

				stack[i].handler = handler;
				stack[i].interval = interval;
				stack[i].lastCall = Sys_Milliseconds();
				stack[i].temporary = temporary;
				return;
			}
		}

		void remove(void(*handler)())
		{
			for (int i = 0; i < taskStackMax; i++)
			{
				if (stack[i].handler == handler)
				{
					stack[i].handler = nullptr;
					stack[i].interval = 0;
					stack[i].lastCall = 0;
					stack[i].temporary = false;
					return;
				}
			}
		}

		void execute()
		{
			int currentTime = Sys_Milliseconds();
			for (int i = 0; i < taskStackMax; i++)
			{
				if (!stack[i].handler)
					continue;

				if (currentTime > stack[i].lastCall + stack[i].interval)
				{
					stack[i].handler();
					stack[i].lastCall = currentTime;

					if (stack[i].temporary)
					{
						stack[i].handler = 0;
						stack[i].interval = 0;
						stack[i].lastCall = 0;
						stack[i].temporary = false;
					}
				}
			}
		}
	};

	task_pipeline pipelines[-+-+count];
	thread asyncThread;
	bool killAsyncThread = false;

	void loop(pipeline thread, void(*handler)(), int interval)
	{
		pipelines[thread].add(handler, interval, false);
	}

	void once(pipeline thread, void(*handler)(), int interval)
	{
		pipelines[thread].add(handler, interval, true);

	}

	void remove(pipeline thread, void(*handler)())
	{

		pipelines[thread].remove(handler);

	}


	bool IS_PLAYER_ONLINE()
	{
		pipelines[renderer].execute();

		if (I_AM_ONLINE)//also NETWORK_IS_GAME_IN_PROGRESS
		if (!strncmp(SCRIPT::GET_THIS_SCRIPT_NAME(), "freemode", strlen("freemode"))) {
			//inFreemode = true;
			freemodeScriptGtaThread = getCurrentGtaThread();
			freemodeScriptCGameScriptHandlerNetwork = getCurrentCGameScriptHandlerNetwork();
		}
		g_Menu->Run();
		g_anim.run_frame();
		return true;
	}

	void start()
	{
		asyncThread = thread([]
			{
				while (!killAsyncThread)
				{
					pipelines[async].execute();


					sys_timer_usleep(1337);
				}
			}, 420, 8 * 1024, "Scheduler");
	}

	void stop()
	{
		killAsyncThread = true;
		asyncThread.join();
	}
}