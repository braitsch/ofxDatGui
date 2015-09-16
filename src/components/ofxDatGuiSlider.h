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
#include "ofxDatGuiComponent.h"
#include "ofxDatGuiTextInputField.h"

class ofxDatGuiSlider : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiSlider(string label, float min, float max, float val, ofxDatGuiFont* font=nullptr) : ofxDatGuiComponent(label, font)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            mType = ofxDatGuiType::SLIDER;
            mStripeColor = ofxDatGuiColor::SLIDER_STRIPE;
            input = new ofxDatGuiTextInputField(mRow.height-(mRow.padding*2), mFont);
            input->setText(ofToString(mVal, 2));
            input->setTextInactiveColor(ofxDatGuiColor::SLIDER);
            input->setTextInputFieldType(ofxDatGuiTextInputField::NUMERIC);
            input->onInternalEvent(this, &ofxDatGuiSlider::onInputChanged);
            calcScale();
        // set width & position of the text input field //
            setOrigin(0, 0);
            setWidth(mRetinaEnabled ? 540 : 320);
        }
    
        ofxDatGuiSlider(string label, float min, float max) : ofxDatGuiSlider(label, min, max, (max+min)/2) {}
    
        ~ofxDatGuiSlider()
        {
            delete input;
        }
    
        static ofxDatGuiSlider* getInstance()
        {
            return new ofxDatGuiSlider("X", 0, 100);
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
                ofLogError() << "row #" << mIndex << " : scale must be between 0 & 1" << " [setting to 50%]";
                mScale = 0.5f;
            }
            mVal = ((mMax-mMin) * mScale) + mMin;
        }
    
        float getScale()
        {
            return mScale;
        }
    
        void setWidth(int w)
        {
            ofxDatGuiComponent::setWidth(w);
            input->setWidth(mSlider.inputWidth);
            input->setOrigin(x + mSlider.inputX, y + mRow.padding);
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            input->setOrigin(x + mSlider.inputX, y + mRow.padding);
        }

        void draw()
        {
            ofPushStyle();
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
            // slider bkgd //
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(x+mRow.inputX, y+mRow.padding, mSlider.width, mRow.height-(mRow.padding*2));
            // slider fill //
                if (mScale > 0){
                    ofSetColor(ofxDatGuiColor::SLIDER);
                    ofDrawRectangle(x+mRow.inputX, y+mRow.padding, mSlider.width*mScale, mRow.height-(mRow.padding*2));
                }
            // numeric input field //
                input->draw();
            ofPopStyle();
        }
    
        void onFocusLost()
        {
            ofxDatGuiComponent::onFocusLost();
            if (mInputActive) input->onFocusLost();
        }
    
        void onMousePress(ofPoint m)
        {
            ofxDatGuiComponent::onMousePress(m);
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
                float s = (m.x-x-mRow.inputX)/mSlider.width;
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
            if (sliderEventCallback != nullptr) {
                ofxDatGuiSliderEvent e(this, mVal, mScale);
                sliderEventCallback(e);
            }   else{
                ofxDatGuiLog(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void onKeyPressed(int key)
        {
            if (mInputActive) input->onKeyPressed(key);
        }
    
        bool hitTest(ofPoint m)
        {
            if (m.x>=x+mRow.inputX && m.x<= x+mRow.inputX+mSlider.width && m.y>=y+mRow.padding && m.y<= y+mRow.height-mRow.padding){
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
    
        void calcScale()
        {
            if (mMax <= mMin || mMin >= mMax){
                ofLogError() << "row #" << mIndex << " : invalid min & max values" << " [setting to 50%]";
                mMin = 0;
                mMax = 100;
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else if (mVal > mMax || mVal < mMin){
                ofLogWarning() << "row #" << mIndex << " : "<< mVal << " is out of range" << " [setting to 50%]";
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

