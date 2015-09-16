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

#include "ofxDatGuiComponent.h"

ofxDatGuiComponent::ofxDatGuiComponent(string label, ofxDatGuiFont* font)
{
    mAlpha = 255;
    mVisible = true;
    mEnabled = true;
    mFocused = false;
    mMouseOver = false;
    mMouseDown = false;
    mLabelMarginRight = 0;
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    mLabelAlignment = ofxDatGuiAlignment::LEFT;
    mRetinaEnabled = (ofGetScreenWidth()>=2560 && ofGetScreenHeight()>=1600);
    mIcon.y = 8;
    mIcon.size = 10;
    mRow.width = 320;
    mRow.height = 26;
    mRow.padding = 2;
    mRow.spacing = 1;
    mStripeWidth = 2;
    if (mRetinaEnabled){
        mRow.width = 540;
        mIcon.y *=2;
        mIcon.size *=2;
        mRow.height *=2;
        mRow.padding*=2;
        mRow.spacing*=2;
        mStripeWidth*=2;
    }
    if (font!=nullptr) {
        mFont = font;
    }   else{
        mFont = new ofxDatGuiFont(mRetinaEnabled);
    }
    setLabel(label);
    setOrigin(0, 0);
    setWidth(mRow.width);
}

ofxDatGuiComponent::~ofxDatGuiComponent()
{
    delete mFont;
    cout << "ofxDatGuiComponent deleted" << endl;
}

/*
    ofxDatGuiFont
*/

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
            if (mRetinaEnabled) ypos-=2;
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
            if (!mRetinaEnabled) ypos-=2;
            ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
        }
    ofPopStyle();
}

/*
    instance methods
*/

void ofxDatGuiComponent::setIndex(int index)
{
    mIndex = index;
}

int ofxDatGuiComponent::getIndex()
{
    return mIndex;
}

ofxDatGuiType ofxDatGuiComponent::getType()
{
    return mType;
}

void ofxDatGuiComponent::setOpacity(float opacity)
{
    mAlpha = opacity*255;
    for (int i=0; i<children.size(); i++) children[i]->setOpacity(opacity);
}

void ofxDatGuiComponent::setWidth(int w)
{
    mRow.width = w;
    mRow.lWidth=mRow.width*.35;
    mRow.inputX=mRow.lWidth;
    mRow.rWidth=mRow.width-mRow.inputX;
    mFont->labelX=(mRow.width*.03)+10;
    mIcon.x=mRow.width-(mRow.width*.05)-20;
    mSlider.width=mRow.rWidth*.7;
    mSlider.inputX=mRow.inputX+mSlider.width+mRow.padding;
    mSlider.inputWidth=mRow.rWidth-mSlider.width-(mRow.padding*2);
    for (int i=0; i<children.size(); i++) children[i]->setWidth(w);
}

int ofxDatGuiComponent::getWidth()
{
    return mRow.width;
}

int ofxDatGuiComponent::getHeight()
{
    return mRow.height;
}

void ofxDatGuiComponent::setLabel(string label)
{
    mLabel = label;
    mLabelRect = mFont->getStringBoundingBox(mLabel, 0, 0);
}

string ofxDatGuiComponent::getLabel()
{
    return mLabel;
}

void ofxDatGuiComponent::setAlignment(ofxDatGuiAlignment align)
{
    mLabelAlignment = align;
    for (int i=0; i<children.size(); i++) children[i]->setAlignment(align);
}

void ofxDatGuiComponent::setVisible(bool visible)
{
    mVisible = visible;
}

bool ofxDatGuiComponent::getVisible()
{
    return mVisible;
}

void ofxDatGuiComponent::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool ofxDatGuiComponent::getEnabled()
{
    return mEnabled;
}

void ofxDatGuiComponent::setStripeColor(ofColor color)
{
    mStripeColor = color;
}

void ofxDatGuiComponent::setOrigin(int x, int y)
{
    this->x = x;
    this->y = mOriginY = y;
    mLabelAreaWidth = mRow.lWidth;
    for(int i=0; i<children.size(); i++) children[i]->setOrigin(x, this->y + (mRow.height+mRow.spacing)*(i+1));
}

