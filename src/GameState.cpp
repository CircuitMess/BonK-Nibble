#include "GameState.h"
#include <Input/Input.h>
#include "Bonk.h"
#include "bitmaps/bonk_title.hpp"
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

Bonk::GameState* Bonk::GameState::instance = nullptr;
Bonk::GameState::GameState(Sprite* sprite) : State(sprite)
{
	instance = this;

	//player variables
	playerScore = 0;
	playerHeight = 32;
	playerWidth = 6;
	playerX = 5;
	playerY = (sprite->height() - playerHeight) / 2;
	playerSpeedY = 1.0;
	//oponent variables
	opponentScore = 0;
	opponentHeight = 32;
	opponentWidth = 6;
	opponentX = sprite->width() - opponentWidth - 5;
	opponentY = (sprite->height() - opponentHeight) / 2;
	opponentSpeedY = 1.0;
	//ball variables
	ballSize = 12;
	ballX = sprite->width() - ballSize - opponentWidth - 1;
	ballY = (sprite->height() - ballSize) / 2;
	ballSpeedX = 1.75;
	ballSpeedY = 1.75;

	winCondition = 0;
	deathTimer = 0;
}
void Bonk::GameState::start(Bonk& _game)
{
	game = &_game;
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 1, [](uint){
		instance->playerY = max(0, instance->playerY - instance->playerSpeedY);
	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 1, [](uint){
		instance->playerY = min(instance->display->height() - instance->playerHeight, instance->playerY + instance->playerSpeedY);
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->game->pauseGame();
	});
}
Bonk::GameState::~GameState()
{
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 0, nullptr);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 0, nullptr);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
}
void Bonk::GameState::draw()
{
	display->setTextSize(5);
	display->setTextFont(1);
	display->setTextColor(TFT_WHITE);
	display->clear(TFT_BLACK);
	
	if(winCondition)
	{
		display->clear(TFT_BLACK);
		display->setTextFont(2);
		display->setTextColor(TFT_WHITE);
		display->setTextSize(2);
		display->setCursor(60, 30);
		if(playerScore > 9){
			display->printCenter("PLAYER 1");
		}
		else if(opponentScore > 9){
			display->printCenter("PLAYER 2");
		}
		display->setCursor(60,60);
		display->printCenter("WINS");
		if(deathTimer >= 2000000)
		{
			game->newGame();
		}
		return;
	}

	//move the oponent
	if ((opponentY + (opponentHeight / 2)) < (ballY + (ballSize / 2))) { //if the ball is below the oponent
		opponentY = opponentY + opponentSpeedY; //move down
		opponentY = min(display->height() - opponentHeight, opponentY); //don't go out of the screen
	}
	else {
		opponentY = opponentY - opponentSpeedY; //move up
		opponentY = max(0, opponentY); //don't go out of the screen
	}

	//draw the score
	display->setTextSize(3);
	display->setCursor(15, 32);
	display->printCenter(String(String(playerScore) + "    " + String(opponentScore)));
	//draw the ball
	display->fillRect(ballX, ballY, ballSize, ballSize, TFT_WHITE);
	//draw the player
	display->fillRect(playerX, playerY, playerWidth, playerHeight, TFT_RED);
	//draw the oponent
	display->fillRect(opponentX, opponentY, opponentWidth, opponentHeight, TFT_BLUE);
}
void Bonk::GameState::update(uint _time, Bonk& game)
{
	//reset score when 10 is reached
	if ((playerScore == 10) || (opponentScore == 10)) {
		winCondition = 1;
	}
	if(winCondition)
	{
		deathTimer+=_time;
		return;
	}

	//move the ball
	ballX = ballX + ballSpeedX;
	ballY = ballY + ballSpeedY;

	//check for ball collisions
	//collision with the top border
	if (ballY < 0) {
		ballY = 0;
		ballSpeedY = -ballSpeedY;
		tone(BUZZ_PIN, 50, 50);
	}
	//collision with the bottom border
	if ((ballY + ballSize) > display->height()) {
		ballY = display->height() - ballSize;
		ballSpeedY = -ballSpeedY;
		tone(BUZZ_PIN, 50, 50);

	}
	//collision with the player
	if (rectRect(ballX, ballY, ballSize, ballSize, playerX, playerY, playerWidth, playerHeight)) {
		ballX = playerX + playerWidth;
		ballSpeedX = -ballSpeedX;
		tone(BUZZ_PIN, 100, 50);

	}
	//collision with the oponent
	if (rectRect(ballX, ballY, ballSize, ballSize, opponentX, opponentY, opponentWidth, opponentHeight)) {
		ballX = opponentX - ballSize;
		ballSpeedX = -ballSpeedX;
		tone(BUZZ_PIN, 150, 50);
	}
	//collision with the left side
	if (ballX < 0) {
		opponentScore = opponentScore + 1;
		//mp.sound.playCancel();
		ballX = display->width() - ballSize - opponentWidth - 1;
		ballSpeedX = -abs(ballSpeedX);
		ballY = random(0, display->height() - ballSize);
		tone(BUZZ_PIN, 350, 50);
	}
	//collision with the right side
	if ((ballX + ballSize) > display->width()) {
		playerScore = playerScore + 1;
		//mp.sound.playOK();
		ballX = display->width() - ballSize - opponentWidth - 16; //place the ball on the oponent side
		ballSpeedX = -abs(ballSpeedX);
		ballY = random(0, display->height() - ballSize);
		tone(BUZZ_PIN, 350, 50);
	}
}
bool Bonk::GameState::rectRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 >= x2 && x1 <= x2 + w2 &&
		y1 + h1 >= y2 && y1 <= y2 + h2)
	{
		return true;
	}
	return false;
}