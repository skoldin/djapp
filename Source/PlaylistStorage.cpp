/*
  ==============================================================================

    PlaylistStorage.cpp
    Created: 29 Aug 2021 12:17:04pm
    Author:  Igor Skoldin

  ==============================================================================
*/
#include <sstream>
#include <iostream>
#include <fstream>
#include "PlaylistStorage.h"

void PlaylistStorage::addTrack(juce::File file)
{
    std::cout << storageFilePath << std::endl;
    
    juce::File storageFile (storageFilePath);
    juce::FileOutputStream output (storageFile);
    
    if (!output.openedOk())
    {
        std::cout << "File does not exist" << std::endl;
        return;
    }
    
    output.setNewLineString("\n");

    output.writeText(file.getFullPathName().toStdString() + output.getNewLineString().toStdString(), true, true, output.getNewLineString().toStdString().c_str());
    
    output.flush();
}


std::vector<std::string> PlaylistStorage::getTracks()
{
    std::cout << "PlaylistStorage::getTracks" << std::endl;
    std::vector<std::string> paths;
    
    juce::File storageFile (storageFilePath);
    
    std::cout << "LOAD STORAGE FILE " << storageFilePath << std::endl;
    
    if (!storageFile.existsAsFile())
    {
        std::cout << "PlaylistStorage::getTracks File does not exist" << std::endl;
        return paths;
    }
    
    auto playlistContent = storageFile.loadFileAsString();
    
    std::cout << playlistContent << std::endl;
    
    std::string result;
    std::stringstream ss(playlistContent.toStdString());
    
    while(std::getline(ss, result, '\n'))
    {
        double firstSlashPos = result.find("/");
        
        result = result.substr(firstSlashPos, result.length() - firstSlashPos);
        
        paths.push_back(result);
    }
    
    return paths;
}
