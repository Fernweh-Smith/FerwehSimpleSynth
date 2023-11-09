//
// Created by Dylan Smith on 31/10/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "ParameterListener.h"
#include "Pad.h"

struct PadAndAttachment{
    PadAndAttachment(int value, juce::AudioParameterChoice& param);
    Pad pad;
    PadToChoiceParameterAttachment attachment;
};

struct SliderAndAttachment{
    explicit SliderAndAttachment(juce::AudioParameterFloat& param);
    juce::Slider slider;
    juce::SliderParameterAttachment attachment;
};

class WaveSelectionPad : public juce::Component {

public:
    explicit WaveSelectionPad(juce::AudioParameterChoice& parameter);

    void paint(juce::Graphics &g) override;

    void resized() override;



private:
    juce::Label titleLabel;
    juce::AudioParameterChoice& param;
    std::vector<std::unique_ptr<PadAndAttachment>> pads;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveSelectionPad)
};

//class ShaperSelectionPad : public juce::Component {
//
//public:
//    explicit ShaperSelectionPad(juce::AudioParameterChoice& parameter) {
//
//    }
//
//    void paint(juce::Graphics &g) override {
//        Component::paint(g);
//    }
//
//    void resized() override {
//        Component::resized();
//    }
//
//
//private:
//
//    juce::AudioParameterChoice& param;
//    std::vector<std::unique_ptr<PadAndAttachment>> pads;
//    std::unique_ptr<SliderAndAttachment> slider;
//
//
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShaperSelectionPad)
//};
//
