#include "ofApp.h"

void ofApp::setup()
{
    if (ofGetWidth()!=ofGetScreenWidth()) ofSetWindowPosition(100, 100);
    gui = new ofxDatGui( ofxDatGuiAnchor::TR );
    ofxDatGuiInput* input = gui->addInput("INPUT", "# OPEN FRAMEWORKS #");
//  input->setText("ok");
    ofxDatGuiSlider* slider = gui->addSlider("X POSITION", -40, 40);
//  slider->setValue(30);
    slider->setScale(.25);
    gui->addSlider("X POSITION", -80, -40);
    gui->addSlider("Z POSITION", 0, 100);
    vector<string> options = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(options);
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", false);
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
    gui->setOpacity(.2);
    image.load("bkgd-image.jpg");
//  https://www.flickr.com/photos/pinks2000/14604733850

}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        cout << "onGuiEvent::BUTTON_CLICKED " << e.target << endl;
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "onGuiEvent::INPUT_CHANGED " << e.target << " :: " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "onGuiEvent::SLIDER_CHANGED " << e.target << " :: " << e.value << " :: " << e.scale<<"%" << endl;
        gui->setOpacity(e.scale);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.target << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "onGuiEvent::BUTTON_TOGGLED " << e.target << " :: " << e.value << endl;
    }
}

void ofApp::update()
{

}

void ofApp::draw()
{
    image.draw(0, 0, ofGetWidth(), ofGetHeight());
}
