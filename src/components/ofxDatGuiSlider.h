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

class ofxDatGuiSlider : public ofxDatGuiItem {

    public:
    
        ofxDatGuiSlider(string label, float min, float max, float val) : ofxDatGuiItem(label)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            mStripeColor = ofxDatGuiColor::SLIDER_STRIPE;
            input = new ofxDatGuiTextInputField(sliderInputWidth);
            input->setText(ofToString(mVal, 2));
            input->setTextInactiveColor(ofxDatGuiColor::SLIDER);
            input->setTextIndent(ofxDatGuiFont::retinaEnabled ? TEXT_INDENT*2 : TEXT_INDENT);
            input->setTextInputFieldType(ofxDatGuiTextInputField::NUMERIC);
            input->onInternalEvent(this, &ofxDatGuiSlider::onInputChanged);
            calcScale();
        }
    
        ~ofxDatGuiSlider()
        {
            delete input;
            cout << "bye bye" << endl;
        }
    
        void onInputChanged(ofxDatGuiInternalEvent e)
        {
            setValue(ofToFloat(input->getText()));
            dispatchSliderChangedEvent();
        }
    
        void setValue(float value)
        {
            mVal = value;
            calcScale();
        }
    
        float getValue()
        {
            return mVal;
        }
    
        void setScale(float scale)
        {
            mScale = scale;
            if (mScale < 0 || mScale > 1){
                ofLogError() << "row #" << mId << " : scale must be between 0 & 1" << " [setting to 50%]";
                mScale = 0.5f;
            }
            mVal = ((mMax-mMin) * mScale) + mMin;
        }
    
        float getScale()
        {
            return mScale;
        }
    
        void draw()
        {
            if (mVisible){
                ofPushStyle();
                    ofxDatGuiItem::drawBkgd();
                    ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                    ofxDatGuiItem::drawStripe();
                // slider bkgd //
                    ofSetColor(ofxDatGuiColor::INPUT);
                    ofDrawRectangle(x+sliderX, y+mPadding, sliderWidth, mHeight-(mPadding*2));
                // slider fill //
                    if (mScale > 0){
                        ofSetColor(ofxDatGuiColor::SLIDER);
                        ofDrawRectangle(x+sliderX, y+mPadding, sliderWidth*mScale, mHeight-(mPadding*2));
                    }
                // numeric input field //
                input->draw(x + sliderInputX, y + mPadding);
                ofPopStyle();
            }
        }
    
        void onFocusLost()
        {
            if (mInputActive) input->onFocusLost();
        }
    
        void onMousePress(ofPoint m)
        {
            if (input->hitTest(m)){
                input->onFocus();
                mInputActive = true;
            }   else{
                input->onFocusLost();
                mInputActive = false;
            }
        }
    
        void onMouseDrag(ofPoint m)
        {
            if (mInputActive == false){
                float s = (m.x-x-sliderX)/sliderWidth;
                if (s > .99) s = 1;
                if (s < .01) s = 0;
        // don't dispatch an event if scale hasn't changed //
                if (s == mScale) return;
                mScale = s;
                mVal = ((mMax-mMin) * mScale) + mMin;
                input->setText(ofToString(mVal, 2));
                dispatchSliderChangedEvent();
            }
        }
    
        void dispatchSliderChangedEvent()
        {
        // dispatch event out to main application //
            ofxDatGuiSliderEvent e(this, mVal, mScale);
            sliderEventCallback(e);
        }
    
        void onKeyPressed(int key)
        {
            if (mInputActive) input->onKeyPressed(key);
        }
    
        bool hitTest(ofPoint m)
        {
            if (m.x>=x+sliderX && m.x<= x+sliderX+sliderWidth && m.y>=y+mPadding && m.y<= y+mHeight-mPadding){
                return true;
            }   else if (input->hitTest(m)){
                return true;
            }   else{
                return false;
            }
        }
    
    private:
        float mMin;
        float mMax;
        float mVal;
        float mScale;
        bool mChanged;
        bool mInputActive;
        ofxDatGuiTextInputField* input;
        int static const TEXT_INDENT = 12;
    
        void calcScale()
        {
            if (mMax <= mMin || mMin >= mMax){
                ofLogError() << "row #" << mId << " : invalid min & max values" << " [setting to 50%]";
                mMin = 0;
                mMax = 100;
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else if (mVal > mMax || mVal < mMin){
                ofLogWarning() << "row #" << mId << " : "<< mVal << " is out of range" << " [setting to 50%]";
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else{
                if (mMin<0){
                    float n = abs(mMin);
                    float a = mMin+n;
                    float b = mMax+n;
                    float c = mVal+n;
                    mScale = (c-a)/(b-a);
                }   else{
                    mScale = (mVal-mMin)/(mMax-mMin);
                }
            }
            input->setText(ofToString(mVal, 2));
        }
        
};

