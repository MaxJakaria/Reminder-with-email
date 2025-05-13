#include "melody.h"
#include <Arduino.h>

// Define melody notes (Super Mario Theme)
int melody[] = {
    NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C5,
    NOTE_E4, NOTE_G4, NOTE_F4, NOTE_D4,
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4,
    NOTE_E4, NOTE_C5, NOTE_E4, NOTE_G4};

int noteDurations[] = {
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4};

void playMelody()
{
    const int channel = 0;
    const int resolution = 8;

    ledcSetup(channel, 1000, resolution); // Initial setup, frequency is overwritten
    ledcAttachPin(25, channel);           // Assumes buzzer is on pin 25

    for (int i = 0; i < sizeof(melody) / sizeof(int); i++)
    {
        int noteDuration = 1000 / noteDurations[i];
        ledcWriteTone(channel, melody[i]); // Output frequency to speaker
        delay(noteDuration);
        ledcWriteTone(channel, 0); // Stop note
        delay(noteDuration * 0.3); // Brief pause between notes
    }
}
