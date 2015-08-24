//
//  ofxDatGuiItem.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGuiItem.h"

uint16_t ofxDatGuiItem::guiWidth = 270;
uint16_t ofxDatGuiItem::guiPadding = 0;
uint16_t ofxDatGuiItem::rowWidth = guiWidth -(guiPadding*2);
uint16_t ofxDatGuiItem::rowHeight = 26;
uint16_t ofxDatGuiItem::rowPadding = 2;
uint16_t ofxDatGuiItem::rowSpacing = 1;
uint16_t ofxDatGuiItem::labelX = 12;
uint16_t ofxDatGuiItem::labelWidth = 80;
uint16_t ofxDatGuiItem::labelHeight = 7;
uint16_t ofxDatGuiItem::sliderX = labelX+labelWidth+rowPadding;
uint16_t ofxDatGuiItem::sliderWidth = 100;
uint16_t ofxDatGuiItem::sliderLabelX = sliderX+sliderWidth+rowPadding;
uint16_t ofxDatGuiItem::sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;
uint16_t ofxDatGuiItem::stripeWidth = 2;
uint16_t ofxDatGuiItem::dropdownIconX = rowWidth-18;
uint16_t ofxDatGuiItem::dropdownIconY = 11;

void ofxDatGuiItem::init(ofVec2f position, bool e)
{
    enableRetina(e);
    ofxDatGuiPosition::x = position.x;
    ofxDatGuiPosition::y = position.y;
// resize everything first if retina //
}

void ofxDatGuiItem::init(uint8_t position, bool e)
{
    enableRetina(e);
// resize everything first if retina //
    if (position == ofxDatGuiAnchor::TR) ofxDatGuiPosition::x = ofGetWidth()-ofxDatGuiItem::guiWidth;
}

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    mWidth = rowWidth;
    mHeight = rowHeight;
    mIsExpanded = false;
    mLabelX = labelX;
    mLabelY = mHeight/2 + labelHeight;
    x = ofxDatGuiPosition::x + guiPadding;
    y = ofxDatGuiPosition::y + guiPadding + (mId*(rowHeight+rowSpacing));
    originY = y;
}

ofxDatGuiItem::ofxDatGuiItem(int id, string label, bool centerLabel) : ofxDatGuiItem(id)
{
    mLabel = label;
    mMouseOver = false;
    mMouseDown = false;
}

void ofxDatGuiItem::enableRetina(bool e)
{
    if (e){
        guiWidth*=2;
        guiPadding*=2;
        rowWidth=guiWidth-(guiPadding*2);
        rowHeight*=2;
        rowPadding*=2;
        rowSpacing*=2;
        labelX*=2;
        labelWidth*=2;
        sliderX = labelX+labelWidth+rowPadding;
        sliderWidth*=2;
        sliderLabelX = sliderX+sliderWidth+rowPadding;
        sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;
        stripeWidth*=2;
        dropdownIconX*=2;
        dropdownIconY*=2;
    }
}

int ofxDatGuiItem::getHeight()
{
    return mHeight;
}

string ofxDatGuiItem::getLabel()
{
    return mLabel;
}

bool ofxDatGuiItem::isExpanded()
{
    return mIsExpanded;
}

void ofxDatGuiItem::setYPosition(int ypos)
{
    y = originY + ypos;
}

// draw methods //

void ofxDatGuiItem::drawBkgd(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, mWidth, mHeight);
    ofPopStyle();
}

void ofxDatGuiItem::drawLabel(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawBitmapString(mLabel, x + mLabelX, y + mLabelY);
    ofPopStyle();
}

void ofxDatGuiItem::drawText(string text, ofColor color, int xpos)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawBitmapString(text, xpos, y + mLabelY);
    ofPopStyle();
}

void ofxDatGuiItem::drawStripe(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, stripeWidth, mHeight);
    ofPopStyle();
}

// events //

void ofxDatGuiItem::onMouseEnter(ofPoint m)
{
     mMouseOver = true;
}

void ofxDatGuiItem::onMouseLeave(ofPoint m)
{
     mMouseOver = false;
     mMouseDown = false;
}

void ofxDatGuiItem::onMousePress(ofPoint m)
{
    mMouseDown = true;
}

void ofxDatGuiItem::onMouseRelease(ofPoint m)
{
    mMouseDown = false;
}

void ofxDatGuiItem::onFocusLost() { }
void ofxDatGuiItem::onKeyPressed(int key) { }
void ofxDatGuiItem::onMouseDrag(ofPoint m) { }



