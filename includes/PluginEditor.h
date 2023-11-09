//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "components/GainFader.h"
#include "components/SelectionPads.h"
#include "components/Pad.h"

class PluginAudioProcessor;

class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    PluginEditor (PluginAudioProcessor& p, PluginParameters& paramStruct);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& pluginProcessor;
    PluginParameters& parameters;

    GainFader gainFader;
    WaveSelectionPad choicePad;
    Pad pad;
    PadToChoiceParameterAttachment padAttachment;
//    juce::AudioProcessorValueTreeState::ButtonAttachment ba;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
