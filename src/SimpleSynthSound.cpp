//
// Created by Dylan Smith on 2/10/2023.
//

#include "SimpleSynthSound.h"

SimpleSynthSound::SimpleSynthSound(){}

SimpleSynthSound::~SimpleSynthSound() {}

bool SimpleSynthSound::appliesToNote(int midiNoteNumber) {
    return midiNoteNumber >= MIN_MIDI_NOTE && midiNoteNumber <= MAX_MIDI_NOTE;
}

bool SimpleSynthSound::appliesToChannel(int midiChannel) {
    return true;
}


