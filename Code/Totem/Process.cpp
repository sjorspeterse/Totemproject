#include "totem.h"

bool Input::available = false;
int Input::input;
bool Background::is_active[10] = {false};
Process* Background::process_list[10] = {nullptr};

void Animation::run() {

}

static void Input::run() {
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
}

void Audio::run() {

}

void Timer::run() {

}

static void Background::run_all(){
	int time = millis();

	for(int i = 0; i<10; i++) {
		if(is_active[i]) {
			process_list[i]->run();
		}
	}
}

static void Background::add(Process *process){
	int i = 0;
	while(is_active[i]) i++;

	process_list[i] = process;
	is_active[i] = true;
}

static void Background::remove(int index){
	delete process_list[index];
	is_active[index] = false;
}