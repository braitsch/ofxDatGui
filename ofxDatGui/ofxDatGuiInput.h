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
    
        void setText(string text)
        {
            mText = text;
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
                ofxDatGuiEvent e(ofxDatGuiEventType::INPUT_CHANGED, mId);
                e.text = mText;
                changeEventCallback(e);
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
