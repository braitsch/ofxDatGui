//
//  ofxDatGuiDropdown.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/18/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiDropdownOption : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdownOption(int index, string label, int ypos) : ofxDatGuiButton(index, label)
        {
            this->y = originY = ypos;
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::DROPDOWN_STRIPE);
        }
    
        void drawLabel()
        {
            ofxDatGuiItem::drawText(" * "+mLabel, ofxDatGuiColor::LABEL, x+labelX);
        }
    
    private:

};

class ofxDatGuiDropdown : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdown(int index, string label, vector<string> options) : ofxDatGuiButton(index, label)
        {
            for(uint8_t i=0; i<options.size(); i++){
                int y = this->y+(children.size()*(rowHeight+rowSpacing)) + (rowHeight+rowSpacing);
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(children.size(), options[i], y);
                opt->onGuiEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                children.push_back(opt);
            }
            if (icon.isAllocated() == false) icon.load("dropdown-icon.png");
            mHeight = children.size() * (ofxDatGuiItem::rowHeight+ofxDatGuiItem::rowSpacing);
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::DROPDOWN_STRIPE);
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::LABEL);
                icon.draw(x+dropdownIconX, y+dropdownIconY, dropdownIconSize, dropdownIconSize);
                if (mIsExpanded) for(uint8_t i=0; i<children.size(); i++) children[i]->draw();
            ofPopStyle();
        }
    
        int getHeight()
        {
            return mHeight;
        }
    
        void collapse()
        {
            mIsExpanded = false;
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
            e.child = e.target;
            e.target = mId;
        // convert button_pressed to type option_selected //
            e.type = ofxDatGuiEventType::OPTION_SELECTED;
            mLabel = children[e.child]->getLabel();
        // auto close the dropdown when an option is selected //
            mIsExpanded = !mIsExpanded;
            changeEventCallback(e);
        }
    
    protected:
        int mHeight;
        ofImage icon;
};

