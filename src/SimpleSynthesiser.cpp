//
// Created by Dylan Smith on 8/10/2023.
//

#include "SimpleSynthesiser.h"
#include "SimpleSynthSound.h"

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
