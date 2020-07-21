#include "TitleState.h"
#include <Input/Input.h>
#include "Bonk.h"
#include "bitmaps/bonk_title.hpp"


TitleState* TitleState::instance = nullptr;
TitleState::TitleState(Sprite* sprite) : State(sprite)
{
	instance = this;
}
void TitleState::start(Bonk& _game)
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
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, [](){
		if(instance->titleCursor < 1){
			instance->titleCursor++;
		}
	});
}
TitleState::~TitleState()
{
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
}
void TitleState::draw()
{
	display->clear(TFT_BLACK);
	// drawBitmap(30, 14, bonk_title, TFT_WHITE, 2);
	display->drawMonochromeIcon(bonk_title, 30, 14, 56, 20, 2, TFT_WHITE);
	display->setTextSize(1);
	display->setTextFont(2);
	display->setCursor(32, 72);
	display->setTextColor(TFT_WHITE);
	display->printCenter("START");
	display->setCursor(46, 96);
	display->printCenter("QUIT");
	display->drawRect(14, 69 + titleCursor * 24, 100, 22, blinkState ? TFT_RED : TFT_BLACK);
	display->drawRect(15, 70 + titleCursor * 24, 98, 20, blinkState ? TFT_RED : TFT_BLACK);
}
void TitleState::update(uint _time, Bonk& game)
{
	blinkMicros+=_time;
	if(blinkMicros > 200000)
	{
		blinkState = !blinkState;
		blinkMicros = 0;
	}
}