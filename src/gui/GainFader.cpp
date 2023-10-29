//
// Created by Dylan Smith on 29/10/2023.
//

#include "components/GainFader.h"

GainFader::GainFader(juce::AudioProcessorValueTreeState& treeState, const juce::String& paramID) : sliderAttachment(treeState, paramID, slider) {
    titleLabel.setText("Gain", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);

    valueLabel.setText(slider.getTextFromValue(slider.getValue()), juce::dontSendNotification);
    valueLabel.setJustificationType(juce::Justification::centred);
    slider.onValueChange = [this](){ valueLabel.setText(slider.getTextFromValue(slider.getValue()), juce::dontSendNotification); };

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0,0);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(valueLabel);
    addAndMakeVisible(slider);

}

void GainFader::paint(juce::Graphics &g) {
//    g.fillAll(juce::Colours::palegreen.darker());

    auto childBounds = getLookAndFeel().getSliderLayout(slider).sliderBounds;
    auto bounds = getLocalArea(&slider, childBounds);
//    g.drawRect(bounds);
//    g.drawRect(childBounds);
    std::vector<float> valuesToMark {6.0f, 3.0f, 0.0f, -3.0f, -6.0f, -12.0f, -20.0f, -30.0f, -100.0f};

    g.setColour(juce::Colours::white);

    for(auto val : valuesToMark){
        const double posOnSlider = slider.valueToProportionOfLength(val);
        const float minY = bounds.getBottom();
        const float maxY = bounds.getTopLeft().getY();
        const float centerX = bounds.getCentreX();
        const float startX = centerX - 5.0f;
        const float endX = startX - 10.0f;
        const auto yPos = juce::jmap<float>(posOnSlider, minY, maxY);
        g.drawLine(startX, yPos, endX, yPos);
        g.setFont(12.0f);
        const auto textRect = juce::Rectangle(40.0f, 2.0f).withCentre({endX - 25, yPos});
        g.drawText(juce::String(val), textRect, juce::Justification::centredRight);
    }

//    g.setColour(juce::Colours::white.darker());
//    auto labelOutline = gainLabel.getBounds();
//    g.drawRect(labelOutline);

    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f, 1.0f), 12.0f, 2.0f);
}

void GainFader::resized() {


//    subBox.performLayout(getLocalBounds());

    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    fb.flexDirection = juce::FlexBox::Direction::column;




    fb.items.add(juce::FlexItem(valueLabel).withMinHeight(30).withMinWidth(MIN_WIDTH));
    fb.items.add(juce::FlexItem(slider).withMinHeight(100).withWidth(40).withFlex(2.0f).withMargin(juce::FlexItem::Margin(0,0,0,getLocalBounds().getWidth()-40)));

    fb.items.add(juce::FlexItem(titleLabel).withMinHeight(30).withMinWidth(MIN_WIDTH));


    fb.performLayout(getLocalBounds());
}
