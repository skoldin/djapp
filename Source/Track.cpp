/*
  ==============================================================================

    Track.cpp
    Created: 25 Aug 2021 8:26:55am
    Author:  Igor Skoldin

  ==============================================================================
*/

#include "Track.h"
#include <JuceHeader.h>

Track::Track(juce::File file) :
    url(juce::URL{file}),
    title(file.getFileName().toStdString())
{
    // auto* reader = formatManager.createReaderFor(url.createInputStream(false));
}

std::string Track::getTitle()
{
    return title;
}

const bool operator== (const Track& t1, const Track& t2)
{
    return t1.title == t2.title;
}

const bool operator!= (const Track& t1, const Track& t2)
{
    return t1.title != t2.title;
}

//std::string Track::getLength() {
//    //auto* reader = formatManager.createReaderFor(url.createInputStream(false));
//    
////    std::cout << reader->sampleRate << std::endl;
//
//    if (reader != nullptr)
//    {
//        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource(reader, true));
////        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
////        readerSource.reset (newSource.release());
//    }
//    
//    return "1";
//};
