//
// Created by Dylan Smith on 31/10/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "ParameterListener.h"



class ChoicePad : public juce::Component {

public:
    ChoicePad(juce::AudioParameterChoice& parameter, juce::AudioProcessorValueTreeState& treeState);

    void paint(juce::Graphics &g) override;

    void resized() override;

private:

    std::vector<std::unique_ptr<juce::TextButton>> buttons;
    juce::AudioParameterChoice& parameter;
    juce::AudioProcessorValueTreeState& treeState;
    const OnChangeCallback paramChangedCallback = [this](const juce::String &parameterID, float newValue){
            for(size_t i = 0; i < buttons.size(); i++){
                auto& button = buttons.at(i);
                if(juce::approximatelyEqual(newValue, float(i))){
                    button->setColour(button->buttonColourId, juce::Colours::green);
                } else {
                    button->setColour(button->buttonColourId, juce::Colours::transparentBlack);
                }
            }
    };
    ParameterListener parameterListener;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChoicePad)
};
