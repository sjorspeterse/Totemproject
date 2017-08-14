#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>

#include "avatars.h"
#include "demo.h"

#include "totem.h"
///#include "Player.cpp"

LCD5110 lcd(7,6,5,3,4); //Creating LCD object
Player Thomas = Player("Thomas");
Player Iris = Player("Iris");
Player Celine = Player("Celine");
Player Wiebke = Player("Wiebke");
Player Sjors = Player("Sjors");
Player *player_list[5];

void setup() {
  lcd.InitLCD(); //Intializing LCD
  Serial.begin(9600);

  player_list[0] = &Iris;
  player_list[1] = &Thomas;
  player_list[2] = &Wiebke;
  player_list[3] = &Celine;
  player_list[4] = &Sjors;
}

void loop() {
  int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  int middlelocx = 42-17;

  for (int nr = 0; nr < 5; nr++) {
    middlelocx = 42-17;
    for(int i = 0; i <11; i++){
      lcd.clrScr(); //Clearing screen
      lcd.drawBitmap(middlelocx - 36 , -yoffset[33 + i], player_list[nr%5]->avatar, AVATAR_HOR, AVATAR_VERT); //Left figure
      lcd.drawBitmap(middlelocx, -yoffset[22 + i], player_list[(nr+1)%5]->avatar, AVATAR_HOR, AVATAR_VERT); //Middle figure
      lcd.drawBitmap(middlelocx + 36, -yoffset[11 + i], player_list[(nr+2)%5]->avatar, AVATAR_HOR, AVATAR_VERT); //Right figure
      lcd.drawBitmap(middlelocx + 2*36, -yoffset[i], player_list[(nr+3)%5]->avatar, AVATAR_HOR, AVATAR_VERT); //Rightmost figure
      lcd.update(); //Updating the LCD
      middlelocx -= acceleratex[i];
      delay(30);   
    }
    delay(1000);
  }

}
