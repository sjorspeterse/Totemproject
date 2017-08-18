#ifndef totem_hfbomb
#define totem_h
#include "LCD5110_Graph.h"
#include "graphics.h"

// General Purpose
#define BUTTON1 1
#define BUTTON2 2 
#define BUTTON3 3
#define BUTTON4 4
#define OK 5
#define UP 2
#define DOWN 3

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
		Player *curPlayer;

		Game(Player **player_list, LCD5110* lcd, Player *curPlayer);
		void demoAll();

	private:
};

class MineSweeper: public Game
{
	public:
		MineSweeper(Player **player_list, LCD5110* lcd, Player *curPlayer);
		Tile** setup();
		void start();
		void generate();
		void drawCursor();
		void eraseCursor();
		void moveCursor(int input);

	private:
		Tile* curTile;
		Tile* _field[9][9];
		int _cursorCol;
		int _cursorRow;

		
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
		int bombNeighbours();
		void open();	

	private:
		int _col;
		int _row;
		unsigned char* _bitmap;
		
		
		
};

int free_ram();
int get_input();

#endif




