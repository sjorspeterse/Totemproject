#include "totem.h"

Player::Player(char* naam, LCD5110_SJORS* lcd)
{
   this->naam = naam;
   this->avatar = new Avatar(naam, lcd);   
}  

