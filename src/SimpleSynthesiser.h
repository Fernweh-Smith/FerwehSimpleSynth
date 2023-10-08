//
// Created by Dylan Smith on 8/10/2023.
//

#pragma once

#include "juce_audio_basics/juce_audio_basics.h"


class SimpleSynthesiser : public juce::Synthesiser {
public:
    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;

};
