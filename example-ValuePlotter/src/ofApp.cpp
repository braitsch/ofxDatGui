#include "ofApp.h"

/*
    Simple example to demonstrate the ValuePlotter Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);
    ofSetBackgroundColor(ofColor::fromHex(0x333333));
    plotter = new ofxDatGuiValuePlotter("VALUE\nPLOTTER", 0, 100);
    plotter->drawFilled(false);
}

void ofApp::update()
{
    plotter->update();
}

void ofApp::draw()
{
    plotter->draw();
    ofSetColor(ofColor::red);
    ofDrawCircle(500, 500, 50);
}




