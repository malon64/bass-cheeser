#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
constexpr auto outputGainParamId = "outputGain";
} // namespace

BassCheeserAudioProcessor::BassCheeserAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                          .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      state(*this, nullptr, "Parameters",
            {
                std::make_unique<juce::AudioParameterFloat>(
                    outputGainParamId,
                    "Output Gain",
                    juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f),
                    0.0f,
                    juce::AudioParameterFloatAttributes().withStringFromValueFunction(
                        [](float value, int) { return juce::String(value, 1) + " dB"; })),
            })
{
}

void BassCheeserAudioProcessor::prepareToPlay(double, int)
{
}

void BassCheeserAudioProcessor::releaseResources()
{
}

bool BassCheeserAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    const auto& mainInLayout = layouts.getChannelSet(true, 0);
    const auto& mainOutLayout = layouts.getChannelSet(false, 0);

    // Only allow mono or stereo and require symmetry between input and output
    if (mainInLayout != mainOutLayout)
        return false;

    return mainInLayout == juce::AudioChannelSet::mono() || mainInLayout == juce::AudioChannelSet::stereo();
}

void BassCheeserAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    auto* gainParam = state.getRawParameterValue(outputGainParamId);
    const auto gainDb = gainParam != nullptr ? gainParam->load() : 0.0f;
    const auto gain = juce::Decibels::decibelsToGain(gainDb);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
    }
}

void BassCheeserAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = state.copyState().createXml())
    {
        copyXmlToBinary(*xml, destData);
    }
}

void BassCheeserAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
    {
        state.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

juce::AudioProcessorEditor* BassCheeserAudioProcessor::createEditor()
{
    return new BassCheeserAudioProcessorEditor(*this);
}

// Factory function required by JUCE to instantiate the processor
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BassCheeserAudioProcessor();
}
