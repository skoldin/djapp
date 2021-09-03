/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 21 Aug 2021 2:16:27pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "Track.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI &deck1, DeckGUI &deck2) : deck1(deck1), deck2(deck2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(searchField);
    addAndMakeVisible(tableComponent);
    
    tableComponent.getHeader().addColumn("Track title", ColumnIds::titleColumnId, 400);
    tableComponent.getHeader().addColumn("Length", ColumnIds::lengthColumnId, 200);
    tableComponent.getHeader().addColumn("Deck", ColumnIds::deckSelectColumnId, 100);
    tableComponent.getHeader().addColumn("", ColumnIds::buttonColumnId, 100);
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(loadButton);
    
    allTracks = playlistStorage.getTracks();
    tracks = allTracks;
    
    loadButton.addListener(this);
    
    searchField.onTextChange = [this] { this->searchTracks(searchField.getText().toStdString()); tableComponent.updateContent(); };
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    double rowHeight = getHeight() / ROWS_NUMBER;

    searchField.setBounds(0, 0, getWidth(), rowHeight);
    tableComponent.setBounds(0, rowHeight, getWidth(), getHeight() - rowHeight * 2);
    loadButton.setBounds(0, getHeight() - rowHeight, getWidth(), rowHeight);
}

int PlaylistComponent::getNumRows()
{
    return tracks.size();
}

void PlaylistComponent::paintRowBackground (juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::orange);
    } else {
        g.fillAll(juce::Colours::darkgrey);
    }
    
};

void PlaylistComponent::paintCell (juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{

    if (columnId == ColumnIds::titleColumnId)
    {
        g.drawText(tracks[rowNumber].getTitle(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    } else if (columnId == ColumnIds::lengthColumnId)
    {
//        g.drawText(tracks[rowNumber].getLength(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
};

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component * existingComponentToUpdate)
{
    juce::String id{std::to_string(rowNumber)};
    
    if (columnId == ColumnIds::buttonColumnId)
    {
        
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"load"};
            
            btn->setComponentID(id);
            btn->addListener(this);
            
            existingComponentToUpdate = btn;
        };
        
        // if no deck chosen in this row, disable the button
        int selectedDeck = deckChoosers[rowNumber]->getSelectedId();
        
        existingComponentToUpdate->setEnabled(selectedDeck != 0);
    } else if (columnId == ColumnIds::deckSelectColumnId)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::ComboBox* deckChoice = new juce::ComboBox;
            
            deckChoice->setComponentID(id);
            
            deckChoice->addItem ("1", 1);
            deckChoice->addItem ("2", 2);
            deckChoice->addItem ("1 & 2", 3);
            
            deckChoice->onChange = [this] { tableComponent.updateContent(); };
            
            deckChoosers[rowNumber] = deckChoice;
            
            existingComponentToUpdate = deckChoice;
        }
    }
    
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
    
        if (chooser.browseForFileToOpen())
        {
            addTrack(chooser.getResult());
        }
    } else
    {
        std::string id = button->getComponentID().toStdString();
        // get deck id from the corresponding chooser
        int chosenDeck = deckChoosers[std::stoi(id)]->getSelectedId();
        juce::File fileToLoad = tracks[std::stoi(id)].getFile();
        
        if (chosenDeck == 1 || chosenDeck == 3)
        {
            deck1.loadFile(tracks[std::stoi(id)].getFile());
        }
        
        if (chosenDeck == 2 || chosenDeck == 3)
        {
            deck2.loadFile(tracks[std::stoi(id)].getFile());
        }
    }
}

void PlaylistComponent::addTrack(juce::File file)
{
    Track track (file);
    
    if (hasTrack(track))
    {
        std::cout << "PlaylistComponent::addTrack Track already exists in the playlist" << std::endl;
        return;
    }
    
    tracks.push_back(track);
    playlistStorage.addTrack(file);
    tableComponent.updateContent();
}

bool PlaylistComponent::hasTrack(Track trackToCheck)
{
    for (auto& track : tracks)
    {
        if (trackToCheck == track) {
            return true;
        }
    }
    
    return false;
}

void PlaylistComponent::loadFile(juce::File file)
{
    addTrack(file);
}

void PlaylistComponent::searchTracks(std::string term)
{
    if (term.empty())
    {
        tracks = allTracks;
        return;
    }
    
    std::vector<Track> filteredTracks;
    
    for (Track& track : allTracks)
    {
        if (track.getTitle().find(term) != std::string::npos)
        {
            filteredTracks.push_back(track);
        }
    }
    
    tracks = filteredTracks;
}
