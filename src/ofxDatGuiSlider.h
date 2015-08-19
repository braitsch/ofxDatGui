//
//  ofxDatGuiSlider.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiSlider : public ofxDatGuiItem {

    public:
    
        ofxDatGuiSlider(int index, string label, float min, float max, float val) : ofxDatGuiItem(index, label)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            if (mMin<0){
                float n = abs(mMin);
                float a = mMin+n;
                float b = mMax+n;
                float c = mVal+n;
                mScale = c/(a+b);
            }   else{
                mScale = mVal/(mMax+mMin);
            }
        }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd();
            ofPushStyle();{
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
                ofSetColor(ofxDatGuiColor::SLIDER);
                ofDrawBitmapString(ofToString(mVal, 2), x+sliderLabelX+labelPosition.x, y+labelPosition.y - 1);
            //
            }; ofPopStyle();
        }
    
        void onMouseDrag(ofPoint m)
        {
            mScale =(m.x-x-sliderX)/sliderWidth;
            if (mScale > .99) mScale = 1;
            if (mScale < .01) mScale = 0;
            mVal = ((mMax-mMin) * mScale) + mMin;
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, mVal);
            changeEventCallback(evt);
        }
    
        void onMousePress(ofPoint m)
        {
    
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x+sliderX && m.x<= x+sliderX+sliderWidth && m.y>=y+rowPadding && m.y<= y+rowHeight-rowPadding);
        }
    
    protected:
        void setScale(ofPoint m);
    
    private:
        float mMin;
        float mMax;
        float mVal;
        float mScale;
        
};

