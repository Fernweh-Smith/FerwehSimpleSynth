//
// Created by Dylan Smith on 2/10/2023.
//

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginParameters.h"


//==============================================================================
PluginEditor::PluginEditor (PluginAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
        : AudioProcessorEditor (&p),
        pluginProcessor (p),
        valueTreeState(apvts),
          gainSliderAttachment(valueTreeState, IDs::out_gain, gainSlider)
{
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, gainSlider.getTextBoxWidth(), gainSlider.getTextBoxHeight());
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);
//    gainSliderAttachment = std::make_unique<SliderAttachment>(pluginProcessor.apvts, IDs::out_gain, gainSlider);

    setSize (400, 300);
}

PluginEditor::~PluginEditor()
{
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour(34, 54, 67));

    auto childBounds = getLookAndFeel().getSliderLayout(gainSlider).sliderBounds;
    auto bounds = getLocalArea(&gainSlider, childBounds);
    g.drawRect(bounds);
    g.drawRect(childBounds);
    std::vector<float> valuesToMark {6.0f, 3.0f, 0.0f, -3.0f, -6.0f, -12.0f, -20.0f, -30.0f, -100.0f};

    g.setColour(juce::Colours::white);

    for(auto val : valuesToMark){
        const double posOnSlider = gainSlider.valueToProportionOfLength(val);
        const float minY = bounds.getBottom();
        const float maxY = bounds.getTopLeft().getY();
        const float centerX = bounds.getCentreX();
        const float startX = centerX - 10.0f;
        const float endX = startX - 15.0f;
        const auto yPos = juce::jmap<float>(posOnSlider, minY, maxY);
        g.drawLine(startX, yPos, endX, yPos);
        g.setFont(12.0f);
        const auto textRect = juce::Rectangle(40.0f, 2.0f).withCentre({endX - 25, yPos});
        g.drawText(juce::String(val), textRect, juce::Justification::centredRight);
    }

}

void PluginEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    auto area = getLocalBounds();
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    fb.flexDirection = juce::FlexBox::Direction::column;
    fb.alignItems = juce::FlexBox::AlignItems::flexEnd;

//    fb.items.add(juce::FlexItem(gainSlider).withMinHeight(200).withMinWidth(75));
    fb.items.add(juce::FlexItem(gainSlider).withMinHeight(200).withWidth(75));

    fb.items.add(juce::FlexItem(gainLabel).withMinHeight(50).withMinWidth(75));


    fb.performLayout(getLocalBounds());
    getLookAndFeel().getSliderLayout(gainSlider).sliderBounds.translate(100, 0);

}
