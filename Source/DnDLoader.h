/*
  ==============================================================================

    DnDLoader.h
    Created: 30 Aug 2021 7:16:30pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <JuceHeader.h>
#pragma once

class DnDLoader : public juce::FileDragAndDropTarget
{
    public:
        bool isInterestedInFileDrag(const juce::StringArray &files) override;
        void filesDropped(const juce::StringArray &files, int x, int y) override;
        virtual void loadFile(juce::File file) = 0;
};

