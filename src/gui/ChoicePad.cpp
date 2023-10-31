//
// Created by Dylan Smith on 31/10/2023.
//

#include "components/ChoicePad.h"

ChoicePad::ChoicePad(juce::AudioParameterChoice &parameter, juce::AudioProcessorValueTreeState &treeState) :
    parameter(parameter), treeState(treeState), parameterListener(treeState, parameter.getParameterID(), paramChangedCallback)
{
    const int nButtons = 8;
    for(int i = 0; i < nButtons; i++){
        auto button = std::make_unique<juce::TextButton>();
        button->setButtonText((std::stringstream() << i).str());
        button->setTriggeredOnMouseDown(true);
        button->onClick = [&parameter, i](){
            parameter = i;
        };

        paramChangedCallback("", parameter.getIndex());

        addAndMakeVisible(button.get());

        buttons.push_back(std::move(button));
    }
}

void ChoicePad::paint(juce::Graphics &g) {
}

void ChoicePad::resized() {
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    grid.templateColumns = {Track(Fr(1)), Track(Fr(1))};
//    grid.templateRows = {Track(Fr(1)), Track(Fr(1))};

    for(auto& button : buttons){
        grid.items.add( juce::GridItem(button.get()).withWidth(50).withHeight(50) );
    }

    grid.performLayout(getLocalBounds());
}
