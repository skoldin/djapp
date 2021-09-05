/*
  ==============================================================================

    PlaylistStorage.h
    Created: 29 Aug 2021 12:17:04pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <filesystem>
#include <vector>
#include <JuceHeader.h>
#include "Track.h"

#pragma once

class PlaylistStorage
{
    public:
        std::vector<std::string> getTracks();
        void addTrack(juce::File file);
    private:
        std::vector<std::string> tracks;
        const std::string storageFilePath = std::string(std::filesystem::current_path()) + "/playlist.csv";
};
