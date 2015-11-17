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
#include "ofxDatGuiTemplate.h"

ofxDatGui* ofxDatGui::mActiveGui;
vector<ofxDatGui*> ofxDatGui::mGuis;

ofxDatGui::ofxDatGui(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    init();
}

ofxDatGui::ofxDatGui(ofxDatGuiAnchor anchor)
{
    init();
    mAnchor = anchor;
    anchorGui();
}

void ofxDatGui::init()
{
    mMoving = false;
    mVisible = true;
    mEnabled = true;
    mExpanded = true;
    mGuiHeader = nullptr;
    mGuiFooter = nullptr;
    mAlphaChanged = false;
    mWidthChanged = false;
    mTemplateChanged = false;
    mAlignmentChanged = false;
    mAlignment = ofxDatGuiAlignment::LEFT;
    
// load a default layout template //
    if (ofxDatGuiIsRetina()){
        mTemplate = ofxDatGui2880x1800::get();
    }   else{
        mTemplate = ofxDatGui1440x900::get();
    }
    mAlpha = 1.0f;
    mWidth = mTemplate->row.width;
    mRowSpacing = mTemplate->row.spacing;
    
// enable autodraw by default //
    setAutoDraw(true);
    
// assign focus to this newly created gui //
    mActiveGui = this;
    mGuis.push_back(this);
    mGuid = mGuis.size();
    ofAddListener(ofEvents().windowResized, this, &ofxDatGui::onWindowResized, OF_EVENT_ORDER_BEFORE_APP);
}

/* 
    public getters & setters
*/

bool ofxDatGui::isMoving()
{
    return mMoving;
}

void ofxDatGui::focus()
{
    if (mActiveGui!= this){
    // enable and make visible if hidden //
        mVisible = true;
        mEnabled = true;
        mActiveGui = this;
    // update the draw order //
        for (int i=0; i<mGuis.size(); i++) {
            if (mGuis[i] == mActiveGui) {
                std::swap(mGuis[i], mGuis[mGuis.size()-1]);
                break;
            }
        }
        for (int i=0; i<mGuis.size(); i++) {
            if (mGuis[i]->getAutoDraw()) mGuis[i]->setAutoDraw(true, i);
        }
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::PANEL_ALREADY_HAS_FOCUS, "#"+ofToString(mGuid));
    }
}

bool ofxDatGui::getVisible()
{
    return mVisible;
}

bool ofxDatGui::getFocused()
{
    return mActiveGui == this;
}

void ofxDatGui::setWidth(int width)
{
    mWidth = width;
    mWidthChanged = true;
    if (mAnchor != ofxDatGuiAnchor::NO_ANCHOR) anchorGui();
}

void ofxDatGui::setTemplate(ofxDatGuiTemplate* t)
{
    mTemplate = t;
    setWidth(mTemplate->row.width);
    mRowSpacing = mTemplate->row.spacing;
    mTemplateChanged = true;
}

