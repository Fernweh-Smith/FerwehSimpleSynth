//
// Created by Dylan Smith on 29/10/2023.
//

#include "components/GainFader.h"
#include "components/Constants.h"

GainFader::GainFader(juce::AudioProcessorValueTreeState& treeState, const juce::String& paramID) : sliderAttachment(treeState, paramID, slider) {
    titleLabel.setText("Gain", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);

    valueLabel.setText(slider.getTextFromValue(slider.getValue()), juce::dontSendNotification);
    valueLabel.setJustificationType(juce::Justification::centred);
    slider.onValueChange = [this](){ valueLabel.setText(slider.getTextFromValue(slider.getValue()), juce::dontSendNotification); };
    valueLabel.setEditable(true);
    valueLabel.onTextChange = [this](){ slider.setValue(slider.getValueFromText(valueLabel.getText())); };


    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0,0);

    addAndMakeVisible(titleLabel);
    addAndMakeVisible(valueLabel);
    addAndMakeVisible(slider);



}

void GainFader::paint(juce::Graphics &g) {

    auto childBounds = getLookAndFeel().getSliderLayout(slider).sliderBounds;
    auto bounds = getLocalArea(&slider, childBounds);

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

    auto borderBounds = getLocalBounds().toFloat().reduced(Style::BorderInset);
    g.drawRoundedRectangle(borderBounds, Style::CornerRadius, Style::BorderThickness);

}

void GainFader::resized() {


//    subBox.performLayout(getLocalBounds());


    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::noWrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexDirection = juce::FlexBox::Direction::column;


    auto valueLabelFI = juce::FlexItem(valueLabel);
    valueLabelFI.minHeight = 30.0f;
    valueLabelFI.minWidth = MIN_WIDTH;

    auto sliderFI = juce::FlexItem(slider);
    sliderFI.width = 25;
    sliderFI.flexGrow = 1.0f;
    sliderFI.margin = {0,10.0f,0,0};
    sliderFI.alignSelf = juce::FlexItem::AlignSelf::flexEnd;

    auto titleLabelFI = juce::FlexItem(titleLabel);
    titleLabelFI.minHeight = 30.0f;
    titleLabelFI.minWidth = MIN_WIDTH;


    fb.items.add(valueLabelFI);
    fb.items.add( sliderFI);
    fb.items.add(titleLabelFI);


    fb.performLayout(getLocalBounds());


}
