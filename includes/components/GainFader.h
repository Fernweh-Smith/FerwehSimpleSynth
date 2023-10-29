//
// Created by Dylan Smith on 29/10/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"


class GainFader : public juce::Component {
public:
    GainFader(juce::AudioProcessorValueTreeState& treeState, const juce::String& paramID);

    void paint(juce::Graphics &g) override;

    void resized() override;

    constexpr static float MIN_WIDTH = 75.0f;

private:
    juce::Label titleLabel;
    juce::Label valueLabel;
    juce::Slider slider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    SliderAttachment sliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainFader)

};
