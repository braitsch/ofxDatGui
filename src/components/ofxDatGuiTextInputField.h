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
#include "ofxDatGuiIntObject.h"

class ofxDatGuiTextInputField : public ofxDatGuiInteractiveObject{

    public:
    
        enum ofxDatGuiTextInputFieldType
        {
            NUMERIC = 1,
            ALPHA_NUMERIC,
            COLORPICKER
        };
    
        ofxDatGuiTextInputField(float height, ofxDatGuiTemplate* tmplt)
        {
            setTemplate(tmplt);
            mRect.height = height;
            mTextChanged = false;
            mHighlightText = false;
            mMaxCharacters = 99;
            mType = ALPHA_NUMERIC;
        }
    
        void setWidth(int w)
        {
            mRect.width = w;
        }
    
        void setOrigin(int x, int y)
        {
            mRect.x = x;
            mRect.y = y;
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            mTemplate = tmplt;
            mFont = mTemplate->font.ttf;
            mTextColor = mTemplate->textInput.color.stripe;
            mBkgdColor = mTemplate->row.color.inputArea;
            mTextActiveColor = mTemplate->row.color.label;
            mTextInactiveColor = mTemplate->textInput.color.stripe;
        }
    
        void draw()
        {
        // center the text //
            int tx = mRect.width/2 - mTextRect.width/2;
            ofPushStyle();
                ofSetColor(mBkgdColor);
                ofDrawRectangle(mRect);
                mTextColor = mHighlightText ? mTextActiveColor : mTextInactiveColor;
                mFont->drawText(mType==COLORPICKER ? "#"+mText : mText, mTextColor, mRect.x+tx, mRect.y+mRect.height/2, mHighlightText);
            ofPopStyle();
        }
    
        int getWidth()
        {
            return mRect.width;
        }
    
        int getHeight()
        {
            return mRect.height;
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=mRect.x && m.x<=mRect.x+mRect.width && m.y>=mRect.y && m.y<=mRect.y+mRect.height);
        }
    
        void setText(string text)
        {
            mText = text;
            mTextChanged = true;
            mTextRect = mFont->getStringBoundingBox(mType==COLORPICKER ? "#"+mText : mText, 0, 0);
        }
    
        string getText()
        {
            return mText;
        }
    
        void setTextActiveColor(ofColor color)
        {
            mTextActiveColor = color;
        }
    
        void setTextInactiveColor(ofColor color)
        {
            mTextInactiveColor = color;
        }
    
        void setTextInputFieldType(ofxDatGuiTextInputFieldType type)
        {
            mType = type;
        }
    
        void setBackgroundColor(ofColor color)
        {
            mBkgdColor = color;
        }
    
        void setMaxNumOfCharacters(int max)
        {
            mMaxCharacters = max;
        }
    
        virtual void onFocus()
        {
            mTextChanged = false;
            mHighlightText = true;
            if (mType != COLORPICKER) mBkgdColor = mTemplate->row.color.mouseOver;
        }
    
        virtual void onFocusLost()
        {
            mHighlightText = false;
            if (mTextChanged){
                mTextChanged = false;
                ofxDatGuiInternalEvent e(ofxDatGuiEventType::INPUT_CHANGED, 0);
                internalEventCallback(e);
            }
            if (mType != COLORPICKER) mBkgdColor = mTemplate->row.color.inputArea;
        }
    
        void onKeyPressed(int key)
        {
            if (!keyIsValid(key)) return;
            if (mHighlightText) mText = "";
            if (key!=OF_KEY_BACKSPACE){
                mText += key;
            }   else {
                if (mText.size() > 0) mText.resize(mText.size()-1);
            }
            mHighlightText = false;
            setText(ofToUpper(mText));
        }
    
        bool keyIsValid(int key)
        {
            if (mType == COLORPICKER){
               if (key==OF_KEY_BACKSPACE){
                    return true;
            // limit string length to six hex characters //
                } else if (!mHighlightText && mText.size() == 6){
                    return false;
            // allows numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
            // allows letters a-f & A-F //
                }   else if ((key>=97 && key<=102) || (key>=65 && key<=70)){
                    return true;
                }   else{
                    return false;
                }
            }   else if (mType == NUMERIC){
                if (key==OF_KEY_BACKSPACE){
                    return true;
            // allow dash (-) or dot (.) //
                }   else if (key==45 || key==46){
                    return true;
            // allows numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
            // an invalid key was entered //
                }   else{
                    return false;
                }
            }   else{
            // allow anything //
                return true;
            }
        }
    
    private:
        string mText;
        bool mTextChanged;
        bool mHighlightText;
        int mMaxCharacters;
        ofRectangle mRect;
        ofRectangle mTextRect;
        ofColor mBkgdColor;
        ofColor mTextColor;
        ofColor mHighLightColor;
        ofColor mTextActiveColor;
        ofColor mTextInactiveColor;
        ofxDatGuiFont* mFont;
        ofxDatGuiTemplate* mTemplate;
        ofxDatGuiTextInputFieldType mType;
};

