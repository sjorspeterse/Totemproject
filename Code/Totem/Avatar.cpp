#include "Arduino.h"
#include "avatars.h"
#include "totem.h"
#include <LCD5110_Graph.h>

Avatar::Avatar(char* naam, LCD5110* lcd)
{
	this->_notdrawn = true;
	this->_lcd = lcd;

   	if(strcmp(naam, "Celine")==0){
      	this->_bitmap = CELINE_AVATAR;
   	} else if(strcmp(naam, "Iris")==0){
      	this->_bitmap = IRIS_AVATAR;
   	} else if(strcmp(naam, "Thomas")==0){
      	this->_bitmap = THOMAS_AVATAR;
   	} else if(strcmp(naam, "Sjors")==0){
      	this->_bitmap = SJORS_AVATAR;
   	} else if(strcmp(naam, "Wiebke")==0){
      	this->_bitmap = WIEBKE_AVATAR;
   	} 
   
}

void Avatar::draw(int x, int y){
	_lcd->drawBitmap(x, y, _bitmap, AVATAR_WIDTH, AVATAR_HEIGHT);
	_locx = x;
	_locy = y;
	_notdrawn = false;
}

void Avatar::action(){
	if(_notdrawn) return;

	for(int i = 0; i<SJORS_ACTION_FRAMECOUNT; i++)
  	{
	    _lcd->drawBitmap(_locx + SJORS_ACTION_OFFSETX, _locy + SJORS_ACTION_OFFSETY, SJORS_ACTION[i], SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
	    _lcd->update();
	    delay(100);
  	} 
}

void Avatar::look(int direction){
	if(_notdrawn) return;

	_lcd->drawBitmap(_locx + SJORS_EYESX, _locy + SJORS_EYESY, SJORS_EYES[direction], SJORS_EYES_WIDTH, SJORS_EYES_HEIGHT);
	_lcd->update();
	delay(100);

	//look back normal
	_lcd->drawBitmap(_locx + SJORS_EYESX, _locy + SJORS_EYESY, SJORS_EYES[EYES_NEUTRAL], SJORS_EYES_WIDTH, SJORS_EYES_HEIGHT);
	_lcd->update();
}