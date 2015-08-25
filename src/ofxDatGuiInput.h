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
        ofxDatGuiInput(int index, string label, string text) : ofxDatGuiItem(index, label)
        {
            mText = text;
            mTextChanged = false;
            mHighlightPadding = 6;
            mHighlightText = false;
            mInputTextColor = ofxDatGuiColor::TEXT;
            mInputBkgdColor = ofxDatGuiColor::INPUT;
            mTextHeight = getStringBoundingBox(mText, 0, 0).height;
        }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::INPUT_STRIPE);
            mInputRect = ofRectangle(x+inputX, y+rowPadding, guiWidth-rowPadding-inputX, rowHeight-(rowPadding*2));
        // draw input field //
            ofPushStyle();
                ofSetColor(mInputBkgdColor);
                ofDrawRectangle(mInputRect);
                if (mHighlightText){
                    ofSetColor(ofxDatGuiColor::TEXT_HIGHLIGHT);
                    ofDrawRectangle(mHighlightRect);
                }
                ofxDatGuiItem::drawText(mText, mInputTextColor, mInputRect.x+inputTextIndent);
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            return mInputRect.inside(m);
        }
    
        void onFocus()
        {
            mTextChanged = false;
            mHighlightText = true;
            mHighlightRect = getStringBoundingBox(mText, mInputRect.x+inputTextIndent, mInputRect.y+mLabelY-(labelHeight/2)+1);
            mHighlightRect.x -= mHighlightPadding;
            mHighlightRect.width += mHighlightPadding*2;
            mHighlightRect.y -= mHighlightPadding;
            mHighlightRect.height += mHighlightPadding*2;
            mInputTextColor = ofxDatGuiColor::LABEL;
            mInputBkgdColor = ofxDatGuiColor::BUTTON_OVER;
        }
    
        void onFocusLost()
        {
            mHighlightText = false;
            mInputTextColor = ofxDatGuiColor::TEXT;
            mInputBkgdColor = ofxDatGuiColor::INPUT;
            if (mTextChanged){
        // dispatch event out to main application //
                ofxDatGuiEvent evt(ofxDatGuiEventType::INPUT_CHANGED, mId, mText);
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
            if (mHighlightText) mText = "";
            if (key != OF_KEY_BACKSPACE){
                mText += key;
            }   else {
                if (mText.size() > 0) mText.resize(mText.size()-1);
            }
            mTextChanged = true;
            mHighlightText = false;
            mText = ofToUpper(mText);
            mTextHeight = getStringBoundingBox(mText, 0, 0).height;
        }
    
    private:
    
        int mTextHeight;
        int mHighlightPadding;
        string mText;
        bool mTextChanged;
        bool mHighlightText;
        ofColor mInputBkgdColor;
        ofColor mInputTextColor;
        ofRectangle mInputRect;
        ofRectangle mHighlightRect;

    
};