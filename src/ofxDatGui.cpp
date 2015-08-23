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

ofxDatGui::ofxDatGui(ofVec2f pos, bool enableRetina)
{
    ofxDatGuiItem::init(pos, enableRetina); init();
}

ofxDatGui::ofxDatGui(uint8_t anchor, bool enableRetina)
{
    ofxDatGuiItem::init(anchor, enableRetina); init();
}

void ofxDatGui::init()
{
    mShowGui = true;
    activeItem = nullptr;
    mousePressed = false;
    mGuiToggler = new ofxDatGuiToggler();
    attachItem( mGuiToggler );
    ofAddListener(ofEvents().keyPressed, this, &ofxDatGui::onKeyPressed);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased);
}

/* add component methods */

void ofxDatGui::addInput(string label, string value)
{
    ofxDatGuiInput* input = new ofxDatGuiInput(items.size()-1, label, value);
    attachItem(input);
}

void ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* btn = new ofxDatGuiButton(items.size()-1, label);
    attachItem(btn);
}

void ofxDatGui::addToggle(string label, bool state)
{
    ofxDatGuiToggle* btn = new ofxDatGuiToggle(items.size()-1, label, state);
    attachItem(btn);
}

void ofxDatGui::addSlider(string label, float min, float max)
{
// default to halfway between min & max values //
    addSlider(label, min, max, min+((max-min)/2));
}

void ofxDatGui::addSlider(string label, float min, float max, float val)
{
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(items.size()-1, label, min, max, val);
    attachItem(slider);
}

void ofxDatGui::addDropdown(vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown(items.size()-1, "SELECT OPTION", options);
    attachItem(dropdown);
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
    item->onGuiEvent(this, &ofxDatGui::onGuiEventCallback);
    if (items.size() == 0){
        items.push_back( item );
    }   else{
        items.insert(items.end()-1, item);
    }
    mHeight = items.size() * (ofxDatGuiItem::rowHeight+ofxDatGuiItem::rowSpacing);
    mHeightMinimum = mHeight;
    mGuiToggler->setOriginY(mHeight - ofxDatGuiItem::rowHeight-ofxDatGuiItem::rowSpacing);
}

void ofxDatGui::onGuiEventCallback(ofxDatGuiEvent e)
{
    
    if (e.type == ofxDatGuiEventType::DROPDOWN_EXPANDED){
    // shift everyone down //
        ofxDatGuiDropdown* dd = dynamic_cast<ofxDatGuiDropdown*>(items[e.target]);
        adjustHeight(e.target+1, dd->getHeight());
    }   else if (e.type == ofxDatGuiEventType::DROPDOWN_COLLAPSED){
    // shift everyone back up //
        ofxDatGuiDropdown* dd = dynamic_cast<ofxDatGuiDropdown*>(items[e.target]);
        adjustHeight(e.target+1, 0);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
    // shift everyone back up //
        ofxDatGuiDropdown* dd = dynamic_cast<ofxDatGuiDropdown*>(items[e.target]);
        adjustHeight(e.target+1, 0);
        changeEventCallback(e);
    }   else if (e.type == ofxDatGuiEventType::GUI_TOGGLED){
        mGuiToggler->isExpanded() ? collapseGui() : expandGui();
    }   else{
        changeEventCallback(e);
    }
}

void ofxDatGui::adjustHeight(int index, int amount)
{
    for (uint8_t i=index; i<items.size(); i++) items[i]->setYPosition(amount);
    mHeight = mHeightMinimum + amount;
}

void ofxDatGui::expandGui()
{
    for (uint8_t i=0; i<items.size(); i++) items[i]->setYPosition(0);
    mHeight = mHeightMinimum;
}

void ofxDatGui::collapseGui()
{
    for (uint8_t i=0; i<items.size(); i++) {
    // collapse anything that has children //
        if (items[i]->children.size() > 0){
            ofxDatGuiDropdown* dd = dynamic_cast<ofxDatGuiDropdown*>(items[i]);
            dd->collapse();
        }
        items[i]->setYPosition(mGuiToggler->getOriginY() * -1);
    }
    mHeight = ofxDatGuiButton::rowHeight;
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

void ofxDatGui::onKeyPressed(ofKeyEventArgs &e)
{
    if (e.key == 'h') mShowGui = !mShowGui;
    if (activeItem != nullptr){
        activeItem->onKeyPressed(e.key);
    }
}

void ofxDatGui::update()
{
    bool hit = false;
    mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
    for (uint8_t i=0; i<items.size(); i++) {
        if (items[i]->isExpanded()){
            for (uint8_t j=0; j<items[i]->children.size(); j++) {
                hit = isMouseOver(items[i]->children[j]);
                if (hit) break;
            }
        }
        if (!hit) {
            hit = isMouseOver(items[i]);
            if (hit) break;
        }
    }
    if (!hit && activeItem != nullptr){
        activeItem->onMouseLeave(mouse);
    //  activeItem->onFocusLost();
        activeItem = nullptr;
    }   else if (hit){
        if (mousePressed) activeItem->onMouseDrag(mouse);
    }
}

bool ofxDatGui::isMouseOver(ofxDatGuiItem* item)
{
    bool hit = false;
    if (item->hitTest(mouse)){
        hit = true;
        if (activeItem != nullptr){
            if (activeItem != item){
                activeItem->onMouseLeave(mouse);
                activeItem = item;
                activeItem->onMouseEnter(mouse);
            }
        }   else{
            activeItem = item;
            activeItem->onMouseEnter(mouse);
        }
    }
    return hit;
}

void ofxDatGui::draw()
{
    if (!mShowGui) return;
    ofSetColor(ofxDatGuiColor::GUI_BKGD);
    ofDrawRectangle(ofxDatGuiPosition::x, ofxDatGuiPosition::y, ofxDatGuiItem::guiWidth, mHeight - ofxDatGuiItem::rowSpacing + (ofxDatGuiItem::guiPadding));
    for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
}

