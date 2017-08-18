#include "Arduino.h"
#include "totem.h"
#include "avatars.h"

Game::Game(Player **player_list, LCD5110* lcd, Player *curPlayer)
{
	this->lcd = lcd;
	this->player_list = player_list;
	this->curPlayer = curPlayer;
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

MineSweeper::MineSweeper(Player **player_list, LCD5110* lcd, Player *curPlayer): Game(player_list, lcd, curPlayer)
{
	this->_cursorCol = 4;
	this->_cursorRow = 4;
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			Tile tile(col, row, lcd);
			_field[row][col] = new Tile(col, row, lcd);  // TODO: DEZE OOK WEER VRIJMAKEN!!""
		}
	}
	this->curTile = _field[_cursorRow][_cursorCol];

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
	
}

void MineSweeper::start() {
	Serial.println("Starting MineSweeper");
	lcd->clrScr();
	for(int col = 0; col<9; col++) {
		for(int row = 0; row<9; row++) {
			_field[row][col]->draw();
		}
	}
	
	curPlayer->avatar->draw(50,0);
	drawCursor();
	lcd->update();

	int input = get_input();
	while(input != OK){
		moveCursor(input);
		lcd->update();
		input = get_input();
	}
	generate();
	while(true) {
		switch(input) {
			case LEFT:
			case RIGHT:
			case UP:
			case DOWN:
				moveCursor(input);
				break;
			case OK:
				curTile->open();
				curPlayer->avatar->action();
				break;
		}
		
		lcd->update();
		input = get_input();
	}


	Serial.println("Game done, clearing up memory");
	// clearing up the memory
	for(int col = 0; col<9; col++) {
		for(int row = 0; row<9; row++) {
			delete _field[row][col];
		}
	}
}

void MineSweeper::moveCursor(int input) {
	eraseCursor();
	switch(input) {
		case LEFT: 
			if(_cursorCol > 0) _cursorCol--;
			curPlayer->avatar->look(EYES_LEFT);
			break;
		case RIGHT: 
			if(_cursorCol < 8) _cursorCol++;
			curPlayer->avatar->look(EYES_RIGHT);
			break;
		case UP: 
			if(_cursorRow > 0) _cursorRow--;
			curPlayer->avatar->look(EYES_UP);
			break;
		case DOWN: 
			if(_cursorRow < 8) _cursorRow++;
			curPlayer->avatar->look(EYES_DOWN);
			break;
		}
	curTile = _field[_cursorRow][_cursorCol];
	drawCursor();
}

void MineSweeper::drawCursor() {
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow); // top left
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow); // top right
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1)); // bottom left
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1)); // bottom right
}

void MineSweeper::eraseCursor() {
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow); // top left
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow); // top right
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1)); // bottom left
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1)); // bottom right
}

void MineSweeper::generate() {
	START:  //goto label
	int bombs_placed = 0;
	Tile *tile;
	while(bombs_placed <= 10) {
		int row = random(9);
		int col = random(9);
		tile = _field[row][col];
		if(tile->isBomb) {
			Serial.print("(");
			Serial.print(row);
			Serial.print(",");
			Serial.print(col);
			Serial.println(") discarded because it already has a bomb.");
			continue; // already a bomb 
		}
		for(int r = row-1; r<=row+1; r++)
			for(int c = col-1; c<=col+1; c++)
				if(r == _cursorRow && c == _cursorCol){
					Serial.print("(");
					Serial.print(row);
					Serial.print(",");
					Serial.print(col);
					Serial.print(") discarded because it is neighbouring (");
					Serial.print(_cursorCol);
					Serial.print(",");
					Serial.print(_cursorCol);
					Serial.println(").");
					goto START; // initial square should have 0 ajacent bombs 
				}
		tile->isBomb = true;
		bombs_placed++;
	}
	Serial.println("Bombs placed!");
}


Tile::Tile(int col, int row, LCD5110* lcd)
{
	this->isBomb = false;
	this->value = UNDISCOVERED;
	this->_col = col;
	this->_row = row;
	this->_bitmap = UNDISCOVERED_BITMAP;
	this->lcd = lcd;
}

void Tile::draw(){
	lcd->drawBitmap(2+ 5*_col, 2+ 5*_row, _bitmap, 4, 4);
}

void Tile::open() {
	if(isBomb)
		Serial.println("You died");
	value = bombNeighbours(); 
	switch(value){
		case 0:
			_bitmap = EMPTY_BITMAP;
			for(int i=0; i<9; i++) 
				if(neighbour[i]->value == UNDISCOVERED)
					neighbour[i]->open();
			break;
		case 1:
			_bitmap = ONE_BITMAP;
			break;
		case 2:
			_bitmap = TWO_BITMAP;
			break;
		case 3:
			_bitmap = THREE_BITMAP;
			break;
		case 4:
			_bitmap = FOUR_BITMAP;
			break;
		case 5:
			_bitmap = FIVE_BITMAP;
			break;
		case 6:
			_bitmap = SIX_BITMAP;
			break;
		case 7:
			_bitmap = SEVEN_BITMAP;
			break;
		case 8:
			_bitmap = EIGHT_BITMAP;
			break;
	}
	draw();
}

int Tile::bombNeighbours(){
	int bombs = 0;
	Tile *tile;
	for(int i = 0; i<8; i++)
	{
		tile = neighbour[i];
		if (tile != NULL && tile->isBomb)
			bombs++;
	}
	return bombs;
}
