//
// Created by Dylan Smith on 2/10/2023.
//

#pragma once

//#include "PluginProcessor.h"

class PluginAudioProcessor;

class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginAudioProcessor&, juce::AudioProcessorValueTreeState& apvts);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& pluginProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Slider gainSlider;
    juce::Label gainLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
//    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    SliderAttachment gainSliderAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
