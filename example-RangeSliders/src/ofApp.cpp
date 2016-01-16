#include "ofApp.h"

/*
    Simple example to demonstrate the Range Slider Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);
    
// instantiate a slider with a default value of 20 //
    slider = new ofxDatGuiSlider("BACKGROUND BRIGHTNESS", 0, 100, 20);
    
// slider values are floats that by default have a two decimal place precision //
// if you want the slider to work with integers simply set the precision to zero //
// the maximum precision that is currently supported is four decimal places //
// slider->setPrecision(0);
   
// let's make it BIG //
    slider->setWidth(ofGetWidth(), .2);
    
// and position it verticaly centered on the screen //
    slider->setPosition(0, ofGetHeight()/2 - slider->getHeight()/2);

// listen for change events //
    slider->onSliderEvent(this, &ofApp::onSliderEvent);
    
// and set the background color to the slider's default value //
    ofSetBackgroundColor(ofColor::white*slider->getScale());
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    ofSetBackgroundColor(ofColor::white*e.scale);
    cout << "value = " << e.value << " : scale = " << e.scale << endl;
}

void ofApp::update()
{
    slider->update();
}

void ofApp::draw()
{
    slider->draw();
}

