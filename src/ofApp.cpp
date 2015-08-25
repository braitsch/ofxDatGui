#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowPosition(100, 100);
    gui = new ofxDatGui( ofxDatGuiAnchor::TR );
    gui->addInput("INPUT", "# OPEN FRAMEWORKS DAT GUI #");
    gui->addSlider("X POSITION", 10, 20, 5);
    gui->addSlider("X POSITION", -20, 60);
    gui->addSlider("Z POSITION", 0, 100, 75);
    vector<string> options = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(options);
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", false);
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        cout << "onGuiEvent::BUTTON_CLICKED " << e.target << endl;
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "onGuiEvent::INPUT_CHANGED " << e.target << " :: " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "onGuiEvent::SLIDER_CHANGED " << e.target << " :: " << e.value << endl;
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.target << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "onGuiEvent::BUTTON_TOGGLED " << e.target << " :: " << e.value << endl;
    }
}

void ofApp::update()
{
    gui->update();
}

void ofApp::draw()
{
    gui->draw();
}
