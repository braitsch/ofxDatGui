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
    
// add some components //
    i1 = gui->addTextInput("MESSAGE", "# OPEN FRAMEWORKS #");
    s1 = gui->addSlider("DRAW SPEED", 0, 120, 5);
    s2 = gui->addSlider("LINE WEIGHT", 1, 60, 2);
    s3 = gui->addSlider("LINE LENGTH", 4, 200, 140);
    s4 = gui->addSlider("DATGUI OPACITY", 0, 100);
    
    b1 = gui->addButton("RESET");
    t1 = gui->addToggle("PAUSE DRAWING", false);
    
// listen for component events //
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
    
// capture the default slider values into variables //
    drawSpeed = s1->getValue();
    lineWeight = s2->getValue();
    Line::MaxLength = s3->getValue();
    gui->setOpacity(s4->getScale());
    drawingPaused = t1->getEnabled();
    
    index = 0;
    lines.push_back(Line(ofGetWidth()*.2, ofGetHeight()/2, ofColor::fromHex(0xE0E4CC)));
    lines.push_back(Line(ofGetWidth()*.4, ofGetHeight()/2, ofColor::fromHex(0x53777A)));
    lines.push_back(Line(ofGetWidth()*.6, ofGetHeight()/2, ofColor::fromHex(0x542437)));
    lines.push_back(Line(ofGetWidth()*.8, ofGetHeight()/2, ofColor::fromHex(0xECD078)));
    
// tile the background with a pattern //
    bkgd.load("bkgd-pattern.png");
}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
        ofxDatGuiItem* button = gui->getItemAt(e.index);
        if (button == b1) reset();
    }   else if (e.type == ofxDatGuiEventType::INPUT_CHANGED){
        cout << "onGuiEvent::INPUT_CHANGED " << e.index << " :: " << e.text << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        ofxDatGuiItem* slider = gui->getItemAt(e.index);
        if (slider == s1){
            drawSpeed = e.value;
        }   else if (slider == s2){
            lineWeight = e.value;
        }   else if (slider == s3){
            Line::MaxLength = e.value;
        }   else if (slider == s4){
            gui->setOpacity(e.scale);
        }
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.index << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        drawingPaused = e.enabled;
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



