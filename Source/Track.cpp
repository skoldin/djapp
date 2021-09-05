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
    file(file),
    title(file.getFileName().toStdString())
{
}

Track::Track(std::string path)
{
    file = juce::File (path);
    title = file.getFileName().toStdString();
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

juce::File Track::getFile()
{
    return file;
}
