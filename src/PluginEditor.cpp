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
    g.fillAll(juce::Colour(34, 54, 67).brighter());


}

void PluginEditor::resized() {

    juce::FlexBox fb;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;


    fb.items.add(juce::FlexItem(gainFader).withWidth(GainFader::MIN_WIDTH).withMinHeight(250));

    fb.performLayout(getLocalBounds());
}