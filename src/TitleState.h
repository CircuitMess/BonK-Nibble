#ifndef BONK_TITLESTATE_H
#define BONK_TITLESTATE_H

#include "State.hpp"

class TitleState : public State
{
public:
	TitleState(Sprite* sprite);
	~TitleState();
	void update(uint _time, Bonk& game) override;
	void draw() override;
	void start(Bonk& game) override;

	void drawBitmap(int16_t x, int16_t y, const byte *bitmap, uint16_t color, uint8_t scale);

private:
	static const char *titleMenu[3] PROGMEM;
	uint8_t titleCursor;
	bool blinkState;
	uint blinkMicros;
	static TitleState* instance;
};


#endif