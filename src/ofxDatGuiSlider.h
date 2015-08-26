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

class ofxDatGuiSlider : public ofxDatGuiItem {

    public:
    
        ofxDatGuiSlider(int index, string label, float min, float max, float val) : ofxDatGuiItem(index, label)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            calcScale();
        }
    
        void setValue(float value)
        {
            mVal = value;
            calcScale();
        }
    
        int getValue()
        {
            return mVal;
        }
    
        void setScale(float scale)
        {
            mScale = scale;
            if (mScale < 0 || mScale > 1){
                ofLogError() << "row #" << mId << " : scale must be between 0 & 1" << " [setting to 50%]";
                mScale = 0.5f;
            }
            mVal = ((mMax-mMin) * mScale) + mMin;
        }
    
        float getScale()
        {
            return mScale;
        }
    
        void draw()
        {
            ofPushStyle();
                ofxDatGuiItem::drawBkgd();
                ofxDatGuiItem::drawStripe(ofxDatGuiColor::SLIDER_STRIPE);
                ofxDatGuiItem::drawLabel();
            // slider bkgd //
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(x+sliderX, y+rowPadding, sliderWidth, rowHeight-(rowPadding*2));
            // slider fill //
                if (mScale > 0){
                    ofSetColor(ofxDatGuiColor::SLIDER);
                    ofDrawRectangle(x+sliderX, y+rowPadding, sliderWidth*mScale, rowHeight-(rowPadding*2));
                }
            // value bkgd //
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(x+sliderLabelX, y+rowPadding, sliderLabelWidth, rowHeight-(rowPadding*2));
            // value label //
                ofxDatGuiItem::drawText(ofToString(mVal, 2), ofxDatGuiColor::SLIDER, x+sliderLabelX+labelX);
            //
            ofPopStyle();
        }

    
        void onMouseDrag(ofPoint m)
        {
            mScale =(m.x-x-sliderX)/sliderWidth;
            if (mScale > .99) mScale = 1;
            if (mScale < .01) mScale = 0;
            mVal = ((mMax-mMin) * mScale) + mMin;
        // dispatch event out to main application //
            ofxDatGuiEvent e(ofxDatGuiEventType::SLIDER_CHANGED, mId);
            e.value = mVal;
            e.scale = mScale;
            changeEventCallback(e);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x+sliderX && m.x<= x+sliderX+sliderWidth && m.y>=y+rowPadding && m.y<= y+rowHeight-rowPadding);
        }
    
    protected:

    
    private:
        float mMin;
        float mMax;
        float mVal;
        float mScale;
    
        void calcScale()
        {
            if (mMax <= mMin || mMin >= mMax){
                ofLogError() << "row #" << mId << " : invalid min & max values" << " [setting to 50%]";
                mMin = 0;
                mMax = 100;
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else if (mVal > mMax || mVal < mMin){
                ofLogWarning() << "row #" << mId << " : "<< mVal << " is out of range" << " [setting to 50%]";
                mScale = 0.5f;
                mVal = (mMax+mMin) * mScale;
            }   else{
                if (mMin<0){
                    float n = abs(mMin);
                    float a = mMin+n;
                    float b = mMax+n;
                    float c = mVal+n;
                    mScale = (c-a)/(b-a);
                }   else{
                    mScale = (mVal-mMin)/(mMax-mMin);
                }
            }
        }
        
};

