#ifndef MELODY_H
#define MELODY_H

// Note frequencies (A = 440 Hz tuning)
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

// Melody data
extern int melody[];
extern int noteDurations[];

// Function declarations
void playMelody();

#endif