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
    
        ofxDatGuiColorPicker(ofxDatGuiGlobals *gui, string label, ofColor color = ofColor::black) : ofxDatGuiTextInput(gui, label)
        {
            mColor = color;
            mStripeColor = ofxDatGuiColor::TOGGLE_STRIPE;
            
        // center the text input field //
            input->setTextInputFieldType(ofxDatGuiTextInputField::COLORPICKER);
            setTextFieldInputColor();
            
        // attach the picker //
            mShowPicker = false;
            pickerRect = ofRectangle(0, 0, input->getWidth(), (mGui->row.height+mPadding) * 3);
            rainbowWidth = 20;
            rainbowHeight = pickerRect.height -(mPadding*2);
            rainbowRect = ofRectangle(0, 0, rainbowWidth, rainbowHeight);
            gradientRect = ofRectangle(0, 0, pickerRect.width-rainbowRect.width-(mPadding*3), rainbowHeight);
            if (rainbow.isAllocated() == false) rainbow.load(ofxDatGuiAssetDir+"/picker-rainbow.png");
            
        // setup the vbo that draws the gradient //
            gPoints.push_back(ofVec2f(0, 0));
            gPoints.push_back(ofVec2f(0, 0));
            gPoints.push_back(ofVec2f(0, 0));
            gPoints.push_back(ofVec2f(0, 0));
            gColors.push_back(ofColor::white);
            gColors.push_back(mColor);
            gColors.push_back(ofColor::black);
            gColors.push_back(ofColor::black);
            vbo.setColorData(&gColors[0], 4, GL_DYNAMIC_DRAW );
        }
    
        void setColor(ofColor color)
        {
            mColor = color;
            setTextFieldInputColor();
        }
    
        void setColor(int hex)
        {
            mColor = ofColor::fromHex(hex);
            setTextFieldInputColor();
        }
    
        void setColor(int r, int g, int b, int a = 255)
        {
            mColor = ofColor(r, g, b, a);
            setTextFieldInputColor();
        }
    
        ofColor getColor()
        {
            return mColor;
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
            ofxDatGuiTextInput::draw();
            if (mShowPicker) {
                pickerRect.x = this->x + mGui->row.inputX;
                pickerRect.y = this->y + mPadding + input->getHeight();
                pickerRect.width = input->getWidth();
                rainbowRect.x = pickerRect.x+pickerRect.width-rainbowWidth-mPadding;
                rainbowRect.y = pickerRect.y+mPadding;
                gradientRect.x = pickerRect.x + mPadding;
                gradientRect.y = pickerRect.y + mPadding;
                gradientRect.width = pickerRect.width-rainbowRect.width-(mPadding*3);
                gPoints[0] = ofVec2f(gradientRect.x, gradientRect.y);
                gPoints[1] = ofVec2f(gradientRect.x+ gradientRect.width, gradientRect.y);
                gPoints[2] = ofVec2f(gradientRect.x+ gradientRect.width, gradientRect.y+gradientRect.height);
                gPoints[3] = ofVec2f(gradientRect.x, gradientRect.y+gradientRect.height);
                vbo.setVertexData(&gPoints[0], 4, GL_DYNAMIC_DRAW );
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    ofDrawRectangle(pickerRect);
                    ofSetColor(ofColor::white);
                    rainbow.draw(rainbowRect);
                    vbo.draw( GL_QUADS, 0, 4 );
                ofPopStyle();
            }
        }
    
        void drawColorPicker()
        {
            if (mVisible && mShowPicker){
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    ofDrawRectangle(pickerRect);
                    ofSetColor(ofColor::white);
                    rainbow.draw(rainbowRect);
                    vbo.draw( GL_QUADS, 0, 4 );
                ofPopStyle();
            }
        }
    
        bool hitTest(ofPoint m)
        {
            if (input->hitTest(m)){
                return true;
            }   else if (mShowPicker && pickerRect.inside(m)){
                unsigned char p[3];
                int y = (ofGetMouseY()-ofGetHeight())*-1;
                glReadPixels(ofGetMouseX(), y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &p);
                gColor.r = int(p[0]);
                gColor.g = int(p[1]);
                gColor.b = int(p[2]);
                if (rainbowRect.inside(m) && mMouseDown){
                    gColors[1] = gColor;
                    vbo.setColorData(&gColors[0], 4, GL_DYNAMIC_DRAW );
                }   else if (gradientRect.inside(m) && mMouseDown){
                    mColor = gColor;
                // dispatch a color changed event out to our application //
                    ofxDatGuiColorPickerEvent e(this, mColor);
                    colorPickerEventCallback(e);
                    setTextFieldInputColor();
                }
                return true;
            }   else{
                return false;
            }
        }
    
        inline void setTextFieldInputColor()
        {
        // convert color value to a six character hex string //
            std::stringstream ss;
            ss<< std::hex << mColor.getHex();
            std::string res ( ss.str() );
            while(res.size() < 6) res+="0";
            mColorHex = ofToUpper(res);
            input->setText(mColorHex);
            input->setBackgroundColor(mColor);
            input->setTextInactiveColor(mColor.getBrightness() < BRIGHTNESS_THRESHOLD ? ofColor::white : ofColor::black);
        }
    
        void onInputChanged(ofxDatGuiInternalEvent e)
        {
            mColor = ofColor::fromHex(ofHexToInt(input->getText()));
            
        // set the input field text & background colors //
            input->setBackgroundColor(mColor);
            input->setTextInactiveColor(mColor.getBrightness() < BRIGHTNESS_THRESHOLD ? ofColor::white : ofColor::black);
            
        // update the gradient picker //
            gColors[1] = mColor;
            vbo.setColorData(&gColors[0], 4, GL_DYNAMIC_DRAW );
            
        // dispatch change event out to the main application //
            ofxDatGuiColorPickerEvent evt(this, mColor);
            colorPickerEventCallback(evt);
        }
    
    private:

        ofColor mColor;
        ofColor gColor;
        string mColorHex;
    
        ofImage rainbow;
        int rainbowWidth;
        int rainbowHeight;
        bool mShowPicker;
    
        ofVbo vbo;
        vector<ofVec2f> gPoints;
        vector<ofFloatColor> gColors;
        ofRectangle pickerRect;
        ofRectangle rainbowRect;
        ofRectangle gradientRect;
    
        static const int BRIGHTNESS_THRESHOLD = 185;

};

