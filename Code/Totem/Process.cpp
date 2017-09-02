#include "totem.h"


bool Background::is_active[10] = {false};

Process* Background::process_list[10] = {nullptr};



static void Background::run_all(){
	int time = millis();
	bool still_active;

	for(int i = 0; i<10; i++) {
		if(is_active[i] && process_list[i]->should_run()) {
			still_active = process_list[i]->run();
			if(!still_active)
				remove(i);
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
	Serial.print("removing Process ");
	Serial.println(index);
	delete process_list[index];
	is_active[index] = false;
}