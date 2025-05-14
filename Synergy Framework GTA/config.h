#pragma once
#include "stdafx.h"


class Configuration
{
public:
	struct
	{
		bool godmode{}, NoRagdoll{}, Invisibility{}, NeverWanted{}, UnlimitedAmmo{}, rapidfire{}, ShotKill{}, noclip{};
	}self;
};

extern Configuration* Config;
