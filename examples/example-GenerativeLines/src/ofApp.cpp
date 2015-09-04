#include "ofApp.h"

int Line::MinLength = 4;
int Line::MaxLength = 100;

void ofApp::setup()
{
    if (ofGetWidth()!=ofGetScreenWidth()) {
        ofSetWindowShape(1920, 1080);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
    
// instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

// add the optional header and footer //
    gui->addTextInput("INPUT MESSAGE", "# OPEN FRAMEWORKS #");
    gui->addFooter();
    
// add some color pickers to color our lines //
    ofxDatGuiFolder* f1 = gui->addFolder("LINE COLORS", ofColor::green);
    p1 = f1->addColorPicker("LINE 1", ofColor::fromHex(0xE0E4CC));
    p2 = f1->addColorPicker("LINE 2", ofColor::fromHex(0x53777A));
    p3 = f1->addColorPicker("LINE 3", ofColor::fromHex(0x542437));
    p4 = f1->addColorPicker("LINE 4", ofColor::fromHex(0xECD078));
    
// and some sliders to adjust how they're drawn //
    ofxDatGuiFolder* f2 = gui->addFolder("LINE CONTROLS", ofxDatGuiColor::SLIDER);
    s1 = f2->addSlider("DRAW SPEED", 0, 120, 5);
    s2 = f2->addSlider("LINE WEIGHT", 1, 60, 2);
    s3 = f2->addSlider("LINE LENGTH", 4, 200, 140);
    
// and a few others widgits for good measure :) //
    s4 = gui->addSlider("DATGUI OPACITY", 0, 100);
    b1 = gui->addButton("RESET");
    t1 = gui->addToggle("PAUSE DRAWING", false);
    
// register a few callbacks to listen for our gui events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    
// capture the default slider values into variables //
    drawSpeed = s1->getValue();
    lineWeight = s2->getValue();
    Line::MaxLength = s3->getValue();
    gui->setOpacity(s4->getScale());
    drawingPaused = t1->getEnabled();
    
// finally add some generative lines to draw //
    lines.push_back(Line(ofGetWidth()*.2, ofGetHeight()/2, p1->getColor()));
    lines.push_back(Line(ofGetWidth()*.4, ofGetHeight()/2, p2->getColor()));
    lines.push_back(Line(ofGetWidth()*.6, ofGetHeight()/2, p3->getColor()));
    lines.push_back(Line(ofGetWidth()*.8, ofGetHeight()/2, p4->getColor()));
    
// and tile the background with a pattern //
    bkgd.load("bkgd-pattern.png");
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
//  every event has a pointer to the object (target) that dispatched the event
    if (e.target->getLabel() == "DRAW SPEED"){
        drawSpeed = e.value;
// you can also compare the target pointer against a local variable
    }   else if (e.target == s2){
        lineWeight = e.value;
// slider event objects also carry the current scale & value of the slider
    }   else if (e.target == s3){
        Line::MaxLength = e.value;
    }   else if (e.target->getLabel() == "DATGUI OPACITY"){
// however you can always read these values directly off of the slider itself
        gui->setOpacity(e.target->getScale());
    }
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == b1) {
        reset();
    }   else if (e.target == t1) {
        drawingPaused = t1->getEnabled();
    }
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    cout << "onTextInputEvent: " << e.target->getLabel() << " " << e.target->getText() << endl;
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    if (e.target->getLabel() == "LINE 1"){
        lines[0].color = e.target->getColor();
    }   else if (e.target->getLabel() == "LINE 2"){
        lines[1].color = e.target->getColor();
    }   else if (e.target->getLabel() == "LINE 3"){
        lines[2].color = e.target->getColor();
    }   else if (e.target->getLabel() == "LINE 4"){
        lines[3].color = e.target->getColor();
    }
}

void ofApp::update()
{
    if (drawingPaused) return;
    for(int i=0; i<lines.size(); i++){
        lines[i].tick();
        lines[i].head->x += (lines[i].dx) * drawSpeed;
        lines[i].head->y += (lines[i].dy) * drawSpeed;
    }
}

void ofApp::draw()
{
// pattern the background //
    for(int i = 0; i < ofGetHeight(); i += 400) for(int j = 0; j < ofGetWidth(); j += 400) bkgd.draw(j, i, 400, 400);
// draw some lines //
    ofPushStyle();
        ofSetLineWidth(lineWeight);
        for (int i=0; i<lines.size(); i++){
            ofSetColor(lines[i].color);
            lines[i].draw();
        }
    ofPopStyle();
}

void ofApp::reset()
{
    for(int i=0; i<lines.size(); i++) lines[i].reset();
}

void ofApp::keyPressed(int key)
{
    if (key == 'f') ofToggleFullscreen();
}



