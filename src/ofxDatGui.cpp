/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ofxDatGui.h"

ofxDatGui::ofxDatGui(int x, int y)
{
    ofxDatGuiItem::init(x, y); init();
}

ofxDatGui::ofxDatGui(uint8_t anchor)
{
    ofxDatGuiItem::init(anchor); init();
}

void ofxDatGui::init()
{
    mShowGui = true;
    mousePressed = false;
    mGuiHeader = nullptr;
    mGuiFooter = nullptr;
    activeHover = nullptr;
    activeFocus = nullptr;
    
    ofAddListener(ofEvents().draw, this, &ofxDatGui::onDraw, OF_EVENT_ORDER_AFTER_APP);
    ofAddListener(ofEvents().update, this, &ofxDatGui::onUpdate, OF_EVENT_ORDER_AFTER_APP);
    ofAddListener(ofEvents().keyPressed, this, &ofxDatGui::onKeyPressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().windowResized, this, &ofxDatGui::onWindowResized, OF_EVENT_ORDER_BEFORE_APP);
}

ofxDatGuiHeader* ofxDatGui::addHeader(string label)
{
    if (mGuiHeader == nullptr){
        mGuiHeader = new ofxDatGuiHeader(label);
        if (items.size() == 0){
            items.push_back(mGuiHeader);
        }   else{
    // always ensure header is at the top of the panel //
            items.insert(items.begin(), mGuiHeader);
        }
        layoutGui();
    }
}

ofxDatGuiFooter* ofxDatGui::addFooter()
{
    if (mGuiFooter == nullptr){
        mGuiFooter = new ofxDatGuiFooter();
        items.push_back(mGuiFooter);
        mGuiFooter->onGuiEvent(this, &ofxDatGui::onGuiEventCallback);
        layoutGui();
    }
}

void ofxDatGui::setOpacity(float opacity)
{
    ofxDatGuiGlobals::guiAlpha = opacity*255;
}

ofxDatGuiItem* ofxDatGui::getItemAt(int index)
{
    if (mGuiHeader == nullptr){
        return items[index];
    }   else{
    // internally add 1 to compensate for the header //
        return items[index+1];
    }
}

/* add component methods */

ofxDatGuiTextInput* ofxDatGui::addTextInput(string label, string value)
{
    ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value);
    attachItem(input);
    return input;
}

ofxDatGuiButton* ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* button = new ofxDatGuiButton(label);
    attachItem(button);
    return button;
}

ofxDatGuiToggle* ofxDatGui::addToggle(string label, bool state)
{
    ofxDatGuiToggle* button = new ofxDatGuiToggle(label, state);
    attachItem(button);
    return button;
}

ofxDatGuiSlider* ofxDatGui::addSlider(string label, float min, float max)
{
// default to halfway between min & max values //
    ofxDatGuiSlider* slider = addSlider(label, min, max, (max+min)/2);
    return slider;
}

ofxDatGuiSlider* ofxDatGui::addSlider(string label, float min, float max, float val)
{
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val);
    attachItem(slider);
    return slider;
}

ofxDatGuiDropdown* ofxDatGui::addDropdown(vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown("SELECT OPTION", options);
    attachItem(dropdown);
    return dropdown;
}

ofxDatGuiFolder* ofxDatGui::addFolder(string label, ofColor color)
{
    ofxDatGuiFolder* folder = new ofxDatGuiFolder(label, color);
    attachItem(folder);
    return folder;
}

ofxDatGuiColorPicker* ofxDatGui::addColorPicker(string label)
{
    ofxDatGuiColorPicker* picker = new ofxDatGuiColorPicker(label);
    attachItem(picker);
    return picker;
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
    item->onGuiEvent(this, &ofxDatGui::onGuiEventCallback);
    if (mGuiFooter != nullptr){
        items.insert(items.end()-1, item);
    }   else {
        items.push_back( item );
    }
    layoutGui();
}

void ofxDatGui::layoutGui()
{
    mHeight = 0;
    for (int i=0; i<items.size(); i++) {
        items[i]->setIndex(i);
        items[i]->setOrigin(ofxDatGuiGlobals::guiX, ofxDatGuiGlobals::guiY + mHeight);
        mHeight += items[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
    }
    mHeightMinimum = mHeight;
}

void ofxDatGui::onGuiEventCallback(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::DROPDOWN_TOGGLED){
        adjustHeight(e.index);
        
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        adjustHeight(e.index);
    // compensate for the header and ensure index is zero based //
        if (mGuiHeader != nullptr) e.index--;
        changeEventCallback(e);
        
    }   else if (e.type == ofxDatGuiEventType::GUI_TOGGLED){
        mGuiFooter->getIsExpanded() ? collapseGui() : expandGui();
        
    }   else{
    // compensate for the header and ensure index is zero based //
        if (mGuiHeader != nullptr) e.index--;
        changeEventCallback(e);
    }
}

