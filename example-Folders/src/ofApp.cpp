#include "ofApp.h"

/*
    Simple example to demonstrate the Dropdown Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    int x = 150;
    int y = 100;
    ofSetWindowPosition(0, 0);

    f1 = new ofxDatGuiFolder("FOLDER 1", ofxDatGuiColor::BUTTON_STRIPE);
    f1->addToggle("TOGGLE");
    f1->addBreak();
    f1->addFRM();
    f1->addBreak();
    f1->addSlider("SLIDER", 0, 100);
    f1->addMatrix("MATRIX", 14);
    f1->addColorPicker("COLOR PICKER", ofxDatGuiColor::SLIDER_STRIPE);
    f1->setOrigin(x, y);
    f1->expand();
    
    f2 = new ofxDatGuiFolder("FOLDER 2", ofxDatGuiColor::INPUT_STRIPE);
    f2->setOrigin(x + f1->getWidth()+40, y);
    f2->addButton("BUTTON");
    f2->addTextInput("TEXT INPUT", "ENTER A MESSAGE");
    f2->addBreak();
    f2->addMatrix("MATRIX", 21, true);
    f2->addBreak();
    f2->add2dPad("2D PAD");
    f2->expand();
    
    f1->onButtonEvent(this, &ofApp::onButtonEvent);
    f1->onSliderEvent(this, &ofApp::onSliderEvent);
    f1->onMatrixEvent(this, &ofApp::onMatrixEvent);
    f1->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    
    f2->onButtonEvent(this, &ofApp::onButtonEvent);
    f2->onMatrixEvent(this, &ofApp::onMatrixEvent);
    f2->on2dPadEvent(this, &ofApp::on2dPadEvent);
    f2->onTextInputEvent(this, &ofApp::onTextInputEvent);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent" << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << "onSliderEvent" << endl;
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "onTextInputEvent" << endl;
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    cout << "on2dPadEvent" << endl;
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent" << endl;
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    cout << "onMatrixEvent" << endl;
}

void ofApp::update()
{
    f1->update();
    f2->update();
}

void ofApp::draw()
{
    f1->draw();
    f2->draw();
}

