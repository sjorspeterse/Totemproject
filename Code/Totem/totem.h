#ifndef totem_h
#define totem_h
#include "LCD5110_Graph.h"

class Player;
class Avatar;

class Player
{
 public:
   char* naam;
   Player( char* naam, LCD5110* lcd);
   Avatar* avatar;

};

// TODO: Implement Avatar class! Thomas.avatar.action(), Thomas.avatar.draw(int locx, int locy), Thomas.avatar.erase()
// variables: unsigned char* _background, int _locx, int _locy, boolean _isdrawn, ...
class Avatar
{
public:
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
	LCD5110* _lcd;
};


#endif




