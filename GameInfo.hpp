#ifndef GAME_INFO
#define GAME_INFO

class Context;
struct GameInfo {
	const char* title;
	const char* description;
	const uint16_t* icon;
	Context* (*launch)(Display& display);
};
#endif

#include <Arduino.h>
#include <Display/Display.h>
#include "src/bitmaps/spacerocks_icon.hpp"
#include "src/SpaceRocks.h"

const GameInfo SpaceRocksInfo {
		"SpaceRocks",
		"Shoot the asteroids to survive!",
		spacerocks_icon,
		[](Display& display) -> Context* { return new SpaceRocks(display); }
};