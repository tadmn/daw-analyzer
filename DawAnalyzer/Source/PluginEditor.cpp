/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{

const auto labelHeight = 23;
const auto numLabelRows = 2;

}

//==============================================================================
DawAnalyzerAudioProcessorEditor::DawAnalyzerAudioProcessorEditor (DawAnalyzerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(bpm);
    addAndMakeVisible(timeSigNumerator);
    addAndMakeVisible(timeSigDenominator);
    addAndMakeVisible(timeInSamples);
    addAndMakeVisible(timeInSeconds);
    addAndMakeVisible(editOriginTime);
    addAndMakeVisible(ppqPosition);
    addAndMakeVisible(ppqPositionOfLastBarStart);
    addAndMakeVisible(frameRate);
    addAndMakeVisible(isPlaying);
    addAndMakeVisible(isRecording);
    addAndMakeVisible(ppqLoopStart);
    addAndMakeVisible(ppqLoopEnd);
    addAndMakeVisible(isLooping);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, numLabelRows * labelHeight);

    startTimer(30);
}

DawAnalyzerAudioProcessorEditor::~DawAnalyzerAudioProcessorEditor()
{
}

//==============================================================================
void DawAnalyzerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DawAnalyzerAudioProcessorEditor::resized()
{
    const auto numPerRow = 7;
    const auto w = getWidth() / numPerRow;

    auto b = getLocalBounds();
    auto r1 = b.removeFromTop(labelHeight);
    auto r2 = b.removeFromTop(labelHeight);

    int i = 0;
    for (auto c : getChildren())
    {
        auto bounds = i < numPerRow ? r1.removeFromLeft(w) : r2.removeFromLeft(w);
        c->setBounds(bounds);
        ++i;
    }
}

void DawAnalyzerAudioProcessorEditor::timerCallback()
{
    CPI cpi;
    if (!processor.cpiFifo.pop(cpi))
        return;

    auto update = [](Label& l, auto text, auto value)
    {
        l.setText(String(text) + ": " + String(value), dontSendNotification);
    };

//    farbot::RealtimeMutatable<AudioPlayHead::CurrentPositionInfo>::ScopedAccess<false> cpi(processor.currentPositionInfo);

#define UPDATE(name) update(name, #name, cpi.name)
    UPDATE(bpm);
    UPDATE(timeSigNumerator);
    UPDATE(timeSigDenominator);
    UPDATE(timeInSamples);
    UPDATE(timeInSeconds);
    UPDATE(editOriginTime);
    UPDATE(ppqPosition);
    UPDATE(ppqPositionOfLastBarStart);
    UPDATE(frameRate);
    UPDATE(ppqLoopStart);
    UPDATE(ppqLoopEnd);
#undef UPDATE

#define UPDATE_BOOL(name) name.setText(#name + String(": ") + String(cpi.name ? "y" : "n"), dontSendNotification)
    UPDATE_BOOL(isPlaying);
    UPDATE_BOOL(isRecording);
    UPDATE_BOOL(isLooping);
#undef UPDATE_BOOL
}
