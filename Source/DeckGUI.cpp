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
DeckGUI::DeckGUI(DJAudioPlayer* _player, juce::AudioFormatManager &formatManagerToUse, juce::AudioThumbnailCache &cacheToUse) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playStopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(waveformDisplay);
    
    playStopButton.addListener(this);

    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    volSlider.setLookAndFeel (&slidersLookAndFeel);
    
    speedSlider.addListener(this);
    speedSlider.setValue(1.0);
    speedSlider.setLookAndFeel (&slidersLookAndFeel);
    
    addAndMakeVisible (volLabel);
    volLabel.setText ("Volume", juce::dontSendNotification);
    volLabel.attachToComponent (&volSlider, false);
    volLabel.setJustificationType(juce::Justification::centredTop);
    
    addAndMakeVisible (speedLabel);
    speedLabel.setText ("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent (&speedSlider, false);
    speedLabel.setJustificationType(juce::Justification::centredTop);

    positionSlider.addListener(this);
    positionSlider.setRange(0.0, 1.0);
    
    addAndMakeVisible (positionLabel);
    positionLabel.setText ("Position", juce::dontSendNotification);
    positionLabel.attachToComponent (&positionSlider, false);
    positionLabel.setJustificationType(juce::Justification::centredTop);

    startTimer(100);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    double rowHeight = getHeight() / 8;

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    
    g.drawText (fileName, 120, 0, getWidth() - 100, rowHeight, juce::Justification::left);   // draw some placeholder text
    
    playStopButton.setEnabled(!fileName.isEmpty());
}

void DeckGUI::resized()
{
    double rowHeight = getHeight() / 8;
    playStopButton.setBounds(0, 0, 100, rowHeight);
    volSlider.setBounds(0, rowHeight * 2, getWidth() / 2, rowHeight * 2);
    speedSlider.setBounds(getWidth() / 2, rowHeight * 2, getWidth() / 2, rowHeight * 2);
    positionSlider.setBounds(0, rowHeight * 5, getWidth(), rowHeight);
    waveformDisplay.setBounds(0, rowHeight * 6, getWidth(), rowHeight * 2);
}

void DeckGUI::buttonClicked(juce::Button *button)
{
    if (button == &playStopButton)
    {
        if (!player->isPlaying())
        {
            std::cout << "Play button was clicked" << std::endl;
            player->start();
            button->setButtonText("STOP");
        } else
        {
            std::cout << "Stop button was clicked" << std::endl;
            player->stop();
            button->setButtonText("PLAY");
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

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::loadFile(juce::File file)
{
    player->loadURL(juce::URL{file});
    waveformDisplay.loadURL(juce::URL{file});
    
    fileName = file.getFileName();
    repaint();
}
