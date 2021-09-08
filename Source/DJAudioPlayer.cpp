/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 30 Jul 2021 10:41:32am
    Author:  Igor Skoldin

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager &_formatManager) : formatManager(_formatManager) {};
DJAudioPlayer::~DJAudioPlayer() {};

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
};
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
};
void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
};

void DJAudioPlayer::loadURL(juce::URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
};
void DJAudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
        return;
    }
    
    transportSource.setGain(gain);
};
void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0 || ratio > 10.0) {
        std::cout << "DJAudioPlayer::setSpeed speed should be between 0 and 10" << std::endl;
        return;
    }
    
    resampleSource.setResamplingRatio(ratio);
};
void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
};

void DJAudioPlayer::start() {
    transportSource.start();
};
void DJAudioPlayer::stop() {
    transportSource.stop();
};

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 11) {
        std::cout << "DJAudioPlayer::setPositionRelative speed should be between 0 and 1" << std::endl;
        return;
    }
    
    double posInSecs  = transportSource.getLengthInSeconds()  * pos;
    setPosition(posInSecs);
}

double DJAudioPlayer::getPositionRelative()
{
    double lengthInSeconds = transportSource.getLengthInSeconds();
    
    if (lengthInSeconds == 0)
    {
        return 0;
    }
    
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}


std::string DJAudioPlayer::getFormattedTrackLength(juce::URL audioURL)
{
    loadURL(audioURL);
    
    const int secondsInMinute = 60;
    int lengthInSeconds = int(transportSource.getLengthInSeconds());
    
    int minutes = lengthInSeconds / secondsInMinute;
    int seconds = lengthInSeconds % secondsInMinute;
    
    std::string minutesStr = std::to_string(minutes);
    std::string secondsStr = std::to_string(seconds);
    
    if (minutes < 10)
    {
        minutesStr = "0" + minutesStr;
    }
    
    if (seconds < 10)
    {
        secondsStr = "0" + secondsStr;
    }
    
    std::cout << minutes << " Minutes " << seconds << " Seconds" << std::endl;
    
    return minutesStr + ":" + secondsStr;
}

bool DJAudioPlayer::isPlaying()
{
    return transportSource.isPlaying();
}
