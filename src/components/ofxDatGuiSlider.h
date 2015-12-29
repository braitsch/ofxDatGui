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
    
        ofxDatGuiSlider(string label, float min, float max, float val) : ofxDatGuiComponent(label)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            mPrecision = 2;
            mType = ofxDatGuiType::SLIDER;
            input = new ofxDatGuiTextInputField(mStyle.height - (mStyle.padding * 2));
            input->setTextInputFieldType(ofxDatGuiTextInputField::NUMERIC);
            input->onInternalEvent(this, &ofxDatGuiSlider::onInputChanged);
            onThemeSet(ofxDatGuiComponent::getTheme());
        }
    
        ofxDatGuiSlider(string label, float min, float max) : ofxDatGuiSlider(label, min, max, (max+min)/2) {}
    
        ~ofxDatGuiSlider()
        {
            delete input;
        }
    
        void setPrecision(int precision)
        {
            mPrecision = precision;
    // max precision is currently four decimal places //
            if (mPrecision > 4) mPrecision = 4;
            calculateScale();
        }
    
        void setValue(float value)
        {
            mVal = value;
            calculateScale();
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
            float totalWidth = mStyle.width - mLabel.width;
            mSliderWidth = totalWidth * .7;
            mInputX = mLabel.width + mSliderWidth + mStyle.padding;
            mInputWidth = totalWidth - mSliderWidth - (mStyle.padding * 2);
            input->setWidth(mInputWidth);
            input->setOrigin(x + mInputX, y + mStyle.padding);
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            input->setOrigin(x + mInputX, y + mStyle.padding);
        }

    /*
        data binding - experiemental feature
    */

        void bind(int *val, int min, int max)
        {
            mMin = min;
            mMax = max;
            mBoundi = val;
            mBoundf = nullptr;
        }
    
        void bind(float *val, float min, float max)
        {
            mMin = min;
            mMax = max;
            mBoundf = val;
            mBoundi = nullptr;
        }
    
        inline void getBoundf()
        {
            if (*mBoundf != pVal) {
                setValue(*mBoundf);
                pVal = *mBoundf;
            }
        }
    
        inline void getBoundi()
        {
            if (*mBoundi != pVal) {
                setValue(*mBoundi);
                pVal = *mBoundi;
            }
        }
    
    /*
        data binding - experiemental feature
    */

        void draw()
        {
            if (!mVisible) return;
        // experimental - check for bound variables //
            if (mBoundf != nullptr) {
                getBoundf();
            }   else if (mBoundi != nullptr){
                getBoundi();
            }
            
            ofPushStyle();
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
            // slider bkgd //
                ofSetColor(mBackgroundFill);
                ofDrawRectangle(x+mLabel.width, y+mStyle.padding, mSliderWidth, mStyle.height-(mStyle.padding*2));
            // slider fill //
                if (mScale > 0){
                    ofSetColor(mSliderFill);
                    ofDrawRectangle(x+mLabel.width, y+mStyle.padding, mSliderWidth*mScale, mStyle.height-(mStyle.padding*2));
                }
            // numeric input field //
                input->draw();
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            if (!mEnabled){
                return false;
            }   else if (m.x>=x+mLabel.width && m.x<= x+mLabel.width+mSliderWidth && m.y>=y+mStyle.padding && m.y<= y+mStyle.height-mStyle.padding){
                return true;
            }   else if (input->hitTest(m)){
                return true;
            }   else{
                return false;
            }
        }
    
        static ofxDatGuiSlider* getInstance() { return new ofxDatGuiSlider("X", 0, 100); }
    
    protected:
    
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
            if (mFocused && mInputActive == false){
                float s = (m.x-x-mLabel.width)/mSliderWidth;
                if (s > .999) s = 1;
                if (s < .001) s = 0;
        // don't dispatch an event if scale hasn't changed //
                if (s == mScale) return;
                mScale = s;
                mVal = round((((mMax-mMin) * mScale) + mMin), mPrecision);
                setTextInput();
                dispatchSliderChangedEvent();
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiComponent::onMouseRelease(m);
            if (input->hitTest(m) == false) onFocusLost();
        }
    
        void onFocusLost()
        {
            ofxDatGuiComponent::onFocusLost();
            if (mInputActive) input->onFocusLost();
        }
    
        void onInputChanged(ofxDatGuiInternalEvent e)
        {
            setValue(ofToFloat(input->getText()));
            dispatchSliderChangedEvent();
        }
    
        void dispatchSliderChangedEvent()
        {
         // experimental - check for bound variables //
            if (mBoundf != nullptr) {
                *mBoundf = mVal;
            } else if (mBoundi != nullptr) {
                *mBoundi = mVal;
            }
            
        // dispatch event out to main application //
            if (sliderEventCallback != nullptr) {
                ofxDatGuiSliderEvent e(this, mVal, mScale);
                sliderEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        void onKeyPressed(int key)
        {
            if (mInputActive) input->onKeyPressed(key);
        }
    
        void onThemeSet(const ofxDatGuiTheme* tmplt)
        {
            mSliderFill = tmplt->color.slider.fill;
            mBackgroundFill = tmplt->color.inputAreaBackground;
            mStyle.stripe.color = tmplt->stripe.slider;
            input->setTheme(tmplt);
            input->setTextInactiveColor(tmplt->color.slider.text);
            calculateScale();
            setWidth(mStyle.width);
        }

    private:
    
        float   mMin;
        float   mMax;
        float   mVal;
        float   mScale;
        int     mPrecision;
        bool    mChanged;
        bool    mInputActive;
        int     mInputX;
        int     mInputWidth;
        int     mSliderWidth;
        ofColor mSliderFill;
        ofColor mBackgroundFill;
        ofxDatGuiTextInputField* input;
    
        float   pVal;
        int*    mBoundi = nullptr;
        float*  mBoundf = nullptr;
    
        void calculateScale()
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
                mScale = ofxDatGuiScale(mVal, mMin, mMax);
            }
            mVal = round(mVal, mPrecision);
            setTextInput();
        }
    
        void setTextInput()
        {
            string v = ofToString(mVal);
            if (mVal != mMin && mVal != mMax){
                int p = v.find('.');
                if (p == -1 && mPrecision != 0){
                    v+='.';
                    p = v.find('.');
                }
                while(v.length() - p < (mPrecision+1)) v+='0';
            }
            input->setText(v);
        }
    
        float round(float num, int precision)
        {
            return floorf(num * pow(10.0f, precision) + .5f)/pow(10.0f, precision);
        }
        
};

