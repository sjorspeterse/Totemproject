#include "totem.h"

MineSweeper::MineSweeper(Player **player_list, LCD5110* lcd, Player *curPlayer): Game(player_list, lcd, curPlayer){
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
	    case Button::ok : 
	    	if(_curTile->value == UNDISCOVERED) 
	    		return MineSweeper::flag;
	    	else 
	    		return MineSweeper::openNumber;
	    case Button::one : return MineSweeper::flag;
	    case Button::two : return MineSweeper::open;
	    case Button::three : return MineSweeper::openNumber;
	    case Button::four : return MineSweeper::none;
	}
}

int MineSweeper::handle_input(int input) {
	int status = Tile::success;
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
			status = _curTile->open();
			if(status == Tile::success)
				//curPlayer->avatar->action();
			break;
		case MineSweeper::openNumber:
			if(_curTile->value != UNDISCOVERED)
				status = _curTile->open_number();
			break;
		}
	return status;
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
	curPlayer->avatar->draw(50,0, Avatar::normal);

	// drawing the cursor
	drawCursor();

	// displaying everything
	lcd->update();

	// wait until a field is opened
	int input = get_input();
	while(input != MineSweeper::open){
		handle_input(input);
		lcd->update();
		input = get_input();
	}

	// then generate the bombs and open the tiles
	generate_bombs();
	_curTile->open();
	curPlayer->avatar->action();

	// main Minesweeper loop
	int status = Tile::success;

	long lastTime = 0;
	long curTime;
	while(true) {	
		curTime = millis();
		Serial.print("Time: ");
		Serial.println(curTime - lastTime);
		lastTime = curTime;

		status = handle_input(input);

		if( won() ){
			Serial.println("You won!");
			curPlayer->avatar->draw(50,0, Avatar::glasses);
			break;
		} else if(status == Tile::died) {
			Serial.println("You died!");
			curPlayer->avatar->draw(50,0, Avatar::dead);
			show_bombs();
			break;
		}

		lcd->update();
		//input = get_input();
	}

	//Either won or lost, wait for ok
	lcd->update();
	while((input = get_hardware_input()) != Button::ok)
		;


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

void MineSweeper::generate_bombs() {
	int bombs_placed = 0;
	Tile *tile;
	while(bombs_placed < 10) {
		START:  //goto label
		int row = random(9);
		int col = random(9);
		tile = _field[row][col];
		if(tile->isBomb) {
			continue; // already a bomb 
		}
		for(int r = row-1; r<=row+1; r++)
			for(int c = col-1; c<=col+1; c++)
				if(r == _cursorRow && c == _cursorCol){
					goto START; // initial square should have 0 ajacent bombs 
				}
		tile->isBomb = true;
		bombs_placed++;
	}
	Serial.println("Bombs placed!");
}

bool MineSweeper::won() {
	Tile *tile;
	for(int row=0; row<9; row++) {
		for(int col=0; col<9; col++) {
			tile = _field[row][col];
			if(tile->isBomb == false && tile->value == UNDISCOVERED) {
				return false;
			}
		}
	}
	return true;
}

void MineSweeper::show_bombs() {
	Tile* tile;
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			tile = _field[row][col];

			// optie een: undiscovered -> bom
			if(tile->isBomb==true && tile->flag==false)
				tile->bitmap = BOMB_BITMAP;
			
			// optie twee: flag -> broken flag
			if(tile->isBomb==false && tile->flag==true)
				tile->bitmap = BROKEN_FLAG_BITMAP;

			tile->draw();
		}
	}
}