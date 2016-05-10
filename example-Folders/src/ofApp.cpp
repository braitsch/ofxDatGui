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

    f1 = new ofxDatGuiFolder("folder 1", ofColor::fromHex(0xFFD00B));
    f1->addToggle("toggle");
    f1->addBreak();
    f1->addFRM();
    f1->addBreak();
    f1->addSlider("slider", 0, 100);
    f1->addMatrix("matrix", 14);
    f1->addColorPicker("color picker", ofColor::fromHex(0x2FA1D6));
    f1->addWaveMonitor("wave monitor", 3, .5);
    f1->setPosition(x, y);
    f1->expand();
    
    f2 = new ofxDatGuiFolder("folder 2", ofColor::fromHex(0x1ED36F));
    f2->setPosition(x + f1->getWidth()+40, y);
    f2->addButton("button");
    f2->addTextInput("text input", "enter a message");
    f2->addBreak();
    f2->addMatrix("matrix", 21, true);
    f2->addBreak();
    f2->add2dPad("2d pad");
    f2->addSlider("slider", 0, 100);
    f2->expand();
    
    f1->onButtonEvent(this, &ofApp::onButtonEvent);
    f1->onToggleEvent(this, &ofApp::onToggleEvent);
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

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    cout << "onToggleEvent " << e.checked << endl;
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

