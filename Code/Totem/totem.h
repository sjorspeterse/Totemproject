#ifndef totem_hfbomb
#define totem_h
#include "LCD5110_Graph.h"
#include "graphics.h"
#include <avr/pgmspace.h>
#include "avatars.h"
#include "demo.h"
#include "sounds.h"
#include "TM1637Display.h"


// General Purpose
//enum button 
enum dir{up, down, left, right};

// Minesweeper
#define UNDISCOVERED -1

#define SPEAKER_PIN 8

#define BUTTON_UP_PIN 15 //8
#define BUTTON_DOWN_PIN  27//10
#define BUTTON_LEFT_PIN 31 //12
#define BUTTON_RIGHT_PIN 19
#define BUTTON_OK_PIN 23 //16

#define OK 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define BUTTON_NOTHING 0
#define BUTTON_PRESSED 1
#define BUTTON_RELEASED_SHORT 2
#define BUTTON_RELEASED_LONG 3

//Timer
#define TIMER_CLK 3
#define TIMER_DIO 5

class Player;
class Avatar;
class Game;
class MineSweeper;
class Tile;
class Button;
class LCD5110_SJORS;
class Process;
class Animation;
class Input;
class Audio;
class Timer;
class Background;

class Player
{
	public:
	   	char* naam;
	   	Avatar* avatar;

	   	Player( char* naam, LCD5110_SJORS* lcd);

};
// TODO: Implement Avatar class! Thomas.avatar.action(), Thomas.avatar.draw(int locx, int locy), Thomas.avatar.erase()
// variables: unsigned char* _background, int _locx, int _locy, boolean _isdrawn, ...
class Avatar
{
	public:
		enum {normal, glasses, dead};
	  	LCD5110_SJORS* lcd;
	  	
	  	Avatar(char* naam, LCD5110_SJORS* lcd);
		void action();
		void erase();
		void draw(int x, int y, int type);
		void look(int direction);
	
	private:
		unsigned char* _bitmap;
		unsigned char* _bitmap_glasses;
		unsigned char* _bitmap_dead;
		int _locx;
		int _locy;
		bool _notdrawn;
	
};

class Game
{
	public:
		enum action_type {up, down, left, right, flag, open, openNumber, none};
		LCD5110_SJORS *lcd;
		Player **player_list;
		Player *curPlayer;
		TM1637Display *timer;

		Game(Player **player_list, LCD5110_SJORS *lcd, Player *curPlayer, TM1637Display *timer);
		virtual action_type get_input() = 0;
		virtual int handle_input(action_type input) = 0;//int input) = 0;
		void demoAll();

	private:
		Player* rotate_list(int dir);
};

class MineSweeper: public Game
{
	public:

		MineSweeper(Player **player_list, LCD5110_SJORS* lcd, Player *curPlayer, TM1637Display *timer);
		Tile** setup();
		void start();
		void generate_bombs();
		void drawCursor();
		void eraseCursor();
		void moveCursor(action_type input);
		bool won();
		void show_bombs();
		virtual action_type get_input() override;
		virtual int handle_input(action_type input) override; //int input) override;

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
		LCD5110_SJORS *lcd;		

		Tile(int col, int row, LCD5110_SJORS* lcd);
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


class LCD5110_SJORS: public LCD5110
{
	public:
		using LCD5110::LCD5110;
		bool getPixel(int x, int y);
		void getBuffer(int x, int y, uint8_t* bitmap, int sx, int sy);
		void drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy);
		void drawBitmapDynamic(int x, int y, uint8_t* bitmap, int sx, int sy);
		void setPixel(uint16_t x, uint16_t y);
		void clrPixel(uint16_t x, uint16_t y);
		void update();

		bool changed = false;

	private:
		// int8_t LCD5110::getByte(int index);
};

class Process
{
	public:
		virtual bool run() = 0;
		virtual bool should_run() = 0;

	protected:
		void sleep(int time);

		unsigned long next_call_time;
		int index;
};

// TODO: verdergaan met het implementeren van Animation ofzo.

class Animation: public Process
{
	public:
		virtual bool run() override;
		virtual bool should_run() override;
};

class Input: public Process
{
	public:
		Input();
		virtual bool run() override;
		virtual bool should_run() override;
		static bool available;
		static int button_status[6];

	private:
		unsigned long buttons_last_pressed[6] = {0, 0, 0, 0, 0, 0};
};

class Audio: public Process
{
	public:
		Audio(int sound, bool loop);
		virtual bool run() override;
		virtual bool should_run() override;
		static void start_music(int song);
		static void play_sound(int sound);
		enum {MARIO_MAIN_THEME};

	private:
		int frame;
		int size;
		int melody_mem;
		int tempo_mem;
		bool loop;

};

class Timer: public Process
{
	public:
		Timer(TM1637Display* timer);
		virtual bool run() override;
		virtual bool should_run() override;

	private:
		int value;
		TM1637Display *timer;

};

class Background
{
	public:
		static void run_all();
		static void add(Process *p);
		static void remove(int index);

	private:
		static Process *process_list[10];	
		static bool is_active[10];// = {false};

};

int free_ram();
int get_hardware_input();

#endif