void ofxDatGuiComponent::setAnchor(ofxDatGuiAnchor anchor)
{
    mAnchor = anchor;
    if (mAnchor == ofxDatGuiAnchor::TOP_LEFT){
        setOrigin(0, 0);
    }   else if (mAnchor == ofxDatGuiAnchor::TOP_RIGHT){
        setOrigin(ofGetWidth()-mRow.width, 0);
    }
}

int ofxDatGuiComponent::getX()
{
    return this->x;
}

int ofxDatGuiComponent::getY()
{
    return this->y;
}

void ofxDatGuiComponent::setPositionY(int ypos)
{
    this->y = ypos;
}

int ofxDatGuiComponent::getPositionY()
{
    return y;
}

bool ofxDatGuiComponent::getIsExpanded(){}

/*
    draw methods
*/

void ofxDatGuiComponent::update()
{
    if (!mEnabled) return;
    bool mp = ofGetMousePressed();
    ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
    if (hitTest(mouse)){
        if (!mMouseOver){
            onMouseEnter(mouse);
        }   else {
            if (!mMouseDown && mp){
                onMousePress(mouse);
                if (!mFocused) {
                    onFocus();
                    ofAddListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
                }
            }
        }
    }   else{
        if (mMouseOver){
            onMouseLeave(mouse);
        }
        if (mp && mFocused) {
            ofRemoveListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
            onFocusLost();
        }
    }
    if (mMouseDown) {
        if (mp){
            onMouseDrag(mouse);
        }   else{
            onMouseRelease(mouse);
        }
    }
// if we're anchored, check if the window was resized //
    if (mAnchor != ofxDatGuiAnchor::NO_ANCHOR) if (ofGetWidth() != mWindow.width) setAnchor(mAnchor);
// don't iterate over children unless they're visible //
// TODO need to stop iterating over children once hitTest returns true //
    if (getIsExpanded()) for(int i=0; i<children.size(); i++) children[i]->update();
}

void ofxDatGuiComponent::onKeyPressed(ofKeyEventArgs &e)
{
    onKeyPressed(e.key);
    if ((e.key == OF_KEY_RETURN || e.key == OF_KEY_TAB)){
        onFocusLost();
        ofRemoveListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
    }
}

void ofxDatGuiComponent::drawBkgd(ofColor color, int alpha)
{
    ofPushStyle();
        ofFill();
        ofSetColor(color, alpha!=-1 ? alpha  : mAlpha);
        ofDrawRectangle(x, y, mRow.width, mRow.height);
    ofPopStyle();
}

void ofxDatGuiComponent::drawLabel()
{
    drawLabel(mLabel);
}

void ofxDatGuiComponent::drawLabel(string label)
{
    int lx;
    if (mLabelAlignment == ofxDatGuiAlignment::LEFT){
        lx = mFont->labelX;
    }   else if (mLabelAlignment == ofxDatGuiAlignment::CENTER){
        lx = mLabelAreaWidth/2-mLabelRect.width/2;
    }   else if (mLabelAlignment == ofxDatGuiAlignment::RIGHT){
        lx = mLabelAreaWidth-mLabelRect.width-mFont->labelX-mLabelMarginRight;
    }
    mFont->drawLabel(label, x+lx, y+(mRow.height/2));
}

void ofxDatGuiComponent::drawStripe()
{
    ofPushStyle();
        ofSetColor(mStripeColor);
        ofDrawRectangle(x, y, mStripeWidth, mRow.height);
    ofPopStyle();
}

void ofxDatGuiComponent::drawColorPicker() { }

/*
    events
*/

void ofxDatGuiComponent::onMouseEnter(ofPoint m)
{
     mMouseOver = true;
}

void ofxDatGuiComponent::onMouseLeave(ofPoint m)
{
    mMouseOver = false;
}

void ofxDatGuiComponent::onMousePress(ofPoint m)
{
    mMouseDown = true;
}

void ofxDatGuiComponent::onMouseRelease(ofPoint m)
{
    mMouseDown = false;
}

void ofxDatGuiComponent::onFocus()
{
    mFocused = true;
}

void ofxDatGuiComponent::onFocusLost()
{
    mFocused = false;
}

void ofxDatGuiComponent::onKeyPressed(int key) { }
void ofxDatGuiComponent::onMouseDrag(ofPoint m) { }



