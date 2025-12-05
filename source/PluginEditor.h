#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class BassCheeserAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit BassCheeserAudioProcessorEditor(BassCheeserAudioProcessor&);
    ~BassCheeserAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    BassCheeserAudioProcessor& processorRef;

    juce::Slider outputGainSlider;
    juce::AudioProcessorValueTreeState::SliderAttachment outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BassCheeserAudioProcessorEditor)
};
