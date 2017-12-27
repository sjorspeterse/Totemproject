#include "totem.h"

/* 
CONNECTIONS:

GND -> LCD GND (pin 8)
GND -> 330 ohm -> LCD LIGHT (pin 7)
3.3V -> LCD VCC (pin 6)
D3 -> 10k -> LCD RST (pin 1)
D4 -> 1k -> LCD CE (pin 2)
D5 -> 10k -> LCD DC (pin 3)
D6 -> 10k -> LCD DIN (pin 4)
D7 -> 10k -> LCD CLK (pin 5)
D8 -> Speaker+ -> Speaker- -> 1k -> GND
*/

LCD5110_SJORS lcd(38,40,42,46,44); //Creating LCD object
Player Thomas = Player("Thomas", &lcd);
Player Iris = Player("Iris", &lcd);
Player Celine = Player("Celine", &lcd);
Player Wiebke = Player("Wiebke", &lcd);
Player Sjors = Player("Sjors", &lcd);
Player Richard = Player("Richard", &lcd);
Player Aniek = Player("Aniek", &lcd);
Player Anna = Player("Anna", &lcd);
Player Corijn = Player("Corijn", &lcd);
Player Jeroen = Player("Jeroen", &lcd);
Player Rik = Player("Rik", &lcd);
Player Sander = Player("Sander", &lcd);
Player Thijs = Player("Thijs", &lcd);

Player *player_list[13];

//Timer
TM1637Display timer(TIMER_CLK, TIMER_DIO);
 

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
	player_list[5] = &Aniek;
	player_list[6] = &Anna;
	player_list[7] = &Corijn;
	player_list[8] = &Jeroen;
	player_list[9] = &Richard;
  	player_list[10] = &Rik;
	player_list[11] = &Sander;
	player_list[12] = &Thijs;

  	Background::add(new Input());		// DEZE NOG DELETEN 
  	timer.setBrightness(0x0f);

}

void loop() { 
	// MineSweeper game(player_list, &lcd, &Wiebke, &timer); //
	// game.demoAll();

  	MineSweeper ms = MineSweeper(player_list, &lcd, &Sjors, &timer);
  	Serial.println ("Created MineSweeper object!");
  	ms.start();
}

int free_ram () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

int get_hardware_input(){
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
