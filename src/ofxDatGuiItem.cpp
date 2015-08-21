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
    mIsExpanded = false;
    x = ofxDatGuiPosition::x + ofxDatGuiPadding;
    y = ofxDatGuiPosition::y + ofxDatGuiPadding + (mId*(rowHeight+rowSpacing));
    originY = y;
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

bool ofxDatGuiItem::isExpanded()
{
    return mIsExpanded;
}

void ofxDatGuiItem::setYPosition(uint16_t ypos)
{
    y = originY + ypos;
}

// draw methods //

void ofxDatGuiItem::drawBkgd(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, rowWidth, rowHeight);
    ofPopStyle();
}

void ofxDatGuiItem::drawLabel(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawBitmapString(mLabel, x+labelPosition.x, y+labelPosition.y - 1);
    ofPopStyle();
}

void ofxDatGuiItem::drawStripe(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, 2, rowHeight);
    ofPopStyle();
}

// mouse events //

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

