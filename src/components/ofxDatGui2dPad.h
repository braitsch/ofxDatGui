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

class ofxDatGui2dPad : public ofxDatGuiItem {

    public:
    
        ofxDatGui2dPad(ofxDatGuiGlobals *gui, string label) : ofxDatGuiItem(gui, label)
        {
            init();
            mScaleOnResize = true;
            mBounds = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
    
        ofxDatGui2dPad(ofxDatGuiGlobals *gui, string label, ofRectangle bounds) : ofxDatGuiItem(gui, label)
        {
            init();
            mBounds = bounds;
            mScaleOnResize = false;
        }
    
        void init()
        {
            reset();
            mHeight = 140;
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
            mPad = ofRectangle(0, 0, mWidth-mPadding-mGui->input.x, mHeight-(mPadding*2));
        }
    
        void reset()
        {
            mx = 0.5f;
            my = 0.5f;
        }
    
        void draw()
        {
            if (mVisible){
                mPad.x = x + mGui->input.x;
                mPad.y = y + mPadding;
                pt.x = mPad.x + mPad.width * mx;
                pt.y = mPad.y + mPad.height * my;
                drawBkgd();
                ofxDatGuiItem::drawLabel();
                ofxDatGuiItem::drawStripe();
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(mPad);
                ofSetLineWidth(2);
                ofSetColor(ofxDatGuiColor::LABEL);
                ofDrawCircle(pt, 10);
                ofDrawLine(mPad.x, pt.y, mPad.x+mPad.width, pt.y);
                ofDrawLine(pt.x, mPad.y, pt.x, mPad.y+mPad.height);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+mWidth && m.y>=y && m.y<= y+mHeight);
        }
    
        void onMouseDrag(ofPoint m)
        {
            if (mPad.inside(m)){
                mx = (m.x-mPad.x)/mPad.width;
                my = (m.y-mPad.y)/mPad.height;
                ofxDatGui2dPadEvent e(this, mBounds.x + (mBounds.width*mx), mBounds.y + (mBounds.height*my));
                pad2dEventCallback(e);
            }
        }
    
        void onWindowResize(int w, int h)
        {
            if (mScaleOnResize){
        // scale the bounds to the resized window //
                mBounds.width*=(w/mBounds.width);
                mBounds.height*=(h/mBounds.height);
            }
            ofxDatGuiItem::onWindowResize(w, h);
        }
    
    private:
        float mx;
        float my;
        bool mScaleOnResize;
        ofPoint pt;
        ofRectangle mPad;
        ofRectangle mBounds;
    
};
    