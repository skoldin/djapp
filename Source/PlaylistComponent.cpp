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
PlaylistComponent::PlaylistComponent(juce::AudioFormatManager &formatManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
//    trackTitles.push_back("Track 1");
//    trackTitles.push_back("Track 2");
    
    addAndMakeVisible(tableComponent);
    
    tableComponent.getHeader().addColumn("Track title", titleColumnId, 400);
    tableComponent.getHeader().addColumn("Length", lengthColumnId, 200);
    tableComponent.getHeader().addColumn("", buttonColumnId, 200);
    
    tableComponent.setModel(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

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
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    std::cout << "PlaylistComponent::getNumRows num of tracks " << tracks.size() << std::endl;
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
    std::cout << "PlaylistComponent::paintCell column " << columnId << std::endl;
    
    if (columnId == titleColumnId)
    {
        g.drawText(tracks[rowNumber].getTitle(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    } else if (columnId == lengthColumnId)
    {
        g.drawText(tracks[rowNumber].getLength(), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
};

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component * existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"play"};
            
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout  <<  "PlaylistComponent::buttonClicked " << tracks[id].getTitle() << std::endl;
}

void PlaylistComponent::addTrack(juce::File file)
{
//    std::cout << "Added track " << track.getTitle() << std::endl;
    //  TODO: investigate why it is needed to register formats here, maybe the original pointer is not passed through and this is a new instance
    formatManager.registerBasicFormats();
    tracks.push_back(Track{file, formatManager});
    tableComponent.updateContent();
}

//bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray &files) {
//    std::cout  <<  "PlaylistComponent::isInterestedInFileDrag" << std::endl;
//    return true;
//    
//}
//void PlaylistComponent::filesDropped(const juce::StringArray &files, int x, int y) {
//    std::cout  <<  "PlaylistComponent::filesDropped" << std::endl;
//    if (files.size() == 1)
//    {
//        // TODO: load into the library
//    }
//}
