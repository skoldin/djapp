/*
  ==============================================================================

    SlidersLookAndFeel.h
    Created: 6 Sep 2021 3:58:06pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once

class SlidersLookAndFeel : public juce::LookAndFeel_V4
{
    public:
        SlidersLookAndFeel();
        void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                               const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
