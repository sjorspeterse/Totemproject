#include "Arduino.h"
#include "totem.h"
#include "avatars.h"

Game::Game(Player **player_list, LCD5110* lcd)
{
	this->lcd = lcd;
	this->player_list = player_list;
}


void Game::demoAll() {

	/**********************************
	// demoAll usage:				 //
	// Game game(player_list, &lcd); //
  	// game.demoAll();				 //
	**********************************/

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
		    left->draw(middlelocx - 36 , -yoffset[33 + i]); //Left figure
	      	center->draw(middlelocx, -yoffset[22 + i]); //Middle figure
    	  	right->draw(middlelocx + 36, -yoffset[11 + i]); //Right figure
	      	rightmost->draw(middlelocx + 2*36, -yoffset[i]); //Rightmost figure
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
	avatar->draw(-10, -10);
	unsigned char bitmap [20*3];
  	lcd->getBuffer(0, 0, bitmap, 20, 20);
  	lcd->drawBitmapDynamic(40, 0, bitmap, 20, 20);
  	lcd->update();
  	delay(1000);
}

MineSweeper::MineSweeper(Player **player_list, LCD5110* lcd): Game(player_list, lcd)
{
	Serial.println("MineSweeper constructor");
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			//Serial.print("row = ");
			//Serial.println(row);
			_field[row][col] = new Tile(col, row, lcd);  // TODO: DEZE OOK WEER VRIJMAKEN!!""
		}
	}
	Serial.print("Created all the Tiles. _col and _row of _field[5][6] are ");
	Serial.print(_field[5][6]->_col);
	Serial.print(" and ");
	Serial.println(_field[5][6]->_row);

	Tile* tile;
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			tile = _field[row][col];
			tile->neighbour[RIGHT] 			= (col<8) 			? _field[row][col+1] : NULL;
			tile->neighbour[LEFT] 			= (col>0) 			? _field[row][col-1] : NULL;
			tile->neighbour[TOP] 			= (row>0) 			? _field[row-1][col] : NULL;
			tile->neighbour[BOTTOM] 		= (row<8) 			? _field[row+1][col] : NULL;
			tile->neighbour[TOPRIGHT] 		= (col<8 && row>0) 	? _field[row-1][col+1] : NULL;
			tile->neighbour[TOPLEFT] 		= (col>0 && row>0) 	? _field[row-1][col-1] : NULL;
			tile->neighbour[BOTTOMRIGHT]	= (col<8 && row<8) 	? _field[row+1][col+1] : NULL;
			tile->neighbour[BOTTOMLEFT] 	= (col>0 && row<8) 	? _field[row+1][col-1] : NULL;
		}
	}
	Serial.println("connected Tiles together");
	Serial.print("Check: 2 = ");
	Serial.println(_field[0][0]->neighbour[RIGHT]->neighbour[BOTTOMRIGHT]->_col);
	
}

void MineSweeper::start() {
	Serial.println("Starting MineSweeper");
	lcd->clrScr();
	for(int col = 0; col<9; col++) {
		for(int row = 0; row<9; row++) {
			_field[row][col]->draw();
		}
	}
	
	lcd->drawBitmap(50,0, WIEBKE_AVATAR, AVATAR_WIDTH, AVATAR_HEIGHT);
	lcd->update();
	delay(1000);
}

Tile::Tile(int col, int row, LCD5110* lcd)
{
	//Serial.print("tile ");
	this->isBomb = false;
	this->value = UNDISCOVERED;
	this->_col = col;
	this->_row = row;
	this->_bitmap = UNDISCOVERED_BITMAP;
	this->lcd = lcd;
}

void Tile::draw(){
	/*Serial.print("drawing! col = ");
	Serial.print(_col);
	Serial.print(", row = ");
	Serial.println(_row);*/
	lcd->drawBitmap(2+ 5*_col, 2+ 5*_row, _bitmap, 4, 4);
}
