#include "Bonk.h"
#include "TitleState.h"
#include "GameState.h"
#include "PauseState.h"

Bonk::Bonk(Display& display) : Context(display), display(&display), canvas(display.getBaseSprite()), score(0)
{
	randomSeed(micros()*millis());
	state = new TitleState(canvas);
	state->start(*this);
}

void Bonk::draw()
{
	state->draw();
}
void Bonk::update(uint _time)
{
	state->update(_time, *this);
	draw();
	display->commit();
}
void Bonk::start()
{
	UpdateManager::addListener(this);
}
void Bonk::stop()
{
	delete state;
}
void Bonk::newGame()
{
	delete state;
	state = new GameState(canvas);
	state->start(*this);
}
void Bonk::pauseGame()
{
	state->stop();
	pausedGameState = state;
	state = new PauseState(canvas);
	state->start(*this);
}
void Bonk::resumeGame()
{
	delete state;
	state = pausedGameState;
	state->start(*this);
}
void Bonk::quitGame()
{
	delete state;
	state = new TitleState(canvas);
	state->start(*this);
}
