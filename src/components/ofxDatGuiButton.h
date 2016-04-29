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

class ofxDatGuiButton : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiButton(string label) : ofxDatGuiComponent(label)
        {
            mType = ofxDatGuiType::BUTTON;
            setTheme(ofxDatGuiComponent::theme.get());
        }
    
        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            mStyle.stripe.color = theme->stripe.button;
            setWidth(theme->layout.width, theme->layout.labelWidth);
        }
    
        void setWidth(int width, float labelWidth = 1)
        {
            ofxDatGuiComponent::setWidth(width, labelWidth);
            mLabel.width = mStyle.width;
            mLabel.rightAlignedXpos = mLabel.width - mLabel.margin;
            ofxDatGuiComponent::positionLabel();
        }
    
        void draw()
        {
            if (mVisible) {
            // anything that extends ofxDatGuiButton has the same rollover effect //
                ofPushStyle();
                    if (mStyle.border.visible) drawBorder();
                    ofFill();
                    if (mFocused && mMouseDown){
                        ofSetColor(mStyle.color.onMouseDown, mStyle.opacity);
                    }   else if (mMouseOver){
                        ofSetColor(mStyle.color.onMouseOver, mStyle.opacity);
                    }   else{
                        ofSetColor(mStyle.color.background, mStyle.opacity);
                    }
                    ofDrawRectangle(x, y, mStyle.width, mStyle.height);
                    drawLabel();
                    if (mStyle.stripe.visible) drawStripe();
                ofPopStyle();
            }
        }
    
        virtual void toggle(){}
        virtual void setEnabled(bool enable){}
        virtual bool getEnabled(){return false;}
    
        static ofxDatGuiButton* getInstance() { return new ofxDatGuiButton("X"); }
    
    protected:
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiComponent::onFocusLost();
            ofxDatGuiComponent::onMouseRelease(m);
        // dispatch event out to main application //
            if (buttonEventCallback != nullptr) {
                ofxDatGuiButtonEvent e(this);
                buttonEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(string label, bool enabled) : ofxDatGuiButton(label)
        {
            mEnabled = enabled;
            mType = ofxDatGuiType::TOGGLE;
            setTheme(ofxDatGuiComponent::theme.get());
        }
    
        void setTheme(ofxDatGuiTheme* theme)
        {
            setComponentStyle(theme);
            radioOn = theme->icon.radioOn;
            radioOff = theme->icon.radioOff;
            mStyle.stripe.color = theme->stripe.toggle;
            setWidth(theme->layout.width, theme->layout.labelWidth);
        }
    
        void setWidth(int width, float labelWidth = 1)
        {
            ofxDatGuiComponent::setWidth(width, labelWidth);
            mLabel.width = mStyle.width;
            mLabel.rightAlignedXpos = mIcon.x - mLabel.margin;
            ofxDatGuiComponent::positionLabel();
        }
    
        void toggle()
        {
            mEnabled = !mEnabled;
        }
    
        void setEnabled(bool enable)
        {
            mEnabled = enable;
        }
    
        bool getEnabled()
        {
            return mEnabled;
        }

        void draw()
        {
            if (mVisible) {
                ofPushStyle();
                ofxDatGuiButton::draw();
                ofSetColor(mIcon.color);
                if (mEnabled == true){
                    radioOn->draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
                }   else{
                    radioOff->draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
                }
                ofPopStyle();
            }
        }
    
        static ofxDatGuiToggle* getInstance() { return new ofxDatGuiToggle("X", false); }
    
    protected:
    
        void onMouseRelease(ofPoint m)
        {
            mEnabled = !mEnabled;
            ofxDatGuiComponent::onFocusLost();
            ofxDatGuiComponent::onMouseRelease(m);
        // dispatch event out to main application //
            if (buttonEventCallback != nullptr) {
                ofxDatGuiButtonEvent e(this, mEnabled);
                buttonEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
    private:
        bool mEnabled;
        shared_ptr<ofImage> radioOn;
        shared_ptr<ofImage> radioOff;

};



