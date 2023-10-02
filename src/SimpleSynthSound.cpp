//
// Created by Dylan Smith on 2/10/2023.
//

#include "SimpleSynthSound.h"

SimpleSynthSound::SimpleSynthSound(){}

SimpleSynthSound::~SimpleSynthSound() {}

bool SimpleSynthSound::appliesToNote(int midiNoteNumber) {
    return true;
}

bool SimpleSynthSound::appliesToChannel(int midiChannel) {
    return true;
}


