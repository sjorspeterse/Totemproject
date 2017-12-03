#include "totem.h"

bool Input::available = false;
int Input::input;


bool Input::run() {
	// if (Serial.available() == 0){
	// 	available = false;
	// } else {
	// 	char c = Serial.read();
	// 	available = true;
	// 	switch(c) {
	// 	    case 'l' : 
	// 	    	input =  Button::left;
	// 	    	break;
	// 	    case 'r' : 
	// 	    	input = Button::right;
	// 	    	break;
	// 	    case 'u' : 
	// 	    	input = Button::up;
	// 	    	break;
	// 	    case 'd' : 
	// 	    	input = Button::down;
	// 	    	break;
	// 	    case 'o' : 
	// 	    	input = Button::ok;
	// 	    	break;
	// 	    case '1' : 
	// 	    	input = Button::one;
	// 	    	break;
	// 	    case '2' : 
	// 	    	input = Button::two;
	// 	    	break;
	// 	    case '3' : 
	// 	    	input = Button::three;
	// 	    	break;
	// 	    case '4' : 
	// 	    input = Button::four;
	// 	    	break;
	// 	}
	// }

	// check all pins

	// if input available: next_call time = cur call_time + 1 sec
	// if not, sooner!

	int truePin = -1;
	int pins[] = {BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_LEFT_PIN, BUTTON_RIGHT_PIN, BUTTON_OK_PIN};
	for(const int pin : pins) {
		// Serial.println(pin);
		// reading = digitalRead(pin);
		int kaas = digitalRead(pin);
		if(digitalRead(pin)){
			truePin = pin;
		}
		// Serial.print(reading);
	}
	// Serial.println("");

//	Serial.println("truePin: " + truePin);
	available = true;
	switch(truePin) {
		case BUTTON_LEFT_PIN : 
			Serial.print("pressed left");
	    	input =  Button::left;
	    	break;
	    case BUTTON_RIGHT_PIN : 
	    	input = Button::right;
	    	break;
	    case BUTTON_UP_PIN: 
	    	input = Button::up;
	    	break;
	    case BUTTON_DOWN_PIN : 
	    	input = Button::down;
	    	break;
	    case BUTTON_OK_PIN : 
	    	input = Button::two;
	    	break;
	    default:
	    	available = false;
	    	break;
	}
	return true;
}

bool Input::should_run() {
	return true;
}
