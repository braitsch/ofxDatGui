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
    
        ofxDatGuiButton(string label, ofxDatGuiFont* font=nullptr) : ofxDatGuiComponent(label, font)
        {
            mType = ofxDatGuiType::BUTTON;
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
        }
    
        static ofxDatGuiButton* getInstance()
        {
            return new ofxDatGuiButton("X");
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            mLabelAreaWidth = mRow.width;
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
            ofPopStyle();
        }
    
        void drawBkgd()
        {
        // anything that extends ofxDatGuiButton has the same rollover effect //
            if (mMouseDown){
                ofxDatGuiComponent::drawBkgd(ofxDatGuiColor::BUTTON_DOWN, 255);
            }   else if (mMouseOver){
                ofxDatGuiComponent::drawBkgd(ofxDatGuiColor::BUTTON_OVER, 255);
            }   else{
                ofxDatGuiComponent::drawBkgd(ofxDatGuiColor::ROW_BKGD);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+mRow.width && m.y>=y && m.y<= y+mRow.height);
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiComponent::onMouseRelease(m);
        // dispatch event out to main application //
            if (buttonEventCallback != nullptr) {
                ofxDatGuiButtonEvent e(this);
                buttonEventCallback(e);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        virtual void toggle(){}
        virtual void setEnabled(bool enable){}
        virtual bool getEnabled(){return false;}
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(string label, bool enabled, ofxDatGuiFont* font=nullptr) : ofxDatGuiButton(label, font)
        {
            mEnabled = enabled;
            mStripeColor = ofxDatGuiColor::TOGGLE_STRIPE;
            if (!radioOn.isAllocated()) radioOn.load(ofxDatGuiAssetDir+"/icon-radio-on.png");
            if (!radioOff.isAllocated()) radioOff.load(ofxDatGuiAssetDir+"/icon-radio-off.png");
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            mLabelMarginRight = mRow.width-mIcon.x;
        }
    
        void toggle()
        {
            mEnabled =!mEnabled;
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
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiComponent::drawLabel();
            ofxDatGuiComponent::drawStripe();
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::LABEL);
                if (mEnabled == true){
                    radioOn.draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
                }   else{
                    radioOff.draw(x+mIcon.x, y+mIcon.y, mIcon.size, mIcon.size);
                }
            ofPopStyle();
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiComponent::onMouseRelease(m);
            mEnabled = !mEnabled;
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
        ofImage radioOn;
        ofImage radioOff;

};



