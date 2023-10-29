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
          gainFader(valueTreeState, IDs::out_gain)
{

    addAndMakeVisible(gainFader);

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


}

void PluginEditor::resized() {
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
    using FlexBox = juce::FlexBox;

    FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.flexDirection = FlexBox::Direction::column;
    fb.justifyContent = FlexBox::JustifyContent::center;
    fb.alignContent = FlexBox::AlignContent::center;


    fb.items.add(juce::FlexItem(gainFader).withWidth(GainFader::MIN_WIDTH).withMinHeight(250));

    fb.performLayout(getLocalBounds());
}