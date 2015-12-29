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
std::unique_ptr<ofxDatGuiTemplate> ofxDatGuiComponent::theme;

ofxDatGuiComponent::ofxDatGuiComponent(string label)
{
    mName = label;
    mVisible = true;
    mEnabled = true;
    mFocused = false;
    mMouseOver = false;
    mMouseDown = false;
    mStyle.opacity = 255;
    mStyle.stripe.visible = true;
    mRetinaEnabled = ofxDatGuiIsRetina();
    mAnchor = ofxDatGuiAnchor::NO_ANCHOR;
    mLabel.text = label;
    mLabel.marginRight = 0;
    mLabel.alignment = ofxDatGuiAlignment::LEFT;
    if (theme == nullptr){
// load a default layout template //
        if (mRetinaEnabled){
            theme = make_unique<ofxDatGui2880x1800>();
        } else {
            theme = make_unique<ofxDatGui1440x900>();
        }
    }
    setTemplate(theme.get());
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

void ofxDatGuiComponent::setTemplate(ofxDatGuiTemplate* tmplt)
{
    mStyle.width = tmplt->row.width;
    mStyle.height = tmplt->row.height;
    mStyle.padding = tmplt->row.padding;
    mStyle.vMargin = tmplt->row.spacing;
    mStyle.color.background = tmplt->row.color.bkgd;
    mStyle.color.inputArea = tmplt->row.color.inputArea;
    mStyle.color.onMouseOver = tmplt->row.color.mouseOver;
    mStyle.color.onMouseDown = tmplt->row.color.mouseDown;
    mStyle.stripe.width = tmplt->row.stripeWidth;
    mStyle.guiBackground = tmplt->gui.background;
    mIcon.y = mStyle.height * .33;
    mIcon.size = mRetinaEnabled ? 20 : 10;
    mIcon.color = tmplt->icon.color;
    mFont = tmplt->font.ttf;
    mLabel.maxWidth = tmplt->row.label.maxAreaWidth;
    mLabel.forceUpperCase = tmplt->row.label.forceUpperCase;
    setLabel(mLabel.text);
    setWidth(mStyle.width);
    for (int i=0; i<children.size(); i++) children[i]->setTemplate(tmplt);
    onTemplateSet(tmplt);
}

void ofxDatGuiComponent::setWidth(int w)
{
    mStyle.width = w;
    mLabel.width = mStyle.width * .35;
    if (mLabel.width > mLabel.maxWidth) mLabel.width = mLabel.maxWidth;
    mFont->labelX = (mStyle.width * .03) + 10;
    mIcon.x = mStyle.width - (mStyle.width * .05) - 20;
    for (int i=0; i<children.size(); i++) children[i]->setWidth(w);
  //  onWidthSet(w);
}

// methods to be overridden in derived classes after component has been updated //
//void ofxDatGuiComponent::onWidthSet(int width) {}
void ofxDatGuiComponent::onTemplateSet(const ofxDatGuiTemplate* tmplt) {

}

const ofxDatGuiTemplate* ofxDatGuiComponent::getTheme()
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
    mStyle.opacity = opacity*255;
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

void ofxDatGuiComponent::setAlignment(ofxDatGuiAlignment align)
{
    mLabel.alignment = align;
    for (int i=0; i<children.size(); i++) children[i]->setAlignment(align);
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
    mLabel.rect = mFont->getStringBoundingBox(mLabel.text, 0, 0);
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
    int lx;
    if (mLabel.alignment == ofxDatGuiAlignment::LEFT){
        lx = mFont->labelX;
    }   else if (mLabel.alignment == ofxDatGuiAlignment::CENTER){
        lx = (mLabel.width / 2) - (mLabel.rect.width / 2);
    }   else if (mLabel.alignment == ofxDatGuiAlignment::RIGHT){
        lx = mLabel.width - mLabel.rect.width - mFont->labelX - mLabel.marginRight;
    }
    mFont->drawLabel(label, x+lx, y+mStyle.height/2-mLabel.rect.height/2);
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


