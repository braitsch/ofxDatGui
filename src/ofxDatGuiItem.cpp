//
//  ofxDatGuiItem.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGuiItem.h"

uint16_t ofxDatGuiCore::guiWidth = 270;
uint16_t ofxDatGuiCore::guiPadding = 6;
uint16_t ofxDatGuiCore::guiHeight = ofxDatGuiCore::guiPadding*2;
ofPoint ofxDatGuiCore::guiPosition;
ofTrueTypeFont ofxDatGuiCore::font;

const uint16_t ofxDatGuiItem::rowWidth = ofxDatGuiCore::guiWidth-(ofxDatGuiCore::guiPadding*2);
const uint16_t ofxDatGuiItem::rowHeight = 26;
const uint16_t ofxDatGuiItem::rowPadding = 2;
const uint16_t ofxDatGuiItem::rowSpacing = 2;
const uint16_t ofxDatGuiItem::labelX = 12;
const uint16_t ofxDatGuiItem::labelWidth = 80;

const uint16_t ofxDatGuiItem::sliderX = labelX+labelWidth+rowPadding;
const uint16_t ofxDatGuiItem::sliderWidth = 100;
const uint16_t ofxDatGuiItem::sliderLabelX = sliderX+sliderWidth+rowPadding;
const uint16_t ofxDatGuiItem::sliderLabelWidth = rowWidth-sliderLabelX-rowPadding;

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    x = ofxDatGuiCore::guiPosition.x+ofxDatGuiCore::guiPadding;
    y = ofxDatGuiCore::guiPosition.y+ofxDatGuiCore::guiPadding + (mId*(rowHeight+rowSpacing));
}

void ofxDatGuiItem::drawBkgd(ofColor bkgd_color)
{
    ofSetColor(bkgd_color);
    ofDrawRectangle(x, y, rowWidth, rowHeight);
}

void ofxDatGuiItem::onMouseEnter(ofPoint m)
{
     mMouseOver = true;
}


void ofxDatGuiItem::onMouseLeave(ofPoint m)
{
     mMouseOver = false;
}

void ofxDatGuiItem::onMouseDrag(ofPoint m) { }
void ofxDatGuiItem::onMouseRelease(ofPoint m) { }

void ofxDatGuiItem::drawLabel(ofColor label_color)
{
    ofSetColor(label_color);
    ofDrawBitmapString(mLabel, x+labelPos.x, y+labelPos.y - 1);
//  ofxDatGuiCore::font.drawString(mLabel, x+labelPos.x, y+labelPos.y);
}

