#include "totem.h"

Audio::Audio(int sound, bool loop)
{
	switch(sound){
		case Audio::MARIO_MAIN_THEME:
			this->size = sizeof(MARIO_THEME_TUNE) / sizeof(unsigned int);
			Serial.print("size = ");
			Serial.println(this->size);
			this->melody_mem = MARIO_THEME_TUNE;
			this->tempo_mem = MARIO_THEME_DURATIONS;
	}

	this->frame = 0;
	this->loop = loop;
}

bool Audio::run() {
	uint16_t noteDuration = 1000 / pgm_read_word_near(tempo_mem + 2*frame); // 2 bytes for every frame
	uint16_t note = pgm_read_word_near(melody_mem + 2*frame);

	Serial.print("running Music frame ");
	Serial.print(frame);
	Serial.print(": ");
	Serial.print(note);
	Serial.println(" Hz");

    tone(SPEAKER_PIN, note, noteDuration);

  		// to distinguish the notes, set a minimum time between them.
  		// the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

  		// stop the tone playing:
	tone(SPEAKER_PIN, 0, noteDuration);

	frame++;

	if(loop){
		if(frame >= size)
			frame = 0;
		return true
	} else{
		return frame < size;
	}
}

bool Audio::should_run() {
	return true;
}

static void Audio::start_music(int song){

	Background::add(new Audio(song, true));

}

static void Audio::play_sound(int sound){

	Background::add(new Audio(sound, false));

}