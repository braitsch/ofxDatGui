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
            scale = 0;
            mVal = val;
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
                if (scale > 0){
                    ofSetColor(ofxDatGuiColor::input_fill);
                    ofDrawRectangle(x+inputX, y+itemPadding, inputWidth*scale, itemHeight-(itemPadding*2));
                }
            // item label //
                ofSetColor(ofColor::white);
                ofxDatGuiCore::font.drawString(mLabel, x+labelPos.x, y+labelPos.y);
            }; ofPopStyle();
        }
        void onMousePress(ofPoint m)
        {
            scale =(m.x-x-inputX)/inputWidth;
            if (scale > .99) scale = 1;
            if (scale < .01) scale = 0;
        }
    
    protected:
        float mVal;
        float scale;
        void setScale(ofPoint m);
    
    private:
        string mLabel;
        ofPoint labelPos;
        
};
