#include "ofApp.h"

/*
    Simple example to demonstrate the 2dPad Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);
    ofSetCircleResolution(100);
    
// instantiate a 2d pad that by default will map to the window dimensions //
    pad = new ofxDatGui2dPad("2D PAD");
    
// position the component in the middle of the screen //
    pad->setPosition(ofGetWidth()/2 - pad->getWidth()/2, ofGetHeight()/2 - pad->getHeight()/2);
    
// adjust the component's opacity to help us see the circle behind it //
    pad->setOpacity(.75);
    
// and register to listen for events //
    pad->on2dPadEvent(this, &ofApp::on2dPadEvent);

// optionally we can set the bounds rectangle the 2d pad maps to //
    mUseCustomBounds = true;
    if (mUseCustomBounds) setBounds();
}

void ofApp::update()
{
    pad->update();
}

void ofApp::draw()
{
// draw the circle at the pad's point position //
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawCircle(pad->getPoint(), 150);

// draw the component //
    pad->draw();

// draw our custom bounds rectangle //
    ofNoFill();
    ofSetColor(ofColor::grey);
    ofDrawRectangle(bounds);
}

void ofApp::setBounds()
{
    int padding = 200;
// set the bounds to be 200px smaller than the application window //
    bounds = ofRectangle(padding, padding, ofGetWidth()-padding*2, ofGetHeight()-padding*2);
    pad->setBounds(bounds);
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    cout << "on2dPadEvent :: x=" << e.x << " y=" << e.y << endl;
}

void ofApp::windowResized(int w, int h)
{
// reset the bounds to the new window dimensions //
    if (mUseCustomBounds) setBounds();
// and recenter the 2dpad component onscreen //
    pad->setPosition(ofGetWidth()/2 - pad->getWidth()/2, ofGetHeight()/2 - pad->getHeight()/2);
}

