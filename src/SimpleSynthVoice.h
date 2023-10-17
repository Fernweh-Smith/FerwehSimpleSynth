//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

class SimpleSynthVoice : public juce::SynthesiserVoice {
public:
    SimpleSynthVoice(int midiNoteNumber, std::function<double(double)> toneFunc, std::function<juce::ADSR::Parameters()> adsrParamFunc);

    ~SimpleSynthVoice() override;

    bool canPlaySound(juce::SynthesiserSound *sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                   int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

private:
    const int midiNote;
    const double frequency;
    double currentPhase = 0.0;
    double phasePerSample = 0.0;
    double currentTime = 0.0;
    double timePerSample = 0.0;

    juce::ADSR adsr;
    void reset();
    void incrementTimers();

    std::function<double(double angle)> toneFunction;
    std::function<juce::ADSR::Parameters()> adsrParamFunction;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleSynthVoice)
};
