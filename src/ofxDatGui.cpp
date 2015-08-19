//
//  ofxDatGui.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGui.h"

namespace ofxDatGuiPosition
{
    int x = 0;
    int y = 0;
}

ofxDatGui::ofxDatGui(int x, int y)
{
    init(x, y);
}

ofxDatGui::ofxDatGui(uint8_t anchor)
{
    int x = 0;
    int y = 0;
    if (anchor == ofxDatGuiAnchor::TR) x = ofGetWidth()-ofxDatGuiWidth;
    init(x, y);
}

void ofxDatGui::init(int x, int y)
{
    mousePressed = false;
    activeItem = nullptr;
    ofxDatGuiPosition::x = x;
    ofxDatGuiPosition::y = y;
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

void ofxDatGui::addDropdown(vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown(items.size(), "SELECT OPTION", options);
    attachItem(dropdown);
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
    item->onGuiEvent(this, &ofxDatGui::dispatchEvent);
    items.push_back( item );
    ofxDatGuiHeight = items.size() * (ofxDatGuiItem::rowHeight+ofxDatGuiItem::rowSpacing);
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
            if (activeItem != nullptr){
                if (activeItem != items[i]){
                    activeItem->onMouseLeave(mouse);
                    activeItem = items[i];
                    activeItem->onMouseEnter(mouse);
                }
            }   else{
                activeItem = items[i];
                activeItem->onMouseEnter(mouse);
            }
            break;
        }
    }
    if (!hit && activeItem != nullptr){
        activeItem->onMouseLeave(mouse);
        activeItem = nullptr;
    }   else if (hit){
        if (mousePressed) activeItem->onMouseDrag(mouse);
    }
}

void ofxDatGui::draw()
{
    ofSetColor(ofxDatGuiColor::GUI_BKGD);
    ofDrawRectangle(ofxDatGuiPosition::x, ofxDatGuiPosition::y, ofxDatGuiWidth, ofxDatGuiHeight - ofxDatGuiItem::rowSpacing + (ofxDatGuiPadding));
    for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
}

