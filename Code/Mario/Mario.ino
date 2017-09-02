/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/
*/

#include "pitches.h"
int melodyPin = 8;

// notes in the melody:
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  sing(1);
  sing(2);
  
   // Play coin sound   
  tone(8,NOTE_B5,100);
  delay(100);
  tone(8,NOTE_E6,850);
  delay(800);
  noTone(8);
  
  delay(2000);  // pause 2 seconds

  // Play 1-up sound
  tone(8,NOTE_E6,125);
  delay(130);
  tone(8,NOTE_G6,125);
  delay(130);
  tone(8,NOTE_E7,125);
  delay(130);
  tone(8,NOTE_C7,125);
  delay(130);
  tone(8,NOTE_D7,125);
  delay(130);
  tone(8,NOTE_G7,125);
  delay(125);
  noTone(8);

  delay(2000);  // pause 2 seconds

  // Play Fireball sound
  tone(8,NOTE_G4,35);
  delay(35);
  tone(8,NOTE_G5,35);
  delay(35);
  tone(8,NOTE_G6,35);
  delay(35);
  noTone(8);
  
  delay(2000);  // pause 2 seconds
}

void sing(int song) {  
int size;
int *mel;
int * temp;

switch(song){
  case 1:
    Serial.println(" 'Mario Theme'");
    size = sizeof(melody) / sizeof(int);
    mel =  melody;
    temp = tempo;
    break;
  case 2:
    Serial.println(" 'Underworld Theme'");
    size = sizeof(underworld_melody) / sizeof(int);
    mel = underworld_melody;
    temp = underworld_tempo;
    break;
}
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < size; thisNote++) {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / temp[thisNote]; 
    tone(melodyPin, mel[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    Serial.println(pauseBetweenNotes);
    delay(pauseBetweenNotes);

      // stop the tone playing:
    tone(melodyPin, 0, noteDuration);
    }
}
