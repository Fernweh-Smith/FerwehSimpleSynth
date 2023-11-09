//
// Created by Dylan Smith on 31/10/2023.
//

#include "components/SelectionPads.h"
#include "components/Constants.h"

PadAndAttachment::PadAndAttachment(int value, juce::AudioParameterChoice &param)
        : attachment(param, pad, value) {

}

SliderAndAttachment::SliderAndAttachment(juce::AudioParameterFloat &param)
        : attachment(param, slider) {

}


//================ Wave Selection Pad ================

WaveSelectionPad::WaveSelectionPad(juce::AudioParameterChoice &parameter) : param(parameter)
{
    titleLabel.setText("Wave Selection", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    const int nButtons = 4;
    for(int i = 0; i < nButtons; i++){

        auto padAndAttachment = std::make_unique<PadAndAttachment>(i, param);

        addAndMakeVisible(padAndAttachment.get()->pad);

        pads.push_back(std::move(padAndAttachment));
    }
}

void WaveSelectionPad::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::white);
    auto borderBounds = getLocalBounds().toFloat().reduced(Style::BorderInset);
    g.drawRoundedRectangle(borderBounds, Style::CornerRadius, Style::BorderThickness);
}

void WaveSelectionPad::resized() {
    const int labelHeight = 40.0f;
    const int spacing = 30.0f;
    const int padding = 10.0f;


    {
        auto labelBounds = getLocalBounds().removeFromTop(padding);
        labelBounds = labelBounds.withHeight(labelHeight);

        titleLabel.setBounds(labelBounds);
    }

    {
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

        auto gridBounds = getLocalBounds().withTrimmedTop(labelHeight + spacing)
                .withTrimmedBottom(padding)
                .withTrimmedRight(padding)
                .withTrimmedLeft(padding);

        if(gridBounds.getHeight() > gridBounds.getWidth()){
            const auto diff = gridBounds.getHeight() - gridBounds.getWidth();
            gridBounds.removeFromTop(diff);
        } else {
            const auto diff = (gridBounds.getWidth() - gridBounds.getHeight()) / 2;
            gridBounds.removeFromLeft(diff);
            gridBounds.removeFromRight(diff);

        }

        grid.performLayout(gridBounds);

    }
}


//================ Shaper Selection Pad ================
