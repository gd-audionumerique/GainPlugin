//================================================================================================================================
//
// PluginEditor.cpp
//
//================================================================================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"


//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
PluginEditor::PluginEditor (PluginProcessor& p, juce::AudioProcessorValueTreeState& apvts)
	:
	AudioProcessorEditor (&p),
	mProcessor (p)
{
	mGainLabel.setFont (15.0f);
	mGainLabel.setText ("Gain", juce::dontSendNotification);
	mGainLabel.setJustificationType (juce::Justification::centred);
	addAndMakeVisible (mGainLabel);
	
	mGainSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	mGainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 80, 20);
//	mGainSlider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
	addAndMakeVisible (mGainSlider);
	
	mGainAttachment.reset (new SliderAttachment (apvts, "GAIN", mGainSlider));
	
	setSize (400, 150);
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
PluginEditor::~PluginEditor()
{
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginEditor::paint (juce::Graphics& g)
{
	g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	g.setColour (juce::Colours::white);
	g.setFont (15.0f);
	g.drawFittedText ("Hello DAW :) !", getLocalBounds(), juce::Justification::centred, 1);
}

//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
void PluginEditor::resized()
{
	mGainLabel.setBounds (0, 0, 100, 20);
	mGainSlider.setBounds (0, 20, 100, 100);
}

//–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––– eof
