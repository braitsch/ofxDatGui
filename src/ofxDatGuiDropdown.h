//
//  ofxDatGuiDropdown.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/18/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiDropdownOption{

    public:
        ofxDatGuiDropdownOption(int index, string label)
        {
        
        }
        void draw(){
        
        }
    private:
        string mLabel;

};

class ofxDatGuiDropdown : public ofxDatGuiItem {

    public:
    
        ofxDatGuiDropdown(int index, string label, vector<string> options) : ofxDatGuiItem(index, label)
        {
            for(uint8_t i=0; i<options.size(); i++){
                mOptions.push_back(new ofxDatGuiDropdownOption(mOptions.size(), label));
            }
            if (icon.isAllocated() == false) icon.load("dropdown-icon.png");
        }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd(mMouseOver ? ofxDatGuiColor::BUTTON_OVER : ofxDatGuiColor::ROW_BKGD);
            ofxDatGuiItem::drawLabel();
            icon.draw(x+rowWidth-20, y+9, 10, 10);
        }
    
        void onMousePress(ofPoint m)
        {
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, 1);
            changeEventCallback(evt);
        }
    
        void onMouseRelease(ofPoint m)
        {
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, 0);
            changeEventCallback(evt);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+rowWidth && m.y>=y && m.y<= y+rowHeight);
        }
    
    protected:
    
    
    private:
        vector<ofxDatGuiDropdownOption*> mOptions;
        ofImage icon;
};

