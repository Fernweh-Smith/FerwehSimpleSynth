//
// Created by Dylan Smith on 15/10/2023.
//

#include "ParameterListener.h"
#include <iostream>

#include <utility>

ParameterListener::ParameterListener(juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& id, OnChangeCallback changedCallback) :
    ParameterListener(valueTreeState, std::vector<juce::String>{id}, std::move(changedCallback))
{}

ParameterListener::ParameterListener(juce::AudioProcessorValueTreeState &valueTreeState,
                                     std::vector<juce::String> idsToTrack, OnChangeCallback changedCallback) :
                                        trackedIDs(std::move(idsToTrack)) , apvts(valueTreeState), callback(std::move(changedCallback)){

    for(auto& id : trackedIDs){
        apvts.addParameterListener(id, this);
    }

}


ParameterListener::~ParameterListener() {

    for(auto& id : trackedIDs){
        apvts.removeParameterListener(id, this);
    }

}


void ParameterListener::parameterChanged(const juce::String &parameterID, float newValue) {
    callback(parameterID.toStdString(), newValue);
}





