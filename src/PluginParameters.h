//
// Created by Dylan Smith on 17/10/2023.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

namespace IDs {
#define DEFINE_ID(id) static constexpr const char* id = #id;

    DEFINE_ID(simple_synth_apvts)

    DEFINE_ID(main_group)
    DEFINE_ID(out_gain)

    DEFINE_ID(generator_group)
    DEFINE_ID(wave_type)
    DEFINE_ID(sin_wave)
    DEFINE_ID(sawtooth_wave)
    DEFINE_ID(triangle_wave)
    DEFINE_ID(square_wave)
    DEFINE_ID(shaper_type)
    DEFINE_ID(power_strength)

    DEFINE_ID(adsr_group)
    DEFINE_ID(attack)
    DEFINE_ID(decay)
    DEFINE_ID(sustain)
    DEFINE_ID(release)
}

struct ParameterReferences{
    using paramLayout = juce::AudioProcessorValueTreeState::ParameterLayout;
    using paramGroup = juce::AudioProcessorParameterGroup;

    using floatParam = juce::AudioParameterFloat;
    using choiceParam = juce::AudioParameterChoice;
    using boolParam = juce::AudioParameterBool;

    struct MainGroup{
        explicit MainGroup(paramGroup& group);

        floatParam& outGain;
    };
    struct GeneratorGroup{
        explicit GeneratorGroup(paramGroup& group);

        choiceParam& wave_type;
        choiceParam& shaper_type;
        floatParam& powerStrength;
    };
    struct ADSRGroup{
        explicit ADSRGroup(paramGroup& group);

        floatParam& attack;
        floatParam& decay;
        floatParam& sustain;
        floatParam& release;

    };

    explicit ParameterReferences(paramLayout& layout);

    MainGroup mainGroup;
    GeneratorGroup generatorGroup;
    ADSRGroup adsrGroup;
};