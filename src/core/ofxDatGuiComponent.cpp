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
#include "ofxDatGuiTemplate.h"

bool ofxDatGuiLog::mQuiet = false;

ofxDatGuiComponent::ofxDatGuiComponent(string label, ofxDatGuiTemplate* tmplt)
{
    mAlpha = 255;
    mName = label;
    mLabel = label;
    mVisible = true;
    mEnabled = true;
    mFocused = false;
    mMouseOver = false;
    mMouseDown = false;
    mLabelMarginRight = 0;
    mRetinaEnabled = ofxDatGuiIsRetina();
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    mLabelAlignment = ofxDatGuiAlignment::LEFT;
    if (tmplt == nullptr){
// load a default layout template //
        if (mRetinaEnabled){
            tmplt = ofxDatGui2880x1800::get();
        } else {
            tmplt = ofxDatGui1440x900::get();
        }
    }
    setTemplate(tmplt);
}

ofxDatGuiComponent::~ofxDatGuiComponent()
{
    cout << "ofxDatGuiComponent deleted" << endl;
}

/*
    instance getters & setters
*/


void ofxDatGuiComponent::setIndex(int index)
{
    mIndex = index;
}

int ofxDatGuiComponent::getIndex()
{
    return mIndex;
}

void ofxDatGuiComponent::setLabel(string label)
{
    if (mTemplate->row.label.forceUpperCase) label = ofToUpper(label);
    mLabel = label;
    mLabelRect = mFont->getStringBoundingBox(mLabel, 0, 0);
}

string ofxDatGuiComponent::getLabel()
{
    return mLabel;
}

void ofxDatGuiComponent::setName(string name)
{
    mName = name;
}

string ofxDatGuiComponent::getName()
{
    return mName;
}

bool ofxDatGuiComponent::is(string name)
{
// convenience method to perform a case insensitive lookup //
    return ofToLower(mName) == ofToLower(name);
}

ofxDatGuiType ofxDatGuiComponent::getType()
{
    return mType;
}

int ofxDatGuiComponent::getWidth()
{
    return mRow.width;
}

int ofxDatGuiComponent::getHeight()
{
    return mRow.height;
}

void ofxDatGuiComponent::setTemplate(ofxDatGuiTemplate* tmplt)
{
    mTemplate = tmplt;
    mRow.width = mTemplate->row.width;
    mRow.height = mTemplate->row.height;
    mRow.padding = mTemplate->row.padding;
    mRow.spacing = mTemplate->row.spacing;
    mRow.stripeWidth = mTemplate->row.stripeWidth;
    mIcon.y = mRow.height * .33;
    mIcon.size = mRetinaEnabled ? 20 : 10;
    mFont = mTemplate->font.ttf;
    setLabel(mLabel);
}

void ofxDatGuiComponent::setWidth(int w)
{
    mRow.width = w;
    mRow.lWidth=mRow.width * mTemplate->row.label.lWidthRatio;
    if (mRow.lWidth > mTemplate->row.label.maxAreaWidth) mRow.lWidth = mTemplate->row.label.maxAreaWidth;
    mRow.inputX=mRow.lWidth;
    mRow.rWidth=mRow.width-mRow.inputX;
    mFont->labelX=(mRow.width*.03)+10;
    mIcon.x=mRow.width-(mRow.width*.05)-20;
    mSlider.width=mRow.rWidth*.7;
    mSlider.inputX=mRow.inputX+mSlider.width+mRow.padding;
    mSlider.inputWidth=mRow.rWidth-mSlider.width-(mRow.padding*2);
    for (int i=0; i<children.size(); i++) children[i]->setWidth(w);
}

void ofxDatGuiComponent::setVisible(bool visible)
{
    mVisible = visible;
    if (internalEventCallback!=nullptr){
        ofxDatGuiInternalEvent e(ofxDatGuiEventType::VISIBILITY_CHANGED, mIndex);
        internalEventCallback(e);
    }
}

bool ofxDatGuiComponent::getVisible()
{
    return mVisible;
}

void ofxDatGuiComponent::setOpacity(float opacity)
{
    mAlpha = opacity*255;
    for (int i=0; i<children.size(); i++) children[i]->setOpacity(opacity);
}

void ofxDatGuiComponent::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

bool ofxDatGuiComponent::getEnabled()
{
    return mEnabled;
}

