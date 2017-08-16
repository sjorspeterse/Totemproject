#include "Arduino.h"
#include "avatars.h"
#include "totem.h"

Avatar::Avatar(char* naam)
{
	this->_isdrawn = false;

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
	
}
