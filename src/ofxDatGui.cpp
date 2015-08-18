//
//  ofxDatGui.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGui.h"

ofxDatGui::ofxDatGui(int x, int y)
{
    mousePressed = false;
    ofxDatGuiCore::init(x, y);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased);
}

ofxDatGui::ofxDatGui(uint8_t anchor)
{
    int x = 0;
    int y = 0;
    if (anchor == ofxDatGuiPosition::TR) x = ofGetWidth()-ofxDatGuiCore::guiWidth;
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
    ofxDatGuiCore::guiHeight = items.size() * (ofxDatGuiItem::itemHeight+ofxDatGuiItem::itemSpacing);
    ofxDatGuiCore::guiHeight+= ofxDatGuiItem::itemSpacing*2;
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
    ofSetColor(ofxDatGuiColor::gui_bkgd);
    ofDrawRectangle(ofxDatGuiCore::guiPosition.x, ofxDatGuiCore::guiPosition.y, ofxDatGuiCore::guiWidth, ofxDatGuiCore::guiHeight + (ofxDatGuiCore::guiPadding));
    for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
}
