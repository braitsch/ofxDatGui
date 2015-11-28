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
			mFocused = false;
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
            mUpperCaseText = mTemplate->textInput.forceUpperCase;
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

				//draw cursor
				if (mFocused) {
					float xPos = mRect.x + tx;
					if (mText.size() == 0) {
						xPos = mRect.getCenter().x;
					} else if (mCursorPos > 0) {
						ofRectangle bbox = mFont->getStringBoundingBox(mText.substr(0, mCursorPos), mRect.x + tx, mRect.y);
						xPos = bbox.getRight();
					}
					ofSetColor(mTextColor);
					ofLine(ofPoint(xPos, mRect.getBottom()), ofPoint(xPos, mRect.getTop()));
				}
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
    
        bool hasFocus()
        {
            return mFocused;
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=mRect.x && m.x<=mRect.x+mRect.width && m.y>=mRect.y && m.y<=mRect.y+mRect.height);
        }
    
        void setText(string text)
        {
            mText = text;
            mTextChanged = true;
            if (mUpperCaseText) mText = ofToUpper(mText);
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
    
        void onFocus()
        {
            mFocused = true;
            mTextChanged = false;
            mHighlightText = true;
			mCursorPos = mText.size();
            if (mType != COLORPICKER) mBkgdColor = mTemplate->row.color.mouseOver;
        }
    
        void onFocusLost()
        {
            mFocused = false;
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
			if (mHighlightText) {
				//if key is printable or delete
				if (key >= 32 && key <= 255 || key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) {
					mText = "";
					mCursorPos = 0;
				}
			}
            if (key==OF_KEY_BACKSPACE){
				if (mCursorPos > 0) {
					mText = mText.substr(0, mCursorPos - 1) + mText.substr(mCursorPos);
					mCursorPos--;
					
				}
			} else if (key == OF_KEY_LEFT) {
				mCursorPos = max( (int) mCursorPos - 1, 0);
			} else if (key == OF_KEY_RIGHT) {
				mCursorPos = min( mCursorPos + 1, (unsigned int) mText.size());
			} else {
				//mText += key;
				mText = mText.substr(0, mCursorPos) + (char)key + mText.substr(mCursorPos);
				mCursorPos++;

            }
            mHighlightText = false;
            setText(mText);
        }
    
        bool keyIsValid(int key)
        {
            if (key==OF_KEY_BACKSPACE || key == OF_KEY_LEFT || key == OF_KEY_RIGHT){
                return true;
            }   else if (mType == COLORPICKER){
            // limit string length to six hex characters //
                if (!mHighlightText && mText.size() == 6){
                    return false;
            // allow numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
            // allow letters a-f & A-F //
                }   else if ((key>=97 && key<=102) || (key>=65 && key<=70)){
                    return true;
                }   else{
            // an invalid key was entered //
                    return false;
                }
            }   else if (mType == NUMERIC){
            // allow dash (-) or dot (.) //
                if (key==45 || key==46){
                    return true;
            // allow numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
                }   else{
            // an invalid key was entered //
                    return false;
                }
            }   else if (mType == ALPHA_NUMERIC){
            // limit range to printable characters http://www.ascii-code.com //
                if (key >= 32 && key <= 255) {
                    return true;
                }   else {
            // an invalid key was entered //
                    return false;
                }
            }   else{
            // invalid textfield type //
                return false;
            }
        }
    
    private:
		unsigned int mCursorPos;
        string mText;
        bool mFocused;
        bool mTextChanged;
        bool mHighlightText;
        bool mUpperCaseText;
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

