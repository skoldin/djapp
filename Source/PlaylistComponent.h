/*
  ==============================================================================

    PlaylistComponent.h
    Created: 21 Aug 2021 2:16:27pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    PlaylistComponent(juce::AudioFormatManager &formatManagerToUse);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void paintRowBackground (juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    
    void paintCell (juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    int getNumRows() override;
    
    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component * existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
        
    void addTrack(juce::File file);
    
//    bool isInterestedInFileDrag(const juce::StringArray &files) override;
//    void filesDropped(const juce::StringArray &files, int x, int y) override;

private:
    
    juce::TableListBox tableComponent;
    
    std::vector<Track> tracks;
    
    juce::AudioFormatManager formatManager;
    
    const int titleColumnId = 1;
    const int lengthColumnId = 2;
    const int buttonColumnId = 3;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
