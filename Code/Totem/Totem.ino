
#include <LCD5110_Graph.h>
#include <avr/pgmspace.h>

#include "avatars.h"
#include "demo.h"

#include "totem.h"

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
  const int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  int middlelocx = 42-17;

  unsigned char black [] PROGMEM= {0xd0, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff,};

  lcd.clrScr();
  
  uint8_t bitmap[AVATAR_WIDTH*AVATAR_HEIGHT/8];
  //uint8_t bitmap[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,};

  lcd.drawBitmap(0, 0, WIEBKE_AVATAR, AVATAR_WIDTH, AVATAR_HEIGHT);
  lcd.getBuffer(0, 0, bitmap, AVATAR_WIDTH, AVATAR_HEIGHT);
  lcd.drawBitmapDynamic(40, 0, bitmap, AVATAR_WIDTH, AVATAR_HEIGHT);
  lcd.update();

  
  /*for (uint8_t i = 0; i < 0xff; i++) {
    lcd.clrScr();
    bitmap[0] = i;
    lcd.drawBitmapDynamic(0, 0, bitmap, 8, 8);
    //Serial.print("Real: ");
    //Serial.print(bitmap[0]);
    lcd.getBuffer(0, 0, bitmap, 8, 8);
    //Serial.print(" Copied: ");
    //Serial.println(bitmap[0]);
    lcd.drawBitmapDynamic(40, 0, bitmap, 8, 8); 
    lcd.update(); //Updating the LCD
    //Serial.print("scrbuf[0] = ");
    uint8_t data = lcd.getByte(0);
    //Serial.println(data);
    //Serial.print("After: bitmap[0] = ");
    //Serial.println(bitmap[0]);

    if(lcd.getPixel(0, 0)) 
      {
        Serial.print("True,  bitmap[0 + (0/8)*1] before = ");
        Serial.print( bitmap[0 + (0/8)*1]);
        Serial.print(", 1<<0 = ");
        Serial.print(1<<0);
        Serial.print(", bitmap[0 + (0/8)*1] | (1<<0) = ");
        Serial.print(bitmap[0 + (0/8)*1] | (1<<0));
        bitmap[0 + (0/8)*1] |= (1<<0);
        Serial.print(",  bitmap[0 + (0/8)*1] after = ");
        Serial.println( bitmap[0 + (0/8)*1]);
      }
      else{
        Serial.print("False,  bitmap[0 + (0/8)*1] before = ");
        Serial.print( bitmap[0 + (0/8)*1]);
        Serial.print(", ~(1<<0) = ");
        Serial.print(~(1<<0));
        Serial.print(", bitmap[cx + (cy/8)*sx] & ~(1<<0) = ");
        Serial.print(bitmap[0 + (0/8)*1] & ~(1<<0));
        bitmap[0 + (0/8)*1] &= !(1<<0);
        Serial.print(",  bitmap[0 + (0/8)*1] after = ");
        Serial.println( bitmap[0 + (0/8)*1]); 
      }

    
    
    delay(100);
  }*/
  
  
  //Serial.println(lcd.getPixel(5,0));
  /*
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
  }*/

}
