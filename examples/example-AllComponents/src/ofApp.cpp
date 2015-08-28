#include "ofApp.h"

void ofApp::setup()
{
    if (ofGetWidth()!=ofGetScreenWidth()) {
        ofSetWindowShape(1920, 1080);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
    
// instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
// add some components //
    gui->addMessage("MESSAGE", "# OPEN FRAMEWORKS #");
    gui->addSlider("POSITION X", 0, 120, 75);
    gui->addSlider("POSITION Y", -40, 240, 200);
    gui->addSlider("POSITION Z", -80, 120, -40);
    gui->addSlider("DATGUI OPACITY", 0, 100);
    
// add a dropdown //
    vector<string> options = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(options);

// and a couple buttons //
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", false);
    
// listen for component events //
    gui->onGuiEvent(this, &ofApp::onGuiEvent);

}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        cout << "onGuiEvent::BUTTON_CLICKED " << e.index << endl;
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "onGuiEvent::INPUT_CHANGED " << e.index << " :: " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "onGuiEvent::SLIDER_CHANGED " << e.index << " :: " << e.value << " :: " << e.scale<<"%" << endl;
        if (e.index == 4) gui->setOpacity(e.scale);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.index << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "onGuiEvent::BUTTON_TOGGLED " << e.index << " :: " << e.enabled << endl;
    }
}

void ofApp::update()
{

}

void ofApp::draw()
{

}


