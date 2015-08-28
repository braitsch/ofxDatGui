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
    activeHover = nullptr;
    activeFocus = nullptr;
    mousePressed = false;
    
    mGuiHeader = new ofxDatGuiHeader();
    mGuiFooter = new ofxDatGuiFooter();
    attachItem( mGuiHeader );
    attachItem( mGuiFooter );
    
    ofAddListener(ofEvents().draw, this, &ofxDatGui::onDraw, OF_EVENT_ORDER_AFTER_APP);
    ofAddListener(ofEvents().update, this, &ofxDatGui::onUpdate, OF_EVENT_ORDER_AFTER_APP);
    ofAddListener(ofEvents().keyPressed, this, &ofxDatGui::onKeyPressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().windowResized, this, &ofxDatGui::onWindowResized, OF_EVENT_ORDER_AFTER_APP);
}

void ofxDatGui::setHeader(string label)
{
    mGuiHeader->setLabel(label);
}

void ofxDatGui::setOpacity(float opacity)
{
    ofxDatGuiGlobals::guiAlpha = opacity*255;
}

ofxDatGuiItem* ofxDatGui::getItemAt(int index)
{
// internally add 1 to index to compensate for header //
    return items[index+1];
}

/* add component methods */

ofxDatGuiTextInput* ofxDatGui::addTextInput(string label, string value)
{
    ofxDatGuiTextInput* message = new ofxDatGuiTextInput(items.size()-1, label, value);
    attachItem(message);
    return message;
}

ofxDatGuiButton* ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* button = new ofxDatGuiButton(items.size()-1, label);
    attachItem(button);
    return button;
}

ofxDatGuiToggle* ofxDatGui::addToggle(string label, bool state)
{
    ofxDatGuiToggle* button = new ofxDatGuiToggle(items.size()-1, label, state);
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
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(items.size()-1, label, min, max, val);
    attachItem(slider);
    return slider;
}

ofxDatGuiDropdown* ofxDatGui::addDropdown(vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown(items.size()-1, "SELECT OPTION", options);
    attachItem(dropdown);
    return dropdown;
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
    item->onGuiEvent(this, &ofxDatGui::onGuiEventCallback);
    if (items.size() < 2){
        items.push_back( item );
    }   else{
        items.insert(items.end()-1, item);
    }
    mHeight = 0;
    for (int i=0; i<items.size(); i++) {
        items[i]->setOrigin(ofxDatGuiGlobals::guiX, mHeight);
        mHeight += items[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
    }
    mHeightMinimum = mHeight;
}

void ofxDatGui::onGuiEventCallback(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::DROPDOWN_EXPANDED){
    // shift everyone down //
        adjustHeight(e.index);
    }   else if (e.type == ofxDatGuiEventType::DROPDOWN_COLLAPSED){
    // shift everyone back up //
        adjustHeight(e.index);
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
    // shift everyone back up //
        adjustHeight(e.index);
    // compensate for the header and ensure index is zero based //
        e.index--;
        changeEventCallback(e);
    }   else if (e.type == ofxDatGuiEventType::GUI_TOGGLED){
        mGuiFooter->isExpanded() ? collapseGui() : expandGui();
    }   else{
    // compensate for the header and ensure index is zero based //
        e.index--;
        changeEventCallback(e);
    }
}

void ofxDatGui::adjustHeight(int index)
{
    ofxDatGuiItem* target = items[index];
    mHeight = target->getOriginY() - ofxDatGuiGlobals::guiY + target->getHeight() + ofxDatGuiGlobals::rowSpacing;
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

bool ofxDatGui::isMouseOver(ofxDatGuiItem* item)
{
    bool hit = false;
    if (item->getVisible() && item->hitTest(mouse)){
        hit = true;
        if (activeHover != nullptr){
            if (activeHover != item){
                activeHover->onMouseLeave(mouse);
                activeHover = item;
                activeHover->onMouseEnter(mouse);
            }
        }   else{
            activeHover = item;
            activeHover->onMouseEnter(mouse);
        }
    }
    return hit;
}

void ofxDatGui::onUpdate(ofEventArgs &e)
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
    if (!hit && activeHover != nullptr){
        activeHover->onMouseLeave(mouse);
        activeHover = nullptr;
    }   else if (hit){
        if (mousePressed) {
            activeHover->onMouseDrag(mouse);
        // allow the panel to be repositioned //
            if (activeHover == mGuiHeader) moveGui(mouse-mGuiHeader->dragOffset);
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
        for (uint16_t i=0; i<items.size(); i++) items[i]->draw();
    ofPopStyle();
}


void ofxDatGui::onWindowResized(ofResizeEventArgs &e)
{
    for (uint16_t i=0; i<items.size(); i++) items[i]->onWindowResize(e.width, e.height);
}

