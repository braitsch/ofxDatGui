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

class ofxDatGuiBreak : public ofxDatGuiComponent{

    public:
    
        ofxDatGuiBreak(int height = 0, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent("", tmplt)
        {
            if (height > 0){
                mHeight = height;
            }   else {
                mHeight = mTemplate->row.height * .1;
            }
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofFill();
                ofSetColor(mTemplate->row.color.bkgd, mAlpha);
                ofDrawRectangle(x, y, mRow.width, mHeight);
            ofPopStyle();
        }
    
        int getHeight()
        {
            return mHeight;
        }
    
        bool hitTest(ofPoint m)
        {
            return false;
        }
    
    private:
        float mHeight;
        

};

class ofxDatGuiLabel : public ofxDatGuiComponent{

    public:
        
        ofxDatGuiLabel(string label, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            mStripeColor = mTemplate->label.color.stripe;
        }
    
        void draw()
        {
            ofxDatGuiComponent::drawBkgd();
            ofxDatGuiComponent::drawLabel();
            ofxDatGuiComponent::drawStripe();
        }
    
        bool hitTest(ofPoint m)
        {
            return false;
        }
    
    protected:


};