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
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);

    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(0.5);
    
    speedSlider.addListener(this);
    speedSlider.setValue(1.0);

    positionSlider.addListener(this);
    positionSlider.setRange(0.0, 1.0);

    startTimer(100);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
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
    double rowHeight = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowHeight);
    stopButton.setBounds(0, rowHeight, getWidth(), rowHeight);
    volSlider.setBounds(0, rowHeight * 3, getWidth(), rowHeight);
    speedSlider.setBounds(0, rowHeight * 4, getWidth(), rowHeight);
    positionSlider.setBounds(0, rowHeight * 5, getWidth(), rowHeight);
    waveformDisplay.setBounds(0, rowHeight * 6, getWidth(), rowHeight * 2);
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
}
