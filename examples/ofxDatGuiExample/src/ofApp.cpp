#include "ofApp.h"

void ofApp::setup()
{
    if (ofGetWidth()!=ofGetScreenWidth()) {
        ofSetWindowShape(1920, 1080);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
// add components //
    gui->addInput("INPUT", "# OPEN FRAMEWORKS #");
    gui->addSlider("X POSITION", 0, 100, 25);
    gui->addSlider("Y POSITION", -80, -40);
    gui->addSlider("Z POSITION", 20, 240, 185);
    vector<string> options = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(options);
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", false);
    
// listen for component events //
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
    
// optionally set the background opacity //
    gui->setOpacity(.5);
    image.load("bkgd-pattern.png");

}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        cout << "onGuiEvent::BUTTON_CLICKED " << e.index << endl;
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "onGuiEvent::INPUT_CHANGED " << e.index << " :: " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "onGuiEvent::SLIDER_CHANGED " << e.index << " :: " << e.value << " :: " << e.scale<<"%" << endl;
    // set the opacity of the gui to any of the incoming slider values //
        gui->setOpacity(e.scale);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.index << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "onGuiEvent::BUTTON_TOGGLED " << e.index << " :: " << e.enabled << endl;
    }
}

void ofApp::draw()
{
// pattern the background //
    for(int i = 0; i < ofGetHeight(); i += 400) for(int j = 0; j < ofGetWidth(); j += 400) image.draw(j, i, 400, 400);
}
