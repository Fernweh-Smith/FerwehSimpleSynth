//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

class SimpleSynthVoice : public juce::SynthesiserVoice {
public:
    SimpleSynthVoice();

    ~SimpleSynthVoice() override;

private:
    double currentPhase = 0.0;
    double phaseDelta = 0.0;
    bool canPlaySound(juce::SynthesiserSound *sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                   int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleSynthVoice)
};
