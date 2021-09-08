/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 30 Jul 2021 10:41:32am
    Author:  Igor Skoldin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
    DJAudioPlayer(juce::AudioFormatManager &_formatManager);
    ~DJAudioPlayer();
    
    /** lifecycle method that invokes before playing **/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /** lifecycle method that invokes when we getting next audio buffer to send it to the sound card  */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    /** lifecycle method that cleans up resources when we are done */
    void releaseResources() override;

    /** loads the file to the transport */
    void loadURL(juce::URL audioURL);
    /** sets volume */
    void setGain(double gain);
    /** sets play  speed */
    void setSpeed(double ratio);
    /** rewinds to the position  passed in */
    void setPosition(double posInSecs);

    /** rewinds to the position from 0 to 1 where 1 is 100% of the track */
    void setPositionRelative(double pos);
    
    /** starts playing */
    void start();
    /** stops playing */
    void stop();
    
    /**  get the rellative position of the playhead */
    double getPositionRelative();
    
    /** get track length formatted for displaying */
    std::string getFormattedTrackLength(juce::URL audioURL);
    
    /** check if the audio is currently playing */
    bool isPlaying();
    
private:
    juce::AudioFormatManager &formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
};
