#ifndef BONK_PAUSESTATE_H
#define BONK_PAUSESTATE_H

#include "State.hpp"

class PauseState : public State
{
public:
	PauseState(Sprite* sprite);
	~PauseState();
	void update(uint _time, Bonk& game) override;
	void draw() override;
	void start(Bonk& game) override;

private:
	static PauseState* instance;
};


#endif