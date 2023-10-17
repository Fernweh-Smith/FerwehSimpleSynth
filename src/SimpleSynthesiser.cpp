//
// Created by Dylan Smith on 8/10/2023.
//

#include "SimpleSynthesiser.h"
#include "SimpleSynthSound.h"
#include "SimpleSynthVoice.h"

SimpleSynthesiser::SimpleSynthesiser(ParameterReferences &paramRefs) : juce::Synthesiser(), parameters(paramRefs) {
    addSound(new SimpleSynthSound());
    for(int n = SimpleSynthSound::MIN_MIDI_NOTE; n <= SimpleSynthSound::MAX_MIDI_NOTE; n++){
        addVoice(new SimpleSynthVoice(n));
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

