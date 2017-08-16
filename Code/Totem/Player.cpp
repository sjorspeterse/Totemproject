#include "Arduino.h"
//#include "avatars.h"
#include "totem.h"

Player::Player(char* naam)
{
   this->naam = naam;
   this->avatar = new Avatar(naam);
   /*if(strcmp(naam, "Celine")==0){
      this->avatar = CELINE_AVATAR;
   } else if(strcmp(naam, "Iris")==0){
      this->avatar = IRIS_AVATAR;
   } else if(strcmp(naam, "Thomas")==0){
      this->avatar = THOMAS_AVATAR;
   } else if(strcmp(naam, "Sjors")==0){
      this->avatar = SJORS_AVATAR;
   } else if(strcmp(naam, "Wiebke")==0){
      this->avatar = WIEBKE_AVATAR;
   } */
   
}  

