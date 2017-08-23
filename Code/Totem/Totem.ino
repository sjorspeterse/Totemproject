
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

  	randomSeed(analogRead(0));
  
	player_list[0] = &Iris;
	player_list[1] = &Thomas;
	player_list[2] = &Wiebke;
	player_list[3] = &Celine;
	player_list[4] = &Sjors;
  
}

void loop() { 

	Game game(player_list, &lcd, &Wiebke); //
  	game.demoAll();
  	/*MineSweeper ms = MineSweeper(player_list, &lcd, &Sjors);
  	Serial.println ("Created MineSweeper object!");
  	ms.start();*/
}

int free_ram () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

int get_input(){
	while (Serial.available() == 0) /* wait for input */ ;	
	char c = Serial.read();
	switch(c) {
	    case 'l' : return Button::left;
	    case 'r' : return Button::right;
	    case 'u' : return Button::up;
	    case 'd' : return Button::down;
	    case '1' : return Button::one;
	    case '2' : return Button::two;
	    case '3' : return Button::three;
	    case '4' : return Button::four;
	    case 'o' : return Button::ok;
	}
}