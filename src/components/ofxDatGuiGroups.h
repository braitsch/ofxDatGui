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

#pragma once
#include "ofxDatGuiLabel.h"
#include "ofxDatGuiButton.h"
#include "ofxDatGuiSlider.h"
#include "ofxDatGuiTextInput.h"
#include "ofxDatGuiFRM.h"
#include "ofxDatGui2dPad.h"
#include "ofxDatGuiColorPicker.h"
#include "ofxDatGuiMatrix.h"
#include "ofxDatGuiTimeGraph.h"

class ofxDatGuiGroup : public ofxDatGuiButton {

    public:
    
        ofxDatGuiGroup(string label, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiButton(label, tmplt)
        {
            mIsExpanded = false;
            if (mImage.isAllocated() == false) mImage.load(OFXDG_ASSET_DIR+"/icon-dropdown.png");
        }
    
        int getHeight()
        {
            return mHeight;
        }
    
        bool getIsExpanded()
        {
            return mIsExpanded;
        }
    
        void setWidth(int w)
        {
            ofxDatGuiComponent::setWidth(w);
            mLabelMarginRight = mRow.width-mIcon.x;
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            layout();
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
                ofSetColor(mTemplate->row.color.label);
                mImage.draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
            if (mIsExpanded) {
                int mHeight = mRow.height;
                ofSetColor(mTemplate->gui.color.bkgd, mAlpha);
                ofDrawRectangle(x, y+mHeight, mRow.width, mRow.spacing);
                for(int i=0; i<children.size(); i++) {
                    mHeight += mRow.spacing;
                    children[i]->draw();
                    mHeight += children[i]->getHeight();
                    if (i == children.size()-1) break;
                    ofSetColor(mTemplate->gui.color.bkgd, mAlpha);
                    ofDrawRectangle(x, y+mHeight, mRow.width, mRow.spacing);
                }
                for(int i=0; i<children.size(); i++) children[i]->drawColorPicker();
            }
            ofPopStyle();
        }
    
        void onMouseRelease(ofPoint m)
        {
            if (mFocused){
            // open & close the group when its header is clicked //
                ofxDatGuiComponent::onMouseRelease(m);
                mIsExpanded ? collapse() : expand();
            // dispatch an event out to the gui panel to adjust its children //
                if (internalEventCallback != nullptr){
                    ofxDatGuiInternalEvent e(ofxDatGuiEventType::DROPDOWN_TOGGLED, mIndex);
                    internalEventCallback(e);
                }
            }
        }
    
        void expand()
        {
            mIsExpanded = true;
            layout();
        }
    
        void collapse()
        {
            mIsExpanded = false;
            layout();
        }
    
        void layout()
        {
            mHeight = mRow.height + mRow.spacing;
            for (int i=0; i<children.size(); i++) {
                if (children[i]->getVisible() == false) continue;
                if (mIsExpanded == false){
                    children[i]->setOrigin(x, y + mHeight);
                }   else{
                    children[i]->setOrigin(x, y + mHeight);
                    mHeight += children[i]->getHeight() + mRow.spacing;
                }
            }
        }
    
        void dispatchInternalEvent(ofxDatGuiInternalEvent e)
        {
            if (e.type == ofxDatGuiEventType::VISIBILITY_CHANGED) layout();
            internalEventCallback(e);
        }
    
    protected:
    
        int mHeight;
        ofImage mImage;
        bool mIsExpanded;
    
};

class ofxDatGuiFolder : public ofxDatGuiGroup{

    public:
    
