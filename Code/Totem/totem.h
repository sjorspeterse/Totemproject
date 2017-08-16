#ifndef totem_h
#define totem_h
#include "LCD5110_Graph.h"

class Player;
class Avatar;
class Game;

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
		unsigned char* _background;
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


#endif




