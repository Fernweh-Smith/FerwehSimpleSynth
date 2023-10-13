//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "SimpleSynthesiser.h"

namespace IDs {
#define DEFINE_ID(id) static constexpr const char* id = #id;

    DEFINE_ID(simple_synth_apvts)

    DEFINE_ID(main_group)
    DEFINE_ID(out_gain)

    DEFINE_ID(generator_group)
    DEFINE_ID(wave_type)
    DEFINE_ID(shaper_type)
    DEFINE_ID(power_strength)

    DEFINE_ID(adsr_group)
    DEFINE_ID(attack)
    DEFINE_ID(decay)
    DEFINE_ID(sustain)
    DEFINE_ID(release)
}

double sinFromPhase (double phase);

class PluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PluginAudioProcessor();
    ~PluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();


    SimpleSynthesiser synth;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessor)
};
