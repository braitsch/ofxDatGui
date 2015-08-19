//
//  ofxDatGuiItem.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGuiItem.h"

const uint16_t ofxDatGuiItem::rowWidth = ofxDatGuiWidth -(ofxDatGuiPadding*2);
const uint16_t ofxDatGuiItem::rowHeight = 26;
const uint16_t ofxDatGuiItem::rowPadding = 4;
const uint16_t ofxDatGuiItem::rowSpacing = 1;
const uint16_t ofxDatGuiItem::labelX = 12;
const uint16_t ofxDatGuiItem::labelWidth = 80;
ofPoint ofxDatGuiItem::labelPosition = ofPoint(12, 19);

const uint16_t ofxDatGuiItem::sliderX = labelX+labelWidth+rowPadding;
const uint16_t ofxDatGuiItem::sliderWidth = 100;
const uint16_t ofxDatGuiItem::sliderLabelX = sliderX+sliderWidth+rowPadding;
const uint16_t ofxDatGuiItem::sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    x = ofxDatGuiPosition::x + ofxDatGuiPadding;
    y = ofxDatGuiPosition::y + ofxDatGuiPadding + (mId*(rowHeight+rowSpacing));
}

ofxDatGuiItem::ofxDatGuiItem(int id, string label, bool centerLabel) : ofxDatGuiItem(id)
{
    mLabel = label;
    mMouseOver = false;
}

string ofxDatGuiItem::getLabel()
{
    return mLabel;
}

void ofxDatGuiItem::drawBkgd(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, rowWidth, rowHeight);
    ofPopStyle();
}

void ofxDatGuiItem::onMouseEnter(ofPoint m)
{
     mMouseOver = true;
}

void ofxDatGuiItem::onMouseLeave(ofPoint m)
{
     mMouseOver = false;
}

void ofxDatGuiItem::onMousePress(ofPoint m) { }
void ofxDatGuiItem::onMouseDrag(ofPoint m) { }
void ofxDatGuiItem::onMouseRelease(ofPoint m) { }

void ofxDatGuiItem::drawLabel(ofColor color)
{
    ofSetColor(color);
    ofDrawBitmapString(mLabel, x+labelPosition.x, y+labelPosition.y - 1);
}

