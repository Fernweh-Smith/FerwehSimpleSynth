//
// Created by Dylan Smith on 31/10/2023.
//

#include "components/ChoicePad.h"

ChoicePad::ChoicePad(juce::AudioParameterChoice &parameter) : param(parameter)
{
    const int nButtons = 4;
    for(int i = 0; i < nButtons; i++){

        auto padAndAttachment = std::make_unique<PadAndAttachment>(i, param);

        addAndMakeVisible(padAndAttachment.get()->pad);

        pads.push_back(std::move(padAndAttachment));
    }
}

void ChoicePad::paint(juce::Graphics &g) {
}

void ChoicePad::resized() {
    juce::Grid grid;
    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;
    using Px = juce::Grid::Px;
    grid.templateColumns = {Track(Fr(1)), Track(Fr(1))};
    grid.templateRows = {Track(Fr(1)), Track(Fr(1))};

    grid.setGap(Px(9));

    for(auto& pad : pads){
        grid.items.add( juce::GridItem(pad.get()->pad));
    }

    grid.performLayout(getLocalBounds());
}


ChoicePad::PadAndAttachment::PadAndAttachment(int value, juce::AudioParameterChoice &param)
: attachment(param, pad, value) {

}
