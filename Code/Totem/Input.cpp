#include "totem.h"

#define LONG_PRESS 300

bool Input::available = false;
static int Input::button_status[6] = {BUTTON_NOTHING, BUTTON_NOTHING, BUTTON_NOTHING, BUTTON_NOTHING, BUTTON_NOTHING, BUTTON_NOTHING};

Input::Input(){
	for(int i=0; i<6; i++){
		this->buttons_last_pressed[i] = 0;
	}
}

bool Input::run() {	
	int pins[] = {BUTTON_OK_PIN, BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_LEFT_PIN, BUTTON_RIGHT_PIN};

	// Serial.print("status(");
	// Serial.print(millis());
	// Serial.print("): [");
	available = false;
	for(int i=0; i<5; i++) {
		if(digitalRead(pins[i])){
			button_status[i] = BUTTON_PRESSED;
			if(buttons_last_pressed[i] == 0){
				buttons_last_pressed[i] = millis();
        available = true;
        Serial.print(" TRUE ");
			}
		} else {
			int press_length = millis() - buttons_last_pressed[i];
			if(press_length > LONG_PRESS && buttons_last_pressed[i] != 0){
				button_status[i] = BUTTON_RELEASED_LONG;
				available = true;
				//Serial.println("Input is available, because released short");
			}
			else if(buttons_last_pressed[i] > 0){
				button_status[i] = BUTTON_RELEASED_SHORT;
				available = true;
				//Serial.println("Input is available, because released long");

			}

			if(buttons_last_pressed[i] == 0){
				button_status[i] = BUTTON_NOTHING;
			}
			buttons_last_pressed[i] = 0;
		}
		 Serial.print(button_status[i]);
		 Serial.print("(");
		 Serial.print(buttons_last_pressed[i]);
		 Serial.print("), ");
	}
	// Serial.println("]");
	Serial.print("Input::run(): available = ");
	Serial.println(available);
	return true;
}

bool Input::should_run() {
	return true;
}
