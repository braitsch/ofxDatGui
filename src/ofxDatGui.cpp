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
    init(x, y);
}

ofxDatGui::ofxDatGui(uint8_t anchor)
{
    int x = 0;
    int y = 0;
    if (anchor == ofxDatGuiPosition::TR) x = ofGetWidth()-ofxDatGuiCore::guiWidth;
    init(x, y);
}

void ofxDatGui::init(int x, int y)
{
    mousePressed = false;
    activeItem = nullptr;
    ofxDatGuiCore::init(x, y);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased);
}

/* add component methods */

void ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* btn = new ofxDatGuiButton(items.size(), label);
    attachItem(btn);
}

void ofxDatGui::addSlider(string label, float min, float max)
{
// default to halfway between min & max values //
    addSlider(label, min, max, min+((max-min)/2));
}

void ofxDatGui::addSlider(string label, float min, float max, float val)
{
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(items.size(), label, min, max, val);
    attachItem(slider);
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
    item->onGuiEvent(this, &ofxDatGui::dispatchEvent);
    items.push_back( item );
    ofxDatGuiCore::guiHeight = items.size() * (ofxDatGuiItem::rowHeight+ofxDatGuiItem::rowSpacing);
    ofxDatGuiCore::guiHeight+= ofxDatGuiItem::rowSpacing*2;
}

/* event handlers & update / draw loop */

void ofxDatGui::onMousePressed(ofMouseEventArgs &e)
{
    mousePressed = true;
    if (activeItem != nullptr){
    //  cout << "onMousePressed" << endl;
        activeItem->onMousePress(mouse);
    }
}

void ofxDatGui::onMouseReleased(ofMouseEventArgs &e)
{
    mousePressed = false;
    if (activeItem != nullptr){
    //  cout << "onMouseReleased" << endl;
        activeItem->onMouseRelease(mouse);
    }
}

void ofxDatGui::update()
{
    bool hit = false;
    mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
    for (uint16_t i=0; i<items.size(); i++) {
        if (items[i]->hitTest(mouse)){
            hit = true;
            if (activeItem == nullptr) items[i]->onMouseEnter(mouse);
            activeItem = items[i];
            break;
        }
    }
    if (!hit && activeItem != nullptr){
    //  cout << "onMouseLeave" << endl;
        activeItem->onMouseLeave(mouse);
        activeItem = nullptr;
    }   else if (hit){
        if (mousePressed) activeItem->onMouseDrag(mouse);
    }
}

void ofxDatGui::draw()
{
    ofSetColor(ofxDatGuiColor::gui_bkgd);
    ofDrawRectangle(ofxDatGuiCore::guiPosition.x, ofxDatGuiCore::guiPosition.y, ofxDatGuiCore::guiWidth, ofxDatGuiCore::guiHeight + (ofxDatGuiCore::guiPadding));
    for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
}
