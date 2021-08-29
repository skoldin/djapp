/*
  ==============================================================================

    PlaylistStorage.cpp
    Created: 29 Aug 2021 12:17:04pm
    Author:  Igor Skoldin

  ==============================================================================
*/
#include <iostream>
#include <fstream>
#include "PlaylistStorage.h"

void PlaylistStorage::addTrack(juce::File file)
{
    std::cout << storageFilePath << std::endl;
    
    juce::File storageFile (storageFilePath);
    
//    if (!storageFile.existsAsFile())
//    {
//        std::cout << "PlaylistStorage::addTrack File does not exist" << std::endl;
//        return;
//    }
    
    juce::FileOutputStream output (storageFile);
    
    if (!output.openedOk())
    {
        std::cout << "File does not exist" << std::endl;
        return;
    }
    
    output.setNewLineString("\n");

    output.writeText(file.getFileName().toStdString() + ",", true, true, output.getNewLineString().toStdString().c_str());
    
    output.writeText(file.getFullPathName().toStdString() + output.getNewLineString().toStdString(), true, false, nullptr);
    
    output.flush();
}

std::vector<Track> PlaylistStorage::getTracks()
{
    std::cout << "PlaylistStorage::getTracks" << std::endl;
    std::vector<Track> tracks;
    
    juce::File storageFile (storageFilePath);
    
    if (!storageFile.existsAsFile())
    {
        std::cout << "PlaylistStorage::getTracks File does not exist" << std::endl;
        return tracks;
    }
    
    auto playlistContent = storageFile.loadFileAsString();
    
    std::cout << playlistContent << std::endl;
    
    // TODO: read track by track, load and add to tracks
    
    return tracks;
}
