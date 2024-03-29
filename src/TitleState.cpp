#include "TitleState.h"
#include <Input/Input.h>
#include "Bonk.h"
#include "bitmaps/bonk_title.hpp"
#include <Audio/Piezo.h>

Bonk::TitleState* Bonk::TitleState::instance = nullptr;
Bonk::TitleState::TitleState(Sprite* sprite) : State(sprite)
{
	instance = this;
	titleCursor = 0;
	blinkState = 0;
}
void Bonk::TitleState::start(Bonk& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		switch (instance->titleCursor)
		{
		case 0:
			instance->game->newGame();
			break;
		case 1:
			instance->game->pop();
			break;
		
		default:
			break;
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		if(instance->titleCursor > 0){
			instance->titleCursor--;
			Piezo.tone(200, 50);
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, [](){
		if(instance->titleCursor < 1){
			instance->titleCursor++;
			Piezo.tone(200, 50);
		}
	});
}
void Bonk::TitleState::stop()
{
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
}
void Bonk::TitleState::draw()
{
	display->clear(TFT_BLACK);
	// drawBitmap(30, 14, bonk_title, TFT_WHITE, 2);
	display->drawMonochromeIcon(bonk_title, 14, 8, 51, 28, 2, TFT_DARKGREY);
	display->drawMonochromeIcon(bonk_title, 12, 6, 51, 28, 2, TFT_WHITE);
	display->setTextSize(1);
	display->setTextFont(2);
	display->setCursor(32, 77);
	display->setTextColor(TFT_WHITE);
	display->printCenter("START");
	display->setCursor(46, 101);
	display->printCenter("QUIT");
	display->drawRect(14, 74 + titleCursor * 24, 100, 22, blinkState ? TFT_RED : TFT_BLACK);
	display->drawRect(15, 75 + titleCursor * 24, 98, 20, blinkState ? TFT_RED : TFT_BLACK);
}
void Bonk::TitleState::update(uint _time, Bonk& game)
{
	blinkMicros+=_time;
	if(blinkMicros > 200000)
	{
		blinkState = !blinkState;
		blinkMicros = 0;
	}
}