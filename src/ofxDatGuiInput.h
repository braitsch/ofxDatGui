//
//  ofxDatGuiInput.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/22/15.
//
//


#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiInput : public ofxDatGuiItem {

    public:
        ofxDatGuiInput(int index, string label, string val) : ofxDatGuiItem(index, label)
        {
            mVal = val;
            onFocusLost();
            mInput = ofRectangle(sliderX, rowPadding, rowWidth-rowPadding-sliderX, rowHeight-(rowPadding*2));
        }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::INPUT_STRIPE);
        // draw input field //
            ofPushStyle();
                ofSetColor(inputBkgdColor);
                ofDrawRectangle(x+mInput.x, y+mInput.y, mInput.width, mInput.height);
                ofxDatGuiItem::drawText(mVal, inputTextColor, x+mInput.x + 10);
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x+mInput.x && m.x<=x-mInput.x+mInput.width && m.y>=y+mInput.y && m.y<=y+mInput.y+mInput.height);
        }
    
        void onFocusLost()
        {
            inputTextColor = ofxDatGuiColor::TEXT;
            inputBkgdColor = ofxDatGuiColor::INPUT;
        }
    
        void onMouseRelease(ofPoint m)
        {
        // if we just received focus highlight the text and wait for key press before clearing it //
            mHighlightText = true;
            ofxDatGuiItem::onMouseRelease(m);
            inputTextColor = ofxDatGuiColor::LABEL;
            inputBkgdColor = ofxDatGuiColor::BUTTON_OVER;
        }
    
        void onKeyPressed(int key)
        {
            if (mHighlightText) mVal = "";
            mHighlightText = false;
            mVal += key;
        }
    
    private:
    
        int textX;
        int textY;
        string mVal;
        ofColor inputBkgdColor;
        ofColor inputTextColor;
        bool mHighlightText;
        ofRectangle mInput;

};