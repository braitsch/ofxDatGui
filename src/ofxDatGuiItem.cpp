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
//    cout <<  bar::kode << " : " << test->y << endl;
    x = ofxDatGuiPosition::x + ofxDatGuiPadding;
    y = ofxDatGuiPosition::y + ofxDatGuiPadding + (mId*(rowHeight+rowSpacing));
}

void ofxDatGuiItem::drawBkgd(ofColor bkgd_color)
{
    ofSetColor(bkgd_color);
    ofDrawRectangle(x, y, rowWidth, rowHeight);
    ofSetColor(ofxDatGuiColor::SLIDER);
    ofDrawRectangle(x, y, 2, rowHeight);
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
    ofDrawBitmapString(mLabel, x+labelPosition.x, y+labelPosition.y - 1);
}

