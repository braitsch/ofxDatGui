#include "ofApp.h"

void ofApp::setup()
{
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addHeader("POLYGON EXAMPLE");
    gui->addSlider("MIN RADIUS", 0, 100);
    gui->addSlider("MAX RADIUS", 100, 740);
    gui->addSlider("ZOOM SPEED", 0, 100);
    gui->addSlider("NUM SIDES", 3, 50);
    gui->addSlider("MARGIN", -100, 500);
    gui->addColorPicker("LINE COLOR");
    gui->addSlider("LINE WEIGHT", 1, 100);
    gui->addColorPicker("BACKGROUND");
    gui->addButton("RESET");
    gui->addFooter();
    
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    
    reset();
    isFullscreen = true;
    ofSetFullscreen(isFullscreen);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->getLabel() == "RESET") reset();
}

void ofApp::reset()
{
    margin = 0;
    zSpeed = 0.10f;
    numSides = 10;
    oscillator = 0;
    minRadius = 50;
    maxRadius = 300;
    lineWeight = 2;
    lineColor = ofColor::fromHex(0xEEEEEE);
    bkgdColor = ofColor::fromHex(0x333333);
    gui->getSliderByName("MIN RADIUS")->setValue(minRadius);
    gui->getSliderByName("MAX RADIUS")->setValue(maxRadius);
    gui->getSliderByName("ZOOM SPEED")->setScale(zSpeed);
    gui->getSliderByName("NUM SIDES")->setValue(numSides);
    gui->getSliderByName("MARGIN")->setValue(margin);
    gui->getSliderByName("LINE WEIGHT")->setValue(lineWeight);
    gui->getColorPickerByName("LINE COLOR")->setColor(lineColor);
    poly.setLineColor(lineColor);
    poly.setLineWeight(lineWeight);
    ofSetBackgroundColor(bkgdColor);
    poly.reset(margin, (maxRadius-minRadius)/2, numSides);
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target->getLabel() == "MIN RADIUS"){
        minRadius = e.target->getValue();
    }  else if (e.target->getLabel() == "MAX RADIUS"){
        maxRadius = e.target->getValue();
    }  else if (e.target->getLabel() == "NUM SIDES"){
        poly.setNumSides(e.target->getValue());
    }  else if (e.target->getLabel() == "MARGIN"){
        poly.setMargin(e.target->getValue());
    }  else if (e.target->getLabel() == "ZOOM SPEED"){
        zSpeed = e.target->getScale();
    }  else if (e.target->getLabel() == "LINE WEIGHT"){
        poly.setLineWeight(e.target->getValue());
    }
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    if (e.target->getLabel() == "LINE COLOR"){
        poly.setLineColor(e.target->getColor());
    }   else if (e.target->getLabel() == "BACKGROUND"){
        ofSetBackgroundColor(e.target->getColor());
    }
}

void ofApp::draw()
{
    poly.draw();
}

void ofApp::update()
{
    oscillator+=(0.25 * float(zSpeed));
    poly.setRadius((sin(oscillator)*maxRadius) + (maxRadius+minRadius));
}

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



