#include "totem.h"

bool Input::available = false;
int Input::input;

bool Input::run() {
	if (Serial.available() == 0){
		available = false;
	} else {
		char c = Serial.read();
		available = true;
		switch(c) {
		    case 'l' : 
		    	input =  Button::left;
		    	break;
		    case 'r' : 
		    	input = Button::right;
		    	break;
		    case 'u' : 
		    	input = Button::up;
		    	break;
		    case 'd' : 
		    	input = Button::down;
		    	break;
		    case 'o' : 
		    	input = Button::ok;
		    	break;
		    case '1' : 
		    	input = Button::one;
		    	break;
		    case '2' : 
		    	input = Button::two;
		    	break;
		    case '3' : 
		    	input = Button::three;
		    	break;
		    case '4' : 
		    input = Button::four;
		    	break;
		}
	}
	return true;
}

bool Input::should_run() {
	return true;
}
