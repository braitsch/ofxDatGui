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

class ofxDatGui2dPad : public ofxDatGuiComponent {

    public:
    
        ofxDatGui2dPad(string label, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            init();
            mScaleOnResize = true;
            mBounds = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
    
        ofxDatGui2dPad(string label, ofRectangle bounds, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            init();
            mBounds = bounds;
            mScaleOnResize = false;
        }
    
        static ofxDatGui2dPad* getInstance()
        {
            return new ofxDatGui2dPad("X");
        }
    
        ofPoint getPosition()
        {
            return pWorld;
        }
    
        void setBounds(ofRectangle bounds)
        {
            mBounds = bounds;
            reset();
            mScaleOnResize = false;
        }
    
        void init()
        {
            reset();
            mType = ofxDatGuiType::PAD2D;
            mStyle.stripe.color = mTemplate->pad2d.color.stripe;
            mStyle.height = mTemplate->pad2d.height;
            mPad = ofRectangle(0, 0, mStyle.width-mStyle.padding-mLabel.width, mStyle.height-(mStyle.padding*2));
            setWidth(mStyle.width);
        }
    
        void reset()
        {
            mx = 0.5f;
            my = 0.5f;
            pWorld.x = mBounds.x + (mBounds.width*mx);
            pWorld.y = mBounds.y + (mBounds.height*my);
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            if (mScaleOnResize){
        // scale the bounds to the resized window //
                mBounds.width*=(ofGetWidth()/mBounds.width);
                mBounds.height*=(ofGetHeight()/mBounds.height);
            }
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiComponent::setTemplate(tmplt);
            mStyle.height = mTemplate->pad2d.height;
            mPad = ofRectangle(0, 0, mStyle.width-mStyle.padding-mLabel.width, mStyle.height-(mStyle.padding*2));
            setWidth(mStyle.width);
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                mPad.x = x + mLabel.width;
                mPad.y = y + mStyle.padding;
                mPad.width = mStyle.width-mStyle.padding-mLabel.width;
                pLocal.x = mPad.x + mPad.width * mx;
                pLocal.y = mPad.y + mPad.height * my;
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
                ofSetColor(mTemplate->row.color.inputArea);
                ofDrawRectangle(mPad);
                ofSetLineWidth(2);
                ofSetColor(mTemplate->pad2d.color.lines);
                ofDrawLine(mPad.x, pLocal.y, mPad.x+mPad.width, pLocal.y);
                ofDrawLine(pLocal.x, mPad.y, pLocal.x, mPad.y+mPad.height);
                ofSetColor(mTemplate->pad2d.color.circle);
                ofDrawCircle(pLocal, 10);
            ofPopStyle();
        }
    
        void onMouseDrag(ofPoint m)
        {
            if (mPad.inside(m)){
                mx = (m.x-mPad.x)/mPad.width;
                my = (m.y-mPad.y)/mPad.height;
                pWorld.x = mBounds.x + (mBounds.width*mx);
                pWorld.y = mBounds.y + (mBounds.height*my);
            // dispatch event out to main application //
                if (pad2dEventCallback != nullptr) {
                    ofxDatGui2dPadEvent e(this, pWorld.x, pWorld.y);
                    pad2dEventCallback(e);
                }   else{
                    ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
                }
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
    