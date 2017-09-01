#include "totem.h"

Game::Game(Player **player_list, LCD5110_SJORS* lcd, Player *curPlayer)
{
	this->lcd = lcd;
	this->player_list = player_list;
	this->curPlayer = curPlayer;
}

void Game::demoAll() {

	/*******************************************
	// demoAll usage:				          //
	// Game game(player_list, &lcd, &Wiebke); //
  	// game.demoAll();				          //
	*******************************************/

	/****************************************
	// Demo Avatar select, action and eyes //
	****************************************/

	int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  	int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  	int middlelocx = 42-17;
	Avatar *leftmost, *left, *center, *right, *rightmost;

  	for (int nr = 0; nr < 5; nr++) {
    	middlelocx = 42-17;
    	for(int i = 0; i <11; i++){
	     	leftmost = player_list[nr%5]->avatar;
	      	left = player_list[(nr+1)%5]->avatar;
	      	center = player_list[(nr+2)%5]->avatar;
	      	right = player_list[(nr+3)%5]->avatar;
	      	rightmost = player_list[(nr+4)%5]->avatar;

		    lcd->clrScr();
		    left->draw(middlelocx - 36 , -yoffset[33 + i], Avatar::normal); //Left figure
	      	center->draw(middlelocx, -yoffset[22 + i], Avatar::normal); //Middle figure
    	  	right->draw(middlelocx + 36, -yoffset[11 + i], Avatar::normal); //Right figure
	      	rightmost->draw(middlelocx + 2*36, -yoffset[i], Avatar::normal); //Rightmost figure
	      	lcd->update();

	      	middlelocx -= acceleratex[i];
	      	delay(30);   
    	}

    right->action();
    right->look(EYES_LEFT);
    right->look(EYES_RIGHT);
    right->look(EYES_UP);
    right->look(EYES_DOWN);

    delay(200);
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
