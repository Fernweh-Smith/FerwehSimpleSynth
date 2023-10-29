//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once

#include "components/GainFader.h"

class PluginAudioProcessor;

class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    PluginEditor (PluginAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& pluginProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    GainFader gainFader;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
