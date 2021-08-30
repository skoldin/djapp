/*
  ==============================================================================

    DnDLoader.cpp
    Created: 30 Aug 2021 7:16:30pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include "DnDLoader.h"

bool DnDLoader::isInterestedInFileDrag(const juce::StringArray &files) {
    std::cout  <<  "DnDLoader::isInterestedInFileDrag" << std::endl;
    return true;
    
}
void DnDLoader::filesDropped(const juce::StringArray &files, int x, int y) {
    std::cout  <<  "DnDLoader::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        loadFile(juce::File{files[0]});
    }
}
