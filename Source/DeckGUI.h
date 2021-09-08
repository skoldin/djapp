/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jul 2021 4:31:53pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "SlidersLookAndFeel.h"
//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::Timer
{
public:
    DeckGUI(
            DJAudioPlayer* _player,
            juce::AudioFormatManager &formatManagerToUse,
            juce::AudioThumbnailCache &cacheToUse
    );
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** implement Button::Listener */
    void buttonClicked(juce::Button *) override;
    
    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider *) override;
    
    void timerCallback() override;
    /** load a file into the deck */
    void loadFile(juce::File file);
private:
    SlidersLookAndFeel slidersLookAndFeel;
    
    juce::TextButton playStopButton{"PLAY"};
    
    juce::Slider volSlider{juce::Slider::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::Slider speedSlider{juce::Slider::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::Slider positionSlider{juce::Slider::LinearHorizontal, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    
    juce::Label  volLabel;
    juce::Label  speedLabel;
    juce::Label  positionLabel;

    
    DJAudioPlayer *player;
    
    WaveformDisplay waveformDisplay;
    
    juce::AudioFormatManager formatManager;
    
    juce::String fileName;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
