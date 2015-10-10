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
    
    gui = new ofxDatGui();
  //  gui->setWidth(1200);
    gui->setAlignment(ofxDatGuiAlignment::CENTER);
    gui->addHeader("wave monitor & value plotter example");
    gui->addFooter();
    m1 = gui->addWaveMonitor("wave monitor", 3, .5);
    s1 = gui->addSlider("frequency", 0, 50, 5);
// amplitude multiplier must be a value between 0 & 1 //
    s2 = gui->addSlider("amplitude", 0, 1);
    gui->addBreak(20);
    p1 = gui->addValuePlotter("value plotter", 0, 100);
    gui->addSlider("multiplier", 0, 1, .02);
    gui->addSlider("sweep speed", 0, 30, 3);
    gui->addBreak(20);
    
// add a dropdown to select between the four draw modes //
    vector<string> drawModes = {"lines", "filled", "points", "outline"};
    dd = gui->addDropdown("select draw mode", drawModes);
    
// set the frequency and amplitude //
    m1->setFrequency(s1->getValue());
    m1->setAmplitude(s2->getValue());
    
    p1->setSpeed(gui->getSlider("sweep speed")->getValue());
    
    gui->setOrigin(ofGetWidth()/2 - gui->getWidth()/2, 100);
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
        case ofxDatGuiGraph::LINES :
            m1->setDrawMode(ofxDatGuiGraph::LINES);
            p1->setDrawMode(ofxDatGuiGraph::LINES);
            dd->setLabel("drawing mode : lines");
        break;
        case ofxDatGuiGraph::FILLED :
            m1->setDrawMode(ofxDatGuiGraph::FILLED);
            p1->setDrawMode(ofxDatGuiGraph::FILLED);
            dd->setLabel("drawing mode : filled");
        break;
        case ofxDatGuiGraph::POINTS :
            m1->setDrawMode(ofxDatGuiGraph::POINTS);
            p1->setDrawMode(ofxDatGuiGraph::POINTS);
            dd->setLabel("drawing mode : points");
        break;
        case ofxDatGuiGraph::OUTLINE :
            m1->setDrawMode(ofxDatGuiGraph::OUTLINE);
            p1->setDrawMode(ofxDatGuiGraph::OUTLINE);
            dd->setLabel("drawing mode : outline");
        break;
    }
}

void ofApp::update()
{
// generate a sine wave between 0 & 1 //
    float val = (1+sin(angle1+=gui->getSlider("multiplier")->getValue()))/2;
// and multiply it by the range of the plotter //
    p1->setValue(val * p1->getRange());
    p1->setSpeed(gui->getSlider("sweep speed")->getValue());
}

void ofApp::draw()
{

}




