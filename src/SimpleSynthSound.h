//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>


class SimpleSynthSound : public juce::SynthesiserSound {
public:
    SimpleSynthSound();
    ~SimpleSynthSound() override;


    bool appliesToNote(int midiNoteNumber) override;

    bool appliesToChannel(int midiChannel) override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleSynthSound)
};
