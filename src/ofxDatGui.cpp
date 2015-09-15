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
    mPosition.x = x;
    mPosition.y = y;
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    init();
}

ofxDatGui::ofxDatGui(ofxDatGuiAnchor anchor)
{
    mPosition.x = 0;
    mPosition.y = 0;
    mAnchor = anchor;
    init();
}

void ofxDatGui::init()
{
    setWidth(540);
    setOpacity(1.0f);
    mRowSpacing = 1;
    mVisible = true;
    mDisabled = false;
    mExpanded = true;
    mousePressed = false;
    setAutoDraw(true);
    mGuiHeader = nullptr;
    mGuiFooter = nullptr;
    activeHover = nullptr;
    activeFocus = nullptr;
    mAlignment = ofxDatGuiAlignment::LEFT;
    bool retinaEnabled = (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600);
    if (retinaEnabled) mRowSpacing*=2;
    mFont = new ofxDatGuiFont(retinaEnabled);
    ofAddListener(ofEvents().keyPressed, this, &ofxDatGui::onKeyPressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mousePressed, this, &ofxDatGui::onMousePressed, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().mouseReleased, this, &ofxDatGui::onMouseReleased, OF_EVENT_ORDER_BEFORE_APP);
    ofAddListener(ofEvents().windowResized, this, &ofxDatGui::onWindowResized, OF_EVENT_ORDER_BEFORE_APP);
}

/* 
    public getters & setters
*/

void ofxDatGui::setWidth(int width)
{
    mWidth = width;
    mWidthChanged = true;
    if (mAnchor == ofxDatGuiAnchor::TOP_RIGHT) anchorGui();
}

void ofxDatGui::setOpacity(float opacity)
{
    mAlpha = opacity;
    mAlphaChanged = true;
}

void ofxDatGui::setVisible(bool visible)
{
    mVisible = visible;
}

void ofxDatGui::setDisabled(bool disable)
{
    mDisabled = disable;
}

void ofxDatGui::setPosition(int x, int y)
{
    moveGui(ofPoint(x, y));
}

void ofxDatGui::setAutoDraw(bool autodraw)
{
    if (autodraw){
        ofAddListener(ofEvents().draw, this, &ofxDatGui::onDraw, OF_EVENT_ORDER_AFTER_APP);
        ofAddListener(ofEvents().update, this, &ofxDatGui::onUpdate, OF_EVENT_ORDER_AFTER_APP);
    }   else{
        ofRemoveListener(ofEvents().draw, this, &ofxDatGui::onDraw, OF_EVENT_ORDER_AFTER_APP);
        ofRemoveListener(ofEvents().update, this, &ofxDatGui::onUpdate, OF_EVENT_ORDER_AFTER_APP);
    }
}

void ofxDatGui::setAlignment(ofxDatGuiAlignment align)
{
    mAlignment = align;
    mAlignmentChanged = true;
}

ofPoint ofxDatGui::getPosition()
{
    return ofPoint(mPosition.x, mPosition.y);
}

int ofxDatGui::getWidth()
{
    return mWidth;
}

int ofxDatGui::getHeight()
{
    return mHeight;
}

/* 
    add component methods
*/

ofxDatGuiHeader* ofxDatGui::addHeader(string label)
{
    if (mGuiHeader == nullptr){
        mGuiHeader = new ofxDatGuiHeader(label, mFont);
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
        mGuiFooter = new ofxDatGuiFooter(mFont);
        items.push_back(mGuiFooter);
        mGuiFooter->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
        layoutGui();
    }
}

ofxDatGuiTextInput* ofxDatGui::addTextInput(string label, string value)
{
    ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value, mFont);
    input->onTextInputEvent(this, &ofxDatGui::onTextInputEventCallback);
    attachItem(input);
    return input;
}

ofxDatGuiButton* ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* button = new ofxDatGuiButton(label, mFont);
    button->onButtonEvent(this, &ofxDatGui::onButtonEventCallback);
    attachItem(button);
    return button;
}

ofxDatGuiToggle* ofxDatGui::addToggle(string label, bool state)
{
    ofxDatGuiToggle* button = new ofxDatGuiToggle(label, state, mFont);
    button->onButtonEvent(this, &ofxDatGui::onButtonEventCallback);
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
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val, mFont);
    slider->onSliderEvent(this, &ofxDatGui::onSliderEventCallback);
    attachItem(slider);
    return slider;
}

ofxDatGuiColorPicker* ofxDatGui::addColorPicker(string label, ofColor color)
{
    ofxDatGuiColorPicker* picker = new ofxDatGuiColorPicker(label, color, mFont);
    picker->onColorPickerEvent(this, &ofxDatGui::onColorPickerEventCallback);
    attachItem(picker);
    return picker;
}

ofxDatGuiDropdown* ofxDatGui::addDropdown(vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown("SELECT OPTION", options, mFont);
    dropdown->onDropdownEvent(this, &ofxDatGui::onDropdownEventCallback);
    dropdown->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
    attachItem(dropdown);
    return dropdown;
}

