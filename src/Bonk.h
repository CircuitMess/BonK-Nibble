#ifndef BONK_H
#define BONK_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include <gpio.h>
#include <avr/pgmspace.h>
#include <Support/Context.h>
#include "../Nibble.hpp"
#include <UI/Image.h>
#include <Display/Sprite.h>

extern Context* runningContext;
extern bool exitingGame;

namespace Bonk {
	class State;
	
	class Bonk : public Context, public LoopListener {
	public:
		Bonk(Display& Display);

		void draw() override;
		void start() override;
		void loop(uint _time) override;
		void stop() override;
		void pack() override;
		
		void newGame();
		void pauseGame();
		void gameOver();
		void resumeGame();
		void quitGame();

	private:
		State* state;
		State* pausedGameState = nullptr;
		Display* display;
		Sprite* canvas;
	};
};
#endif