void ofxDatGui::setOrigin(int x, int y)
{
    moveGui(ofPoint(x, y));
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

void ofxDatGui::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

void ofxDatGui::setAutoDraw(bool autodraw, int priority)
{
    mAutoDraw = autodraw;
    ofRemoveListener(ofEvents().draw, this, &ofxDatGui::onDraw);
    ofRemoveListener(ofEvents().update, this, &ofxDatGui::onUpdate);
    if (autodraw){
        ofAddListener(ofEvents().draw, this, &ofxDatGui::onDraw, OF_EVENT_ORDER_AFTER_APP + priority);
        ofAddListener(ofEvents().update, this, &ofxDatGui::onUpdate, OF_EVENT_ORDER_AFTER_APP + priority);
    }
}

bool ofxDatGui::getAutoDraw()
{
    return mAutoDraw;
}

void ofxDatGui::setAlignment(ofxDatGuiAlignment align)
{
    mAlignment = align;
    mAlignmentChanged = true;
}

int ofxDatGui::getWidth()
{
    return mWidth;
}

int ofxDatGui::getHeight()
{
    return mHeight;
}

ofPoint ofxDatGui::getPosition()
{
    return ofPoint(mPosition.x, mPosition.y);
}

/* 
    add component methods
*/

ofxDatGuiHeader* ofxDatGui::addHeader(string label, bool draggable)
{
    if (mGuiHeader == nullptr){
        mGuiHeader = new ofxDatGuiHeader(label, draggable, mTemplate);
        if (items.size() == 0){
            items.push_back(mGuiHeader);
        }   else{
    // always ensure header is at the top of the panel //
            items.insert(items.begin(), mGuiHeader);
        }
        layoutGui();
	}
    return mGuiHeader;
}

ofxDatGuiFooter* ofxDatGui::addFooter()
{
    if (mGuiFooter == nullptr){
        mGuiFooter = new ofxDatGuiFooter(mTemplate);
        items.push_back(mGuiFooter);
        mGuiFooter->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
        layoutGui();
	}
    return mGuiFooter;
}

ofxDatGuiLabel* ofxDatGui::addLabel(string label)
{
    ofxDatGuiLabel* lbl = new ofxDatGuiLabel(label, mTemplate);
    attachItem(lbl);
    return lbl;
}

ofxDatGuiButton* ofxDatGui::addButton(string label)
{
    ofxDatGuiButton* button = new ofxDatGuiButton(label, mTemplate);
    button->onButtonEvent(this, &ofxDatGui::onButtonEventCallback);
    attachItem(button);
    return button;
}

ofxDatGuiToggle* ofxDatGui::addToggle(string label, bool enabled)
{
    ofxDatGuiToggle* button = new ofxDatGuiToggle(label, enabled, mTemplate);
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
    ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val, mTemplate);
    slider->onSliderEvent(this, &ofxDatGui::onSliderEventCallback);
    attachItem(slider);
    return slider;
}

ofxDatGuiIntSlider* ofxDatGui::addIntSlider(string label, int min, int max)
{
    // default to halfway between min & max values //
    ofxDatGuiIntSlider* slider = addIntSlider(label, min, max, (max+min)/2);
    return slider;
}

ofxDatGuiIntSlider* ofxDatGui::addIntSlider(string label, int min, int max, int val)
{
    ofxDatGuiIntSlider* slider = new ofxDatGuiIntSlider(label, min, max, val, mTemplate);
    slider->onIntSliderEvent(this, &ofxDatGui::onIntSliderEventCallback);
    attachItem(slider);
    return slider;
}

ofxDatGuiTextInput* ofxDatGui::addTextInput(string label, string value)
{
    ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value, mTemplate);
    input->onTextInputEvent(this, &ofxDatGui::onTextInputEventCallback);
    attachItem(input);
    return input;
}

ofxDatGuiColorPicker* ofxDatGui::addColorPicker(string label, ofColor color)
{
    ofxDatGuiColorPicker* picker = new ofxDatGuiColorPicker(label, color, mTemplate);
    picker->onColorPickerEvent(this, &ofxDatGui::onColorPickerEventCallback);
    attachItem(picker);
    return picker;
}

ofxDatGuiWaveMonitor* ofxDatGui::addWaveMonitor(string label, float frequency, float amplitude)
{
    ofxDatGuiWaveMonitor* monitor = new ofxDatGuiWaveMonitor(label, frequency, amplitude, mTemplate);
    attachItem(monitor);
    return monitor;
}

ofxDatGuiValuePlotter* ofxDatGui::addValuePlotter(string label, float min, float max)
{
    ofxDatGuiValuePlotter* plotter = new ofxDatGuiValuePlotter(label, min, max, mTemplate);
    attachItem(plotter);
    return plotter;
}

ofxDatGuiDropdown* ofxDatGui::addDropdown(string label, vector<string> options)
{
    ofxDatGuiDropdown* dropdown = new ofxDatGuiDropdown(label, options, mTemplate);
    dropdown->onDropdownEvent(this, &ofxDatGui::onDropdownEventCallback);
    attachItem(dropdown);
    return dropdown;
}