ofxDatGui2dPad* ofxDatGui::add2dPad(string label)
{
    ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, mFont);
    pad->on2dPadEvent(this, &ofxDatGui::on2dPadEventCallback);
    attachItem(pad);
    return pad;
}

ofxDatGui2dPad* ofxDatGui::add2dPad(string label, ofRectangle bounds)
{
    ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, bounds, mFont);
    pad->on2dPadEvent(this, &ofxDatGui::on2dPadEventCallback);
    attachItem(pad);
    return pad;
}

ofxDatGuiMatrix* ofxDatGui::addMatrix(string label, int numButtons, bool showLabels)
{
    ofxDatGuiMatrix* matrix = new ofxDatGuiMatrix(label, numButtons, showLabels, mFont);
    matrix->onMatrixEvent(this, &ofxDatGui::onMatrixEventCallback);
    attachItem(matrix);
    return matrix;
}

ofxDatGuiFolder* ofxDatGui::addFolder(string label, ofColor color)
{
    ofxDatGuiFolder* folder = new ofxDatGuiFolder(label, color, mFont);
    folder->onButtonEvent(this, &ofxDatGui::onButtonEventCallback);
    folder->onSliderEvent(this, &ofxDatGui::onSliderEventCallback);
    folder->onTextInputEvent(this, &ofxDatGui::onTextInputEventCallback);
    folder->onColorPickerEvent(this, &ofxDatGui::onColorPickerEventCallback);
    folder->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
    attachItem(folder);
    return folder;
}

void ofxDatGui::attachItem(ofxDatGuiItem* item)
{
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
        items[i]->setOrigin(mPosition.x, mPosition.y + mHeight);
        mHeight += items[i]->getHeight() + mRowSpacing;
    }
    mHeightMinimum = mHeight;
}

/*
    experimental component retrieval methods
*/

ofxDatGuiButton* ofxDatGui::getButton(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiButton*>(item);
    }   else{
        ofxDatGuiButton* button = new ofxDatGuiButton("X", mFont);
        cout << "ERROR! BUTTON: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(button);
        return button;
    }
}

ofxDatGuiSlider* ofxDatGui::getSlider(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiSlider*>(item);
    }   else{
        ofxDatGuiSlider* slider = new ofxDatGuiSlider("X", 0, 100, 50);
        cout << "ERROR! SLIDER: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(slider);
        return slider;
    }
}

ofxDatGuiTextInput* ofxDatGui::getTextInput(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiTextInput*>(item);
    }   else{
        ofxDatGuiTextInput* input = new ofxDatGuiTextInput("X", "");
        cout << "ERROR! TEXT INPUT: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(input);
        return input;
    }
}

ofxDatGuiDropdown* ofxDatGui::getDropdown(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiDropdown*>(item);
    }   else{
        vector<string> opts = {" ", " "};
        ofxDatGuiDropdown* dd = new ofxDatGuiDropdown("", opts);
        cout << "ERROR! DROPDOWN: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(dd);
        return dd;
    }
}

ofxDatGui2dPad* ofxDatGui::get2dPad(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGui2dPad*>(item);
    }   else{
        ofxDatGui2dPad* pad = new ofxDatGui2dPad("X");
        cout << "ERROR! 2DPAD: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(pad);
        return pad;
    }
}

ofxDatGuiColorPicker* ofxDatGui::getColorPicker(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiColorPicker*>(item);
    }   else{
        ofxDatGuiColorPicker* picker = new ofxDatGuiColorPicker("X");
        cout << "ERROR! COLOPICKER: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(picker);
        return picker;
    }
}

ofxDatGuiMatrix* ofxDatGui::getMatrix(string key)
{
    ofxDatGuiItem* item = getComponent(key);
    if (item != nullptr){
        return static_cast<ofxDatGuiMatrix*>(item);
    }   else{
        ofxDatGuiMatrix* matrix = new ofxDatGuiMatrix("X", 0);
        cout << "ERROR! MATRIX: "<< key <<" NOT FOUND!" << endl;
        trash.push_back(matrix);
        return matrix;
    }
}

ofxDatGuiItem* ofxDatGui::getComponent(string key)
{
    ofxDatGuiItem* item = nullptr;
    for (int i=0; i<items.size(); i++)
    {
    // first search against labels, then keys, ids, etc...
        ofxDatGuiItem* o = items[i];
        if (ofToLower(o->getLabel()) == ofToLower(key)) return items[i];
        for (int j=0; j<o->children.size(); j++)
        {
            if (ofToLower(o->children[j]->getLabel()) == ofToLower(key)) return o->children[j];
        }
    }
    return item;
}

/*
    event callbacks
*/

void ofxDatGui::onButtonEventCallback(ofxDatGuiButtonEvent e)
{
    buttonEventCallback(e);
}

void ofxDatGui::onSliderEventCallback(ofxDatGuiSliderEvent e)
{
    sliderEventCallback(e);
}

void ofxDatGui::onTextInputEventCallback(ofxDatGuiTextInputEvent e)
{
    textInputEventCallback(e);
}

