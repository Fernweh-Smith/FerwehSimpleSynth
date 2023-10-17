//
// Created by Dylan Smith on 8/10/2023.
//

#pragma once

#include "juce_audio_basics/juce_audio_basics.h"
#include "PluginParameters.h"


class SimpleSynthesiser : protected juce::Synthesiser {
public:
    explicit SimpleSynthesiser(ParameterReferences& paramRefs);
    ~SimpleSynthesiser() override;
    void prepareToPlay(double sampleRate);
    void processNextBlock (juce::AudioBuffer< float >& outputAudio, const juce::MidiBuffer& inputMidi, int startSample, int numSamples);




protected:
    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;


private:
    ParameterReferences& parameters;


};
