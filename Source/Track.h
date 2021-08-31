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
        juce::File getFile();
//        std::string getLength();
    
        const friend bool operator== (const Track& t1, const Track& t2);
        const friend bool operator!= (const Track& t1, const Track& t2);
    private:
        juce::File file;
        std::string title;
//        int length;
//        juce::AudioFormatManager &formatManager;
//        juce::AudioFormatReader* reader;
//        juce::AudioTransportSource transportSource;
};
    
