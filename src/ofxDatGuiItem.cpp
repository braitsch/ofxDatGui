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

void ofxDatGuiItem::draw()
{
// item background //
    ofSetColor(ofxDatGuiColor::item_bkgd);
    ofDrawRectangle(x, y, rowWidth, rowHeight);
}

bool ofxDatGuiItem::hitTest(ofPoint m)
{
    return (m.x>=x+sliderX && m.x<= x+sliderX+sliderWidth && m.y>=y+rowPadding && m.y<= y+rowHeight-rowPadding);
}