        ofxDatGuiFolder(string label, ofColor color=ofColor::white, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiGroup(label, tmplt)
        {
    // all items within a folder share the same stripe color //
            mStripeColor = color;
            mType = ofxDatGuiType::OFXDATGUI_FOLDER;
        }
    
        static ofxDatGuiFolder* getInstance()
        {
            return new ofxDatGuiFolder("X");
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiGroup::setTemplate(tmplt);
            for (int i=0; i<children.size(); i++) children[i]->setTemplate(mTemplate);
            setWidth(mRow.width);
        }
    
        void drawColorPicker()
        {
            for(int i=0; i<pickers.size(); i++) pickers[i]->drawColorPicker();
        }
    
        void dispatchButtonEvent(ofxDatGuiButtonEvent e)
        {
            if (buttonEventCallback != nullptr) {
                buttonEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchSliderEvent(ofxDatGuiSliderEvent e)
        {
            if (sliderEventCallback != nullptr) {
                sliderEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchTextInputEvent(ofxDatGuiTextInputEvent e)
        {
            if (textInputEventCallback != nullptr) {
                textInputEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchColorPickerEvent(ofxDatGuiColorPickerEvent e)
        {
            if (colorPickerEventCallback != nullptr) {
                colorPickerEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatch2dPadEvent(ofxDatGui2dPadEvent e)
        {
            if (pad2dEventCallback != nullptr) {
                pad2dEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchMatrixEvent(ofxDatGuiMatrixEvent e)
        {
            if (matrixEventCallback != nullptr) {
                matrixEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }

    /*
        component add methods
    */

        ofxDatGuiLabel* addLabel(string label)
        {
            ofxDatGuiLabel* lbl = new ofxDatGuiLabel(label, mTemplate);
            lbl->setStripeColor(mStripeColor);
            attachItem(lbl);
            return lbl;
        }

        ofxDatGuiButton* addButton(string label)
        {
            ofxDatGuiButton* button = new ofxDatGuiButton(label, mTemplate);
            button->setStripeColor(mStripeColor);
            button->onButtonEvent(this, &ofxDatGuiFolder::dispatchButtonEvent);
            attachItem(button);
            return button;
        }
    
        ofxDatGuiButton* addToggle(string label, bool enabled = false)
        {
            ofxDatGuiToggle* toggle = new ofxDatGuiToggle(label, enabled, mTemplate);
            toggle->setStripeColor(mStripeColor);
            toggle->onButtonEvent(this, &ofxDatGuiFolder::dispatchButtonEvent);
            attachItem(toggle);
            return toggle;
        }
    
        ofxDatGuiSlider* addSlider(string label, float min, float max)
        {
        // default to halfway between min & max values //
            ofxDatGuiSlider* slider = addSlider(label, min, max, (max+min)/2);
            return slider;
        }

        ofxDatGuiSlider* addSlider(string label, float min, float max, float val)
        {
            ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val, mTemplate);
            slider->setStripeColor(mStripeColor);
            slider->onSliderEvent(this, &ofxDatGuiFolder::dispatchSliderEvent);
            attachItem(slider);
            return slider;
        }
    
        ofxDatGuiTextInput* addTextInput(string label, string value)
        {
            ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value, mTemplate);
            input->setStripeColor(mStripeColor);
            input->onTextInputEvent(this, &ofxDatGuiFolder::dispatchTextInputEvent);
            attachItem(input);
            return input;
        }
    
        ofxDatGuiColorPicker* addColorPicker(string label, ofColor color = ofColor::black)
        {
            shared_ptr<ofxDatGuiColorPicker> picker(new ofxDatGuiColorPicker(label, color, mTemplate));
            picker->setStripeColor(mStripeColor);
            picker->onColorPickerEvent(this, &ofxDatGuiFolder::dispatchColorPickerEvent);
            attachItem(picker.get());
            pickers.push_back(picker);
            return picker.get();
        }
    
        ofxDatGuiFRM* addFRM(float refresh = 1.0f)
        {
            ofxDatGuiFRM* monitor = new ofxDatGuiFRM(refresh, mTemplate);
            monitor->setStripeColor(mStripeColor);
            attachItem(monitor);
            return monitor;
        }

        ofxDatGuiBreak* addBreak(int height = 0)
        {
            ofxDatGuiBreak* brk = new ofxDatGuiBreak(height, mTemplate);
            attachItem(brk);
            return brk;
        }
    
        ofxDatGui2dPad* add2dPad(string label)
        {
            ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, mTemplate);
            pad->setStripeColor(mStripeColor);
            pad->on2dPadEvent(this, &ofxDatGuiFolder::dispatch2dPadEvent);
            attachItem(pad);
            return pad;
        }

        ofxDatGuiMatrix* addMatrix(string label, int numButtons, bool showLabels = false)
        {
            ofxDatGuiMatrix* matrix = new ofxDatGuiMatrix(label, numButtons, showLabels, mTemplate);
            matrix->setStripeColor(mStripeColor);
            matrix->onMatrixEvent(this, &ofxDatGuiFolder::dispatchMatrixEvent);
            attachItem(matrix);
            return matrix;
        }
    
        ofxDatGuiWaveMonitor* addWaveMonitor(string label, float frequency, float amplitude)
        {
            ofxDatGuiWaveMonitor* monitor = new ofxDatGuiWaveMonitor(label, frequency, amplitude, mTemplate);
            monitor->setStripeColor(mStripeColor);
            attachItem(monitor);
            return monitor;
        }
    
        ofxDatGuiValuePlotter* addValuePlotter(string label, float min, float max)
        {
            ofxDatGuiValuePlotter* plotter = new ofxDatGuiValuePlotter(label, min, max, mTemplate);
            plotter->setStripeColor(mStripeColor);
            attachItem(plotter);
            return plotter;
        }
    
        void attachItem(ofxDatGuiComponent* item)
        {
            item->setIndex(children.size());
            item->onInternalEvent(this, &ofxDatGuiFolder::dispatchInternalEvent);
            children.push_back(item);
        }
    
        ofxDatGuiComponent* getComponent(ofxDatGuiType type, string label)
        {
            for (int i=0; i<children.size(); i++) {
                if (children[i]->getType() == type){
                    if (children[i]->is(label)) return children[i];
                }
            }
            return NULL;
        }

    private:
    
        vector<shared_ptr<ofxDatGuiColorPicker>> pickers;
    
};

class ofxDatGuiDropdownOption : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdownOption(string label, ofxDatGuiTemplate* tmplt) : ofxDatGuiButton(label, tmplt)
        {
            mLabelRect = mFont->getStringBoundingBox("* "+mLabel, 0, 0);
            mStripeColor = mTemplate->dropdown.color.stripe;
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiComponent::drawLabel("* "+mLabel);
            ofxDatGuiComponent::drawStripe();
        }

};

class ofxDatGuiDropdown : public ofxDatGuiGroup {

    public:

        ofxDatGuiDropdown(string label, const vector<string>& options = vector<string>(), ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiGroup(label, tmplt)
        {
            mOption = 0;
            mType = ofxDatGuiType::OFXDATGUI_DROPDOWN;
            mStripeColor = mTemplate->dropdown.color.stripe;
            for(int i=0; i<options.size(); i++){
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(options[i], mTemplate);
                opt->setIndex(children.size());
                opt->onButtonEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                children.push_back(opt);
            }
        }
    
        static ofxDatGuiDropdown* getInstance()
        {
            return new ofxDatGuiDropdown("X");
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiGroup::setTemplate(tmplt);
            for (int i=0; i<children.size(); i++) children[i]->setTemplate(mTemplate);
            setWidth(mRow.width);
        }
    
        void select(int cIndex)
        {
        // ensure value is in range //
            if (cIndex < 0 || cIndex >= children.size()){
                ofLogError() << "ofxDatGuiDropdown->select("<<cIndex<<") is out of range";
            }   else{
                setLabel(children[cIndex]->getLabel());
            }
        }

        int size()
        {
            return children.size();
        }
    
        ofxDatGuiDropdownOption* getChildAt(int index)
        {
            return static_cast<ofxDatGuiDropdownOption*>(children[index]);
        }
    
        ofxDatGuiDropdownOption* getSelected()
        {
            return static_cast<ofxDatGuiDropdownOption*>(children[mOption]);
        }
    
        void onOptionSelected(ofxDatGuiButtonEvent e)
        {
            for(int i=0; i<children.size(); i++) if (e.target == children[i]) mOption = i;
            setLabel(children[mOption]->getLabel());
            collapse();
            if (dropdownEventCallback != nullptr) {
                ofxDatGuiDropdownEvent e1(this, mIndex, mOption);
                dropdownEventCallback(e1);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
    private:
        int mOption;
    
};


