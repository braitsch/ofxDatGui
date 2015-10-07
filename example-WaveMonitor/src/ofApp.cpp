#include "ofApp.h"

/*
    Simple example to demonstrate the WaveMonitor Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    int x = 150;
    int y = 180;
    int margin = 40;
    angle1 = 0.0f;
    ofSetWindowPosition(0, 0);
    
    g1 = new ofxDatGui(x, y);
// set the range that we care about //
    g1m1 = g1->addWaveMonitor("SINE WAVE", -1, 1);
    g1s1 = g1->addSlider("FREQUENCY", -1, 1);
    g1s1->setEnabled(false);
// amplitude multiplier must be between 0 & 10 //
    g1s2 = g1->addSlider("AMPLITUDE", 0, 10);
    g1m1->setAmplitude(g1s2->getValue());
    g1->onSliderEvent(this, &ofApp::onGui1SliderEvent);
    
    g2 = new ofxDatGui(x+g1->getWidth()+margin, y);
    g2m1 = g2->addWaveMonitor("SQUARE WAVE", -1, 1);
    g2s1 = g2->addSlider("FREQUENCY", -1, 1);
    g2s2 = g2->addSlider("AMPLITUDE", 0, 10, 10);
    g2m1->setAmplitude(g2s2->getValue());
    g2->onSliderEvent(this, &ofApp::onGui2SliderEvent);
}

void ofApp::onGui1SliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target == g1s1){
        g1m1->setFrequency(g1s1->getValue());
    }   else if (e.target == g1s2){
        g1m1->setAmplitude(g1s2->getValue());
    }
}

void ofApp::onGui2SliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target == g2s1){
        g2m1->setFrequency(g2s1->getValue());
    }   else if (e.target == g2s2){
        g2m1->setAmplitude(g2s2->getValue());
    }
}

void ofApp::update()
{
// sine wave //
    float val = sin(angle1+=0.05);
    g1s1->setValue(val);
    g1m1->setFrequency(val);
}

void ofApp::draw()
{

}




