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
#include "ofxDatGuiItem.h"

class ofxDatGuiDropdownOption : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdownOption(int index, string label) : ofxDatGuiButton(index, label)
        {

        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiFont::drawLabel(" * "+mLabel, x, y + mHeight/2);
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::DROPDOWN_STRIPE);
        }
    
    private:

};

class ofxDatGuiDropdown : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdown(int index, string label, vector<string> options) : ofxDatGuiButton(index, label)
        {
            for(uint8_t i=0; i<options.size(); i++){
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(children.size(), options[i]);
                opt->onGuiEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                children.push_back(opt);
            }
            if (icon.isAllocated() == false) icon.load(ofxDatGuiAssetDir+"icon-dropdown.png");
            mExpandedHeight = children.size() * (mHeight+ofxDatGuiGlobals::rowSpacing);
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
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe(ofxDatGuiColor::DROPDOWN_STRIPE);
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    icon.draw(x+dropdownIconX, y+dropdownIconY, dropdownIconSize, dropdownIconSize);
                    if (mIsExpanded) for(uint8_t i=0; i<children.size(); i++) children[i]->draw();
                ofPopStyle();
            }
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiItem::setOrigin(x, y);
        }

        bool isExpanded()
        {
            return mIsExpanded;
        }
    
        int getHeight()
        {
            if (!mIsExpanded){
                return mHeight;
            }   else{
                return mHeight + mExpandedHeight;
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            int eType;
            if (!mIsExpanded){
                mIsExpanded = true;
                eType = ofxDatGuiEventType::DROPDOWN_EXPANDED;
            }   else {
                mIsExpanded = false;
                eType = ofxDatGuiEventType::DROPDOWN_COLLAPSED;
            }
            ofxDatGuiEvent e = ofxDatGuiEvent(eType, mId);
            changeEventCallback(e);
        }
    
        void onOptionSelected(ofxDatGuiEvent e)
        {
            mOption = e.index;
            e.index = mId;
            e.child = mOption;
        // convert button_pressed to type option_selected //
            e.type = ofxDatGuiEventType::OPTION_SELECTED;
            mLabel = children[e.child]->getLabel();
        // auto close the dropdown when an option is selected //
            mIsExpanded = !mIsExpanded;
            changeEventCallback(e);
        }
    
    protected:
        int mOption;
        bool mIsExpanded;
        int mExpandedHeight;
        ofImage icon;
};

