//
//  ofDatGuiToggle.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/20/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

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
            mState = !mState;
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_TOGGLED, mId, mState);
            changeEventCallback(evt);
        }

        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
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