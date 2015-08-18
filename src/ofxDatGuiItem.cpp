//
//  ofxDatGuiItem.cpp
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#include "ofxDatGuiItem.h"

const uint16_t ofxDatGuiItem::itemWidth = 270;
const uint16_t ofxDatGuiItem::itemHeight = 28;
const uint16_t ofxDatGuiItem::itemPadding = 2;
const uint16_t ofxDatGuiItem::itemSpacing = 2;
const uint16_t ofxDatGuiItem::labelX = 8;
const uint16_t ofxDatGuiItem::labelWidth = 100;
const uint16_t ofxDatGuiItem::inputX = labelX+labelWidth+itemPadding;
const uint16_t ofxDatGuiItem::inputWidth = itemWidth-inputX-itemPadding;

ofPoint ofxDatGuiCore::guiPosition;
ofTrueTypeFont ofxDatGuiCore::font;

ofxDatGuiItem::ofxDatGuiItem(int index)
{
    index = index;
    x = ofxDatGuiCore::guiPosition.x;
    y = ofxDatGuiCore::guiPosition.y + (index*(itemHeight+itemSpacing));
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

