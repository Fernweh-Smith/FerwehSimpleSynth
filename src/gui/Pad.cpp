//
// Created by Dylan Smith on 2/11/2023.
//

#include "components/Pad.h"

Pad::Pad() : juce::Button("")
{
    setTriggeredOnMouseDown(true);
}

Pad::~Pad() {

}


void Pad::paintButton(juce::Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
    const float cornerSize = 6.0f;
    const auto bounds = getLocalBounds().toFloat();
    const float innerBuffer = 4.0f;

    if(isEngaged()){
        g.setColour(activeColour);
    } else {
        g.setColour(idleColour);
    }

    g.fillRoundedRectangle(bounds, cornerSize);

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(bounds.reduced(innerBuffer), cornerSize - (innerBuffer/2.0f));
}

void Pad::engage(bool shouldSendNotification) {
    const auto notification = shouldSendNotification ? juce::sendNotification : juce::dontSendNotification;

    if(isToggleable()){
        setToggleState(true, notification);
    } else {
        triggerClick();
    }
}

void Pad::release(bool shouldSendNotification) {
    const auto notification = shouldSendNotification ? juce::sendNotification : juce::dontSendNotification;

    if(isToggleable()){
        setToggleState(false, notification);
    }
}

bool Pad::isEngaged() {
    if(isToggleable()){
        return getToggleState();
    } else {
        return isDown();
    }
}


//================ Param Attachment ================

PadToChoiceParameterAttachment::PadToChoiceParameterAttachment(juce::AudioParameterChoice &parameter, Pad &pad, int outputValue,
                                                               juce::UndoManager *undoManager) :
                                                               pad(pad),
                                                               storedParameter(parameter),
                                                               value(outputValue),
                                                               attachment(storedParameter, [this](float value) { setValue(value); },
                                                                          undoManager)
{
    pad.addListener(this);

    pad.setToggleable(true);

    sendInitialUpdate();
}

PadToChoiceParameterAttachment::~PadToChoiceParameterAttachment() {
    pad.setToggleable(false);

    pad.removeListener(this);
}

void PadToChoiceParameterAttachment::sendInitialUpdate() {
    attachment.sendInitialUpdate();
}

void PadToChoiceParameterAttachment::setValue(float newValue) {
    const juce::ScopedValueSetter<bool> svs (ignoreCallbacks, true);

    if(juce::approximatelyEqual(newValue, (float)value))
        pad.engage();
    else
        pad.release();
}

void PadToChoiceParameterAttachment::buttonClicked(juce::Button *button) {
    if(ignoreCallbacks)
        return;

    attachment.setValueAsCompleteGesture((float)value);
}
