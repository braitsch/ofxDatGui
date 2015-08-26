/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ofxDatGuiItem.h"

ofBitmapFont ofxDatGuiItem::bFont;
ofTrueTypeFont ofxDatGuiItem::tFont;
int ofxDatGuiItem::mAnchorPosition;
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
    mAnchorPosition = position;
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600) enableRetina();
    if (position == ofxDatGuiAnchor::TOP_RIGHT) ofxDatGuiPosition::x = ofGetWidth()-ofxDatGuiItem::guiWidth;
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
    setFont(ofxDatGuiAssetDir+"font-verdana.ttf");
}

/*
    instance methods
*/

int ofxDatGuiItem::getHeight() { return mHeight; }
void ofxDatGuiItem::setYPosition(int ypos) { y = originY + ypos; }

string ofxDatGuiItem::getLabel() { return mLabel; }
void ofxDatGuiItem::setLabel(string label) { mLabel = label; }

void ofxDatGuiItem::setValue(int value){};
int ofxDatGuiItem::getValue(){}
void ofxDatGuiItem::setScale(float scale){};
float ofxDatGuiItem::getScale(){}
void ofxDatGuiItem::setText(string text){};
string ofxDatGuiItem::getText(){};

void ofxDatGuiItem::toggle(){};
void ofxDatGuiItem::select(int index){};
int ofxDatGuiItem::getSelectedIndex(){};

bool ofxDatGuiItem::isExpanded()
{
    return mIsExpanded;
}

void ofxDatGuiItem::onWindowResize(int w, int h)
{
    if (mAnchorPosition == ofxDatGuiAnchor::TOP_RIGHT){
        ofxDatGuiPosition::x = this->x = w-ofxDatGuiItem::guiWidth;
    }
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



