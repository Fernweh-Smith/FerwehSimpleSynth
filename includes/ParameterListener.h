//
// Created by Dylan Smith on 15/10/2023.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

using OnChangeCallback = std::function<void(const juce::String &parameterID, float newValue)>;

class ParameterListener : protected juce::AudioProcessorValueTreeState::Listener{

public:
    ParameterListener(juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& idToTrack, OnChangeCallback changedCallback);
    ParameterListener(juce::AudioProcessorValueTreeState& valueTreeState, std::vector<juce::String> idsToTrack, OnChangeCallback changedCallback);

    ~ParameterListener() override;
    ParameterListener(ParameterListener& other) = delete;
    ParameterListener& operator= (const ParameterListener& other) = delete;
    ParameterListener(ParameterListener&& other) = delete;
    ParameterListener& operator= (const ParameterListener&& other) = delete;


    const std::vector<juce::String> trackedIDs;

private:
    juce::AudioProcessorValueTreeState& apvts;
    const OnChangeCallback callback;
    void parameterChanged(const juce::String &parameterID, float newValue) override;


};
