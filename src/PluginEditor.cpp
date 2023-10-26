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
    g.fillAll(juce::Colours::grey);

//    g.setColour(juce::Colours::pink);

    auto componentBounds = gainSlider.getBounds();
    auto childBounds = getLookAndFeel().getSliderLayout(gainSlider).sliderBounds;
    auto offset = componentBounds.getTopLeft();
    g.drawRect(childBounds.translated(offset.getX(), offset.getY()));




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

    fb.items.add(juce::FlexItem(gainSlider).withMinHeight(200).withMinWidth(75));
    fb.items.add(juce::FlexItem(gainLabel).withMinHeight(50).withMinWidth(75));


    fb.performLayout(getLocalBounds());
}
