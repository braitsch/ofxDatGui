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
    
// finally listen for component events //
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
    
// capture the default slider values into variables //
    drawSpeed = s1->getValue();
    lineWeight = s2->getValue();
    Line::MaxLength = s3->getValue();
    gui->setOpacity(s4->getScale());
    drawingPaused = t1->getEnabled();
    
    index = 0;
    lines.push_back(Line(ofGetWidth()*.2, ofGetHeight()/2, p1->getColor()));
    lines.push_back(Line(ofGetWidth()*.4, ofGetHeight()/2, p2->getColor()));
    lines.push_back(Line(ofGetWidth()*.6, ofGetHeight()/2, p3->getColor()));
    lines.push_back(Line(ofGetWidth()*.8, ofGetHeight()/2, p4->getColor()));
    
// tile the background with a pattern //
    bkgd.load("bkgd-pattern.png");
}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        ofxDatGuiItem* button = gui->getItemAt(e.index);
        if (button == b1) reset();
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "COMPONENT #" << e.index << " :: INPUT_CHANGED" << " > " << e.text << endl;
    /* 
        events will very soon carry a pointer to the component that dispatched it so this will become much easier!
    */
    }   else if (e.index == 2){
        if (e.child == 0){
            drawSpeed = e.value;
        }   else if (e.child == 1){
            lineWeight = e.value;
        }   else if (e.child == 2){
            Line::MaxLength = e.value;
        }
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        gui->setOpacity(e.scale);
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        drawingPaused = e.enabled;
    }   else if (e.type == ofxDatGuiEventType::COLOR_CHANGED){
    /* 
        events will very soon carry a pointer to the component that dispatched it so this will become much easier!
    */
        if (e.child == 0){
            lines[0].color = p1->getColor();
        }   else if (e.child == 1){
            lines[1].color = p2->getColor();
        }   else if (e.child == 2){
            lines[2].color = p3->getColor();
        }   else if (e.child == 3){
            lines[3].color = p4->getColor();
        }
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



