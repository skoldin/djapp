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
        std::vector<Track> getTracks();
        void addTrack(juce::File file);
    private:
        std::vector<Track> tracks;
        const std::string storageFilePath = std::string(std::filesystem::current_path()) + "/playlist.csv";
};
