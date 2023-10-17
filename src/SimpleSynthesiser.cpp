//
// Created by Dylan Smith on 8/10/2023.
//

#include "SimpleSynthesiser.h"
#include "SimpleSynthSound.h"
#include "SimpleSynthVoice.h"
#include "WaveFunctions.h"

SimpleSynthesiser::SimpleSynthesiser(ParameterReferences &paramRefs) : juce::Synthesiser(), parameters(paramRefs) {
    addSound(new SimpleSynthSound());
    for(int n = SimpleSynthSound::MIN_MIDI_NOTE; n <= SimpleSynthSound::MAX_MIDI_NOTE; n++){
        addVoice(new SimpleSynthVoice(n,
                                      [this](double angle){ return toneFromAngle(angle); },
                                      [this](){ return adsrPramsFromPluginParams(); } ));
    }
}



SimpleSynthesiser::~SimpleSynthesiser() {

}


void SimpleSynthesiser::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
//    Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
    const juce::ScopedLock sl (lock);

    if(getNumSounds() == 0 || getNumVoices() == 0)
        return;

    auto mainSound = dynamic_cast<SimpleSynthSound*>(getSound(0).get());

    if(mainSound == nullptr)
        return;

    if(!mainSound->appliesToNote(midiNoteNumber) || !mainSound->appliesToChannel(midiChannel))
        return;

    const int voiceIndex = midiNoteNumber - SimpleSynthSound::MIN_MIDI_NOTE;
    auto* voice = getVoice(voiceIndex);

    if (voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel (midiChannel))
        stopVoice (voice, 1.0f, true);


    startVoice(voice, mainSound, midiChannel, midiNoteNumber, velocity);

}

void SimpleSynthesiser::prepareToPlay(double sampleRate) {
    setCurrentPlaybackSampleRate(sampleRate);
}

void SimpleSynthesiser::processNextBlock(juce::AudioBuffer<float> &outputAudio, const juce::MidiBuffer &inputMidi,
                                         int startSample, int numSamples) {
    renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
}

double SimpleSynthesiser::toneFromAngle(double angle) {
    const auto waveType = parameters.generatorGroup.wave_type.getIndex();

    switch (waveType) {
        case(0):
            return WaveFunctions::sinFromAngle(angle);
        case(1):
            return WaveFunctions::sawtoothFromAngle(angle);
        case(2):
            return WaveFunctions::triangleFromAngle(angle);
        case(3):
            return WaveFunctions::squareFromAngle(angle);
        default:
            return WaveFunctions::sinFromAngle(angle);
    }
}

juce::ADSR::Parameters SimpleSynthesiser::adsrPramsFromPluginParams() {
    const float attack = parameters.adsrGroup.attack.get();
    const float decay = parameters.adsrGroup.decay.get();
    const float sustain = parameters.adsrGroup.sustain.get();
    const float release = parameters.adsrGroup.release.get();
    return juce::ADSR::Parameters(attack, decay, sustain, release);
}

