#include "ofApp.h"

/*
    Simple example to demonstrate the 2dPad Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);
    
// instantiate a 2d pad that by default will map to the window dimensions //
    pad = new ofxDatGui2dPad("2D PAD");
    
// position the component in the middle of the screen //
    pad->setPosition(ofGetWidth()/2 - pad->getWidth()/2, ofGetHeight()/2 - pad->getHeight()/2);
    
// adjust the component's opacity to help us see the circle behind it //
    pad->setOpacity(.75);
    
// and register to listen for events //
    pad->on2dPadEvent(this, &ofApp::on2dPadEvent);

// optionally we can set the bounds rectangle the 2d pad maps to //
    int padding = 200;
    bounds = ofRectangle(padding, padding, ofGetWidth()-padding*2, ofGetHeight()-padding*2);
// comment this next line out to see the difference //
    pad->setBounds(bounds);

// position the circle at the component's default position //
    circlePosition = pad->getPosition();
}

void ofApp::update()
{
    pad->update();
}

void ofApp::draw()
{
// draw the circle //
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawCircle(circlePosition.x, circlePosition.y, 150);

// draw the component //
    pad->draw();

// draw our custom bounds rectangle //
    ofNoFill();
    ofSetColor(ofColor::grey);
    ofDrawRectangle(bounds);
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    circlePosition.x = e.x;
    circlePosition.y = e.y;
}

