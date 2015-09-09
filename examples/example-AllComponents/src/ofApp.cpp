#include "ofApp.h"

void ofApp::setup()
{
// instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
// add some components //
    gui->addTextInput("MESSAGE", "OPEN FRAMEWORKS DATGUI");
    
// add a folder to group a few components together //
    ofxDatGuiFolder* folder = gui->addFolder("MY WHITE FOLDER", ofColor::white);
    folder->addTextInput("** INPUT", "");
    folder->addSlider("** SLIDER", 0, 100);
    folder->addToggle("** TOGGLE");
    folder->addColorPicker("** PICKER", ofxDatGuiColor::DROPDOWN_STRIPE);
// let's have it open by default. note: call this only after you're done adding items //
    folder->expand();
    
// add a couple range sliders //
    gui->addSlider("POSITION X", 0, 120, 75);
    gui->addSlider("POSITION Y", -40, 240, 200);
    gui->addSlider("POSITION Z", -80, 120, -40);
    gui->addSlider("DATGUI OPACITY", 0, 100);

// and a colorpicker! //
    gui->addColorPicker("COLOR PICKER", ofxDatGuiColor::TOGGLE_STRIPE);
    
// add a dropdown menu //
    vector<string> o1 = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(o1);

// add a 2d pad //
    gui->add2dPad("2D PAD");

// a button matrix //
    gui->addButtonMatrix("MATRIX", 21);
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
    gui->on2dPadEvent(this, &ofApp::on2dPadEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    
    gui->setOpacity(gui->getSlider("datgui opacity")->getScale());
    
// let's launch the app fullscreen //
    isFullscreen = true;
    ofSetFullscreen(isFullscreen);
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getValue() << endl;
    if (e.target->getLabel()=="DATGUI OPACITY") gui->setOpacity(e.scale);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getEnabled() << endl;
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getText() << endl;
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.x << ":" << e.y << endl;
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "Target: " << e.target->getLabel() << " Selected Child Index: " << e.target->getSelectedChildIndex() << endl;
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "Target: " << e.target->getLabel() << " " << e.target->getColor() << endl;
    ofSetBackgroundColor(e.color);
}

void ofApp::draw() { }
void ofApp::update() { }

void ofApp::keyPressed(int key)
{
    if (key == 'f') {
        isFullscreen =!isFullscreen;
        ofSetFullscreen(isFullscreen);
        if (!isFullscreen) {
            ofSetWindowShape(1920, 1080);
            ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
        }
    }
}

