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

class ofxDatGuiGroup : public ofxDatGuiButton {

    public:
    
        ofxDatGuiGroup(string label, ofxDatGuiFont* font) : ofxDatGuiButton(label, font)
        {
            mIsExpanded = false;
            mChildrenHeight = 0;
            if (mImage.isAllocated() == false) mImage.load(ofxDatGuiAssetDir+"/icon-dropdown.png");
        }
    
        void setWidth(int w)
        {
            ofxDatGuiItem::setWidth(w);
            mLabelMarginRight = mRow.width-mIcon.x;
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiItem::setOrigin(x, y);
            int ypos = mRow.height + mRow.spacing;
            for(int i=0; i<children.size(); i++){
                if (mIsExpanded){
                    children[i]->setOrigin(x, y + (ypos*(i+1)));
                }   else{
                    children[i]->setOrigin(x, y);
                }
            }
        }
    
        void setPositionY(int y)
        {
            ofxDatGuiItem::setPositionY(y);
            int ypos = mRow.height + mRow.spacing;
            for(int i=0; i<children.size(); i++) {
                if (mIsExpanded){
                    children[i]->setPositionY(y + (ypos*(i+1)));
                }   else{
                    children[i]->setPositionY(y);
                }
            }
        }
    
        int getHeight()
        {
            if (!mIsExpanded){
                return mRow.height;
            }   else{
                return mRow.height + mChildrenHeight;
            }
        }
    
        bool getIsExpanded()
        {
            return mIsExpanded;
        }
    
        void draw()
        {
            ofPushStyle();
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiItem::drawLabel();
                ofxDatGuiItem::drawStripe();
                ofSetColor(ofxDatGuiColor::LABEL);
                mImage.draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
            if (mIsExpanded) {
//                ofSetColor(ofxDatGuiColor::GUI_BKGD, mAlpha);
//                int ypos = y + mRow.height;
//                ofDrawRectangle(x, ypos, mRow.width, mRow.padding);
                for(int i=0; i<children.size(); i++) {
                    children[i]->draw();
//                    if (i == children.size()-1) break;
//                    ypos+=mRow.height + mRow.spacing;
//                    ofPushStyle();
//                        ofSetColor(ofxDatGuiColor::GUI_BKGD, mAlpha);
//                        ofDrawRectangle(x, ypos, mRow.width, mRow.padding);
//                    ofPopStyle();
                }
                for(int i=0; i<children.size(); i++) children[i]->drawColorPicker();
            }
            ofPopStyle();
        }
    
        void onMouseRelease(ofPoint m)
        {
    // open & close the group when its header is clicked //
            ofxDatGuiItem::onMouseRelease(m);
            mIsExpanded ? collapse() : expand();
            if (internalEventCallback!=nullptr){
                ofxDatGuiInternalEvent e(ofxDatGuiEventType::DROPDOWN_TOGGLED, mIndex);
                internalEventCallback(e);
            }
        }
    
        void expand()
        {
            mIsExpanded = true;
//            int ypos = mRow.height + mRow.spacing;
//            for(int i=0; i<children.size(); i++) {
//                children[i]->setVisible(true);
//                children[i]->setOrigin(x, y + ypos);
//                ypos+=mRow.height + mRow.spacing;
//            }
            int mHeight = mRow.height + mRow.spacing;
            for (int i=0; i<children.size(); i++) {
                children[i]->setVisible(true);
                children[i]->setOrigin(x, y + mHeight);
                mHeight += children[i]->getHeight() + mRow.spacing;
            }
        }
    
        void collapse()
        {
            mIsExpanded = false;
            for(int i=0; i<children.size(); i++) {
                children[i]->setVisible(false);
                children[i]->setOrigin(x, y);
            }
        }
    
    protected:
    
        ofImage mImage;
        bool mIsExpanded;
        int mChildrenHeight;
    
};

class ofxDatGuiFolder : public ofxDatGuiGroup{

    public:
    
