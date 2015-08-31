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
#include "ofxDatGuiButton.h"
#include "ofxDatGuiSlider.h"
#include "ofxDatGuiTextInput.h"

class ofxDatGuiGroup : public ofxDatGuiButton {

    public:
    
        ofxDatGuiGroup(string label) : ofxDatGuiButton(label)
        {
            mIsExpanded = false;
            mChildrenHeight = 0;
            if (mIcon.isAllocated() == false) mIcon.load(ofxDatGuiAssetDir+"icon-dropdown.png");
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiItem::setOrigin(x, y);
            int ypos = mHeight + ofxDatGuiGlobals::rowSpacing;
            for(int i=0; i<children.size(); i++) {
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
            int ypos = mHeight + ofxDatGuiGlobals::rowSpacing;
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
                return mHeight;
            }   else{
                return mHeight + mChildrenHeight;
            }
        }
    
        bool getIsExpanded()
        {
            return mIsExpanded;
        }
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe();
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    mIcon.draw(x+dropdownIconX, y+dropdownIconY, dropdownIconSize, dropdownIconSize);
                    for(int i=0; i<children.size(); i++) children[i]->draw();
                ofPopStyle();
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
    // open & close the group when its header is clicked //
            ofxDatGuiItem::onMouseRelease(m);
            mIsExpanded ? collapse() : expand();
            ofxDatGuiEvent e = ofxDatGuiEvent(ofxDatGuiEventType::DROPDOWN_TOGGLED, mId);
            changeEventCallback(e);
        }

    
    protected:
    
        ofImage mIcon;
        bool mIsExpanded;
        int mChildrenHeight;
    
        void expand()
        {
            mIsExpanded = true;
            int ypos = mHeight + ofxDatGuiGlobals::rowSpacing;
            for(int i=0; i<children.size(); i++) {
                children[i]->setVisible(true);
                children[i]->setOrigin(x, y + (ypos*(i+1)));
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
    
};

class ofxDatGuiFolder : public ofxDatGuiGroup{

    public:
    
        ofxDatGuiFolder(string label, ofColor color) : ofxDatGuiGroup(label)
        {
    // all items within a folder share the same stripe color //
            mStripeColor = color;
        }
    
        void onFolderEvent(ofxDatGuiEvent e)
        {
            e.child = e.index;
            e.index = mId;
            changeEventCallback(e);
        }

        ofxDatGuiButton* addButton(string label)
        {
            ofxDatGuiButton* button = new ofxDatGuiButton(label);
            button->setStripeColor(mStripeColor);
            attachItem(button);
            return button;
        }
    
        ofxDatGuiButton* addToggle(string label, bool enabled = false)
        {
            ofxDatGuiToggle* toggle = new ofxDatGuiToggle(label, enabled);
            toggle->setStripeColor(mStripeColor);
            attachItem(toggle);
            return toggle;
        }
    
        ofxDatGuiSlider* addSlider(string label, float min, float max)
        {
        // default to halfway between min & max values //
            ofxDatGuiSlider* slider = addSlider(label, min, max, (max+min)/2);
            slider->setStripeColor(mStripeColor);
            return slider;
        }

        ofxDatGuiSlider* addSlider(string label, float min, float max, float val)
        {
            ofxDatGuiSlider* slider = new ofxDatGuiSlider(label, min, max, val);
            slider->setStripeColor(mStripeColor);
            attachItem(slider);
            return slider;
        }
    
        ofxDatGuiTextInput* addTextInput(string label, string value)
        {
            ofxDatGuiTextInput* input = new ofxDatGuiTextInput(label, value);
            input->setStripeColor(mStripeColor);
            attachItem(input);
            return input;
        }
    
        void attachItem(ofxDatGuiItem* item)
        {
            item->onGuiEvent(this, &ofxDatGuiFolder::onFolderEvent);
            item->setVisible(false);
            item->setIndex(children.size());
            children.push_back(item);
        // recalculate the group's height //
            mChildrenHeight = 0;
            for(int i=0; i<children.size(); i++) mChildrenHeight += children[i]->getHeight() + ofxDatGuiGlobals::rowSpacing;
        }
    
};

class ofxDatGuiDropdownOption : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdownOption(string label) : ofxDatGuiButton(label)
        {
            mStripeColor = ofxDatGuiColor::DROPDOWN_STRIPE;
        }
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiFont::drawLabel(" * "+mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe();
            }
        }

};

class ofxDatGuiDropdown : public ofxDatGuiGroup {

    public:
    
        ofxDatGuiDropdown(string label, vector<string> options) : ofxDatGuiGroup(label)
        {
            mStripeColor = ofxDatGuiColor::DROPDOWN_STRIPE;
            for(uint8_t i=0; i<options.size(); i++){
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(options[i]);
                opt->setIndex(children.size());
                opt->onGuiEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                opt->setVisible(false);
                children.push_back(opt);
            }
            mChildrenHeight = children.size() * (mHeight+ofxDatGuiGlobals::rowSpacing);
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
    
        int getSelectedChildIndex()
        {
            return mOption;
        }
    
        void onOptionSelected(ofxDatGuiEvent e)
        {
            mOption = e.index;
            e.index = mId;
            e.child = mOption;
        // convert button_pressed event to option_selected //
            e.type = ofxDatGuiEventType::OPTION_SELECTED;
            mLabel = children[e.child]->getLabel();
        // auto close the dropdown when an option is selected //
            collapse();
            changeEventCallback(e);
        }
    
    private:
        int mOption;
    
};


