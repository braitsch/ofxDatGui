#include "ofApp.h"

/*
    Simple example to demonstrate the Text Input Component.
    Type something into the component and see it displayed in the center of the screen
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
    
    input = new ofxDatGuiTextInput("TEXT INPUT", "Type Something Here");
    input->onTextInputEvent(this, &ofApp::onTextInputEvent);
    input->setWidth(800, .2);
    input->setPosition(ofGetWidth()/2 - input->getWidth()/2, 240);
    font.load("ofxbraitsch/fonts/Verdana.ttf", 24);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
// text input events carry the text of the input field //
    cout << "From Event Object: " << e.text << endl;
// although you can also retrieve it from the event target //
    cout << "From Event Target: " << e.target->getText() << endl;
}

void ofApp::update()
{
    input->update();
}

void ofApp::draw()
{
    input->draw();
    string str = "Text Input: "+input->getText();
    ofRectangle bounds = font.getStringBoundingBox(str, ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(ofColor::black);
    font.drawString(str, bounds.x-bounds.width/2, bounds.y-bounds.height/2);
}

