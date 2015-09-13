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
    
        ofxDatGui2dPad(string label, ofxDatGuiFont* font=nullptr) : ofxDatGuiItem(label, font)
        {
            init();
            mScaleOnResize = true;
            mBounds = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
    
        ofxDatGui2dPad(string label, ofRectangle bounds, ofxDatGuiFont* font=nullptr) : ofxDatGuiItem(label, font)
        {
            init();
            mBounds = bounds;
            mScaleOnResize = false;
        }
    
        ofPoint getPosition()
        {
            return pWorld;
        }
    
        void setBounds(ofRectangle bounds)
        {
            mBounds = bounds;
            mScaleOnResize = false;
        }
    
        void init()
        {
            reset();
            mRow.height = 164;
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
            mPad = ofRectangle(0, 0, mRow.width-mRow.padding-mRow.inputX, mRow.height-(mRow.padding*2));
        }
    
        void reset()
        {
            mx = 0.5f;
            my = 0.5f;
        }
    
        void setOriginX(int x)
        {
            ofxDatGuiItem::setOriginX(x);
            if (mScaleOnResize){
        // scale the bounds to the resized window //
                mBounds.width*=(ofGetWidth()/mBounds.width);
                mBounds.height*=(ofGetHeight()/mBounds.height);
            }
        }
    
        void draw()
        {
            mPad.x = x + mRow.inputX;
            mPad.y = y + mRow.padding;
            mPad.width = mRow.width-mRow.padding-mRow.inputX;
            pLocal.x = mPad.x + mPad.width * mx;
            pLocal.y = mPad.y + mPad.height * my;
            ofxDatGuiItem::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe();
            ofSetColor(ofxDatGuiColor::INPUT);
            ofDrawRectangle(mPad);
            ofSetLineWidth(2);
            ofSetColor(ofxDatGuiColor::LABEL);
            ofDrawCircle(pLocal, 10);
            ofDrawLine(mPad.x, pLocal.y, mPad.x+mPad.width, pLocal.y);
            ofDrawLine(pLocal.x, mPad.y, pLocal.x, mPad.y+mPad.height);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+mRow.width && m.y>=y && m.y<= y+mRow.height);
        }
    
        void onMouseDrag(ofPoint m)
        {
            if (mPad.inside(m)){
                mx = (m.x-mPad.x)/mPad.width;
                my = (m.y-mPad.y)/mPad.height;
                pWorld.x = mBounds.x + (mBounds.width*mx);
                pWorld.y = mBounds.y + (mBounds.height*my);
                ofxDatGui2dPadEvent e(this, pWorld.x, pWorld.y);
                pad2dEventCallback(e);
            }
        }
    
    private:
        float mx;
        float my;
        bool mScaleOnResize;
        ofPoint pLocal;
        ofPoint pWorld;
        ofRectangle mPad;
        ofRectangle mBounds;
    
};
    