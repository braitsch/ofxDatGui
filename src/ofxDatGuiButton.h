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
    
        ofxDatGuiButton(int index, string label) : ofxDatGuiItem(index, label)
        {
            mIsExpanded = false;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_CLICKED, mId);
            changeEventCallback(evt);
        }
    
        bool isExpanded()
        {
            return mIsExpanded;
        }
    
        void draw()
        {
            if (mVisible){
                drawBkgd();
                ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
            }
        }
    
        void drawBkgd()
        {
        // anything that extends ofxDatGuiButton has the same rollover effect //
            if (mMouseDown){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_DOWN, 255);
            }   else if (mMouseOver){
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::BUTTON_OVER, 255);
            }   else{
                ofxDatGuiItem::drawBkgd(ofxDatGuiColor::ROW_BKGD);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+mWidth && m.y>=y && m.y<= y+mHeight);
        }
    
        protected:
            bool mIsExpanded;
    
};

class ofxDatGuiToggle : public ofxDatGuiButton {
    
    public:
    
        ofxDatGuiToggle(int index, string label, bool enabled) : ofxDatGuiButton(index, label)
        {
            mEnabled = enabled;
            if (!radioOn.isAllocated()) radioOn.load(ofxDatGuiAssetDir+"icon-radio-on.png");
            if (!radioOff.isAllocated()) radioOff.load(ofxDatGuiAssetDir+"icon-radio-off.png");
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
                ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe(ofxDatGuiColor::TOGGLE_STRIPE);
                ofPushStyle();
                    ofSetColor(ofxDatGuiColor::LABEL);
                    if (mEnabled == true){
                        radioOn.draw(x+radioIconX, y+radioIconY, radioIconSize, radioIconSize);
                    }   else{
                        radioOff.draw(x+radioIconX, y+radioIconY, radioIconSize, radioIconSize);
                    }
                ofPopStyle();
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            mEnabled = !mEnabled;
        // dispatch event out to main application //
            ofxDatGuiEvent e(ofxDatGuiEventType::BUTTON_TOGGLED, mId);
            e.enabled = mEnabled;
            changeEventCallback(e);
        }
    
    private:
        bool mEnabled;
        ofImage radioOn;
        ofImage radioOff;

};

class ofxDatGuiToggler : public ofxDatGuiButton {


    public:
    
        ofxDatGuiToggler() : ofxDatGuiButton(9999, "COLLAPSE CONTROLS")
        {
            mIsExpanded = true;
            mHeight = ofxDatGuiGlobals::rowHeight*.8;
            setLabel("COLLAPSE CONTROLS");
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2, true);
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
        }
    
        int getOriginY()
        {
            return mOriginY;
        }
    
        void setOriginY(int y)
        {
            this->y = mOriginY = y;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiEvent e(ofxDatGuiEventType::GUI_TOGGLED, mId);
            e.value = mIsExpanded;
            changeEventCallback(e);
            if (mIsExpanded){
                mIsExpanded = false;
                setLabel("EXPAND CONTROLS");
            }   else{
                mIsExpanded = true;
                setLabel("COLLAPSE CONTROLS");
            }
        }
    
};


