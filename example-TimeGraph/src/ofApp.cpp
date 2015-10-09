#include "ofApp.h"

/*
    Simple example to demonstrate the WaveMonitor Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    angle1 = 0.0f;
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(1920, 1080);
    
    g1 = new ofxDatGui();
    g1->setWidth(1200);
    g1->setAlignment(ofxDatGuiAlignment::CENTER);
    g1->addHeader("wave monitor & value plotter example");
    g1->addFooter();
    g1m1 = g1->addWaveMonitor("wave monitor", 3, .5);
    g1s1 = g1->addSlider("frequency", 0, 50, 5);
// amplitude multiplier must be a value between 0 & 1 //
    g1s2 = g1->addSlider("amplitude", 0, 1);
    g1t1 = g1->addToggle("draw filled", true);
    g1->addBreak(20);
    p1 = g1->addValuePlotter("value plotter", 0, 100);
    g1->addSlider("multiplier", 0, 1, .02);
    g1->addSlider("sweep speed", 0, 30, 3);
    g1t2 = g1->addToggle("draw filled", true);
    
// set the frequency and amplitude //
    g1m1->setFrequency(g1s1->getValue());
    g1m1->setAmplitude(g1s2->getValue());
    
    p1->setSpeed(g1->getSlider("sweep speed")->getValue());
    
    g1->setOrigin(ofGetWidth()/2 - g1->getWidth()/2, 100);
    g1->onButtonEvent(this, &ofApp::onGuiButtonEvent);
    g1->onSliderEvent(this, &ofApp::onGuiSliderEvent);
}

void ofApp::onGuiSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target == g1s1){
        g1m1->setFrequency(g1s1->getValue());
    }   else if (e.target == g1s2){
        g1m1->setAmplitude(g1s2->getValue());
    }
}

void ofApp::onGuiButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == g1t1){
        e.enabled ? g1m1->setDrawMode(ofxDatGuiGraph::FILLED) : g1m1->setDrawMode(ofxDatGuiGraph::POINTS);
        //g1m1->drawFilled(e.enabled);
    } else if (e.target == g1t2){
        //p1->drawFilled(e.enabled);
    }
}

void ofApp::update()
{
// generate a sine wave between 0 & 1 //
    float val = (1+sin(angle1+=g1->getSlider("multiplier")->getValue()))/2;
// and multiply it by the range of the plotter //
    p1->setValue(val * p1->getRange());
    p1->setSpeed(g1->getSlider("sweep speed")->getValue());
}

void ofApp::draw()
{

}




