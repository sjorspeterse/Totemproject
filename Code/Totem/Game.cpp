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
	this->_curTile = _field[_cursorRow][_cursorCol];

	Tile* tile;
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			tile = _field[row][col];
			tile->neighbour[Tile::right] 		= (col<8) 			? _field[row][col+1] : NULL;
			tile->neighbour[Tile::left] 		= (col>0) 			? _field[row][col-1] : NULL;
			tile->neighbour[Tile::top] 			= (row>0) 			? _field[row-1][col] : NULL;
			tile->neighbour[Tile::bottom]		= (row<8) 			? _field[row+1][col] : NULL;
			tile->neighbour[Tile::topright] 	= (col<8 && row>0) 	? _field[row-1][col+1] : NULL;
			tile->neighbour[Tile::topleft] 		= (col>0 && row>0) 	? _field[row-1][col-1] : NULL;
			tile->neighbour[Tile::bottomright]	= (col<8 && row<8) 	? _field[row+1][col+1] : NULL;
			tile->neighbour[Tile::bottomleft] 	= (col>0 && row<8) 	? _field[row+1][col-1] : NULL;
		}
	}
	Serial.println("connected Tiles together");
	
}

int MineSweeper::get_input() {
	int buttonPressed = get_hardware_input();

    switch(buttonPressed) {
	    case Button::left : return MineSweeper::left;
	    case Button::right : return MineSweeper::right;
	    case Button::up : return MineSweeper::up;
	    case Button::down : return MineSweeper::down;
	    case Button::one : 
	    case Button::ok : return MineSweeper::flag;
	    case Button::two : return MineSweeper::open;
	    case Button::three : 
	    case Button::four : return MineSweeper::none;
	}
}

void MineSweeper::start() {
	Serial.println("Starting MineSweeper");
	lcd->clrScr();

	// drawing the field
	for(int col = 0; col<9; col++) {
		for(int row = 0; row<9; row++) {
			_field[row][col]->draw();
		}
	}
	
	// drawing the player
	curPlayer->avatar->draw(50,0);

	//drawing the cursor
	drawCursor();

	//displaying everything
	lcd->update();

	int input = get_input();
	while(input != MineSweeper::open){
		if(input == MineSweeper::flag) {
			_curTile->toggleFlag();
		}
		else{
			moveCursor(input);
		}
		
		lcd->update();
		input = get_input();
	}
	generate();
	_curTile->open();
	curPlayer->avatar->action();

	while(true) {
		switch(input) {
			case MineSweeper::left:
			case MineSweeper::right:
			case MineSweeper::up:
			case MineSweeper::down:
				moveCursor(input);
				break;
			case MineSweeper::flag:
				_curTile->toggleFlag();
				break;
			case MineSweeper::open:
				_curTile->open();
				curPlayer->avatar->action();
				break;
			lcd->update();
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
		case MineSweeper::left: 
			if(_cursorCol > 0) _cursorCol--;
			curPlayer->avatar->look(EYES_LEFT);
			break;
		case MineSweeper::right: 
			if(_cursorCol < 8) _cursorCol++;
			curPlayer->avatar->look(EYES_RIGHT);
			break;
		case MineSweeper::up: 
			if(_cursorRow > 0) _cursorRow--;
			curPlayer->avatar->look(EYES_UP);
			break;
		case MineSweeper::down: 
			if(_cursorRow < 8) _cursorRow++;
			curPlayer->avatar->look(EYES_DOWN);
			break;
		}
	_curTile = _field[_cursorRow][_cursorCol];
	drawCursor();
}

void MineSweeper::drawCursor() {
	/*lcd->setPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow); // top left
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow); // top right
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1)); // bottom left
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1)); // bottom right*/
	lcd->drawRect(1 + 5*_cursorCol, 1 + 5*_cursorRow, 1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
}

void MineSweeper::eraseCursor() {
	/*lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow); // top left
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow); // top right
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1)); // bottom left
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1)); // bottom right*/

	lcd->clrRect(1 + 5*_cursorCol, 1 + 5*_cursorRow, 1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
}

void MineSweeper::generate() {
	int bombs_placed = 0;
	Tile *tile;
	while(bombs_placed < 10) {
		START:  //goto label
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

	///// vanaf hier is test
	/*for(int r = 0; r<9; r++)
			for(int c = 0; c<9; c++){
				Tile *tile = _field[r][c];
				if(tile->isBomb){
					tile->bitmap = FLAG_BITMAP;
					tile->draw();
				}
				else{
					tile->open();
				}
			}*/
}
