#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(2100, 1200);
    
// setup the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addHeader("POLYGON EXAMPLE");
    gui->addSlider("MIN RADIUS", 0, 100);
    gui->addSlider("MAX RADIUS", 100, 740);
    gui->addSlider("ZOOM SPEED", 0, 100);
    gui->addSlider("NUM SIDES", 3, 50);
    gui->addSlider("MARGIN", -100, 500);
    gui->addColorPicker("LINE COLOR");
    gui->addSlider("LINE WEIGHT", 1, 100);
    gui->add2dPad("POLY POSITION");
    gui->addColorPicker("BACKGROUND");
    gui->addButton("RESET");
    gui->addFooter();
    
// and register callbacks to listen for events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->on2dPadEvent(this, &ofApp::on2dPadEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    gui->setOpacity(.5);
    
// setup the poly and default gui settings //
    reset();
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

// reset the gui //
    gui->getSlider("min radius")->setValue(minRadius);
    gui->getSlider("max radius")->setValue(maxRadius);
    gui->getSlider("zoom speed")->setScale(zSpeed);
    gui->getSlider("num sides")->setValue(numSides);
    gui->getSlider("margin")->setValue(margin);
    gui->getSlider("line weight")->setValue(lineWeight);
    gui->get2dPad("poly position")->reset();
    gui->getColorPicker("line color")->setColor(lineColor);

// reset the poly params //
    ofSetBackgroundColor(bkgdColor);
    poly.setLineColor(lineColor);
    poly.setLineWeight(lineWeight);
    poly.setOrigin(ofGetWidth()/2, ofGetHeight()/2);
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

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    poly.setOrigin(e.x, e.y);
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



