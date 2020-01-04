/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DawAnalyzerAudioProcessorEditor  : public AudioProcessorEditor, private Timer
{
public:
    DawAnalyzerAudioProcessorEditor (DawAnalyzerAudioProcessor&);
    ~DawAnalyzerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DawAnalyzerAudioProcessor& processor;

    Label bpm, timeSigNumerator, timeSigDenominator, timeInSamples, timeInSeconds, editOriginTime, ppqPosition,
        ppqPositionOfLastBarStart, frameRate, isPlaying, isRecording, ppqLoopStart, ppqLoopEnd, isLooping;
};