void ofxDatGui::adjustHeight(int index)
{
    ofxDatGuiItem* target = items[index];
    mHeight = target->getPositionY() - ofxDatGuiGlobals::guiY + target->getHeight() + ofxDatGuiGlobals::rowSpacing;
    for (uint8_t i=index+1; i<items.size(); i++){
        items[i]->setPositionY(mHeight);
        mHeight += items[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
    }
}

void ofxDatGui::moveGui(ofPoint pt)
{
    mHeight = 0;
    ofxDatGuiGlobals::guiX = pt.x;
    ofxDatGuiGlobals::guiY = pt.y;
    for (uint8_t i=0; i<items.size(); i++){
        items[i]->setOrigin(ofxDatGuiGlobals::guiX, ofxDatGuiGlobals::guiY + mHeight);
        mHeight += items[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
    }
// disable automatic repositioning on window resize //
    ofxDatGuiGlobals::anchorPosition = 0;
}

void ofxDatGui::expandGui()
{
    mHeight = 0;
    for (uint8_t i=0; i<items.size(); i++) {
        items[i]->setVisible(true);
        mHeight += items[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
    }
    mGuiFooter->setPositionY(mHeight - mGuiFooter->getHeight() - ofxDatGuiGlobals::rowSpacing);
}

void ofxDatGui::collapseGui()
{
    for (uint8_t i=0; i<items.size()-1; i++) items[i]->setVisible(false);
    mGuiFooter->setPositionY(0);
    mHeight = mGuiFooter->getHeight();
}

/* event handlers & update / draw loop */

void ofxDatGui::onMousePressed(ofMouseEventArgs &e)
{
    mousePressed = true;
    if (activeHover != nullptr){
        activeHover->onMousePress(mouse);
        if (activeFocus!= activeHover){
            if (activeFocus != nullptr) activeFocus->onFocusLost();
            activeFocus = activeHover;
            activeFocus->onFocus();
        }
    }   else if (activeFocus != nullptr){
        activeFocus->onFocusLost();
        activeFocus = nullptr;
    }
}

void ofxDatGui::onMouseReleased(ofMouseEventArgs &e)
{
    mousePressed = false;
    if (activeHover != nullptr){
        activeHover->onMouseRelease(mouse);
        if (activeFocus!= activeHover){
            if (activeFocus != nullptr) activeFocus->onFocusLost();
            activeFocus = activeHover;
            activeFocus->onFocus();
        }
    }   else if (activeFocus != nullptr){
        activeFocus->onFocusLost();
        activeFocus = nullptr;
    }
}

void ofxDatGui::onKeyPressed(ofKeyEventArgs &e)
{
    bool disableShowAndHide = false;
    if (activeFocus != nullptr) {
        activeFocus->onKeyPressed(e.key);
        if ((e.key == OF_KEY_RETURN || e.key == OF_KEY_TAB)){
            activeFocus->onFocusLost();
            activeFocus = nullptr;
        }
    // if an text input is active ignore the gui show/hide key command //
        ofxDatGuiTextInput* dd = dynamic_cast<ofxDatGuiTextInput*>(activeFocus);
        disableShowAndHide = (dd != NULL);
    }
    if (e.key == 'h' && disableShowAndHide == false) mShowGui = !mShowGui;
}

bool ofxDatGui::isMouseOverRow(ofxDatGuiItem* row)
{
    bool hit = false;
    if (row->getVisible() && row->hitTest(mouse)){
        hit = true;
        if (activeHover != nullptr){
            if (activeHover != row){
                activeHover->onMouseLeave(mouse);
                activeHover = row;
                activeHover->onMouseEnter(mouse);
            }
        }   else{
            activeHover = row;
            activeHover->onMouseEnter(mouse);
        }
    }
    return hit;
}

bool ofxDatGui::isMouseOverGui()
{
    bool hit = false;
    for (uint8_t i=0; i<items.size(); i++) {
        if (items[i]->getIsExpanded()){
            for (uint8_t j=0; j<items[i]->children.size(); j++) {
                hit = isMouseOverRow(items[i]->children[j]);
                if (hit) return true;
            }
        }
        if (!hit) {
            hit = isMouseOverRow(items[i]);
            if (hit) return true;
        }
    }
    return hit;
}

void ofxDatGui::onUpdate(ofEventArgs &e)
{
    mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
    bool hit = isMouseOverGui();

    if (!hit && activeHover != nullptr){
        activeHover->onMouseLeave(mouse);
        activeHover = nullptr;
    }   else if (hit){
        if (mousePressed) {
            activeHover->onMouseDrag(mouse);
        // allow the panel to be repositioned //
            if (mGuiHeader != nullptr && activeHover == mGuiHeader) moveGui(mouse-mGuiHeader->dragOffset);
        }
    }
}

void ofxDatGui::onDraw(ofEventArgs &e)
{
    if (!mShowGui) return;
    ofPushStyle();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ofSetColor(ofxDatGuiColor::GUI_BKGD, ofxDatGuiGlobals::guiAlpha);
        ofDrawRectangle(ofxDatGuiGlobals::guiX, ofxDatGuiGlobals::guiY, ofxDatGuiGlobals::guiWidth, mHeight - ofxDatGuiGlobals::rowSpacing);
        for (int i=0; i<items.size(); i++) items[i]->draw();
    // color pickers overlap other components when expanded so they must be drawn last //
        for (int i=0; i<items.size(); i++) items[i]->drawColorPicker();
    ofPopStyle();
}


void ofxDatGui::onWindowResized(ofResizeEventArgs &e)
{
    for (uint16_t i=0; i<items.size(); i++) items[i]->onWindowResize(e.width, e.height);
}