void ofxDatGui::onDropdownEventCallback(ofxDatGuiDropdownEvent e)
{
    adjustHeight(e.parent);
    dropdownEventCallback(e);
}

void ofxDatGui::on2dPadEventCallback(ofxDatGui2dPadEvent e)
{
    pad2dEventCallback(e);
}

void ofxDatGui::onColorPickerEventCallback(ofxDatGuiColorPickerEvent e)
{
    colorPickerEventCallback(e);
}

void ofxDatGui::onMatrixEventCallback(ofxDatGuiMatrixEvent e)
{
    matrixEventCallback(e);
}

void ofxDatGui::onInternalEventCallback(ofxDatGuiInternalEvent e)
{
// these events are not dispatched out to the main application //
    if (e.type == ofxDatGuiEventType::DROPDOWN_TOGGLED){
        adjustHeight(e.index);
    }   else if (e.type == ofxDatGuiEventType::GUI_TOGGLED){
        mGuiFooter->getIsExpanded() ? collapseGui() : expandGui();
    }
}

void ofxDatGui::adjustHeight(int index)
{
    ofxDatGuiItem* target = items[index];
    mHeight = target->getPositionY() - mPosition.y + target->getHeight() + mRowSpacing;
    for (uint8_t i=index+1; i<items.size(); i++){
        items[i]->setPositionY(mPosition.y + mHeight);
        mHeight += items[i]->getHeight() + mRowSpacing;
    }
    mWidthChanged = true;
}

void ofxDatGui::moveGui(ofPoint pt)
{
    mHeight = 0;
    mPosition.x = pt.x;
    mPosition.y = pt.y;
    for (uint8_t i=0; i<items.size(); i++){
        items[i]->setOrigin(mPosition.x, mPosition.y + mHeight);
        mHeight += items[i]->getHeight() + mRowSpacing;
    }
// disable automatic repositioning on window resize //
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    mWidthChanged = true;
}

void ofxDatGui::expandGui()
{
    mHeight = 0;
    for (uint8_t i=0; i<items.size(); i++) {
        items[i]->setVisible(true);
        mHeight += items[i]->getHeight() + mRowSpacing;
    }
    mExpanded = true;
    mGuiFooter->setPositionY(mPosition.y + mHeight - mGuiFooter->getHeight() - mRowSpacing);
}

void ofxDatGui::collapseGui()
{
    for (uint8_t i=0; i<items.size()-1; i++) items[i]->setVisible(false);
    mGuiFooter->setPositionY(mPosition.y);
    mExpanded = false;
    mHeight = mGuiFooter->getHeight();
}

/* event handlers & update / draw loop */

void ofxDatGui::onMousePressed(ofMouseEventArgs &e)
{
    if (mDisabled || !mVisible) return;
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
    if (mDisabled || !mVisible) return;
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
    if (mDisabled || !mVisible) return;
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
    if (e.key == 'h' && disableShowAndHide == false) mVisible = !mVisible;
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

void ofxDatGui::update()
{
    if (mDisabled || !mVisible) return;
    if (mAlphaChanged) setGuiAlpha();
    if (mWidthChanged) setGuiWidth();
    if (mAlignmentChanged) setGuiAlignment();
    
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
// empty the trash //
    for (int i=0; i<trash.size(); i++) delete trash[i];
    trash.clear();
}

void ofxDatGui::setGuiAlpha()
{
    for (int i=0; i<items.size(); i++) items[i]->setOpacity(mAlpha);
    mAlphaChanged = false;
}

void ofxDatGui::setGuiWidth()
{
    for (int i=0; i<items.size(); i++) items[i]->setWidth(mWidth);
    layoutGui();
    mWidthChanged = false;
}

void ofxDatGui::setGuiAlignment()
{
    for (int i=0; i<items.size(); i++) items[i]->setAlignment(mAlignment);
    mAlignmentChanged = false;
}

void ofxDatGui::draw()
{
    if (mVisible == false) return;
    ofPushStyle();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ofSetColor(ofxDatGuiColor::GUI_BKGD, mAlpha * 255);
        ofDrawRectangle(mPosition.x, mPosition.y, mWidth, mHeight - mRowSpacing);
        if (mExpanded == false){
            mGuiFooter->draw();
        }   else{
            for (int i=0; i<items.size(); i++) items[i]->draw();
        // color pickers overlap other components when expanded so they must be drawn last //
            for (int i=0; i<items.size(); i++) items[i]->drawColorPicker();
        }
    ofPopStyle();
}

void ofxDatGui::onDraw(ofEventArgs &e) { draw(); }
void ofxDatGui::onUpdate(ofEventArgs &e) { update(); }

void ofxDatGui::onWindowResized(ofResizeEventArgs &e)
{
    if (mAnchor == ofxDatGuiAnchor::TOP_RIGHT) anchorGui();
}

void ofxDatGui::anchorGui()
{
    mPosition.x = ofGetWidth() - mWidth;
    for (int i=0; i<items.size(); i++) items[i]->setOrigin(mPosition.x, mPosition.y);
}

