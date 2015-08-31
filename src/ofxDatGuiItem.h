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

#pragma once
#include "ofxDatGuiSettings.h"
#include "ofxDatGuiComponents.h"

class ofxDatGuiItem : public ofxDatGuiInteractiveObject
{
    public:
    
        ofxDatGuiItem(int id, string label);
        vector<ofxDatGuiItem*> children;
    
        virtual int getHeight();
        void setLabel(string label);
        string getLabel();
        void setStripeColor(ofColor color);
        virtual void setOrigin(int x, int y);
        int getOriginY();
        virtual void setPositionY(int y);
        int getPositionY();
        
        void setVisible(bool visible);
        bool getVisible();
        void onWindowResize(int w, int h);

        static void enableRetina();
        static void init(int x, int y);
        static void init(int position);
    
        virtual void draw() = 0;
        virtual bool hitTest(ofPoint m) = 0;

        virtual void toggle();
        virtual void select(int index);
        virtual void setValue(int value);
        virtual void setScale(float scale);
        virtual void setText(string text);
        virtual void setEnabled(bool enabled);
    
        virtual int getValue();
        virtual float getScale();
        virtual string getText();
        virtual bool getEnabled();
        virtual bool getIsExpanded();
        virtual int getSelectedChildIndex();

        virtual void onFocus();    
        virtual void onFocusLost();
        virtual void onKeyPressed(int key);
        virtual void onMouseEnter(ofPoint m);
        virtual void onMousePress(ofPoint m);
        virtual void onMouseDrag(ofPoint m);
        virtual void onMouseLeave(ofPoint m);
        virtual void onMouseRelease(ofPoint m);
    
    protected:
    
        int x;
        int y;
        int mId;
        int mWidth;
        int mHeight;
        int mOriginY;
        int mPadding;
        ofColor mStripeColor;

        string mLabel;
        bool mVisible;
        bool mMouseOver;
        bool mMouseDown;
    
        void drawBkgd(ofColor color = ofxDatGuiColor::ROW_BKGD, int alpha=ofxDatGuiGlobals::guiAlpha);
        void drawStripe();
    
        static uint16_t inputX;
        static uint16_t inputTextIndent;
        static uint16_t sliderX;
        static uint16_t sliderWidth;
        static uint16_t sliderInputX;
        static uint16_t sliderInputWidth;
        static uint16_t stripeWidth;
        static uint16_t radioIconX;
        static uint16_t radioIconY;
        static uint16_t radioIconSize;
        static uint16_t dropdownIconX;
        static uint16_t dropdownIconY;
        static uint16_t dropdownIconSize;

};

