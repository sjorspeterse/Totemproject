#include "totem.h"

int Timer::value;

Timer::Timer(TM1637Display* timer)
{
	this->timer = timer;
	value = 0;
	next_call_time = millis();
}

bool Timer::run() {
	Serial.println("Running timer!");
	timer->	showNumberDec(value++, false);
	next_call_time = millis() + 1000;
	return true;
}

bool Timer::should_run() {
	if(millis() > next_call_time)
		return true;
	else
		return false;
}
