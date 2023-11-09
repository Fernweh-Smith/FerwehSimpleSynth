//
// Created by Dylan Smith on 2/11/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

class Pad : public juce::Button
{
public:
    Pad();
    ~Pad() override;

    void engage(bool shouldSendNotification = false);
    void release(bool shouldSendNotification = false);

    bool isEngaged();

protected:
    void paintButton(juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    juce::Colour idleColour = juce::Colours::white;
    juce::Colour activeColour = juce::Colours::green.brighter();
    juce::Colour errorColour = juce::Colours::red;

};

class PadToChoiceParameterAttachment : private juce::Button::Listener
{
public:
    PadToChoiceParameterAttachment(juce::AudioParameterChoice& parameter,
                                   Pad& padRef, int outputValue, juce::UndoManager* undoManager = nullptr);
    ~PadToChoiceParameterAttachment() override;

    void sendInitialUpdate();
private:
    void setValue(float newValue);

    void buttonClicked(juce::Button *button) override;

    const int value;

    Pad& pad;
    juce::AudioParameterChoice& storedParameter;
    juce::ParameterAttachment attachment;
    bool ignoreCallbacks = false;
};