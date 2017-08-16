#ifndef totem_h
#define totem_h

class Player;
class Avatar;

class Player
{
 public:
   char* naam;
   Player( char* naam);
   // const unsigned char* avatar; 
   Avatar* avatar;

};

// TODO: Implement Avatar class! Thomas.avatar.action(), Thomas.avatar.draw(int locx, int locy), Thomas.avatar.erase()
// variables: unsigned char* _background, int _locx, int _locy, boolean _isdrawn, ...
class Avatar
{
public:
  Avatar( char* naam);
	void action();
	void erase();
	void draw(int x, int y);

private:
	unsigned char* _bitmap;
	unsigned char* _background;
	int _locx;
	int _locy;
	bool _isdrawn;
};


#endif




