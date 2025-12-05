#include "PluginEditor.h"
#include "PluginProcessor.h"

namespace
{
constexpr int sliderWidth = 120;
constexpr int sliderHeight = 260;
constexpr int padding = 24;
} // namespace

BassCheeserAudioProcessorEditor::BassCheeserAudioProcessorEditor(BassCheeserAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      outputGainAttachment(processorRef.getValueTreeState(), "outputGain", outputGainSlider)
{
    setSize(sliderWidth + padding * 2, sliderHeight + padding * 2);

    outputGainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    outputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 24);
    outputGainSlider.setPopupDisplayEnabled(true, false, this);
    outputGainSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
    outputGainSlider.setColour(juce::Slider::thumbColourId, juce::Colours::darkorange);
    addAndMakeVisible(outputGainSlider);
}

void BassCheeserAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    // Simple placeholder visual to hint at future custom look
    g.setColour(juce::Colours::darkorange);
    g.drawRoundedRectangle(getLocalBounds().reduced(8).toFloat(), 12.0f, 4.0f);

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(20.0f, juce::Font::bold));
    g.drawText("Bass Cheeser", padding, 6, getWidth() - padding * 2, 30, juce::Justification::centred);

    g.setFont(juce::Font(12.0f));
    g.setColour(juce::Colours::lightgrey);
    g.drawText("v0.1 gain tweak", padding, getHeight() - 26, getWidth() - padding * 2, 18, juce::Justification::centred);
}

void BassCheeserAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(padding);
    outputGainSlider.setBounds(bounds.removeFromTop(sliderHeight));
}
