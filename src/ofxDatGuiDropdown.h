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
    
        ofxDatGuiDropdownOption(int index, string label) : ofxDatGuiButton(index, label) { }
    
        void draw()
        {
            ofPushStyle();
                ofxDatGuiButton::draw();
            ofPopStyle();
        }
        void setPosition(int x, int y)
        {
            this->x=x;
            this->y=y;
        }
    
    private:

};

class ofxDatGuiDropdown : public ofxDatGuiButton {

    public:
    
        ofxDatGuiDropdown(int index, string label, vector<string> options) : ofxDatGuiButton(index, label)
        {
            mOptionsVisible = false;
            for(uint8_t i=0; i<options.size(); i++){
                ofxDatGuiDropdownOption* opt = new ofxDatGuiDropdownOption(children.size(), options[i]);
                opt->setPosition(this->x, this->y+(children.size()*(rowHeight+rowSpacing)) + (rowHeight+rowSpacing));
                opt->onGuiEvent(this, &ofxDatGuiDropdown::onOptionSelected);
                children.push_back(opt);
            }
            if (icon.isAllocated() == false) icon.load("dropdown-icon.png");
            mHeight = children.size() * (ofxDatGuiItem::rowHeight+ofxDatGuiItem::rowSpacing);
        }
    
        void draw()
        {
            ofPushStyle();
                ofxDatGuiButton::draw();
                ofSetColor(ofxDatGuiColor::LABEL);
                icon.draw(x+rowWidth-20, y+9, 10, 10);
                if (mOptionsVisible) {
                    ofSetColor(ofxDatGuiColor::GUI_BKGD);
                    ofDrawRectangle(x, y+rowHeight, ofxDatGuiWidth, mHeight);
                    for(uint8_t i=0; i<children.size(); i++) children[i]->draw();
                }
            ofPopStyle();
        }
    
        void onMouseRelease(ofPoint m)
        {
            mOptionsVisible = !mOptionsVisible;
        }
    
        void onOptionSelected(ofxDatGuiEvent e)
        {
            e.child = e.id;
            e.id = mId;
            mOptionsVisible = !mOptionsVisible;
            mLabel = children[e.child]->getLabel();
            changeEventCallback(e);
        }
    
    protected:
    
    
    private:
        ofImage icon;
        uint mHeight;
        bool mOptionsVisible;
};

