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

int ofxDatGuiGlobals::guiX = 0;
int ofxDatGuiGlobals::guiY = 0;
int ofxDatGuiGlobals::guiAlpha = 255;
int ofxDatGuiGlobals::guiWidth = 300;
int ofxDatGuiGlobals::rowHeight = 26;
int ofxDatGuiGlobals::rowPadding = 2;
int ofxDatGuiGlobals::rowSpacing = 1;
int ofxDatGuiGlobals::anchorPosition;

int ofxDatGuiFont::fontSize = 6;
int ofxDatGuiFont::labelX = 12;
int ofxDatGuiFont::labelHeight = 0;
int ofxDatGuiFont::highlightPadding = 3;
bool ofxDatGuiFont::retinaEnabled = false;
ofBitmapFont ofxDatGuiFont::bFont;
ofTrueTypeFont ofxDatGuiFont::tFont;

uint16_t ofxDatGuiItem::inputX = 120;
uint16_t ofxDatGuiItem::inputTextIndent = 8;
uint16_t ofxDatGuiItem::sliderX = inputX;
uint16_t ofxDatGuiItem::sliderWidth = 110;
uint16_t ofxDatGuiItem::sliderInputX = sliderX+sliderWidth+ofxDatGuiGlobals::rowPadding;
uint16_t ofxDatGuiItem::sliderInputWidth = ofxDatGuiGlobals::guiWidth-sliderInputX-ofxDatGuiGlobals::rowPadding;
uint16_t ofxDatGuiItem::stripeWidth = 2;
uint16_t ofxDatGuiItem::radioIconX = ofxDatGuiGlobals::guiWidth-20;
uint16_t ofxDatGuiItem::radioIconY = 8;
uint16_t ofxDatGuiItem::radioIconSize = 10;
uint16_t ofxDatGuiItem::dropdownIconX = ofxDatGuiGlobals::guiWidth-20;
uint16_t ofxDatGuiItem::dropdownIconY = 9;
uint16_t ofxDatGuiItem::dropdownIconSize = 10;

ofxDatGuiItem::ofxDatGuiItem(string label)
{
    mLabel = label;
    mVisible = true;
    mMouseOver = false;
    mMouseDown = false;
    mStripeColor = ofColor::fromHex(0xEEEEEE);
    mWidth = ofxDatGuiGlobals::guiWidth;
    mHeight = ofxDatGuiGlobals::rowHeight;
    mPadding = ofxDatGuiGlobals::rowPadding;
}

/*
    static methods
*/

void ofxDatGuiItem::init(int x, int y)
{
    ofxDatGuiGlobals::guiX = x;
    ofxDatGuiGlobals::guiY = y;
    ofxDatGuiFont::labelHeight = ofxDatGuiFont::getStringBoundingBox("ABCDEFG123456", 0, 0).height;
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600) enableRetina();
}

void ofxDatGuiItem::init(int position)
{
    ofxDatGuiGlobals::anchorPosition = position;
    ofxDatGuiFont::labelHeight = ofxDatGuiFont::getStringBoundingBox("ABCDEFG123456", 0, 0).height;
    if (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600) enableRetina();
    if (position == ofxDatGuiAnchor::TOP_RIGHT) ofxDatGuiGlobals::guiX = ofGetWidth()-ofxDatGuiGlobals::guiWidth;
}

void ofxDatGuiItem::enableRetina()
{
    ofxDatGuiGlobals::guiWidth=540;
    ofxDatGuiGlobals::rowHeight*=2;
    ofxDatGuiGlobals::rowPadding*=2;
    ofxDatGuiGlobals::rowSpacing*=2;

    inputX=190;
    inputTextIndent*=2;
    sliderX=inputX;
    sliderWidth=240;
    sliderInputX = sliderX+sliderWidth+ofxDatGuiGlobals::rowPadding;
    sliderInputWidth = ofxDatGuiGlobals::guiWidth-sliderInputX-ofxDatGuiGlobals::rowPadding;
    stripeWidth*=2;
    dropdownIconX=ofxDatGuiGlobals::guiWidth-39;
    dropdownIconY*=2;
    dropdownIconSize*=2;
    radioIconX=ofxDatGuiGlobals::guiWidth-40;
    radioIconY*=2;
    radioIconSize*=2;

    ofxDatGuiFont::labelX*=2;
    ofxDatGuiFont::fontSize*=2;
    ofxDatGuiFont::highlightPadding*=2;
    ofxDatGuiFont::retinaEnabled = true;
    ofxDatGuiFont::load(ofxDatGuiAssetDir+"font-verdana.ttf");
}

