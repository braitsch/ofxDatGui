#include "ofApp.h"

/*
    Simple example to demonstrate the Button Components
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    numClicks = 0;
    isFullscreen = false;
    ofSetWindowPosition(0, 0);
    
// instantiate a basic button and a toggle button //
    button = new ofxDatGuiButton("CLICK ME");
    toggle = new ofxDatGuiToggle("TOGGLE FULLSCREEN", false);
    
// position the components in the middle of the screen //
    positionButtons();
    
// and register to listen for events //
    button->onButtonEvent(this, &ofApp::onButtonEvent);
    toggle->onButtonEvent(this, &ofApp::onButtonEvent);
}

void ofApp::update()
{
    button->update();
    toggle->update();
}

void ofApp::draw()
{
    button->draw();
    toggle->draw();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
// we have a couple ways to figure out which button was clicked //

// we can compare our button pointer to the target of the event //
    if (e.target == button){
        numClicks++;
        if (numClicks == 1){
            button->setLabel("YOU CLICKED ME ONCE");
        }   else{
            button->setLabel("YOU CLICKED ME "+ofToString(numClicks)+" TIMES");
        }
        
// or we can check against the label of the event target //
    }   else if(e.target->getLabel() == "TOGGLE FULLSCREEN"){
        isFullscreen =!isFullscreen;
        ofSetFullscreen(isFullscreen);
        if (!isFullscreen) {
            ofSetWindowShape(1920, 1080);
            ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
        }
        positionButtons();
    }
}

void ofApp::positionButtons()
{
    button->setPosition(ofGetWidth()/2 - button->getWidth()/2, ofGetHeight()/2 - button->getHeight());
    toggle->setPosition(button->getX(), button->getY() + button->getHeight() + 20);
}



