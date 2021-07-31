/*
  ==============================================================================

    DeckGUI.cpp
    Created: 31 Jul 2021 4:31:53pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    
    speedSlider.addListener(this);
    speedSlider.setValue(1.0);

    positionSlider.addListener(this);
    positionSlider.setRange(0.0, 1.0);

}

DeckGUI::~DeckGUI()
{
}

void DeckGUI::paint (juce::Graphics& g)
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
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowHeight = getHeight() / 6;
    playButton.setBounds(0, 0, getWidth(), rowHeight);
    stopButton.setBounds(0, rowHeight, getWidth(), rowHeight);
    loadButton.setBounds(0, rowHeight * 2, getWidth(), rowHeight);
    volSlider.setBounds(0, rowHeight * 3, getWidth(), rowHeight);
    speedSlider.setBounds(0, rowHeight * 4, getWidth(), rowHeight);
    positionSlider.setBounds(0, rowHeight * 5, getWidth(), rowHeight);
}

void DeckGUI::buttonClicked(juce::Button *button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked" << std::endl;
        player->start();
    } else if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
        player->stop();
    } else if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};

        if (chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{chooser.getResult()});
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        std::cout << "Vol slider value changed " << slider->getValue() << std::endl;
        player->setGain(slider->getValue());
    } else if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    } else if (slider == &positionSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files) {
    std::cout  <<  "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
    
}
void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y) {
    std::cout  <<  "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{juce::File{files[0]}});
    }
}
