#ifndef totem_h
#define totem_h
#include "LCD5110_Graph.h"
#include "graphics.h"

// Minesweeper
#define UNDISCOVERED -1
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3
#define TOPLEFT 4
#define TOPRIGHT 5
#define BOTTOMLEFT 6
#define BOTTOMRIGHT 7

class Player;
class Avatar;
class Game;
class MineSweeper;
class Tile;

class Player
{
	public:
	   	char* naam;
	   	Avatar* avatar;

	   	Player( char* naam, LCD5110* lcd);

};

// TODO: Implement Avatar class! Thomas.avatar.action(), Thomas.avatar.draw(int locx, int locy), Thomas.avatar.erase()
// variables: unsigned char* _background, int _locx, int _locy, boolean _isdrawn, ...
class Avatar
{
	public:
	  	LCD5110* lcd;
	  	
	  	Avatar(char* naam, LCD5110* lcd);
		void action();
		void erase();
		void draw(int x, int y);
		void look(int direction);
	
	private:
		unsigned char* _bitmap;
		int _locx;
		int _locy;
		bool _notdrawn;
	
};

class Game
{
	public:
		LCD5110 *lcd;
		Player **player_list;

		Game(Player **player_list, LCD5110* lcd);
		void demoAll();

	private:
};

class MineSweeper: public Game
{
	public:
		MineSweeper(Player **player_list, LCD5110* lcd);
		Tile** setup();
		void start();
		void generate(Tile **field);

	private:
		Tile* _field[9][9];
		int _cursorx;
		int _curosry;

		
};

class Tile
{
	public:
		bool isBomb;
		int value;
		Tile* neighbour[8];
		LCD5110 *lcd;
		Tile(int col, int row, LCD5110* lcd);
		void draw();
		int checkNeighbours();
		int _col;
		int _row;

	private:
		unsigned char* _bitmap;
		
		
		
};


#endif




