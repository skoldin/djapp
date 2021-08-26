/*
  ==============================================================================

    Track.cpp
    Created: 25 Aug 2021 8:26:55am
    Author:  Igor Skoldin

  ==============================================================================
*/

#include "Track.h"
#include <JuceHeader.h>

Track::Track(juce::File file, juce::AudioFormatManager &formatManager) :
    url(juce::URL{file}),
    title(file.getFileName().toStdString()),
    reader(formatManager.createReaderFor(file))
{
    // auto* reader = formatManager.createReaderFor(url.createInputStream(false));
}

std::string Track::getTitle()
{
    return title;
}

std::string Track::getLength() {
    //auto* reader = formatManager.createReaderFor(url.createInputStream(false));
    
//    std::cout << reader->sampleRate << std::endl;

    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
//        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//        readerSource.reset (newSource.release());
    }
    
    return "1";
};
