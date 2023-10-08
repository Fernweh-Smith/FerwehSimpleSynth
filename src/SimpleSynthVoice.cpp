//
// Created by Dylan Smith on 2/10/2023.
//

#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"
#include <juce_core/juce_core.h>

SimpleSynthVoice::SimpleSynthVoice(int midiNoteNumber) :
    midiNote(midiNoteNumber),
    frequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)) {}

SimpleSynthVoice::~SimpleSynthVoice() {

}

bool SimpleSynthVoice::canPlaySound(juce::SynthesiserSound *sound) {
//    return dynamic_cast<SimpleSynthSound*>(sound) != nullptr;
return true;
}

void SimpleSynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                                 int currentPitchWheelPosition) {
    currentPhase = 0.0;
    phaseDelta = frequency / getSampleRate();
    currentPhase += phaseDelta;

}

void SimpleSynthVoice::stopNote(float velocity, bool allowTailOff) {
    clearCurrentNote();
    phaseDelta = 0.0;

}

void SimpleSynthVoice::pitchWheelMoved(int newPitchWheelValue) {

}

void SimpleSynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SimpleSynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    if(phaseDelta == 0.0)
        return;

    for(auto i = startSample; i < startSample+numSamples; i++){
        auto currentValue = (float)std::sin(currentPhase * juce::MathConstants<double>::twoPi) * 0.025f;

        for (auto c = outputBuffer.getNumChannels(); --c >= 0;){
            outputBuffer.addSample (c, i, currentValue);
        }


        currentPhase += phaseDelta;

    }
}


