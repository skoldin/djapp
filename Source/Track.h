/*
  ==============================================================================

    Track.h
    Created: 25 Aug 2021 8:26:55am
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <string>
#include <JuceHeader.h>
#include "DJAudioPlayer.h"

#pragma once

class Track {
    public:
        Track(std::string path);
        Track(juce::File file);
        std::string getTitle();
        juce::File getFile();
    
        const friend bool operator== (const Track& t1, const Track& t2);
        const friend bool operator!= (const Track& t1, const Track& t2);
    private:
        juce::File file;
        std::string title;
        std::string length;
};
    
