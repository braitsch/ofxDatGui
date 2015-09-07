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

bool ofxDatGuiGlobals::retinaEnabled;

ofxDatGuiItem::ofxDatGuiItem(ofxDatGuiGlobals *gui, string label)
{
    mGui = gui;
    mLabel = label;
    mVisible = true;
    mMouseOver = false;
    mMouseDown = false;
    mWidth = mGui->width;
    mHeight = mGui->row.height;
    mPadding = mGui->row.padding;
    mStripeColor = ofColor::fromHex(0xEEEEEE);
}

ofxDatGuiItem::~ofxDatGuiItem(){ }

/*
    ofxDatGuiFont
*/

void ofxDatGuiFont::init(string file)
{
    tFont.load(file, size);
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
            if (ofxDatGuiGlobals::retinaEnabled) ypos-=2;
            ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
        }
    ofPopStyle();
}

void ofxDatGuiFont::drawLabel(string text, int xpos, int ypos)
{
    ofPushStyle();
        ofSetColor(ofxDatGuiColor::LABEL);
        if (tFont.isLoaded()){
            tFont.drawString(text, xpos, ypos+labelHeight/2);
        }   else{
            if (!ofxDatGuiGlobals::retinaEnabled) ypos-=2;
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

bool ofxDatGuiItem::getIsExpanded(){}
void ofxDatGuiItem::setVisible(bool visible) { mVisible = visible; }
bool ofxDatGuiItem::getVisible() { return mVisible; }
void ofxDatGuiItem::setStripeColor(ofColor color) { mStripeColor = color; }

void ofxDatGuiItem::setOrigin(int x, int y)
{
    this->x = x;
    this->y = mOriginY = y;
    int vSpacing = mGui->row.spacing;
    for(uint8_t i=0; i<children.size(); i++) children[i]->setOrigin(this->x, this->y + (mHeight+vSpacing)*(i+1));
}

int ofxDatGuiItem::getOriginY() { return mOriginY; }
void ofxDatGuiItem::setPositionY(int ypos) { y = mGui->y + ypos; }
int ofxDatGuiItem::getPositionY() { return y;} 

void ofxDatGuiItem::onWindowResize(int w, int h)
{
    if (mGui->anchor == ofxDatGuiAnchor::TOP_RIGHT){
        mGui->x = this->x = w - mGui->width;
        if (this->children.size() != 0){
            for (int i=0; i<this->children.size(); i++) {
                this->children[i]->x = mGui->x;
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
        ofSetColor(color, mGui->alpha);
        ofDrawRectangle(x, y, mWidth, mHeight);
    ofPopStyle();
}

void ofxDatGuiItem::drawLabel(string label)
{
    if (label=="") label=mLabel;
    mGui->font.drawLabel(label, x+mGui->font.labelX, y+mHeight/2);
}

void ofxDatGuiItem::drawStripe()
{
    ofPushStyle();
        ofSetColor(mStripeColor);
        ofDrawRectangle(x, y, mGui->stripeWidth, mHeight);
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



