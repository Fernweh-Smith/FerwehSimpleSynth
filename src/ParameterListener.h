//
// Created by Dylan Smith on 15/10/2023.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>


class ParameterListener : protected juce::AudioProcessorValueTreeState::Listener{
public:
    explicit ParameterListener(juce::AudioProcessorValueTreeState& valueTreeState, std::string id);
    ~ParameterListener() override;
    const std::string idToTrack;

private:
    juce::AudioProcessorValueTreeState& apvts;
    void parameterChanged(const juce::String &parameterID, float newValue) override;


};
