#include "totem.h"

Tile::Tile(int col, int row, LCD5110* lcd)
{
	this->isBomb = false;
	this->flag = false;
	this->value = UNDISCOVERED;
	this->_col = col;
	this->_row = row;
	this->bitmap = UNDISCOVERED_BITMAP;
	this->lcd = lcd;
}

void Tile::draw(){
	lcd->drawBitmap(2+ 5*_col, 2+ 5*_row, bitmap, 4, 4);
}

int Tile::open() {
	if(isBomb){
		Serial.println("You died");
		bitmap = BOMB_BITMAP;
		draw();
		return Tile::died;
	}
	value = bombNeighbours(); 
	switch(value){
		case 0:
			bitmap = EMPTY_BITMAP;
			for(int i=0; i<8; i++) 
				if(neighbour[i]->value == UNDISCOVERED)
					neighbour[i]->open();
			break;
		case 1:
			bitmap = ONE_BITMAP;
			break;
		case 2:
			bitmap = TWO_BITMAP;
			break;
		case 3:
			bitmap = THREE_BITMAP;
			break;
		case 4:
			bitmap = FOUR_BITMAP;
			break;
		case 5:
			bitmap = FIVE_BITMAP;
			break;
		case 6:
			bitmap = SIX_BITMAP;
			break;
		case 7:
			bitmap = SEVEN_BITMAP;
			break;
		case 8:
			bitmap = EIGHT_BITMAP;
			break;
	}
	draw();
	return Tile::success;
}

int Tile::open_number() {
	int surrounding_flags = 0;
	int status = Tile::success;
	Tile *tile;

	for(int i = 0; i<8; i++){
		tile = neighbour[i];
		if (tile != NULL && tile->flag) {
			surrounding_flags++;
		}
	}

	if(surrounding_flags == value) {
		for(int i = 0; i<8; i++){
			tile = neighbour[i];
			if (tile != NULL && tile->value == UNDISCOVERED && tile->flag == false) {
				if(tile->open() == Tile::died)
					status = Tile::died;
			}
		}
	}
	return status;
}

int Tile::bombNeighbours(){
	int bombs = 0;
	Tile *tile;
	for(int i = 0; i<8; i++)
	{
		tile = neighbour[i];
		if (tile != NULL && tile->isBomb) {
			bombs++;
		}
			
	}
	return bombs;
}

void Tile::toggleFlag() {
	if (flag) {
		bitmap = UNDISCOVERED_BITMAP;
		flag = false;
	} else if(value == UNDISCOVERED){
		bitmap = FLAG_BITMAP;
		flag = true;
	}
	draw();
}

void Tile::print() {
	Serial.print("Tile((");
	Serial.print(_row);
	Serial.print(",");
	Serial.print(_col);
	Serial.print("), isBomb = ");
	Serial.print(isBomb);
	Serial.print(", flag = ");
	Serial.print(flag);
	Serial.print(", value = ");
	Serial.print(value);
	Serial.println(")");
}