void ofxDatGuiComponent::setFocused(bool focused)
{
    if (focused){
        onFocus();
    }   else{
        onFocusLost();
    }
}

bool ofxDatGuiComponent::getFocused()
{
    return mFocused;
}

bool ofxDatGuiComponent::getPressed()
{
    return mFocused;
}

int ofxDatGuiComponent::getX()
{
    return this->x;
}

int ofxDatGuiComponent::getY()
{
    return this->y;
}

void ofxDatGuiComponent::setY(int y)
{
    this->y = y;
}

void ofxDatGuiComponent::setOrigin(int x, int y)
{
    this->x = x;
    this->y = y;
    mLabelAreaWidth = mRow.lWidth;
    for(int i=0; i<children.size(); i++) children[i]->setOrigin(x, this->y + (mRow.height+mRow.spacing)*(i+1));
}

void ofxDatGuiComponent::setAnchor(ofxDatGuiAnchor anchor)
{
    mAnchor = anchor;
    if (mAnchor != ofxDatGuiAnchor::NO_ANCHOR){
        ofAddListener(ofEvents().windowResized, this, &ofxDatGuiComponent::onWindowResized);
    }   else{
        ofRemoveListener(ofEvents().windowResized, this, &ofxDatGuiComponent::onWindowResized);
    }
    onWindowResized();
}

void ofxDatGuiComponent::setAlignment(ofxDatGuiAlignment align)
{
    mLabelAlignment = align;
    for (int i=0; i<children.size(); i++) children[i]->setAlignment(align);
}

void ofxDatGuiComponent::setStripeColor(ofColor color)
{
    mStripeColor = color;
}

bool ofxDatGuiComponent::getIsExpanded()
{
	return false;
}

/*
    draw methods
*/

void ofxDatGuiComponent::update(bool acceptEvents)
{
    if (acceptEvents && mEnabled){
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
                    }
                }
            }
        }   else{
    // the mouse is not over the component //
            if (mMouseOver){
                onMouseLeave(mouse);
            }   else if (mp && mFocused && mMouseDown==false){
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
    }
// don't update children unless they're visible //
    if (this->getIsExpanded()) {
        for(int i=0; i<children.size(); i++) {
            children[i]->update(acceptEvents);
            if (children[i]->getFocused()){
                if (acceptEvents == false ) children[i]->setFocused(false);
                acceptEvents = false;
            }
        }
    }
}

void ofxDatGuiComponent::drawBkgd()
{
    drawBkgd(mTemplate->row.color.bkgd, mAlpha);
}

void ofxDatGuiComponent::drawBkgd(ofColor color, int alpha)
{
    ofPushStyle();
        ofFill();
        ofSetColor(color, alpha);
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
    mFont->drawLabel(label, x+lx, y+mRow.height/2-mLabelRect.height/2);
}

void ofxDatGuiComponent::drawStripe()
{
    ofPushStyle();
        ofSetColor(mStripeColor);
        ofDrawRectangle(x, y, mRow.stripeWidth, mRow.height);
    ofPopStyle();
}

void ofxDatGuiComponent::drawColorPicker() { }

/*
    events
*/

bool ofxDatGuiComponent::hitTest(ofPoint m)
{
    return (m.x>=x && m.x<= x+mRow.width && m.y>=y && m.y<= y+mRow.height);
}

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
    ofAddListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
}

void ofxDatGuiComponent::onFocusLost()
{
    mFocused = false;
    mMouseDown = false;
    ofRemoveListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
}

void ofxDatGuiComponent::onKeyPressed(int key) { }
void ofxDatGuiComponent::onMouseDrag(ofPoint m) { }

void ofxDatGuiComponent::onKeyPressed(ofKeyEventArgs &e)
{
    onKeyPressed(e.key);
    if ((e.key == OF_KEY_RETURN || e.key == OF_KEY_TAB)){
        onFocusLost();
        ofRemoveListener(ofEvents().keyPressed, this, &ofxDatGuiComponent::onKeyPressed);
    }
}

void ofxDatGuiComponent::onWindowResized()
{
    if (mAnchor == ofxDatGuiAnchor::TOP_LEFT){
        setOrigin(0, 0);
    }   else if (mAnchor == ofxDatGuiAnchor::TOP_RIGHT){
        setOrigin(ofGetWidth()-mRow.width, 0);
    }
}

void ofxDatGuiComponent::onWindowResized(ofResizeEventArgs &e)
{
    onWindowResized();
}


