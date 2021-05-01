//================================================================================================================================
//
// PluginProcessor.cpp
//
//================================================================================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"


//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
PluginProcessor::PluginProcessor()
	:
	#ifndef JucePlugin_PreferredChannelConfigurations
	AudioProcessor (BusesProperties()
	#if ! JucePlugin_IsMidiEffect
		#if ! JucePlugin_IsSynth
			.withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
		#endif
		.withOutput ("Output", juce::AudioChannelSet::stereo(), true)
	#endif
	),
	#endif
	mAPVTS (*this, nullptr, juce::Identifier ("PARAMETERS"), createParameterLayout())
{
	mGain = mAPVTS.getRawParameterValue ("GAIN");
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
PluginProcessor::~PluginProcessor()
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
const juce::String PluginProcessor::getName() const
{
	return JucePlugin_Name;
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
double PluginProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
int PluginProcessor::getNumPrograms()
{
	return 1;
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
int PluginProcessor::getCurrentProgram()
{
	return 0;
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::setCurrentProgram (int index)
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
const juce::String PluginProcessor::getProgramName (int index)
{
	return {};
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::releaseResources()
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused (layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;
	
	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif
	
	return true;
#endif
}
#endif

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	buffer.applyGain (*mGain);
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
bool PluginProcessor::hasEditor() const
{
	return true;
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
	return new PluginEditor (*this, mAPVTS);
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	auto state = mAPVTS.copyState();
	std::unique_ptr<juce::XmlElement> xml (state.createXml());
	copyXmlToBinary (*xml, destData);
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
	
	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName (mAPVTS.state.getType()))
			mAPVTS.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new PluginProcessor();
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout layout;
	
	layout.add (std::make_unique<juce::AudioParameterFloat> ("GAIN", "Gain", 0.0f, 2.0f, 1.0f));
	
	return layout;
}

//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––– eof
