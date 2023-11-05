//
// Created by Dylan Smith on 31/10/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "ParameterListener.h"
#include "Pad.h"



class ChoicePad : public juce::Component {

public:
    explicit ChoicePad(juce::AudioParameterChoice& parameter);

    void paint(juce::Graphics &g) override;

    void resized() override;



private:
    struct PadAndAttachment{
        PadAndAttachment(int value, juce::AudioParameterChoice& param);
        Pad pad;
        PadToChoiceParameterAttachment attachment;
    };

    juce::AudioParameterChoice& param;
    std::vector<std::unique_ptr<PadAndAttachment>> pads;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChoicePad)
};
