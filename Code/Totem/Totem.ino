
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
	Serial.begin(9600);
  	Serial.println("In setup");
  	lcd.InitLCD(); //Intializing LCD
  	Serial.println("Initilized LCD");
  
	player_list[0] = &Iris;
	player_list[1] = &Thomas;
	player_list[2] = &Wiebke;
	player_list[3] = &Celine;
	player_list[4] = &Sjors;
  
}

void loop() { 
	delay(200);
	Serial.println("Beginning of loop");
	//delay(2000);
  	MineSweeper ms = MineSweeper(player_list, &lcd);
  	Serial.println ("Created MineSweeper object!");
  	ms.start();
}
