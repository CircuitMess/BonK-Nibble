#include "Bonk.h"
#include "TitleState.h"
#include "GameState.h"
#include "PauseState.h"
#include "State.hpp"

Bonk::Bonk::Bonk(Display& display) : Context(display), display(&display), canvas(display.getBaseSprite()), score(0)
{
	randomSeed(micros()*millis());
	state = new TitleState(canvas);
	state->start(*this);
}

void Bonk::Bonk::draw()
{
	state->draw();
}
void Bonk::Bonk::update(uint _time)
{
	state->update(_time, *this);
	draw();
	display->commit();
}
void Bonk::Bonk::start()
{
	UpdateManager::addListener(this);
}
void Bonk::Bonk::stop()
{
	delete state;
}
void Bonk::Bonk::newGame()
{
	delete state;
	state = new GameState(canvas);
	state->start(*this);
}
void Bonk::Bonk::pauseGame()
{
	state->stop();
	pausedGameState = state;
	state = new PauseState(canvas);
	state->start(*this);
}
void Bonk::Bonk::resumeGame()
{
	delete state;
	state = pausedGameState;
	state->start(*this);
}
void Bonk::Bonk::quitGame()
{
	delete state;
	state = new TitleState(canvas);
	state->start(*this);
}
