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
#include <locale>
#include "ofxDatGuiTextInput.h"

class ofxDatGuiColorPicker : public ofxDatGuiTextInput {

    public:
    
        ofxDatGuiColorPicker(string label) : ofxDatGuiTextInput(label, "#FF0000")
        {
            mColor = ofColor::fromHex(0xFF0000);
            mStripeColor = ofxDatGuiColor::TOGGLE_STRIPE;
        // center the text input field //
            input->setTextIndent(input->getWidth()/2 - ofxDatGuiFont::getStringBoundingBox("#FF0000", 0, 0).width/2);
        // attach the picker //
            mShowPicker = false;
            pickerRect = ofRectangle(0, 0, input->getWidth(), (ofxDatGuiGlobals::rowHeight+mPadding) * 3);
        //  cout << (ofxDatGuiGlobals::rowHeight+mPadding) * 3; //168
            rainbowWidth = 20;
            rainbowHeight = pickerRect.height -(mPadding*2);
            rainbowRect = ofRectangle(0, 0, rainbowWidth, rainbowHeight);
            gradientRect = ofRectangle(0, 0, pickerRect.width-rainbowRect.width-(mPadding*3), rainbowHeight);
            if (rainbow.isAllocated() == false) rainbow.load(ofxDatGuiAssetDir+"picker-rainbow.png");
        }
    
        void onMouseEnter(ofPoint mouse)
        {
            mShowPicker = true;
        }
    
        void onMouseLeave(ofPoint mouse)
        {
            mShowPicker = false;
        }
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiTextInput::draw();
                if (mShowPicker) {
                    pickerRect.x = this->x + inputX;
                    pickerRect.y = this->y + mPadding + input->getHeight();
                    rainbowRect.x = pickerRect.x+pickerRect.width-rainbowWidth-mPadding;
                    rainbowRect.y = pickerRect.y+mPadding;
                    gradientRect.x = pickerRect.x + mPadding;
                    gradientRect.y = pickerRect.y + mPadding;
                    ofPushStyle();
                        ofSetColor(ofxDatGuiColor::LABEL);
                        ofDrawRectangle(pickerRect);
                        rainbow.draw(rainbowRect);
                        ofSetColor(mColor);
                        ofDrawRectangle(gradientRect);
                    ofPopStyle();
                }
            }
        }
    
        bool hitTest(ofPoint m)
        {
            if (input->hitTest(m)){
                return true;
            }   else if (mShowPicker && pickerRect.inside(m)){
                getColorFromPicker(m);
                return true;
            }   else{
                return false;
            }
        }
    
        void getColorFromPicker(ofPoint m)
        {
            if (rainbowRect.inside(m)){
                mColor = rainbow.getColor(m.x-rainbowRect.x, m.y-rainbowRect.y);
                std::stringstream ss;
                ss<< std::hex << mColor.getHex(); // int decimal_value
                std::string res ( ss.str() );
                while(res.size() < 6) res+="0";
                input->setText("#"+ofToUpper(res));
            }
        }
    
        void onInputChanged(ofxDatGuiEvent e)
        {
            cout << "onInputChanged"  << endl;
//            e.index = mId;
  //          changeEventCallback(e);
        }
    
    private:

        bool mShowPicker;
        ofColor mColor;
        ofImage rainbow;
        int rainbowWidth;
        int rainbowHeight;
        ofRectangle pickerRect;
        ofRectangle rainbowRect;
        ofRectangle gradientRect;

};