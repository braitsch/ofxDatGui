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
    
        ofxDatGuiSlider(int index, string label, float min, float max, float val) : ofxDatGuiItem(index)
        {
            mMin = min;
            mMax = max;
            mVal = val;
            if (mMin<0){
                float o = abs(mMin);
                float a = mMin+o;
                float b = mMax+o;
                float c = mVal+o;
                cout << "ofxDatGui::scale " << a << "::" << b << "::" << c << endl;
                mScale = c/(a+b);
            }   else{
                mScale = mVal/(mMax+mMin);
            }
            mLabel = label;
            ofRectangle labelRect = ofxDatGuiCore::font.getStringBoundingBox(label, 0, 0);
            labelPos = ofPoint(labelX, labelRect.height+ ((rowHeight-labelRect.height)/2));
        }
    
        void draw()
        {
            ofxDatGuiItem::draw();
            ofPushStyle();{
            // item label //
                ofSetColor(ofxDatGuiColor::font_fill);
                ofDrawBitmapString(mLabel, x+labelPos.x, y+labelPos.y - 1);
            //  ofxDatGuiCore::font.drawString(mLabel, x+labelPos.x, y+labelPos.y);
            // slider bkgd //
                ofSetColor(ofxDatGuiColor::slider_bkgd);
                ofDrawRectangle(x+sliderX, y+rowPadding, sliderWidth, rowHeight-(rowPadding*2));
            // slider fill //
                if (mScale > 0){
                    ofSetColor(ofxDatGuiColor::slider_fill);
                    ofDrawRectangle(x+sliderX, y+rowPadding, sliderWidth*mScale, rowHeight-(rowPadding*2));
                }
            // value bkgd //
                ofSetColor(ofxDatGuiColor::slider_bkgd);
                ofDrawRectangle(x+sliderLabelX, y+rowPadding, sliderLabelWidth, rowHeight-(rowPadding*2));
            // value label //
                ofSetColor(ofxDatGuiColor::slider_fill);
                ofDrawBitmapString(ofToString(mVal, 2), x+sliderLabelX+labelPos.x, y+labelPos.y - 1);
            //  ofxDatGuiCore::font.drawString(ofToString(mScale), x+inputX+labelPos.x, y+labelPos.y);
            }; ofPopStyle();
        }
        
        void onMousePress(ofPoint m)
        {
            mScale =(m.x-x-sliderX)/sliderWidth;
            if (mScale > .99) mScale = 1;
            if (mScale < .01) mScale = 0;
            mVal = ((mMax-mMin) * mScale) + mMin;
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, mVal);
            changeEventCallback(evt);
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
        string mLabel;
        ofPoint labelPos;
        
};