/*
    ofxDatGuiFont
*/

void ofxDatGuiFont::load(string file)
{
    tFont.load(file, fontSize);
    labelHeight = getStringBoundingBox("ABCDEFG123456", 0, 0).height;
}

ofRectangle ofxDatGuiFont::getStringBoundingBox(string str, int x, int y)
{
    if (tFont.isLoaded()){
        return tFont.getStringBoundingBox(str, x, y);
    }   else{
        return bFont.getBoundingBox(str, x, y);
    }
}

void ofxDatGuiFont::drawText(string text, ofColor color, int xpos, int ypos, bool highlight)
{
    ofPushStyle();
        if (highlight){
            ofRectangle hRect = getStringBoundingBox(text, xpos, ypos+labelHeight/2);
            hRect.x -= highlightPadding;
            hRect.width += highlightPadding*2;
            hRect.y -= highlightPadding;
            hRect.height += highlightPadding*2;
            ofSetColor(ofxDatGuiColor::TEXT_HIGHLIGHT);
            ofDrawRectangle(hRect);
        }
        ofSetColor(color);
        if (tFont.isLoaded()){
            tFont.drawString(text, xpos, ypos+labelHeight/2);
        }   else{
            if (!retinaEnabled) ypos-=2;
            ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
        }
    ofPopStyle();
}

void ofxDatGuiFont::drawLabel(string text, int xpos, int ypos, bool center)
{
    if (!center) {
        xpos += labelX;
    }   else{
        xpos += ofxDatGuiGlobals::guiWidth/2 - getStringBoundingBox(text, 0, 0).width/2;
    }
    ofPushStyle();
        ofSetColor(ofxDatGuiColor::LABEL);
        if (tFont.isLoaded()){
            tFont.drawString(text, xpos, ypos+labelHeight/2);
        }   else{
            if (!retinaEnabled) ypos-=2;
            ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
        }
    ofPopStyle();
}

/*
    instance methods
*/

void ofxDatGuiItem::setIndex(int index) { mId = index; }
int ofxDatGuiItem::getHeight() { return mHeight; }
string ofxDatGuiItem::getLabel() { return mLabel; }
void ofxDatGuiItem::setLabel(string label) { mLabel = label; }

/*
    virtual methods overridden in derived classes
*/

void ofxDatGuiItem::setValue(int value){};
int ofxDatGuiItem::getValue(){}
void ofxDatGuiItem::setScale(float scale){};
float ofxDatGuiItem::getScale(){}
void ofxDatGuiItem::setText(string text){};
string ofxDatGuiItem::getText(){};
void ofxDatGuiItem::toggle(){};
void ofxDatGuiItem::setEnabled(bool enabled){};
bool ofxDatGuiItem::getEnabled(){};
void ofxDatGuiItem::select(int index){};
int ofxDatGuiItem::getSelectedChildIndex(){};
bool ofxDatGuiItem::getIsExpanded(){}
void ofxDatGuiItem::setVisible(bool visible) { mVisible = visible; }
bool ofxDatGuiItem::getVisible() { return mVisible; }
void ofxDatGuiItem::setStripeColor(ofColor color) { mStripeColor = color; }

void ofxDatGuiItem::setOrigin(int x, int y)
{
    this->x = x;
    this->y = mOriginY = y;
    int vSpacing = ofxDatGuiGlobals::rowSpacing;
    for(uint8_t i=0; i<children.size(); i++) children[i]->setOrigin(this->x, this->y + (mHeight+vSpacing)*(i+1));
}

int ofxDatGuiItem::getOriginY() { return mOriginY; }
void ofxDatGuiItem::setPositionY(int ypos) { y = ofxDatGuiGlobals::guiY + ypos; }
int ofxDatGuiItem::getPositionY() { return y;} 

void ofxDatGuiItem::onWindowResize(int w, int h)
{
    if (ofxDatGuiGlobals::anchorPosition == ofxDatGuiAnchor::TOP_RIGHT){
        ofxDatGuiGlobals::guiX = this->x = w-ofxDatGuiGlobals::guiWidth;
        if (this->children.size() != 0){
            for (int i=0; i<this->children.size(); i++) {
                this->children[i]->x = w-ofxDatGuiGlobals::guiWidth;
            }
        }
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

void ofxDatGuiItem::drawStripe()
{
    ofPushStyle();
        ofSetColor(mStripeColor);
        ofDrawRectangle(x, y, stripeWidth, mHeight);
    ofPopStyle();
}

void ofxDatGuiItem::drawColorPicker() { }

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



