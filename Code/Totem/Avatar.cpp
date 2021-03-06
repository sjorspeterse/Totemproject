#include "totem.h"

Avatar::Avatar(char* naam, LCD5110_SJORS* lcd)
{
	this->_notdrawn = true;
	this->lcd = lcd;

   	if(strcmp(naam, "Celine")==0){
      	this->_bitmap = CELINE_AVATAR;
   	} else if(strcmp(naam, "Iris")==0){
      	this->_bitmap = IRIS_AVATAR;
   	} else if(strcmp(naam, "Thomas")==0){
      	this->_bitmap = THOMAS_AVATAR;
   	} else if(strcmp(naam, "Sjors")==0){
      	this->_bitmap = SJORS_AVATAR;
      	this->_bitmap_glasses = SJORS_GLASSES;
      	this->_bitmap_dead = SJORS_DEAD;
   	} else if(strcmp(naam, "Wiebke")==0){
      	this->_bitmap = WIEBKE_AVATAR;
   	} else if(strcmp(naam, "Richard")==0){
      	this->_bitmap = RICHARD_AVATAR;
    } else if(strcmp(naam, "Aniek")==0){
      	this->_bitmap = ANIEK_AVATAR;
    } else if(strcmp(naam, "Anna")==0){
      	this->_bitmap = ANNA_AVATAR;
    } else if(strcmp(naam, "Corijn")==0){
      	this->_bitmap = CORIJN_AVATAR;
    } else if(strcmp(naam, "Jeroen")==0){
      	this->_bitmap = JEROEN_AVATAR;
    } else if(strcmp(naam, "Rik")==0){
      	this->_bitmap = RIK_AVATAR;
    } else if(strcmp(naam, "Sander")==0){
      	this->_bitmap = SANDER_AVATAR;
    } else if(strcmp(naam, "Thijs")==0){
      	this->_bitmap = THIJS_AVATAR;
   	} 
   
}

void Avatar::draw(int x, int y, int type){
	// Serial.println("Drawing avatar!");
	unsigned char* bitmap;
	switch(type) {
		case Avatar::normal: 
			bitmap = _bitmap;
			break;
		case Avatar::glasses:
			bitmap = _bitmap_glasses;
			break;
		case Avatar::dead:
			bitmap = _bitmap_dead;
			break;
	}
	// Serial.println("Going to draw bitmap");
	lcd->drawBitmap(x, y, bitmap, AVATAR_WIDTH, AVATAR_HEIGHT);
	_locx = x;
	_locy = y;
	_notdrawn = false;
}

void Avatar::action(){
	if(_notdrawn) return;

	for(int i = 0; i<SJORS_ACTION_FRAMECOUNT; i++)
  	{
	    lcd->drawBitmap(_locx + SJORS_ACTION_OFFSETX, _locy + SJORS_ACTION_OFFSETY, SJORS_ACTION[i], SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
	    lcd->update();
	    delay(100);
  	} 
}

void Avatar::look(int direction){
	if(_notdrawn) return;

	lcd->drawBitmap(_locx + SJORS_EYESX, _locy + SJORS_EYESY, SJORS_EYES[direction], SJORS_EYES_WIDTH, SJORS_EYES_HEIGHT);
	lcd->update();
	delay(100);

	//look back normal
	lcd->drawBitmap(_locx + SJORS_EYESX, _locy + SJORS_EYESY, SJORS_EYES[EYES_NEUTRAL], SJORS_EYES_WIDTH, SJORS_EYES_HEIGHT);
	lcd->update();
}