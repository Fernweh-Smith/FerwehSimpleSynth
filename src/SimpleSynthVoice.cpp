//
// Created by Dylan Smith on 2/10/2023.
//

#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"
#include <juce_core/juce_core.h>
#include "iostream"

SimpleSynthVoice::SimpleSynthVoice(int midiNoteNumber, std::function<double(double angle)> toneFunc, std::function<juce::ADSR::Parameters()> adsrParamFunc) :
    midiNote(midiNoteNumber),
    frequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)),
    toneFunction(toneFunc),
    adsrParamFunction(adsrParamFunc){}

SimpleSynthVoice::~SimpleSynthVoice() {

}

bool SimpleSynthVoice::canPlaySound(juce::SynthesiserSound *sound) {
//    return dynamic_cast<SimpleSynthSound*>(sound) != nullptr;
return true;
}

void SimpleSynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                                 int currentPitchWheelPosition) {
    reset();

    phasePerSample = frequency / getSampleRate();
    timePerSample = 1.0 / getSampleRate();

    adsr.setSampleRate(getSampleRate());
    adsr.setParameters(adsrParamFunction());
    adsr.noteOn();
}

void SimpleSynthVoice::stopNote(float velocity, bool allowTailOff) {
//    clearAndReset();
    adsr.noteOff();

}

void SimpleSynthVoice::pitchWheelMoved(int newPitchWheelValue) {

}

void SimpleSynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SimpleSynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    if(!isVoiceActive())
        return;

    for(auto i = startSample; i < startSample+numSamples; i++){
        const auto functionValue = (float)toneFunction(currentPhase * juce::MathConstants<double>::twoPi) * 0.025f;
        const auto envValue = adsr.getNextSample();
        const auto outValue = functionValue * envValue;


        for (auto c = outputBuffer.getNumChannels(); --c >= 0;){
            outputBuffer.addSample (c, i, outValue);
        }

        incrementTimers();



    }
    if(!adsr.isActive()){
        clearCurrentNote();
        reset();
    }

}

void SimpleSynthVoice::reset() {
    currentPhase = 0.0;
    phasePerSample = 0.0;
    currentTime = 0.0;
    timePerSample = 0.0;
    adsr.reset();
}

void SimpleSynthVoice::incrementTimers() {
    currentPhase += phasePerSample;
    currentTime += timePerSample;
}


