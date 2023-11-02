//
// Created by Dylan Smith on 2/10/2023.
//

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginParameters.h"


//==============================================================================
PluginEditor::PluginEditor (PluginAudioProcessor& p, PluginParameters& paramStruct)
        : AudioProcessorEditor (&p),
        pluginProcessor (p),
        parameters(paramStruct),
          gainFader(parameters.treeState, IDs::out_gain),
          choicePad(parameters.references.generatorGroup.wave_type, parameters.treeState),
          pad(1),
          padAttachment(parameters.references.generatorGroup.wave_type,
                                         pad)
{

    addAndMakeVisible(gainFader);
    addAndMakeVisible(choicePad);
    addAndMakeVisible(pad);

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


//    fb.items.add(juce::FlexItem(gainFader).withWidth(GainFader::MIN_WIDTH).withMinHeight(250));
//    fb.items.add(juce::FlexItem(choicePad).withMinHeight(100).withMinWidth(100));
    fb.items.add(juce::FlexItem(pad).withWidth(100).withHeight(100));
    fb.performLayout(getLocalBounds());
}