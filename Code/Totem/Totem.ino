
#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>

#include "avatars.h"
#include "demo.h"

#include "totem.h"

LCD5110 lcd(7,6,5,3,4); //Creating LCD object
Player Thomas = Player("Thomas", &lcd);
Player Iris = Player("Iris", &lcd);
Player Celine = Player("Celine", &lcd);
Player Wiebke = Player("Wiebke", &lcd);
Player Sjors = Player("Sjors", &lcd);
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
  const int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  
  int middlelocx = 42-17;

 /* 
  lcd.getBuffer(10, 10, bitmap, 13, 19);
  lcd.drawBitmapDynamic(40, 0, bitmap, 13, 19);
  lcd.update();*/

  lcd.clrScr();
  int x = 20;
  int y = -4;

 
  //Sjors.avatar->draw(20,0);
  //Sjors.avatar->action();

  //lcd.drawBitmap(x, y, SJORS_AVATAR, AVATAR_WIDTH, AVATAR_HEIGHT);


  /*for(int i = 0; i<5; i++)
  {
    lcd.drawBitmap(x + SJORS_ACTION_OFFSETX, y + SJORS_ACTION_OFFSETY, SJORS_ACTION[i], SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
    lcd.update();
    delay(100);
  } */

  
/*
  lcd.drawBitmap(x + SJORS_ACTION_OFFSETX, y + SJORS_ACTION_OFFSETY, sjors_action1, SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
  lcd.update();
  delay(100);

  lcd.drawBitmap(x + SJORS_ACTION_OFFSETX, y + SJORS_ACTION_OFFSETY, sjors_action2, SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
  lcd.update();
  delay(100);

  lcd.drawBitmap(x + SJORS_ACTION_OFFSETX, y + SJORS_ACTION_OFFSETY, sjors_action3, SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
  lcd.update();
  delay(100);

  lcd.drawBitmap(x + SJORS_ACTION_OFFSETX, y + SJORS_ACTION_OFFSETY, sjors_action4, SJORS_ACTION_WIDTH, SJORS_ACTION_HEIGHT);
  lcd.update();
  delay(100);
  */

  //lcd->drawBitmap(x, y, _bitmap, AVATAR_WIDTH, AVATAR_HEIGHT);

  Avatar *leftmost, *left, *center, *right, *rightmost;

  for (int nr = 0; nr < 5; nr++) {
    middlelocx = 42-17;
    for(int i = 0; i <11; i++){
      leftmost = player_list[nr%5]->avatar;
      left = player_list[(nr+1)%5]->avatar;
      center = player_list[(nr+2)%5]->avatar;
      right = player_list[(nr+3)%5]->avatar;
      rightmost = player_list[(nr+4)%5]->avatar;

      lcd.clrScr();
      left->draw(middlelocx - 36 , -yoffset[33 + i]); //Left figure
      center->draw(middlelocx, -yoffset[22 + i]); //Middle figure
      right->draw(middlelocx + 36, -yoffset[11 + i]); //Right figure
      rightmost->draw(middlelocx + 2*36, -yoffset[i]); //Rightmost figure
      lcd.update();

      middlelocx -= acceleratex[i];
      delay(30);   
    }
    right->action();
    right->look(EYES_LEFT);
    right->look(EYES_RIGHT);
    right->look(EYES_UP);
    right->look(EYES_DOWN);

    delay(1000);
  }

}
