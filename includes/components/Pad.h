//
// Created by Dylan Smith on 2/11/2023.
//

#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

class Pad : public juce::Component
{
public:
    explicit Pad(int choiceIndex);
    ~Pad() override;
    void paint(juce::Graphics &g) override;
    void resized() override;
    juce::Button& getButtonReference();
    const int value;

private:
    juce::TextButton button;

};

class PadToChoiceParameterAttachment : private juce::Button::Listener
{
public:
    PadToChoiceParameterAttachment(juce::AudioParameterChoice& parameter,
                                   Pad& pad, juce::UndoManager* undoManager = nullptr);
    ~PadToChoiceParameterAttachment() override;

    void sendInitialUpdate();
private:
    void setValue(float newValue);

    void buttonClicked(juce::Button *button) override;

    Pad& pad;
    juce::AudioParameterChoice& storedParameter;
    juce::ParameterAttachment attachment;
    bool ignoreCallbacks = false;
};