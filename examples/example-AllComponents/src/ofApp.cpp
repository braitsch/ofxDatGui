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
    gui->addTextInput("MESSAGE", "# OPEN FRAMEWORKS #");
    
// add a folder to group a few components //
    ofxDatGuiFolder* folder = gui->addFolder("MY WHITE FOLDER", ofColor::white);
    folder->addTextInput("** INPUT", "A NESTED TEXT INPUT");
    folder->addSlider("** SLIDER", 0, 100);
    folder->addToggle("** TOGGLE");
    
    gui->addSlider("POSITION X", 0, 120, 75);
    gui->addSlider("POSITION Y", -40, 240, 200);
    gui->addSlider("POSITION Z", -80, 120, -40);
    opacitySlider = gui->addSlider("DATGUI OPACITY", 0, 100);

    
// add a dropdown //
    vector<string> o1 = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(o1);

// and a couple buttons //
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", true);

// adding the optional header allows you to drag the gui around //
    gui->addHeader(":: DRAG ME TO REPOSITION ::");

// adding the optional footer allows you to collapse/expand the gui //
    gui->addFooter();

// listen for component events //
    gui->onGuiEvent(this, &ofApp::onGuiEvent);

}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        log(e, "BUTTON_CLICKED");
        
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        log(e, "INPUT_CHANGED : " + e.text);
        
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
    // set the gui opacity from the slider's scale value (0-1) //
        if (gui->getItemAt(e.index) == opacitySlider) gui->setOpacity(e.scale);
        log(e, "SLIDER_CHANGED : " + ofToString(e.value, 2) + " // " + ofToString(e.scale, 2) + "%" );
        
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        log(e, "OPTION_SELECTED");
        
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        log(e, "BUTTON_TOGGLED : " + ofToString(e.enabled));
    }
}

void ofApp::log(ofxDatGuiEvent e, string s)
{
    cout << "COMPONENT #" << e.index << ":" << e.child << " >> " << s << endl;
}

void ofApp::update()
{

}

void ofApp::draw()
{

}


