//
// Created by Dylan Smith on 17/10/2023.
//

#include "PluginParameters.h"



template <typename Param>
static Param& addToGroup( juce::AudioProcessorParameterGroup& group, std::unique_ptr<Param> param){
    auto& paramRef = *param;
    group.addChild(std::move(param));
    return paramRef;
}

static juce::AudioProcessorParameterGroup& addToLayout( juce::AudioProcessorValueTreeState::ParameterLayout& layout, std::unique_ptr<juce::AudioProcessorParameterGroup> param){
    auto& paramRef = *param;
    layout.add(std::move(param));
    return paramRef;
}

static juce::AudioParameterFloatAttributes generateGainAttrs(){
    return juce::AudioParameterFloatAttributes()
    .withStringFromValueFunction([](float x, int len){
        return (std::stringstream() << std::fixed << std::setprecision(2) << x << " dB").str();
    })
    .withValueFromStringFunction([](const juce::String& str){
        return str.getFloatValue();
    });
}

static juce::NormalisableRange<float> generateNormRangeADSR(){
    return {0.0f, 4.0f, 0.0, 0.33f};
}

static juce::AudioParameterFloatAttributes generateTimeAttrs(){
    return juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction([](float x, int len){
                if(x < 1.0f){
                    return (std::stringstream() << std::fixed << std::setprecision(0) << (x * 1000.0f) << " ms").str();
                } else {
                    return (std::stringstream() << std::fixed << std::setprecision(2) << x << " s").str();
                }

            })
            .withValueFromStringFunction([](const juce::String& str){
                return str.getFloatValue();
            });
}


ParameterReferences::MainGroup::MainGroup(
        paramGroup &group)
        : outGain(addToGroup(group, std::make_unique<floatParam>(IDs::out_gain,
                                                                 "Gain",
                                                                 juce::NormalisableRange<float>(-12.0f, 12.0f),
                                                                 0.0f,
                                                                 generateGainAttrs())))
{}

ParameterReferences::GeneratorGroup::GeneratorGroup(
        paramGroup &group)
        : wave_type(addToGroup(group, std::make_unique<choiceParam>(IDs::wave_type,
                                                                    "Wave Type",
                                                                    juce::StringArray("Sin", "Sawtooth", "Triangle", "Square"),
                                                                    0))),
          shaper_type(addToGroup(group, std::make_unique<choiceParam>(IDs::shaper_type,
                                                                      "Shaper Type",
                                                                      juce::StringArray("None", "Power"),
                                                                      0))),
          powerStrength(addToGroup(group, std::make_unique<floatParam>(IDs::power_strength,
                                                                       "Power",
                                                                       1.0f,
                                                                       10.f,
                                                                       2.0f)))
{}

ParameterReferences::ADSRGroup::ADSRGroup(
        paramGroup &group)
        : attack(addToGroup(group, std::make_unique<floatParam>(IDs::attack,
                                                                "Attack",
                                                                generateNormRangeADSR(),
                                                                0.01f,
                                                                generateTimeAttrs()))),
          decay(addToGroup(group, std::make_unique<floatParam>(IDs::decay,
                                                               "Decay",
                                                               generateNormRangeADSR(),
                                                               0.3f,
                                                               generateTimeAttrs()))),
          sustain(addToGroup(group, std::make_unique<floatParam>(IDs::sustain,
                                                                 "Sustain",
                                                                 0.0f,
                                                                 1.0f,
                                                                 0.8f))),
          release(addToGroup(group, std::make_unique<floatParam>(IDs::release,
                                                                 "Release",
                                                                 generateNormRangeADSR(),
                                                                 0.6f,
                                                                 generateTimeAttrs())))
{}

ParameterReferences::ParameterReferences(
        paramLayout &layout)
        : mainGroup(addToLayout(layout, std::make_unique<paramGroup>(IDs::main_group, "Main_Group", "|"))),
          generatorGroup(addToLayout(layout, std::make_unique<paramGroup>(IDs::generator_group, "Generator" ,"|"))),
          adsrGroup(addToLayout(layout, std::make_unique<paramGroup>(IDs::adsr_group, "ADSR", "|")))
{}
