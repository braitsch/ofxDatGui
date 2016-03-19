
/*
    Simple example to demonstrate Data Binding (wip)
    https://github.com/braitsch/ofxDatGui @braitsch
*/

#include "ofApp.h"

void ofApp::setup()
{
    ofxDatGuiLog::quiet();

// create a simple circle and position it in the middle of the screen //
    circle = new Circle(150);
    
// instantiate our gui and a couple of range sliders //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addHeader("ofxDATGUI DATA BINDING EXAMPLE");
    sx = gui->addSlider("CIRCLE X", 0, ofGetWidth());
    sy = gui->addSlider("CIRCLE Y", 0, ofGetHeight());
    
// bind the circle's x & y properties to the gui sliders //
    sx->bind(circle->x);
    sy->bind(circle->y);

    ofSetWindowPosition(0, 0);
    ofSetWindowShape(1920, 1080);
    
// center the circle onscreen //
    circle->x = ofGetWidth() / 2;
    circle->y = ofGetHeight() / 2;
    
}

void ofApp::update()
{
// drag the circle around if the mouse is pressed while over it //
    if (ofGetMousePressed() && gui->getMouseDown() == false){
        ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
        if (circle->inside(mouse)) {
            circle->x = mouse.x;
            circle->y = mouse.y;
        }
    }
}

void ofApp::draw()
{
    circle->draw();
}

void ofApp::windowResized(int w, int h)
{
// update the slider boundaries //
    sx->setMax(ofGetWidth());
    sy->setMax(ofGetHeight());
}
