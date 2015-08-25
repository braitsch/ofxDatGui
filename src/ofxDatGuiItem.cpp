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
uint16_t ofxDatGuiItem::guiAlpha = 255;
uint16_t ofxDatGuiItem::guiWidth = 300;
uint16_t ofxDatGuiItem::rowHeight = 26;
uint16_t ofxDatGuiItem::rowPadding = 2;
uint16_t ofxDatGuiItem::rowSpacing = 1;
uint16_t ofxDatGuiItem::labelX = 12;
uint16_t ofxDatGuiItem::labelHeight = 0;
uint16_t ofxDatGuiItem::fontSize = 6;
uint16_t ofxDatGuiItem::inputX = 120;
uint16_t ofxDatGuiItem::inputTextIndent = 8;
uint16_t ofxDatGuiItem::sliderX = inputX;
uint16_t ofxDatGuiItem::sliderWidth = 110;
uint16_t ofxDatGuiItem::sliderLabelX = sliderX+sliderWidth+rowPadding;
uint16_t ofxDatGuiItem::sliderLabelWidth = guiWidth-sliderLabelX-rowPadding;
uint16_t ofxDatGuiItem::stripeWidth = 2;
uint16_t ofxDatGuiItem::radioIconX = guiWidth-20;
uint16_t ofxDatGuiItem::radioIconY = 8;
uint16_t ofxDatGuiItem::radioIconSize = 10;
uint16_t ofxDatGuiItem::dropdownIconX = guiWidth-20;
uint16_t ofxDatGuiItem::dropdownIconY = 9;
uint16_t ofxDatGuiItem::dropdownIconSize = 10;

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    mLabelX = labelX;
    mWidth = guiWidth;
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
    guiWidth=540;
    rowHeight*=2;
    rowPadding*=2;
    rowSpacing*=2;
    labelX*=2;
    fontSize*=2;
    inputX=190;
    inputTextIndent*=2;
    sliderX=inputX;
    sliderWidth=240;
    sliderLabelX = sliderX+sliderWidth+rowPadding;
    sliderLabelWidth = guiWidth-sliderLabelX-rowPadding;
    stripeWidth*=2;
    dropdownIconX=guiWidth-39;
    dropdownIconY*=2;
    dropdownIconSize*=2;
    radioIconX=guiWidth-40;
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

void ofxDatGuiItem::drawBkgd(ofColor color, int alpha)
{
    ofPushStyle();
        ofSetColor(color, alpha);
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



