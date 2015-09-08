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

class ofxDatGuiButton : public ofxDatGuiItem {

    public:
    
        ofxDatGuiButton(ofxDatGuiGlobals *gui, string label) : ofxDatGuiItem(gui, label)
        {
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiButtonEvent e(this);
            buttonEventCallback(e);
        }
    
        void draw()
        {
            if (mVisible){
                drawBkgd();
                ofxDatGuiItem::drawLabel();
                ofxDatGuiItem::drawStripe();
            }
        }
    
        void drawBkgd()
        {
        // anything that extends ofxDatGuiButton has the same rollover effect //
            if (mMouseDown){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_DOWN);
            }   else if (mMouseOver){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_OVER);
            }   else{
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::ROW_BKGD, mGui->alpha);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+mGui->width && m.y>=y && m.y<= y+mHeight);
        }
    
        virtual void toggle(){}
        virtual void setEnabled(bool enable){}
        virtual bool getEnabled(){return false;}
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(ofxDatGuiGlobals *gui, string label, bool enabled) : ofxDatGuiButton(gui, label)
        {
            mEnabled = enabled;
            mStripeColor = ofxDatGuiColor::TOGGLE_STRIPE;
            if (!radioOn.isAllocated()) radioOn.load(ofxDatGuiAssetDir+"/icon-radio-on.png");
            if (!radioOff.isAllocated()) radioOff.load(ofxDatGuiAssetDir+"/icon-radio-off.png");
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
            if (mVisible){
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiItem::drawLabel();
                ofxDatGuiItem::drawStripe();
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    if (mEnabled == true){
                        radioOn.draw(x+mGui->icons.radio.x, y+mGui->icons.radio.y, mGui->icons.radio.size, mGui->icons.radio.size);
                    }   else{
                        radioOff.draw(x+mGui->icons.radio.x, y+mGui->icons.radio.y, mGui->icons.radio.size, mGui->icons.radio.size);
                    }
                ofPopStyle();
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            mEnabled = !mEnabled;
        // dispatch event out to main application //
            ofxDatGuiButtonEvent e(this, mEnabled);
            buttonEventCallback(e);
        }
    
    private:
        bool mEnabled;
        ofImage radioOn;
        ofImage radioOff;

};



