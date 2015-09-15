#include "ofApp.h"

/*
    Simple example to demonstrate the framerate monitor component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);
    
// instantiate a framerate monitor and tell it to update every .5 seconds //
    fps = new ofxDatGuiFPS(0.5f);
    
// let's stick it in the top right corner of the screen //
    fps->setAnchor( ofxDatGuiAnchor::TOP_RIGHT );
    
}

void ofApp::update()
{
    fps->update();
}

void ofApp::draw()
{
    fps->draw();
}
