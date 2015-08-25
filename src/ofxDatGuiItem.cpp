//
//  ofxDatGuiItem.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGuiItem.h"

ofBitmapFont ofxDatGuiItem::bFont;
ofTrueTypeFont ofxDatGuiItem::tFont;
bool ofxDatGuiItem::retinaEnabled = false;
uint16_t ofxDatGuiItem::guiWidth = 270;
uint16_t ofxDatGuiItem::rowWidth = guiWidth;
uint16_t ofxDatGuiItem::rowHeight = 26;
uint16_t ofxDatGuiItem::rowPadding = 2;
uint16_t ofxDatGuiItem::rowSpacing = 1;
uint16_t ofxDatGuiItem::labelX = 12;
uint16_t ofxDatGuiItem::labelWidth = 80;
uint16_t ofxDatGuiItem::labelHeight = 0;
uint16_t ofxDatGuiItem::fontSize = 6;
uint16_t ofxDatGuiItem::sliderX = labelX+labelWidth+rowPadding;
uint16_t ofxDatGuiItem::sliderWidth = 100;
uint16_t ofxDatGuiItem::sliderLabelX = sliderX+sliderWidth+rowPadding;
uint16_t ofxDatGuiItem::sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;
uint16_t ofxDatGuiItem::stripeWidth = 2;
uint16_t ofxDatGuiItem::radioIconX = rowWidth-20;
uint16_t ofxDatGuiItem::radioIconY = 8;
uint16_t ofxDatGuiItem::radioIconSize = 10;
uint16_t ofxDatGuiItem::dropdownIconX = rowWidth-20;
uint16_t ofxDatGuiItem::dropdownIconY = 9;
uint16_t ofxDatGuiItem::dropdownIconSize = 10;

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    mLabelX = labelX;
    mWidth = rowWidth;
    mHeight = rowHeight;
    mIsExpanded = false;
    x = ofxDatGuiPosition::x;
    y = originY = ofxDatGuiPosition::y + (mId*(rowHeight+rowSpacing));
}

ofxDatGuiItem::ofxDatGuiItem(int id, string label, bool centerLabel) : ofxDatGuiItem(id)
{
    mLabel = label;
    mMouseOver = false;
    mMouseDown = false;
}

/*
    static methods
*/

void ofxDatGuiItem::init(ofVec2f position)
{
    ofxDatGuiPosition::x = position.x;
    ofxDatGuiPosition::y = position.y;
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600) enableRetina();
    labelHeight = getStringBoundingBox("ABCDEFG123456", 0, 0).height;
}

void ofxDatGuiItem::init(uint8_t position)
{
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600) enableRetina();
    if (position == ofxDatGuiAnchor::TR) ofxDatGuiPosition::x = ofGetWidth()-ofxDatGuiItem::guiWidth;
    labelHeight = getStringBoundingBox("ABCDEFG123456", 0, 0).height;
}

void ofxDatGuiItem::setFont(string file)
{
    tFont.load(file, fontSize);
    labelHeight = getStringBoundingBox("ABCDEFG123456", 0, 0).height;
}

void ofxDatGuiItem::enableRetina()
{
    guiWidth*=2;
    rowWidth=guiWidth;
    rowHeight*=2;
    rowPadding*=2;
    rowSpacing*=2;
    labelX*=2;
    labelWidth*=2;
    fontSize*=2;
    sliderX = labelX+labelWidth+rowPadding;
    sliderWidth*=2;
    sliderLabelX = sliderX+sliderWidth+rowPadding;
    sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;
    stripeWidth*=2;
    dropdownIconX*=2;
    dropdownIconX+=1;
    dropdownIconY*=2;
    dropdownIconSize*=2;
    radioIconX*=2;
    radioIconY*=2;
    radioIconSize*=2;
    retinaEnabled=true;
    setFont("verdana");
}

/*
    instance methods
*/

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

ofRectangle ofxDatGuiItem::getStringBoundingBox(string str, int x, int y)
{
    if (tFont.isLoaded()){
        return tFont.getStringBoundingBox(str, x, y);
    }   else{
        return bFont.getBoundingBox(str, x, y);
    }
}

/*
    draw methods
*/

void ofxDatGuiItem::drawBkgd(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, mWidth, mHeight);
    ofPopStyle();
}

void ofxDatGuiItem::drawLabel(ofColor color)
{
    mLabelY = mHeight/2 + labelHeight/2;
    ofPushStyle();
        ofSetColor(color);
        if (tFont.isLoaded()){
            tFont.drawString(mLabel, x + mLabelX, y + mLabelY);
        }   else{
            if (!retinaEnabled) mLabelY-=2;
            ofDrawBitmapString(mLabel, x + mLabelX, y + mLabelY);
        }
    ofPopStyle();
}

void ofxDatGuiItem::drawText(string text, ofColor color, int xpos)
{
    mLabelY = mHeight/2 + labelHeight/2;
    ofPushStyle();
        ofSetColor(color);
        if (tFont.isLoaded()){
            tFont.drawString(text, xpos, y + mLabelY);
        }   else{
            if (!retinaEnabled) mLabelY-=2;
            ofDrawBitmapString(text, xpos, y + mLabelY);
        }
    ofPopStyle();
}

void ofxDatGuiItem::drawStripe(ofColor color)
{
    ofPushStyle();
        ofSetColor(color);
        ofDrawRectangle(x, y, stripeWidth, mHeight);
    ofPopStyle();
}

/*
    events
*/

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

void ofxDatGuiItem::onFocus() {}
void ofxDatGuiItem::onFocusLost() { }
void ofxDatGuiItem::onKeyPressed(int key) { }
void ofxDatGuiItem::onMouseDrag(ofPoint m) { }



