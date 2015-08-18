//
//  ofxDatGui.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGui.h"

ofPoint ofxDatGui::pos;

ofxDatGui::ofxDatGui(int x, int y)
{
    mousePressed = false;
    ofxDatGuiCore::init(x, y);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased);
}

void ofxDatGui::onMousePressed(ofMouseEventArgs &e)
{
    mousePressed = true;
}

void ofxDatGui::onMouseReleased(ofMouseEventArgs &e)
{
    mousePressed = false;
}

void ofxDatGui::addSlider(string label, float val)
{
    items.push_back(new ofxDatGuiSlider(items.size(), label, val));
}

void ofxDatGui::update()
{
    if (mousePressed){
        mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
        activeItem = nullptr;
        for (uint16_t i=0; i<items.size(); i++) {
            if (items[i]->hitTest(mouse)){
                activeItem = items[i];
                activeItem->onMousePress(mouse);
                continue;
            }
        }
    }
}

void ofxDatGui::draw()
{
    for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
}
