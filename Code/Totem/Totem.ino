#include "totem.h"
#include <Arduino.h>

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

  	Background::add(new Input());
  	timer.setBrightness(0x0f);

}

Player & CharacterSelect(Player **player_list);

void loop() {
  Player &player = CharacterSelect(player_list);
//  MineSweeper game(player_list, &lcd, &Wiebke, &timer); //
//  game.demoAll();
  	MineSweeper ms = MineSweeper(player_list, &lcd, &player, &timer);
  	Serial.println ("Created MineSweeper object!");
  	ms.start();
}

void RotateLeft(Player **player_list, int char_number);
void RotateRight(Player **player_list, int char_number);


Player & CharacterSelect(Player **player_list) {
  int char_number = 0;
  int total_players = 13;
  int middlelocx = 42 - 17;

  player_list[(char_number + total_players -1)%total_players]->avatar->draw(middlelocx - 36 , -5, Avatar::normal);
  player_list[(char_number)%total_players]->avatar->draw(middlelocx, 0, Avatar::normal);
  player_list[(char_number+1)%total_players]->avatar->draw(middlelocx + 36, -5, Avatar::normal);
  lcd.update();

  while (Input::button_status[OK] != BUTTON_RELEASED_SHORT) {
    Background::run_all();
    if (Input::button_status[LEFT] == BUTTON_PRESSED) {
      RotateLeft(player_list, char_number);
      char_number = (char_number + total_players - 1) % total_players;
    }

    if (Input::button_status[RIGHT] == BUTTON_PRESSED) {
      RotateRight(player_list, char_number);
      char_number = (char_number + 1) % total_players;
    }
    Serial.print("Character is ");
    Serial.println(player_list[char_number]->naam);
  }
  Serial.println("Pressed OK!");
  Background::run_all();
  Player &character = *player_list[char_number];
  return character;
}

void RotateLeft(Player **player_list, int char_number) {
  Serial.print("Rotate left, player is ");
  Serial.println(player_list[char_number]->naam);
  int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  int middlelocx = 42-17;
  Avatar *leftmost, *left, *center, *right, *rightmost;

  int p_c = 13; // player count

  middlelocx = 42-17;
  for(int i = 0; i <11; i++){
    leftmost = player_list[(char_number + p_c-2)%p_c]->avatar;
    left = player_list[(char_number + p_c -1)%p_c]->avatar;
    center = player_list[(char_number)%p_c]->avatar;
    right = player_list[(char_number+1)%p_c]->avatar;
    rightmost = player_list[(char_number+2)%p_c]->avatar;

    lcd.clrScr();
    leftmost->draw(middlelocx - 2 * 36, -yoffset[44 - i], Avatar::normal);
    left->draw(middlelocx - 36 , -yoffset[33 - i], Avatar::normal); //Left figure
    center->draw(middlelocx, -yoffset[22 - i], Avatar::normal); //Middle figure
    right->draw(middlelocx + 36, -yoffset[11 - i], Avatar::normal); //Right figure
    lcd.update();

    middlelocx += acceleratex[i];
    delay(30);
  }
//  right->action();
}

void RotateRight(Player **player_list, int char_number) {
  Serial.print("Rotate right, player is ");
  Serial.println(player_list[char_number]->naam);
  int acceleratex[] = {1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
  int yoffset[] = {41, 40, 38, 35, 31, 26 ,20, 15, 11, 8, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 8, 11, 15, 20, 26, 31, 35, 38, 40, 41};
  int middlelocx = 42-17;
  Avatar *leftmost, *left, *center, *right, *rightmost;

  int p_c = 13; // player count

  middlelocx = 42-17;
  for(int i = 0; i <11; i++){
    leftmost = player_list[(char_number + p_c - 2)%p_c]->avatar;
    left = player_list[(char_number + p_c -1)%p_c]->avatar;
    center = player_list[(char_number)%p_c]->avatar;
    right = player_list[(char_number+1)%p_c]->avatar;
    rightmost = player_list[(char_number+2)%p_c]->avatar;

    lcd.clrScr();
    leftmost->draw(middlelocx - 2*36 , -yoffset[44 + i], Avatar::normal); //Left figure
    left->draw(middlelocx - 36 , -yoffset[33 + i], Avatar::normal); //Left figure
    center->draw(middlelocx, -yoffset[22 + i], Avatar::normal); //Middle figure
    right->draw(middlelocx + 36, -yoffset[11 + i], Avatar::normal); //Right figure
    rightmost->draw(middlelocx + 2*36, -yoffset[i], Avatar::normal); //Rightmost figure
    lcd.update();

    middlelocx -= acceleratex[i];
    delay(30);
  }
//   right->action();
}

int free_ram () {
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
