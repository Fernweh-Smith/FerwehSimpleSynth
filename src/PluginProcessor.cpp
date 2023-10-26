//
// Created by Dylan Smith on 2/10/2023.
//

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SimpleSynthSound.h"
#include "SimpleSynthVoice.h"
#include <juce_dsp/juce_dsp.h>
#include <iostream>


PluginAudioProcessor::PluginAudioProcessor() : PluginAudioProcessor(juce::AudioProcessorValueTreeState::ParameterLayout{}){}


PluginAudioProcessor::~PluginAudioProcessor()
= default;

//==============================================================================
const juce::String PluginAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool PluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PluginAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PluginAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int PluginAudioProcessor::getCurrentProgram() {
    return 0;
}

void PluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String PluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void PluginAudioProcessor::changeProgramName(int index, const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.prepareToPlay(sampleRate);
}

void PluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool PluginAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    #if !JucePlugin_IsSynth
        if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
            return false;
    #endif

    return true;
#endif
}

void PluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                        juce::MidiBuffer &midiMessages) {
    juce::ScopedNoDenormals noDenormals;

    buffer.clear();

//    juce::dsp::Gain<float> gainModule;
//    getBusBuffer(buffer,false,0);
//    bus


    synth.processNextBlock(buffer, midiMessages, 0.0, buffer.getNumSamples());

    const float decibels = paramRefs.mainGroup.outGain.get();
    const float targetGain = juce::Decibels::decibelsToGain(decibels);

    if(juce::approximatelyEqual(targetGain, currentGain) || juce::approximatelyEqual(currentGain, -1.0f)){
        buffer.applyGain(targetGain);
    } else {
        buffer.applyGainRamp(0, buffer.getNumSamples(), currentGain, targetGain);
    }
    currentGain = targetGain;

    midiMessages.clear();
}

//==============================================================================
bool PluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *PluginAudioProcessor::createEditor() {
    return new PluginEditor(*this, apvts);
//    return new juce::GenericAudioProcessorEditor(*this);
}


//==============================================================================
void PluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



juce::AudioProcessorValueTreeState::ParameterLayout PluginAudioProcessor::createParameterLayout() {

    using paramLayout = juce::AudioProcessorValueTreeState::ParameterLayout;
    using paramGroup = juce::AudioProcessorParameterGroup;

    using floatParam = juce::AudioParameterFloat;
    using choiceParam = juce::AudioParameterChoice;
    using boolParam = juce::AudioParameterBool;

    paramLayout params;

    //==== Main Group ====
    {
        auto mainGroup = std::make_unique<paramGroup>(IDs::main_group, "Main_Group", "|");
        auto outGainParam = std::make_unique<floatParam>(IDs::out_gain,
                                                         "Gain",
                                                         0.0f,
                                                         1.0f,
                                                         0.5f);

        auto& gainRef = *outGainParam;
        auto& gain2 = gainRef;
        auto& gain3  = gain2;

        std::cout << outGainParam << "\n";
        std::cout << &gainRef << "\n";
        std::cout << &gain2 << "\n";
        std::cout << &gain3 << "\n";



        mainGroup->  addChild(std::move(outGainParam));
        params.add(std::move(mainGroup));
    }

    //==== Generator Group ====
    {
        auto generatorGroup = std::make_unique<paramGroup>(IDs::generator_group, "Generator" ,"|");

        auto waveTypeParam = std::make_unique<choiceParam>(IDs::wave_type,
                                                           "Wave Type",
                                                           juce::StringArray("Sin", "Saw", "Triangle", "Square"),
                                                           0);
        auto shaperTypeParam = std::make_unique<choiceParam>(IDs::shaper_type,
                                                             "Shaper Type",
                                                             juce::StringArray("None", "Power"),
                                                             0);
        auto powerStrengthParam = std::make_unique<floatParam>(IDs::power_strength,
                                                               "Power",
                                                               1.0f,
                                                               10.f,
                                                               2.0f);

        generatorGroup->addChild(std::move(waveTypeParam));
        generatorGroup->addChild(std::move(shaperTypeParam));
        generatorGroup->addChild(std::move(powerStrengthParam));

        params.add(std::move(generatorGroup));

    }

    //==== ADSR Group ====
    {
        auto adsrGroup = std::make_unique<paramGroup>(IDs::adsr_group, "ADSR", "|");

        auto attackParam = std::make_unique<floatParam>(IDs::attack,
                                                         "Attack",
                                                         0.0f,
                                                         1.0f,
                                                         0.5f);
        auto decayParam = std::make_unique<floatParam>(IDs::decay,
                                                         "Decay",
                                                         0.0f,
                                                         1.0f,
                                                         0.5f);
        auto sustainParam = std::make_unique<floatParam>(IDs::sustain,
                                                         "Sustain",
                                                         0.0f,
                                                         1.0f,
                                                         0.5f);
        auto releaseParam = std::make_unique<floatParam>(IDs::release,
                                                         "Release",
                                                         0.0f,
                                                         1.0f,
                                                         0.5f);

//        auto& releaseReference = *releaseParam;
        adsrGroup->addChild(std::move(attackParam));
        adsrGroup->addChild(std::move(decayParam));
        adsrGroup->addChild(std::move(sustainParam));
        adsrGroup->addChild(std::move(releaseParam));

        params.add(std::move(adsrGroup));

    }


    return params;
}

PluginAudioProcessor::PluginAudioProcessor(juce::AudioProcessorValueTreeState::ParameterLayout layout)
    : AudioProcessor(BusesProperties()
        #if !JucePlugin_IsMidiEffect
        #if !JucePlugin_IsSynth
            .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        #endif
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        #endif
        ),
        paramRefs(layout),
        apvts(*this,
          nullptr,
          juce::Identifier(IDs::simple_synth_apvts),
          std::move(layout)),
          synth(paramRefs)
{

}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new PluginAudioProcessor();
}

