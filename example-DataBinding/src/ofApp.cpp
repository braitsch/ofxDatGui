
/*
    Simple example to demonstrate Data Binding (wip)
    https://github.com/braitsch/ofxDatGui @braitsch
*/

#include "ofApp.h"

void ofApp::setup()
{
    ofxDatGuiLog::quiet();
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(1920, 1080);
    ofSetBackgroundColor(ofColor::white);

// create a simple circle and position it in the middle of the screen //
    circle = new Circle(150);
    circle->x = ofGetWidth()/2;
    circle->y = ofGetHeight()/2;
    
// instantiate our gui and a couple of range sliders //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addHeader("ofxDATGUI DATA BINDING EXAMPLE");
    ofxDatGuiSlider* sx = gui->addSlider("CIRCLE X", 0, 100);
    ofxDatGuiSlider* sy = gui->addSlider("CIRCLE Y", 0, 100);
    
// bind the circle's x & y properties to the gui sliders //
    sx->bind(&circle->x, 0, ofGetWidth());
    sy->bind(&circle->y, 0, ofGetHeight());
    
}

void ofApp::update()
{
// drag the circle around if the mouse is pressed while over it //
    ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
    if (ofGetMousePressed()){
        if (circle->inside(mouse)) mDragging = true;
    }   else{
        mDragging = false;
    }
    if (mDragging){
        circle->x = mouse.x;
        circle->y = mouse.y;
    }
}

void ofApp::draw()
{
    circle->draw();
}
