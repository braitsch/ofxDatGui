#include "ofApp.h"

/*
    Simple example to demonstrate the Text Input Component.
    Type something into the component and see it displayed in the center of the screen
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addTextInput("Text Input", "Type Something Here");
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    font.load("ofxdatgui_assets/font-verdana.ttf", 24);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
// text input events carry the text of the input field //
    cout << "From Event Object: " << e.text;
// although you can also retrieve it from the event target //
    cout << "From Event Target: " << e.target->getText();
// or get the value of the textfield directly from the gui //
    cout << "From The Gui: " << gui->getTextInput("text input")->getText();
}

void ofApp::update()
{

}

void ofApp::draw()
{
    string str = "Text Input: "+gui->getTextInput("text input")->getText();
    ofRectangle bounds = font.getStringBoundingBox(str, ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(ofColor::black);
    font.drawString(str, bounds.x-bounds.width/2, bounds.y-bounds.height/2);
}

