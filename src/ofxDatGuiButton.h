//
//  ofxDatGuiButton.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/18/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiButton : public ofxDatGuiItem {

    public:
    
        ofxDatGuiButton(int index, string label) : ofxDatGuiItem(index, label) { }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_CLICKED, mId);
            changeEventCallback(evt);
        }
    
        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
        }
    
        void drawBkgd()
        {
            ofColor color = ofxDatGuiColor::ROW_BKGD;
            if (mMouseOver) color = ofxDatGuiColor::BUTTON_OVER;
            if (mMouseDown) color = ofxDatGuiColor::BUTTON_DOWN;
        // anything that extends ofxDatGuiButton has the same rollover effect //
            ofxDatGuiItem::drawBkgd(color);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+rowWidth && m.y>=y && m.y<= y+rowHeight);
        }
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(int index, string label, bool state) : ofxDatGuiButton(index, label)
        {
            mState = state;
            if (!radioOn.isAllocated()) radioOn.load("radio-on.png");
            if (!radioOff.isAllocated()) radioOff.load("radio-off.png");
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            mState = !mState;
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_TOGGLED, mId, mState);
            changeEventCallback(evt);
        }

        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::TOGGLE_STRIPE);
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::LABEL);
                if (mState == true){
                    radioOn.draw(x+rowWidth-43, y+15, 22, 22);
                }   else{
                    radioOff.draw(x+rowWidth-43, y+15, 22, 22);
                }
            ofPopStyle();
        }
    
    private:
        bool mState;
        ofImage radioOn;
        ofImage radioOff;

};

class ofxDatGuiToggler : public ofxDatGuiButton {


    public:
    
        ofxDatGuiToggler() : ofxDatGuiButton(9999, "COLLAPSE CONTROLS")
        {
            mIsExpanded = true;
        }
    
        int getOriginY()
        {
            return originY;
        }
    
        void setOriginY(int y)
        {
            this->y = originY = y;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::GUI_TOGGLED, mId, mIsExpanded);
            changeEventCallback(evt);
            if (mIsExpanded){
                mIsExpanded = false;
                mLabel = "EXPAND CONTROLS";
            }   else{
                mIsExpanded = true;
                mLabel = "COLLAPSE CONTROLS";
            }
        }
    
};