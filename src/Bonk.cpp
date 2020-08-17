#include "Bonk.h"
#include "State.hpp"
#include "TitleState.h"
#include "GameState.h"
#include "PauseState.h"
#include "State.hpp"

Bonk::Bonk::Bonk(Display& display) : Context(display), display(&display), canvas(display.getBaseSprite()){
	randomSeed(micros()*millis());
	state = new TitleState(canvas);
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
	runningContext = this;
	state->start(*this);
	UpdateManager::addListener(this);
}
void Bonk::Bonk::stop()
{
	UpdateManager::removeListener(this);
}
void Bonk::Bonk::pack()
{
	state->stop();
	delete state;

	if(pausedGameState != nullptr){
		pausedGameState->stop();
		delete pausedGameState;
	}

	exitingGame = true;
}
void Bonk::Bonk::newGame()
{
	state->stop();
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
	state->stop();
	delete state;
	state = pausedGameState;
	pausedGameState = nullptr;
	state->start(*this);
}
void Bonk::Bonk::quitGame()
{
	delete pausedGameState;
	pausedGameState = nullptr;

	state->stop();
	delete state;
	state = new TitleState(canvas);
	state->start(*this);
}
