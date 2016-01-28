#include "ofApp.h"

/*
    Simple example to demonstrate the Color Picker Component.
    Select a color in the picker to change the color of the canvas.
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
// create a color picker (passing in a color is optional) //
    picker = new ofxDatGuiColorPicker("COLOR PICKER", ofColor::fromHex(0xCECECE));
    picker->setAnchor(ofxDatGuiAnchor::TOP_LEFT);
    
// and register a callback to listen for change events //
    picker->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    ofSetBackgroundColor(e.color);
// seriously, could it possibly be any easier? ;-)
}

void ofApp::update()
{
    picker->update();
}

void ofApp::draw()
{
    picker->draw();
}
