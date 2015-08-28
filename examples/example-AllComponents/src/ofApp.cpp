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
//  gui->setHeader("DATGUI EXAMPLE");
    gui->addTextInput("MESSAGE", "# OPEN FRAMEWORKS #");
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
        cout << "COMPONENT #" << e.index << " :: BUTTON_CLICKED" << endl;
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "COMPONENT #" << e.index << " :: INPUT_CHANGED" << " > " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "COMPONENT #" << e.index << " :: SLIDER_CHANGED" << " > " << ofToString(e.value, 2) << " // " << e.scale<<"%" << endl;
        if (e.index == 5) gui->setOpacity(e.scale);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "COMPONENT #" << e.index << " :: OPTION_SELECTED" << " > " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "COMPONENT #" << e.index << " :: BUTTON_TOGGLED" << " > " << e.enabled << endl;
    }
}

void ofApp::update()
{

}

void ofApp::draw()
{

}


