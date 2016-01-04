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

bool ofxDatGuiLog::mQuiet = false;
std::unique_ptr<ofxDatGuiTheme> ofxDatGuiComponent::theme;

ofxDatGuiComponent::ofxDatGuiComponent(string label)
{
    mName = label;
    mVisible = true;
    mEnabled = true;
    mFocused = false;
    mMouseOver = false;
    mMouseDown = false;
    mStyle.opacity = 255;
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    mLabel.text = label;
    mLabel.alignment = ofxDatGuiAlignment::LEFT;
// load a default theme //
    if (theme == nullptr) theme = make_unique<ofxDatGuiTheme>(true);
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
    return ofToLower(mName) == ofToLower(name);
}

ofxDatGuiType ofxDatGuiComponent::getType()
{
    return mType;
}

int ofxDatGuiComponent::getWidth()
{
    return mStyle.width;
}

int ofxDatGuiComponent::getHeight()
{
    return mStyle.height;
}

void ofxDatGuiComponent::setComponentStyle(ofxDatGuiTheme* theme)
{
    mStyle.width = theme->layout.width;
    mStyle.height = theme->layout.height;
    mStyle.padding = theme->layout.padding;
    mStyle.vMargin = theme->layout.vMargin;
    mStyle.labelArea = theme->layout.labelAreaPercentage;
    mStyle.labelMargin = theme->layout.labelMarginPercentage;
    mStyle.color.background = theme->color.background;
    mStyle.color.inputArea = theme->color.inputAreaBackground;
    mStyle.color.onMouseOver = theme->color.backgroundOnMouseOver;
    mStyle.color.onMouseDown = theme->color.backgroundOnMouseDown;
    mStyle.stripe.width = theme->stripe.width;
    mStyle.stripe.visible = theme->stripe.visible;
    mStyle.guiBackground = theme->color.guiBackground;
    mFont.ttf = &theme->font.ttf;
    mIcon.y = mStyle.height * .33;
    mIcon.color = theme->color.icons;
    mIcon.size = theme->layout.iconSize;
    mLabel.color = theme->color.label;
    mLabel.forceUpperCase = theme->layout.label.forceUpperCase;
    setLabel(mLabel.text);
    setWidth(mStyle.width);
    for (int i=0; i<children.size(); i++) children[i]->setTheme(theme);
}

void ofxDatGuiComponent::setWidth(int w)
{
    mStyle.width = w;
    mLabel.width = mStyle.width * mStyle.labelArea;
    mLabel.marginLeft = mStyle.width * mStyle.labelMargin;
    mLabel.marginRight = mStyle.width * mStyle.labelMargin;
    mIcon.x = mStyle.width - (mStyle.width * .05) - 20;
//    if (mType == ofxDatGuiType::BUTTON || mType == ofxDatGuiType::TOGGLE ||
//        mType == ofxDatGuiType::DROPDOWN || mType == ofxDatGuiType::FOLDER){
//    }
    for (int i=0; i<children.size(); i++) children[i]->setWidth(w);
}

const ofxDatGuiTheme* ofxDatGuiComponent::getTheme()
{
    return theme.get();
}

void ofxDatGuiComponent::setVisible(bool visible)
{
    mVisible = visible;
    if (internalEventCallback != nullptr){
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
    mStyle.opacity = opacity * 255;
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
    for(int i=0; i<children.size(); i++) children[i]->setOrigin(x, this->y + (mStyle.height+mStyle.vMargin)*(i+1));
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

void ofxDatGuiComponent::setLabelAlignment(ofxDatGuiAlignment align)
{
    mLabel.alignment = align;
    for (int i=0; i<children.size(); i++) children[i]->setLabelAlignment(align);
}

bool ofxDatGuiComponent::getIsExpanded()
{
	return false;
}

/*
    visual customization
*/

void ofxDatGuiComponent::setLabel(string label)
{
    if (mLabel.forceUpperCase) label = ofToUpper(label);
    mLabel.text = label;
    mLabel.rect = mFont.getRect(mLabel.text);
}

string ofxDatGuiComponent::getLabel()
{
    return mLabel.text;
}

void ofxDatGuiComponent::setLabelColor(ofColor c)
{
    mLabel.color = c;
}

void ofxDatGuiComponent::setColor(ofColor c1, ofColor c2, ofColor c3)
{
    mStyle.color.background = c1;
    mStyle.color.onMouseOver = c2;
    mStyle.color.onMouseDown = c3;
}

void ofxDatGuiComponent::setBackgroundColor(ofColor c)
{
    mStyle.color.background = c;
}

void ofxDatGuiComponent::setOnMouseOverColor(ofColor c)
{
    mStyle.color.onMouseOver = c;
}

void ofxDatGuiComponent::setOnMouseDownColor(ofColor c)
{
    mStyle.color.onMouseDown = c;
}

void ofxDatGuiComponent::setStroke(ofColor c, int w)
{
    mStyle.stroke.color = c;
    mStyle.stroke.width = w;
}

void ofxDatGuiComponent::setStripe(ofColor color, int width)
{
    mStyle.stripe.color = color;
    mStyle.stripe.width = width;
}

void ofxDatGuiComponent::setStripeColor(ofColor color)
{
    mStyle.stripe.color = color;
}

void ofxDatGuiComponent::setStripeWidth(int width)
{
    mStyle.stripe.width = width;
}

void ofxDatGuiComponent::setStripeVisible(bool visible)
{
    mStyle.stripe.visible = visible;
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
    ofPushStyle();
        ofFill();
        ofSetColor(mStyle.color.background, mStyle.opacity);
        ofDrawRectangle(x, y, mStyle.width, mStyle.height);
    ofPopStyle();
}

void ofxDatGuiComponent::drawLabel()
{
    drawLabel(mLabel.text);
}

void ofxDatGuiComponent::drawLabel(string label)
{
    float lx;
    if (mLabel.alignment == ofxDatGuiAlignment::LEFT){
        lx = mLabel.marginLeft;
    }   else if (mLabel.alignment == ofxDatGuiAlignment::CENTER){
        lx = (mLabel.width / 2) - (mLabel.rect.width / 2);
    }   else if (mLabel.alignment == ofxDatGuiAlignment::RIGHT){
        lx = mLabel.width - mLabel.rect.width - mLabel.marginRight;
    }
    ofPushStyle();
        ofSetColor(mLabel.color);
        mFont.draw(mLabel.text, x+lx, y+mStyle.height/2 + mLabel.rect.height/2);
    ofPopStyle();
}

void ofxDatGuiComponent::drawStripe()
{
    if (mStyle.stripe.visible){
        ofPushStyle();
            ofSetColor(mStyle.stripe.color);
            ofDrawRectangle(x, y, mStyle.stripe.width, mStyle.height);
        ofPopStyle();
    }
}

void ofxDatGuiComponent::drawColorPicker() { }

/*
    events
*/

bool ofxDatGuiComponent::hitTest(ofPoint m)
{
    return (m.x>=x && m.x<= x+mStyle.width && m.y>=y && m.y<= y+mStyle.height);
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
        setOrigin(ofGetWidth()-mStyle.width, 0);
    }
}

void ofxDatGuiComponent::onWindowResized(ofResizeEventArgs &e)
{
    onWindowResized();
}


