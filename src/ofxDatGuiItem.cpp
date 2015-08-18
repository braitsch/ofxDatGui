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

const uint16_t ofxDatGuiItem::itemWidth = ofxDatGuiCore::guiWidth-(ofxDatGuiCore::guiPadding*2);
const uint16_t ofxDatGuiItem::itemHeight = 26;
const uint16_t ofxDatGuiItem::itemPadding = 2;
const uint16_t ofxDatGuiItem::itemSpacing = 2;
const uint16_t ofxDatGuiItem::labelX = 12;
const uint16_t ofxDatGuiItem::labelWidth = 80;
const uint16_t ofxDatGuiItem::inputX = labelX+labelWidth+itemPadding;
const uint16_t ofxDatGuiItem::inputWidth = itemWidth-inputX-itemPadding;

ofxDatGuiItem::ofxDatGuiItem(int id)
{
    mId = id;
    x = ofxDatGuiCore::guiPosition.x+ofxDatGuiCore::guiPadding;
    y = ofxDatGuiCore::guiPosition.y+ofxDatGuiCore::guiPadding + (mId*(itemHeight+itemSpacing));
}

void ofxDatGuiItem::draw()
{
// item background //
    ofSetColor(ofxDatGuiColor::item_bkgd);
    ofDrawRectangle(x, y, itemWidth, itemHeight);
}

bool ofxDatGuiItem::hitTest(ofPoint m)
{
    return (m.x>=x+inputX && m.x<= x+inputX+inputWidth && m.y>=y+itemPadding && m.y<= y+itemHeight-itemPadding);
}