ofxDatGuiFRM* ofxDatGui::addFRM(float refresh)
{
    ofxDatGuiFRM* monitor = new ofxDatGuiFRM(refresh, mTemplate);
    attachItem(monitor);
    return monitor;
}

ofxDatGuiBreak* ofxDatGui::addBreak(int height)
{
    ofxDatGuiBreak* brk = new ofxDatGuiBreak(height, mTemplate);
    attachItem(brk);
    return brk;
}

ofxDatGui2dPad* ofxDatGui::add2dPad(string label)
{
    ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, mTemplate);
    pad->on2dPadEvent(this, &ofxDatGui::on2dPadEventCallback);
    attachItem(pad);
    return pad;
}

ofxDatGui2dPad* ofxDatGui::add2dPad(string label, ofRectangle bounds)
{
    ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, bounds, mTemplate);
    pad->on2dPadEvent(this, &ofxDatGui::on2dPadEventCallback);
    attachItem(pad);
    return pad;
}

ofxDatGuiMatrix* ofxDatGui::addMatrix(string label, int numButtons, bool showLabels)
{
    ofxDatGuiMatrix* matrix = new ofxDatGuiMatrix(label, numButtons, showLabels, mTemplate);
    matrix->onMatrixEvent(this, &ofxDatGui::onMatrixEventCallback);
    attachItem(matrix);
    return matrix;
}

ofxDatGuiFolder* ofxDatGui::addFolder(string label, ofColor color)
{
    ofxDatGuiFolder* folder = new ofxDatGuiFolder(label, color, mTemplate);
    folder->onButtonEvent(this, &ofxDatGui::onButtonEventCallback);
    folder->onSliderEvent(this, &ofxDatGui::onSliderEventCallback);
    folder->onIntSliderEvent(this, &ofxDatGui::onIntSliderEventCallback);
    folder->on2dPadEvent(this, &ofxDatGui::on2dPadEventCallback);
    folder->onMatrixEvent(this, &ofxDatGui::onMatrixEventCallback);
    folder->onTextInputEvent(this, &ofxDatGui::onTextInputEventCallback);
    folder->onColorPickerEvent(this, &ofxDatGui::onColorPickerEventCallback);
    folder->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
    attachItem(folder);
    return folder;
}

void ofxDatGui::attachItem(ofxDatGuiComponent* item)
{
    if (mGuiFooter != nullptr){
        items.insert(items.end()-1, item);
    }   else {
        items.push_back( item );
    }
    item->onInternalEvent(this, &ofxDatGui::onInternalEventCallback);
    layoutGui();
}

/*
    component retrieval methods
*/

