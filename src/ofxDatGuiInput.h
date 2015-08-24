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
            mHighlightPadding = 6;
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
                if (mHighlightText){
                    ofSetColor(ofxDatGuiColor::TEXT_HIGHLIGHT);
                    ofDrawRectangle(mHighlightRect);
                }
                ofxDatGuiItem::drawText(mVal, inputTextColor, x+mInput.x + 10);
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x+mInput.x && m.x<=x+mInput.x+mInput.width && m.y>=y+mInput.y && m.y<=y+mInput.y+mInput.height);
        }
    
        void onFocus()
        {
            mValChanged = false;
            mHighlightText = true;
            mHighlightRect = font.getBoundingBox(mVal, x+mInput.x+ 10, y+mInput.y+mLabelY-(labelHeight));
            mHighlightRect.x -= mHighlightPadding;
            mHighlightRect.width += mHighlightPadding*2;
            mHighlightRect.y -= mHighlightPadding;
            mHighlightRect.height += mHighlightPadding*2;
            inputTextColor = ofxDatGuiColor::LABEL;
            inputBkgdColor = ofxDatGuiColor::BUTTON_OVER;
        }
    
        void onFocusLost()
        {
            mHighlightText = false;
            inputTextColor = ofxDatGuiColor::TEXT;
            inputBkgdColor = ofxDatGuiColor::INPUT;
            if (mValChanged){
        // dispatch event out to main application //
                ofxDatGuiEvent evt(ofxDatGuiEventType::INPUT_CHANGED, mId, mVal);
                changeEventCallback(evt);
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        }
    
        void onKeyPressed(int key)
        {
            if (key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) return;
            if (mHighlightText) mVal = "";
            if (key != OF_KEY_BACKSPACE){
                mVal += key;
            }   else {
                if (mVal.size() > 0) mVal.resize(mVal.size()-1);
            }
            mValChanged = true;
            mVal = ofToUpper(mVal);
            mHighlightText = false;
        }
    
    private:
    
        int textX;
        int textY;
        bool mValChanged;
        int mHighlightPadding;
        string mVal;
        ofBitmapFont font;
        bool mHighlightText;
        ofRectangle mHighlightRect;
        ofColor inputBkgdColor;
        ofColor inputTextColor;
        ofRectangle mInput;
    
};