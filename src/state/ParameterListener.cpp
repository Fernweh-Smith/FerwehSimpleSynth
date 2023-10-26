//
// Created by Dylan Smith on 15/10/2023.
//

#include "ParameterListener.h"
#include <iostream>

#include <utility>

ParameterListener::ParameterListener(juce::AudioProcessorValueTreeState& valueTreeState, std::string id) : idToTrack(std::move(id)) , apvts(valueTreeState) {
    apvts.addParameterListener(idToTrack, this);
}

ParameterListener::~ParameterListener() {
    apvts.removeParameterListener(idToTrack, this);
}


void ParameterListener::parameterChanged(const juce::String &parameterID, float newValue) {
    std::cout << "Tracking ID = " + idToTrack << "\n";
    std::cout << "Incoming ID = " + parameterID << "\n";
    std::cout << "New Value = " << newValue << "\n";
}




