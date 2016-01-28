#include "ofApp.h"

/*
    Simple example to demonstrate the WaveMonitor Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ang1 = ang2 = 0.0f;
    ofSetWindowShape(1920, 1200);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
    
// setup our gui //
    gui = new ofxDatGui();
    gui->setWidth(1200, .2);
    gui->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    gui->addHeader("wave monitor & value plotter example");
    gui->addFooter();
    
// add a wave monitor with a frequency of 3 & amplitude of 50% //
    m1 = gui->addWaveMonitor("wave monitor", 3, .5);
    s1 = gui->addSlider("frequency", 0, 50, 5);
// amplitude multiplier must be a value between 0 & 1 //
    s2 = gui->addSlider("amplitude", 0, 1);
// we'll animate it on a sine wave so let's disable user input //
    s2->setEnabled(false);
    
    gui->addBreak()->setHeight(20);
    
// add a couple value plotters with a range of 0 - 100 //
    p1 = gui->addValuePlotter("value plotter", 0, 100);
    p2 = gui->addValuePlotter("point plotter", 0, 100);
    p2->setDrawMode(ofxDatGuiGraph::POINTS);
    gui->addSlider("multiplier", 0, 1, .10);
    gui->addSlider("sweep speed", 0, 30, 10);
    gui->addBreak()->setHeight(20);
    
// add a dropdown to select between the four draw modes //
    vector<string> drawModes = {"lines", "filled", "points", "outline"};
    dd = gui->addDropdown("select draw mode", drawModes);
    
// set the frequency and amplitude //
    m1->setFrequency(s1->getValue());
    m1->setAmplitude(s2->getValue());
    
    p1->setSpeed(gui->getSlider("sweep speed")->getValue());
    
    gui->setPosition(ofGetWidth()/2 - gui->getWidth()/2, 140);
    gui->onSliderEvent(this, &ofApp::onGuiSliderEvent);
    gui->onDropdownEvent(this, &ofApp::onGuiDropdownEvent);
}

void ofApp::onGuiSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target == s1){
        m1->setFrequency(s1->getValue());
    }   else if (e.target == s2){
        m1->setAmplitude(s2->getValue());
    }
}

void ofApp::onGuiDropdownEvent(ofxDatGuiDropdownEvent e)
{
    switch (e.child) {
        case (int)ofxDatGuiGraph::LINES :
            m1->setDrawMode(ofxDatGuiGraph::LINES);
            p1->setDrawMode(ofxDatGuiGraph::LINES);
            dd->setLabel("drawing mode : lines");
        break;
        case (int)ofxDatGuiGraph::FILLED :
            m1->setDrawMode(ofxDatGuiGraph::FILLED);
            p1->setDrawMode(ofxDatGuiGraph::FILLED);
            dd->setLabel("drawing mode : filled");
        break;
        case (int)ofxDatGuiGraph::POINTS :
            m1->setDrawMode(ofxDatGuiGraph::POINTS);
            p1->setDrawMode(ofxDatGuiGraph::POINTS);
            dd->setLabel("drawing mode : points");
        break;
        case (int)ofxDatGuiGraph::OUTLINE :
            m1->setDrawMode(ofxDatGuiGraph::OUTLINE);
            p1->setDrawMode(ofxDatGuiGraph::OUTLINE);
            dd->setLabel("drawing mode : outline");
        break;
    }
}

void ofApp::update()
{
// generate a couple sine waves between 0 & 1 //
    float v1 = (1+sin(ang1+=.02f))/2;
    float v2 = (1+sin(ang2+=gui->getSlider("multiplier")->getValue()))/2;
    
// oscillate the amplitude of the wave monitor //
    s2->setValue(v1);
    m1->setAmplitude(v1);
    
// and the values we supply to the plotter //
    p1->setValue(v2 * p1->getRange());
    p1->setSpeed(gui->getSlider("sweep speed")->getValue());
    p2->setValue(v2 * p1->getRange());
    p2->setSpeed(gui->getSlider("sweep speed")->getValue());
}

void ofApp::draw()
{

}




