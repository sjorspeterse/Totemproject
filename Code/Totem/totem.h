#ifndef totem_hfbomb
#define totem_h
#include "LCD5110_Graph.h"
#include "graphics.h"

// General Purpose
//enum button 
enum dir{up, down, left, right};

// Minesweeper
#define UNDISCOVERED -1



class Player;
class Avatar;
class Game;
class MineSweeper;
class Tile;
class Button;

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
		virtual int get_input() = 0;
		virtual int handle_input(int input) = 0;
		void demoAll();

	private:
};

class MineSweeper: public Game
{
	public:
		enum {left, right, up, down, flag, open, openNumber, none};

		MineSweeper(Player **player_list, LCD5110* lcd, Player *curPlayer);
		Tile** setup();
		void start();
		void generate_bombs();
		void drawCursor();
		void eraseCursor();
		void moveCursor(int input);
		bool won();
		virtual int get_input() override;
		virtual int handle_input(int input) override;

	private:
		Tile* _curTile;
		Tile* _field[9][9];
		int _cursorCol;
		int _cursorRow;		
};

class Tile
{
	public:
		bool isBomb;
		bool flag;
		enum {top, bottom, left, right, topleft, topright, bottomleft, bottomright};
		enum {died, success};
		int value;
		unsigned char* bitmap;	
		Tile* neighbour[8];
		LCD5110 *lcd;		

		Tile(int col, int row, LCD5110* lcd);
		void draw();
		int bombNeighbours();
		int open();
		int open_number();
		void toggleFlag();
		void print();

	private:
		int _col;
		int _row;
		
};

class Button
{
	public:
		enum {one, two, three, four, ok, up, down, left, right};
};

int free_ram();
int get_hardware_input();

#endif




