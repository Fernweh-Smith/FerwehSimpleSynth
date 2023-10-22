//
// Created by Dylan Smith on 8/10/2023.
//

#pragma once

#include "juce_audio_basics/juce_audio_basics.h"
#include "PluginParameters.h"
#include "WaveFunctions.h"


class SimpleSynthesiser : protected juce::Synthesiser {
public:
    explicit SimpleSynthesiser(ParameterReferences& paramRefs);
    ~SimpleSynthesiser() override;
    void prepareToPlay(double sampleRate);
    void processNextBlock (juce::AudioBuffer< float >& outputAudio, const juce::MidiBuffer& inputMidi, int startSample, int numSamples);




protected:
    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;


private:
    ParameterReferences& parameters;
    const std::function<double(double)> toneFromAngle = [this](double angle){
        const auto waveType = parameters.generatorGroup.wave_type.getIndex();
        const auto shaperType = parameters.generatorGroup.shaper_type.getIndex();
        const auto powerStrength = static_cast<double>(parameters.generatorGroup.powerStrength.get());

        double outValue = 0.0;

        switch (waveType) {
            case(0):
                outValue = WaveFunctions::sinFromAngle(angle);
                break;
            case(1):
                outValue = WaveFunctions::sawtoothFromAngle(angle);
                break;
            case(2):
                outValue = WaveFunctions::triangleFromAngle(angle);
                break;
            case(3):
                outValue = WaveFunctions::squareFromAngle(angle);
                break;
            default:
                outValue = WaveFunctions::sinFromAngle(angle);
                break;
        }

        switch (shaperType){
            case(0):
                return outValue;
            case(1):
                return WaveFunctions::shapeByPower(outValue, powerStrength);
            case(2):
                return WaveFunctions::shapeByFractionalPower(outValue, powerStrength);
            default:
                return outValue;
        }
    };

    const std::function<juce::ADSR::Parameters()> adsrParamsFromPluginParams = [this]{
        const float attack = parameters.adsrGroup.attack.get();
        const float decay = parameters.adsrGroup.decay.get();
        const float sustain = parameters.adsrGroup.sustain.get();
        const float release = parameters.adsrGroup.release.get();
        return juce::ADSR::Parameters(attack, decay, sustain, release);
    };

};
