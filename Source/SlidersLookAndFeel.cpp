/*
  ==============================================================================

    SlidersLookAndFeel.cpp
    Created: 6 Sep 2021 3:58:06pm
    Author:  Igor Skoldin

  ==============================================================================
*/

#include "SlidersLookAndFeel.h"

SlidersLookAndFeel::SlidersLookAndFeel() {};

void SlidersLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                       const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    float radius = juce::jmin (width / 2, height / 2) - 4.0f;
    float centerX = x + width  * 0.5f;
    float centerY = y + height * 0.5f;
    float rx = centerX - radius;
    float ry = centerY - radius;
    float rw = radius * 2.0f;
    float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill
    g.setColour (juce::Colours::whitesmoke);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colours::wheat);
    g.drawEllipse (rx, ry, rw, rw, 5.0f);

    juce::Path path;
    float pointerLength = radius * 0.5f;
    float pointerThickness = 3.0f;
    path.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    path.applyTransform (juce::AffineTransform::rotation (angle).translated (centerX, centerY));

    // pointer
    g.setColour (juce::Colours::dimgrey);
    g.fillPath (path);
}
