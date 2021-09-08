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
        /** load track using an absolute path */
        Track(std::string path);
        /** load track using a file */
        Track(juce::File file);
        /** get track title */
        std::string getTitle();
        /** get track file */
        juce::File getFile();
    
        /** add the possibility to compare if two tracks are the   same */
        const friend bool operator== (const Track& t1, const Track& t2);
        const friend bool operator!= (const Track& t1, const Track& t2);
    private:
        juce::File file;
        std::string title;
        std::string length;
};
    
