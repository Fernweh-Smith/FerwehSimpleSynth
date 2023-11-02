//
// Created by Dylan Smith on 2/11/2023.
//

#include "components/Pad.h"

Pad::Pad(int choiceIndex) : value(choiceIndex){
    button.setTriggeredOnMouseDown(true);
//    button.onClick = []{std::cout<<"Button Clicked\n";};
//    button.onStateChange = [this]{std::cout<<"State Changed\n";
//    std::cout << button.isDown() << "\n"; };

    addAndMakeVisible(button);
}

Pad::~Pad() {

}

void Pad::paint(juce::Graphics &g) {
}

void Pad::resized() {
    button.setBounds(getLocalBounds());
}

juce::Button& Pad::getButtonReference() {
    return button;
}

//================ Param Attachment ================

PadToChoiceParameterAttachment::PadToChoiceParameterAttachment(juce::AudioParameterChoice &parameter, Pad &pad,
                                                               juce::UndoManager *undoManager) :
                                                               pad(pad),
                                                               storedParameter(parameter),
                                                               attachment(storedParameter, [this](float value) { setValue(value); }, undoManager)
{
    sendInitialUpdate();
    pad.getButtonReference().addListener(this);
}

PadToChoiceParameterAttachment::~PadToChoiceParameterAttachment() {
    pad.getButtonReference().removeListener(this);

}

void PadToChoiceParameterAttachment::sendInitialUpdate() {
    attachment.sendInitialUpdate();
}

void PadToChoiceParameterAttachment::setValue(float newValue) {
    const juce::ScopedValueSetter<bool> svs (ignoreCallbacks, true);

}

void PadToChoiceParameterAttachment::buttonClicked(juce::Button *button) {
    if(ignoreCallbacks)
        true;
    if(button != &pad.getButtonReference())
        return;

    std::cout<<"button clicked yo!!\n";
    attachment.setValueAsCompleteGesture((float) pad.value);
}
