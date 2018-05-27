#include "totem.h"

MineSweeper::MineSweeper(Player **player_list, LCD5110_SJORS* lcd, Player *curPlayer, TM1637Display* timer): Game(player_list, lcd, curPlayer, timer){
	this->_cursorCol = 4;
	this->_cursorRow = 4;
	Serial.print("free ram before tiles: ");
	Serial.println(free_ram());
	for(int col = 0; col<9; col++) {
		for(int row=0; row<9; row++) {
			Tile tile(col, row, lcd);
			_field[row][col] = new Tile(col, row, lcd);  // TODO: DEZE OOK WEER VRIJMAKEN!!""
		}
	}
	Serial.print("free ram after: ");
	Serial.println(free_ram());
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

Game::action_type MineSweeper::get_input() {
	int status;
	for(int i=0; i<5; i++){
		status = Input::button_status[i];
		if(status == BUTTON_NOTHING){
			continue;
		}
		switch(i) {
			case OK:
				Serial.println("Pressing OK button!");
				switch(status){
					case BUTTON_PRESSED:
						return MineSweeper::none;
					case BUTTON_RELEASED_SHORT:
						if(this->_curTile->value == UNDISCOVERED){
							return MineSweeper::flag;
						} else if(this->_curTile->flag == 1){
							return MineSweeper::flag;
						} else
							return MineSweeper::openNumber;
						break;
					case BUTTON_RELEASED_LONG:
						if(this->_curTile->value == UNDISCOVERED){
							return MineSweeper::open;
						} else if(this->_curTile->flag == 1){
							return MineSweeper::none;
						} else
							return MineSweeper::none;
						break;
				}
			case UP:
				if(status == BUTTON_PRESSED){
					Serial.println("Pressed up button");
					return MineSweeper::up;
				}
			case DOWN:
				if(status == BUTTON_PRESSED){
					return MineSweeper::down;
				}
			case LEFT:
				if(status == BUTTON_PRESSED){
					return MineSweeper::left;
				}
			case RIGHT:
				if(status == BUTTON_PRESSED){
					return MineSweeper::right;
				}
		}
	}

 //    switch(buttonPressed) {
	//     case Button::left : return MineSweeper::left;
	//     case Button::right : return MineSweeper::right;
	//     case Button::up : return MineSweeper::up;
	//     case Button::down : return MineSweeper::down;
	//     case Button::ok : 
	//     	if(_curTile->value == UNDISCOVERED) 
	//     		return MineSweeper::flag;
	//     	else 
	//     		return MineSweeper::openNumber;
	//     case Button::one : return MineSweeper::flag;
	//     case Button::two : return MineSweeper::open;
	//     case Button::three : return MineSweeper::openNumber;
	//     case Button::four : return MineSweeper::none;
	// }
}

int MineSweeper::handle_input(action_type input) {
	int status = Tile::success;
	Serial.print("Handling input (");
	Serial.print(input);
	Serial.println(")");
	switch(input) {
		case MineSweeper::left:
			Serial.println("Pressed Left");
		case MineSweeper::right:
			Serial.println("Pressed Right");
		case MineSweeper::up:
			Serial.println("Pressed Up");
		case MineSweeper::down:
			Serial.println("Pressed Down");
			moveCursor(input);
			break;
		case MineSweeper::flag:
			_curTile->toggleFlag();
			break;
		case MineSweeper::open:
			status = _curTile->open();
			if(status == Tile::success)
				curPlayer->avatar->action();
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
	Background::add(new Timer(timer));
	// Audio::start_music(Audio::MARIO_MAIN_THEME);
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
	Serial.println("Displayed screen for the first time");

	// wait until a field is opened
	int input = MineSweeper::none;
	while(true){
		Background::run_all();
		if(Input::available){
			Serial.println("input is available!");
			input = get_input();
			if(input == MineSweeper::open)
				break;
			handle_input(input);
			lcd->update();
		}
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

		// status = handle_input();// input);

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

		Background::run_all();
		if(Input::available){
			Serial.println("input is available!");
			input = get_input();
			status = handle_input(input);
		}
		lcd->update();
		// input = get_input();
	}

	//Either won or lost, wait for ok
	lcd->update();
	while(true){
		Background::run_all();
		if(Input::available){
			Serial.println("got input!");
			input = get_input();
			if(input == Button::ok)
				break;
		}
	}

	Serial.println("Game done, clearing up memory");
	// clearing up the memory
	for(int col = 0; col<9; col++) {
		for(int row = 0; row<9; row++) {
			delete _field[row][col];
		}
	}
	// moet nog Input verwijderen
}

void MineSweeper::moveCursor(action_type input) {
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
	// top left
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow);
	lcd->setPixel(1 + 5*_cursorCol + 1, 1 + 5*_cursorRow);
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow + 1);

	// top right
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow);
	lcd->setPixel(1 + 5*(_cursorCol+1) - 1, 1 + 5*_cursorRow);
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow + 1);

	// bottom left
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1));
	lcd->setPixel(1 + 5*_cursorCol + 1, 1 + 5*(_cursorRow+1));
	lcd->setPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1) - 1);

	// bottom right
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
	lcd->setPixel(1 + 5*(_cursorCol+1) - 1, 1 + 5*(_cursorRow+1));
	lcd->setPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1) - 1);

	// lcd->drawRect(1 + 5*_cursorCol, 1 + 5*_cursorRow, 1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
}

void MineSweeper::eraseCursor() {

	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow);
	lcd->clrPixel(1 + 5*_cursorCol + 1, 1 + 5*_cursorRow);
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*_cursorRow + 1);

	// top right
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow);
	lcd->clrPixel(1 + 5*(_cursorCol+1) - 1, 1 + 5*_cursorRow);
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*_cursorRow + 1);

	// bottom left
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1));
	lcd->clrPixel(1 + 5*_cursorCol + 1, 1 + 5*(_cursorRow+1));
	lcd->clrPixel(1 + 5*_cursorCol, 1 + 5*(_cursorRow+1) - 1);

	// bottom right
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
	lcd->clrPixel(1 + 5*(_cursorCol+1) - 1, 1 + 5*(_cursorRow+1));
	lcd->clrPixel(1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1) - 1);

	// lcd->clrRect(1 + 5*_cursorCol, 1 + 5*_cursorRow, 1 + 5*(_cursorCol+1), 1 + 5*(_cursorRow+1));
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
	lcd->update();
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