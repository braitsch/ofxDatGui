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
            input = new ofxDatGuiTextInputField();
            input->setTextInputFieldType(ofxDatGuiInputType::NUMERIC);
            input->onInternalEvent(this, &ofxDatGuiSlider::onInputChanged);
            setTheme(ofxDatGuiComponent::theme.get());
        }
    
        ofxDatGuiSlider(string label, float min, float max) : ofxDatGuiSlider(label, min, max, (max+min)/2) {}
        ofxDatGuiSlider(ofParameter<int> & p) : ofxDatGuiSlider(p.getName(), p.getMin(), p.getMax(), p.get()) {
            mParamI = &p;
            mPrecision = 0;
            calculateScale();
            mParamI->addListener(this, &ofxDatGuiSlider::onParamI);
        }
        ofxDatGuiSlider(ofParameter<float> & p) : ofxDatGuiSlider(p.getName(), p.getMin(), p.getMax(), p.get()) {
            mParamF = &p;
            mPrecision = 2;
            calculateScale();
            mParamF->addListener(this, &ofxDatGuiSlider::onParamF);
        }
    
        ~ofxDatGuiSlider()
        {
            delete input;
        }
    
        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            mSliderFill = theme->color.slider.fill;
            mBackgroundFill = theme->color.inputAreaBackground;
            mStyle.stripe.color = theme->stripe.slider;
            input->setTheme(theme);
            input->setTextInactiveColor(theme->color.slider.text);
            calculateScale();
            setWidth(theme->layout.width, theme->layout.labelWidth);
        }
    
        void setWidth(int width, float labelWidth)
        {
            ofxDatGuiComponent::setWidth(width, labelWidth);
            float totalWidth = mStyle.width - mLabel.width;
            mSliderWidth = totalWidth * .7;
            mInputX = mLabel.width + mSliderWidth + mStyle.padding;
            mInputWidth = totalWidth - mSliderWidth - (mStyle.padding * 2);
            input->setWidth(mInputWidth);
            input->setPosition(x + mInputX, y + mStyle.padding);
        }
    
        void setPosition(int x, int y)
        {
            ofxDatGuiComponent::setPosition(x, y);
            input->setPosition(x + mInputX, y + mStyle.padding);
        }
    
        void setPrecision(int precision)
        {
            mPrecision = precision;
    // max precision is currently four decimal places //
            if (mPrecision > 4) mPrecision = 4;
            calculateScale();
        }
    
        void setMin(float min)
        {
            mMin = min;
            calculateScale();
        }
    
        void setMax(float max)
        {
            mMax = max;
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

    /*
        variable binding methods
    */
    
        void bind(int &val)
        {
            mBoundi = &val;
            mBoundf = nullptr;
        }
    
        void bind(float &val)
        {
            mBoundf = &val;
            mBoundi = nullptr;
        }

        void bind(int &val, int min, int max)
        {
            mMin = min;
            mMax = max;
            mBoundi = &val;
            mBoundf = nullptr;
        }
    
        void bind(float &val, float min, float max)
        {
            mMin = min;
            mMax = max;
            mBoundf = &val;
            mBoundi = nullptr;
        }

        void draw()
        {
            if (!mVisible) return;
            // check for bound variables //
            if (mBoundf != nullptr) {
                getBoundf();
            }   else if (mBoundi != nullptr){
                getBoundi();
            }
            
            ofPushStyle();
                ofxDatGuiComponent::draw();
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
            if (!mEnabled || !mVisible){
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
            
            if (mParamI != nullptr) mParamI->set(mVal);
            if (mParamF != nullptr) mParamF->set(mVal);
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
        ofParameter<int>* mParamI = nullptr;
        ofParameter<float>* mParamF = nullptr;
    
        void onParamI(int& n) { setValue(n); }
        void onParamF(float& n) { setValue(n); }
    
        void calculateScale()
        {
            if (mMax <= mMin || mMin >= mMax){
                ofLogError() << "row #" << mIndex << " : invalid min & max values" << " [setting to 50%]";
                mMin = 0;
                mMax = 100;
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else if (mVal > mMax){
                mVal = mMax;
                mVal = (mMax+mMin) * mScale;
            }   else if (mVal < mMin){
                mVal = mMin;
                mVal = (mMax+mMin) * mScale;
            }   else{
                mScale = ofxDatGuiScale(mVal, mMin, mMax);
            }
            mVal = round(mVal, mPrecision);
            if (mParamI != nullptr){
                mParamI->set(mVal);
            }   else if (mParamF != nullptr){
                mParamF->set(mVal);
            }
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
    
    /*
        private variable binding methods
    */
    
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
        
};

