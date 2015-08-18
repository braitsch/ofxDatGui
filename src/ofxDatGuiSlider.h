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
    
        ofxDatGuiSlider(int index, string label, float val) : ofxDatGuiItem(index)
        {
            f = index;
            ofLogNotice(ofToString(index));
            mScale = val;
            mLabel = label;
            ofRectangle labelRect = ofxDatGuiCore::font.getStringBoundingBox(label, 0, 0);
            labelPos = ofPoint(labelX, labelRect.height+ ((itemHeight-labelRect.height)/2));
        }
    
        void draw()
        {
            ofxDatGuiItem::draw();
            ofPushStyle();{
            // input bkgd //
                ofSetColor(ofxDatGuiColor::input_bkgd);
                ofDrawRectangle(x+inputX, y+itemPadding, inputWidth, itemHeight-(itemPadding*2));
            // input fill //
                if (mScale > 0){
                    ofSetColor(ofxDatGuiColor::input_fill);
                    ofDrawRectangle(x+inputX, y+itemPadding, inputWidth*mScale, itemHeight-(itemPadding*2));
                }
            // item label //
                ofSetColor(ofxDatGuiColor::font_fill);
                ofxDatGuiCore::font.drawString(mLabel, x+labelPos.x, y+labelPos.y);
            }; ofPopStyle();
        }
        void onMousePress(ofPoint m)
        {
            mScale =(m.x-x-inputX)/inputWidth;
            if (mScale > .99) mScale = 1;
            if (mScale < .01) mScale = 0;
            changeEventCallback(mIndex);
        }
    
    protected:
        void setScale(ofPoint m);
    
    private:
        int f;
        float mScale;
        string mLabel;
        ofPoint labelPos;
        
};
