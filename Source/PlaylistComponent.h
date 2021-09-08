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
#include "PlaylistStorage.h"
#include "DnDLoader.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public DnDLoader
{
public:
    PlaylistComponent(DeckGUI &deck1, DeckGUI &deck2, DJAudioPlayer* player);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void paintRowBackground (juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    
    void paintCell (juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    int getNumRows() override;
    
    juce::Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component * existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;
    
    /** adds track to the music library */
    void addTrack(juce::File file);
    
    void loadFile(juce::File file) override;

private:
    bool hasTrack(Track track);
    void searchTracks(std::string term);
    
    juce::Label searchLabel{"search_field", "Search: "};
    juce::TextEditor searchField{"search_field"};
    juce::TextButton loadButton{"LOAD"};
    juce::TableListBox tableComponent;
    
    DeckGUI &deck1;
    DeckGUI &deck2;
    
    // use audio player to get song length
    DJAudioPlayer* player;
    
    std::vector<Track> tracks;
    std::vector<std::string> allTracksPaths;
    std::vector<Track> allTracks;
    
    PlaylistStorage playlistStorage;
    
    std::map<int, juce::ComboBox*> deckChoosers;
    
    std::string getLength();
    
    enum ColumnIds
    {
        titleColumnId = 1,
        lengthColumnId,
        deckSelectColumnId,
        buttonColumnId
    };
    
    const int ROWS_NUMBER = 8;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