        ofxDatGuiFolder(string label, ofColor color, ofxDatGuiFont* font=nullptr) : ofxDatGuiGroup(label, font)
        {
    // all items within a folder share the same stripe color //
            mStripeColor = color;
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
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchSliderEvent(ofxDatGuiSliderEvent e)
        {
            if (sliderEventCallback != nullptr) {
                sliderEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchTextInputEvent(ofxDatGuiTextInputEvent e)
        {
            if (textInputEventCallback != nullptr) {
                textInputEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchColorPickerEvent(ofxDatGuiColorPickerEvent e)
        {
            if (colorPickerEventCallback != nullptr) {
                colorPickerEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatch2dPadEvent(ofxDatGui2dPadEvent e)
        {
            if (pad2dEventCallback != nullptr) {
                pad2dEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void dispatchMatrixEvent(ofxDatGuiMatrixEvent e)
        {
            if (matrixEventCallback != nullptr) {
                matrixEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }

    /*
        component add methods
    */

        ofxDatGuiLabel* addLabel(string label)
        {
            ofxDatGuiLabel* lbl = new ofxDatGuiLabel(label, mFont);
            lbl->setStripeColor(mStripeColor);
            attachItem(lbl);
            return lbl;
        }

        ofxDatGuiButton* addButton(string label)
        {
            ofxDatGuiButton* button = new ofxDatGuiButton(label, mFont);
            button->setStripeColor(mStripeColor);
            button->onButtonEvent(this, &ofxDatGuiFolder::dispatchButtonEvent);
            attachItem(button);
            return button;
        }
    
        ofxDatGuiButton* addToggle(string label, bool enabled = false)
        {
            ofxDatGuiToggle* toggle = new ofxDatGuiToggle(label, enabled, mFont);
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
            ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val, mFont);
            slider->setStripeColor(mStripeColor);
            slider->onSliderEvent(this, &ofxDatGuiFolder::dispatchSliderEvent);
            attachItem(slider);
            return slider;
        }
    
        ofxDatGuiTextInput* addTextInput(string label, string value)
        {
            ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value, mFont);
            input->setStripeColor(mStripeColor);
            input->onTextInputEvent(this, &ofxDatGuiFolder::dispatchTextInputEvent);
            attachItem(input);
            return input;
        }
    
        ofxDatGuiColorPicker* addColorPicker(string label, ofColor color = ofColor::black)
        {
            shared_ptr<ofxDatGuiColorPicker> picker(new ofxDatGuiColorPicker(label, color, mFont));
            picker->setStripeColor(mStripeColor);
            picker->onColorPickerEvent(this, &ofxDatGuiFolder::dispatchColorPickerEvent);
            attachItem(picker.get());
            pickers.push_back(picker);
            return picker.get();
        }
    
        ofxDatGuiFRM* addFRM(float refresh = 1.0f)
        {
            ofxDatGuiFRM* monitor = new ofxDatGuiFRM(refresh, mFont);
            monitor->setStripeColor(mStripeColor);
            attachItem(monitor);
            return monitor;
        }

        ofxDatGuiBreak* addBreak(int height = 0)
        {
            ofxDatGuiBreak* brk = new ofxDatGuiBreak(height, mFont);
            attachItem(brk);
            return brk;
        }
    
        ofxDatGui2dPad* add2dPad(string label)
        {
            ofxDatGui2dPad* pad = new ofxDatGui2dPad(label, mFont);
            pad->setStripeColor(mStripeColor);
            pad->on2dPadEvent(this, &ofxDatGuiFolder::dispatch2dPadEvent);
            attachItem(pad);
            return pad;
        }

        ofxDatGuiMatrix* addMatrix(string label, int numButtons, bool showLabels = false)
        {
            ofxDatGuiMatrix* matrix = new ofxDatGuiMatrix(label, numButtons, showLabels, mFont);
            matrix->setStripeColor(mStripeColor);
            matrix->onMatrixEvent(this, &ofxDatGuiFolder::dispatchMatrixEvent);
            attachItem(matrix);
            return matrix;
        }
    
        void attachItem(ofxDatGuiItem* item)
        {
            item->setVisible(false);
            item->setIndex(children.size());
            children.push_back(item);
        // recalculate the group's height //
            mChildrenHeight = 0;
            for(int i=0; i<children.size(); i++) mChildrenHeight += children[i]->getHeight() + mRow.spacing;
        }

    private:
    
        vector<shared_ptr<ofxDatGuiColorPicker>> pickers;
    
};

class ofxDatGuiDropdownOption : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdownOption(string label, ofxDatGuiFont* font) : ofxDatGuiButton(label, font)
        {
            mLabelRect = mFont->getStringBoundingBox("* "+mLabel, 0, 0);
            mStripeColor = ofxDatGuiColor::DROPDOWN_STRIPE;
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiItem::drawLabel("* "+mLabel);
            ofxDatGuiItem::drawStripe();
        }

};

class ofxDatGuiDropdown : public ofxDatGuiGroup {

    public:
    
        ofxDatGuiDropdown(string label, vector<string> options, ofxDatGuiFont* font=nullptr) : ofxDatGuiGroup(label, font)
        {
            mOption = 0;
            mStripeColor = ofxDatGuiColor::DROPDOWN_STRIPE;
            for(uint8_t i=0; i<options.size(); i++){
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(options[i], mFont);
                opt->setIndex(children.size());
                opt->onButtonEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                opt->setVisible(false);
                children.push_back(opt);
            }
            mChildrenHeight = children.size() * (mRow.height+mRow.spacing);
        }
    
        void select(int cIndex)
        {
        // ensure value is in range //
            if (cIndex < 0 || cIndex >= children.size()){
                ofLogError() << "ofxDatGuiDropdown->select("<<cIndex<<") is out of range";
            }   else{
                mLabel = children[cIndex]->getLabel();
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
            mLabel = children[mOption]->getLabel();
            collapse();
            if (dropdownEventCallback != nullptr) {
                ofxDatGuiDropdownEvent e1(this, mIndex, mOption);
                dropdownEventCallback(e1);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
    private:
        int mOption;
    
};


