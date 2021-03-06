#include "totem.h"

Game::Game(Player **player_list, LCD5110_SJORS* lcd, Player *curPlayer, TM1637Display* timer)
{
	this->lcd = lcd;
	this->player_list = player_list;
	this->curPlayer = curPlayer;
	this->timer = timer;
}

void Game::demoAll() {

	/*******************************************
	// demoAll usage:				          //
	// Game game(player_list, &lcd, &Wiebke); //
  	// game.demoAll();				          //
	*******************************************/


	/*******************************************
	// Demoing timer				          //
	*******************************************/
	for(int k = 0; k < 20; k ++) {
		timer->	showNumberDec(k, false);
		delay(1000);
	}

	/****************************************
	// Demo Avatar select, action and eyes //
	****************************************/

	for(int i = 0; i < 13; i++){
		rotate_list(0);
	}

	/****************************************************
	// Demo getting the buffer and drawing dynamically //
	****************************************************/
	
	lcd->clrScr(); 
	Avatar *avatar = player_list[0]->avatar;
	avatar->draw(-10, -10, Avatar::normal);
	unsigned char bitmap [20*3];
  	lcd->getBuffer(0, 0, bitmap, 20, 20);
  	lcd->drawBitmapDynamic(40, 0, bitmap, 20, 20);
  	lcd->update();
  	delay(1000);
}

Player* Game::rotate_list(int dir){

	// TODO: ALSO ENABLE ROTATION TO THE OTHER SIDE




	int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  	int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  	int middlelocx = 42-17;
	Avatar *leftmost, *left, *center, *right, *rightmost;

	int p_c = 13; // player count

	int nr;
	for(nr = 0; curPlayer != player_list[nr]; nr++);
	Serial.print("player number is ");
	Serial.println(nr);

    middlelocx = 42-17;
	for(int i = 0; i <11; i++){
     	leftmost = player_list[nr%p_c]->avatar;
      	left = player_list[(nr+1)%p_c]->avatar;
      	center = player_list[(nr+2)%p_c]->avatar;
      	right = player_list[(nr+3)%p_c]->avatar;
      	rightmost = player_list[(nr+4)%p_c]->avatar;

	    lcd->clrScr();
	    left->draw(middlelocx - 36 , -yoffset[33 + i], Avatar::normal); //Left figure
      	center->draw(middlelocx, -yoffset[22 + i], Avatar::normal); //Middle figure
	  	right->draw(middlelocx + 36, -yoffset[11 + i], Avatar::normal); //Right figure
      	rightmost->draw(middlelocx + 2*36, -yoffset[i], Avatar::normal); //Rightmost figure
      	lcd->update();

      	middlelocx -= acceleratex[i];
      	delay(30);   
      }
    // right->action();
    // right->look(EYES_LEFT);
    // right->look(EYES_RIGHT);
    // right->look(EYES_UP);
    // right->look(EYES_DOWN);

    // delay(200);
    Player* player = player_list[(nr+1)%p_c];
    curPlayer = player;
	return player;
}