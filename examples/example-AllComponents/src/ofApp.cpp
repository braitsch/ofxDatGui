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
    
// add a folder to group a few components together //
    ofxDatGuiFolder* folder = gui->addFolder("MY WHITE FOLDER", ofColor::white);
    folder->addTextInput("** INPUT", "A NESTED TEXT INPUT");
    folder->addSlider("** SLIDER", 0, 100);
    folder->addToggle("** TOGGLE");
    folder->addColorPicker("picker");
    
// add a couple range sliders //
    gui->addSlider("POSITION X", 0, 120, 75);
    gui->addSlider("POSITION Y", -40, 240, 200);
    gui->addSlider("POSITION Z", -80, 120, -40);
    opacitySlider = gui->addSlider("DATGUI OPACITY", 0, 100);

// and a colorpicker! //
    gui->addColorPicker("COLOR PICKER");
    
// add a dropdown menu //
    vector<string> o1 = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(o1);

// and a couple buttons //
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", true);

// adding the optional header allows you to drag the gui around //
    gui->addHeader(":: DRAG ME TO REPOSITION ::");

// adding the optional footer allows you to collapse/expand the gui //
    gui->addFooter();

// finally register a few callbacks to listen for specific component events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getValue() << endl;
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getEnabled() << endl;
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getText() << endl;
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "Target: " << e.target->getLabel() << " Selected Child Index: " << e.target->getSelectedChildIndex() << endl;
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getColor() << endl;
}

void ofApp::update()
{

}

void ofApp::draw()
{

}


