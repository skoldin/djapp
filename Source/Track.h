/*
  ==============================================================================

    Track.h
    Created: 25 Aug 2021 8:26:55am
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <string>
#include <JuceHeader.h>

#pragma once

class Track {
    public:
        Track(juce::File file);
        std::string getTitle();
//        std::string getLength();
    private:
        juce::URL url;
        std::string title;
//        int length;
//        juce::AudioFormatManager &formatManager;
//        juce::AudioFormatReader* reader;
//        juce::AudioTransportSource transportSource;
};
    
