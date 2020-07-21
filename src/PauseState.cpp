#include "PauseState.h"
#include <Input/Input.h>
#include "Bonk.h"
#include "bitmaps/bonk_title.hpp"


PauseState* PauseState::instance = nullptr;
PauseState::PauseState(Sprite* sprite) : State(sprite)
{
	instance = this;
}
void PauseState::start(Bonk& _game)
{
	game = &_game;
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->game->resumeGame();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->quitGame();
	});
}
PauseState::~PauseState()
{
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}
void PauseState::draw()
{
	display->setTextFont(1);
	display->setTextSize(2);
	display->setTextColor(TFT_WHITE);
	display->clear(TFT_BLACK);
	display->setCursor(0, display->height()/2 - 30);
	display->setTextFont(2);
	display->setTextSize(2);
	display->printCenter("Paused");
	display->setCursor(4, 110);
	display->setTextSize(1);
	display->printCenter("A: resume    B: quit");
}
void PauseState::update(uint _time, Bonk& game)
{
}