ofxDatGuiButton* ofxDatGui::getButton(string bl, string fl)
{
    ofxDatGuiButton* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiButton*>(f->getComponent(ofxDatGuiType::BUTTON, bl));
    }   else{
        o = static_cast<ofxDatGuiButton*>(getComponent(ofxDatGuiType::BUTTON, bl));
    }
    if (o==nullptr){
        o = ofxDatGuiButton::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+bl : bl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiSlider* ofxDatGui::getSlider(string sl, string fl)
{
    ofxDatGuiSlider* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiSlider*>(f->getComponent(ofxDatGuiType::SLIDER, sl));
    }   else{
        o = static_cast<ofxDatGuiSlider*>(getComponent(ofxDatGuiType::SLIDER, sl));
    }
    if (o==nullptr){
        o = ofxDatGuiSlider::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+sl : sl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiIntSlider* ofxDatGui::getIntSlider(string sl, string fl)
{
    ofxDatGuiIntSlider* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiIntSlider*>(f->getComponent(ofxDatGuiType::INTSLIDER, sl));
    }   else{
        o = static_cast<ofxDatGuiIntSlider*>(getComponent(ofxDatGuiType::INTSLIDER, sl));
    }
    if (o==nullptr){
        o = ofxDatGuiIntSlider::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+sl : sl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiTextInput* ofxDatGui::getTextInput(string tl, string fl)
{
    ofxDatGuiTextInput* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiTextInput*>(f->getComponent(ofxDatGuiType::TEXT_INPUT, tl));
    }   else{
        o = static_cast<ofxDatGuiTextInput*>(getComponent(ofxDatGuiType::TEXT_INPUT, tl));
    }
    if (o==nullptr){
        o = ofxDatGuiTextInput::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+tl : tl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGui2dPad* ofxDatGui::get2dPad(string pl, string fl)
{
    ofxDatGui2dPad* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGui2dPad*>(f->getComponent(ofxDatGuiType::PAD2D, pl));
    }   else{
        o = static_cast<ofxDatGui2dPad*>(getComponent(ofxDatGuiType::PAD2D, pl));
    }
    if (o==nullptr){
        o = ofxDatGui2dPad::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+pl : pl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiColorPicker* ofxDatGui::getColorPicker(string cl, string fl)
{
    ofxDatGuiColorPicker* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiColorPicker*>(f->getComponent(ofxDatGuiType::COLOR_PICKER, cl));
    }   else{
        o = static_cast<ofxDatGuiColorPicker*>(getComponent(ofxDatGuiType::COLOR_PICKER, cl));
    }
    if (o==nullptr){
        o = ofxDatGuiColorPicker::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+cl : cl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiWaveMonitor* ofxDatGui::getWaveMonitor(string cl, string fl)
{
    ofxDatGuiWaveMonitor* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiWaveMonitor*>(f->getComponent(ofxDatGuiType::WAVE_MONITOR, cl));
    }   else{
        o = static_cast<ofxDatGuiWaveMonitor*>(getComponent(ofxDatGuiType::WAVE_MONITOR, cl));
    }
    if (o==nullptr){
        o = ofxDatGuiWaveMonitor::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+cl : cl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiValuePlotter* ofxDatGui::getValuePlotter(string cl, string fl)
{
    ofxDatGuiValuePlotter* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiValuePlotter*>(f->getComponent(ofxDatGuiType::VALUE_PLOTTER, cl));
    }   else{
        o = static_cast<ofxDatGuiValuePlotter*>(getComponent(ofxDatGuiType::VALUE_PLOTTER, cl));
    }
    if (o==nullptr){
        o = ofxDatGuiValuePlotter::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+cl : cl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiMatrix* ofxDatGui::getMatrix(string ml, string fl)
{
    ofxDatGuiMatrix* o = nullptr;
    if (fl != ""){
        ofxDatGuiFolder* f = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
        if (f) o = static_cast<ofxDatGuiMatrix*>(f->getComponent(ofxDatGuiType::MATRIX, ml));
    }   else{
        o = static_cast<ofxDatGuiMatrix*>(getComponent(ofxDatGuiType::MATRIX, ml));
    }
    if (o==nullptr){
        o = ofxDatGuiMatrix::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl!="" ? fl+"-"+ml : ml);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiDropdown* ofxDatGui::getDropdown(string dl)
{
    ofxDatGuiDropdown* o = static_cast<ofxDatGuiDropdown*>(getComponent(ofxDatGuiType::DROPDOWN, dl));
    if (o==NULL){
        o = ofxDatGuiDropdown::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, dl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiFolder* ofxDatGui::getFolder(string fl)
{
    ofxDatGuiFolder* o = static_cast<ofxDatGuiFolder*>(getComponent(ofxDatGuiType::FOLDER, fl));
    if (o==NULL){
        o = ofxDatGuiFolder::getInstance();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, fl);
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiHeader* ofxDatGui::getHeader()
{
    ofxDatGuiHeader* o;
    if (mGuiHeader != nullptr){
        o = mGuiHeader;
    }   else{
        o = new ofxDatGuiHeader("X");
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, "HEADER");
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiFooter* ofxDatGui::getFooter()
{
    ofxDatGuiFooter* o;
    if (mGuiFooter != nullptr){
        o = mGuiFooter;
    }   else{
        o = new ofxDatGuiFooter();
        ofxDatGuiLog::write(ofxDatGuiMsg::COMPONENT_NOT_FOUND, "FOOTER");
        trash.push_back(o);
    }
    return o;
}

ofxDatGuiComponent* ofxDatGui::getComponent(ofxDatGuiType type, string label)
{
    for (int i=0; i<items.size(); i++) {
        if (items[i]->getType() == type){
            if (items[i]->is(label)) return items[i];
        }
    // iterate over component's children and return the first match we find //
        for (int j=0; j<items[i]->children.size(); j++) {
            if (items[i]->children[j]->is(label)) return items[i]->children[j];
        }
    }
    return NULL;
}

/*
    event callbacks
*/

void ofxDatGui::onButtonEventCallback(ofxDatGuiButtonEvent e)
{
    if (buttonEventCallback != nullptr) {
        buttonEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onSliderEventCallback(ofxDatGuiSliderEvent e)
{
    if (sliderEventCallback != nullptr) {
        sliderEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onIntSliderEventCallback(ofxDatGuiIntSliderEvent e)
{
    if (intSliderEventCallback != nullptr) {
        intSliderEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onTextInputEventCallback(ofxDatGuiTextInputEvent e)
{
    if (textInputEventCallback != nullptr) {
        textInputEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onDropdownEventCallback(ofxDatGuiDropdownEvent e)
{
    if (dropdownEventCallback != nullptr) {
        dropdownEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
// adjust the gui after a dropdown is closed //
    layoutGui();
}

void ofxDatGui::on2dPadEventCallback(ofxDatGui2dPadEvent e)
{
    if (pad2dEventCallback != nullptr) {
        pad2dEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onColorPickerEventCallback(ofxDatGuiColorPickerEvent e)
{
    if (colorPickerEventCallback != nullptr) {
        colorPickerEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onMatrixEventCallback(ofxDatGuiMatrixEvent e)
{
    if (matrixEventCallback != nullptr) {
        matrixEventCallback(e);
    }   else{
        ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
    }
}

void ofxDatGui::onInternalEventCallback(ofxDatGuiInternalEvent e)
{
// these events are not dispatched out to the main application //
    if (e.type == ofxDatGuiEventType::DROPDOWN_TOGGLED){
        layoutGui();
    }   else if (e.type == ofxDatGuiEventType::GUI_TOGGLED){
        mExpanded ? collapseGui() : expandGui();
    }   else if (e.type == ofxDatGuiEventType::VISIBILITY_CHANGED){
        layoutGui();
    }
}

/*
    layout, position, anchor and check for focus
*/

bool ofxDatGui::hitTest(ofPoint pt)
{
    if (mMoving){
        return true;
    }   else{
        return mGuiBounds.inside(pt);
    }
}

void ofxDatGui::moveGui(ofPoint pt)
{
    mPosition.x = pt.x;
    mPosition.y = pt.y;
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    layoutGui();
}

void ofxDatGui::anchorGui()
{
    mPosition.y = 0;
    if (mAnchor == ofxDatGuiAnchor::TOP_LEFT){
        mPosition.x = 0;
    }   else if (mAnchor == ofxDatGuiAnchor::TOP_RIGHT){
        mPosition.x = ofGetWidth() - mWidth;
    }
    layoutGui();
}

void ofxDatGui::layoutGui()
{
    mHeight = 0;
    for (int i=0; i<items.size(); i++) {
        items[i]->setIndex(i);
    // skip over any components that are currently invisible //
        if (items[i]->getVisible() == false) continue;
        items[i]->setOrigin(mPosition.x, mPosition.y + mHeight);
        mHeight += items[i]->getHeight() + mRowSpacing;
    }
    // move the footer back to the top of the gui //
    if (!mExpanded) mGuiFooter->setY(mPosition.y);
    mGuiBounds = ofRectangle(mPosition.x, mPosition.y, mWidth, mHeight);
}

void ofxDatGui::expandGui()
{
    mExpanded = true;
    mGuiFooter->setY(mPosition.y + mHeight - mGuiFooter->getHeight() - mRowSpacing);
}

void ofxDatGui::collapseGui()
{
    mExpanded = false;
    mGuiFooter->setY(mPosition.y);
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

void ofxDatGui::setGuiTemplate()
{
    for (int i=0; i<items.size(); i++) items[i]->setTemplate(mTemplate);
    layoutGui();
    mTemplateChanged = false;
}

void ofxDatGui::setGuiAlignment()
{
    for (int i=0; i<items.size(); i++) items[i]->setAlignment(mAlignment);
    mAlignmentChanged = false;
}

/* 
    update & draw loop
*/

void ofxDatGui::update()
{
    if (!mVisible) return;

    if (mAlphaChanged) setGuiAlpha();
    if (mTemplateChanged) setGuiTemplate();
    if (mWidthChanged) setGuiWidth();
    if (mAlignmentChanged) setGuiAlignment();
    
    // first check for gui focus change //
    if (ofGetMousePressed() && mActiveGui->isMoving() == false){
        ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
        for (int i=mGuis.size()-1; i>-1; i--){
        // ignore guis that are invisible //
            if (mGuis[i]->getVisible() && mGuis[i]->hitTest(mouse)){
                if (mGuis[i] != mActiveGui) mGuis[i]->focus();
                break;
            }
        }
    }

    if (!getFocused() || !mEnabled){
    // update children but ignore mouse & keyboard events //
        for (int i=0; i<items.size(); i++) items[i]->update(false);
    }   else {
        mMoving = false;
    // this gui has focus so let's see if any of its components were interacted with //
        if (mExpanded == false){
            mGuiFooter->update();
        }   else{
            int activeItemIndex = -1;
            for (int i=0; i<items.size(); i++) {
                items[i]->update();
                if (items[i]->getFocused()) {
                    activeItemIndex = i;
                    if (mGuiHeader != nullptr && mGuiHeader->getDraggable() && mGuiHeader->getPressed()){
                // track that we're moving to force preserve focus //
                        mMoving = true;
                        ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
                        moveGui(mouse - mGuiHeader->dragOffset);
                    }
                    break;
                }   else if (items[i]->getIsExpanded()){
                // check if one of its children has focus //
                    for (int j=0; j<items[i]->children.size(); j++) {
                        if (items[i]->children[j]->getFocused()){
                            activeItemIndex = i;
                            break;
                        }
                    }
                    if (activeItemIndex != -1) break;
                }
            }
        // update the remaining components //
            if (activeItemIndex != -1){
                for (int i=activeItemIndex + 1; i<items.size(); i++) {
        //  but tell them to ignore mouse & keyboard events since we're already determined the active component //
                    items[i]->update(false);
                    if (items[i]->getFocused()) items[i]->setFocused(false);
                }
            }
        }
    }
    
// empty the trash //
    for (int i=0; i<trash.size(); i++) delete trash[i];
    trash.clear();
}

void ofxDatGui::draw()
{
    if (mVisible == false) return;
    ofPushStyle();
        ofFill();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ofSetColor(mTemplate->gui.color.bkgd, mAlpha * 255);
        if (mExpanded == false){
            ofDrawRectangle(mPosition.x, mPosition.y, mWidth, mGuiFooter->getHeight());
            mGuiFooter->draw();
        }   else{
            ofDrawRectangle(mPosition.x, mPosition.y, mWidth, mHeight - mRowSpacing);
            for (int i=0; i<items.size(); i++) items[i]->draw();
        // color pickers overlap other components when expanded so they must be drawn last //
            for (int i=0; i<items.size(); i++) items[i]->drawColorPicker();
        }
    ofPopStyle();
}

void ofxDatGui::onDraw(ofEventArgs &e)
{
    draw();
}

void ofxDatGui::onUpdate(ofEventArgs &e)
{
    update();
}

void ofxDatGui::onWindowResized(ofResizeEventArgs &e)
{
    if (mAnchor != ofxDatGuiAnchor::NO_ANCHOR) anchorGui();
}


