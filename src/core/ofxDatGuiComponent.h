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
#include "ofxDatGuiIntObject.h"

class ofxDatGuiComponent : public ofxDatGuiInteractiveObject
{
    public:
    
        ofxDatGuiComponent(string label);
        virtual ~ofxDatGuiComponent();
    
        vector<ofxDatGuiComponent*> children;
    
        int     getX();
        int     getY();
        void    setIndex(int index);
        int     getIndex();
        void    setName(string name);
        string  getName();
        bool    is(string name);
    
        void    setColor(ofColor c1, ofColor c2, ofColor c3);
        void    setBackgroundColor(ofColor c);
        void    setOnMouseOverColor(ofColor c);
        void    setOnMouseDownColor(ofColor c);

        void    setLabel(string label);
        void    setLabelColor(ofColor c);
        string  getLabel();
    
        void    setStroke(ofColor c, int width);
        void    setStrokeColor(ofColor c);
        void    setStrokeWidth(int width);
        void    setStrokeVisible(bool visible);
    
        void    setStripe(ofColor color, int width);
        void    setStripeWidth(int width);
        void    setStripeColor(ofColor color);
        void    setStripeVisible(bool visible);
    
        void    setAnchor(ofxDatGuiAnchor anchor);
        void    setEnabled(bool visible);
        bool    getEnabled();
        void    setVisible(bool visible);
        bool    getVisible();
        void    setFocused(bool focused);
        bool    getFocused();
        void    setOpacity(float opacity);
        bool    getPressed();
        ofxDatGuiType getType();
    
        virtual void draw() = 0;
        virtual void update(bool acceptEvents = true);
        virtual bool hitTest(ofPoint m);

        virtual void setY(int y);
        virtual void setWidth(int w);
        virtual void setOrigin(int x, int y);
        virtual void setTemplate(ofxDatGuiTemplate* t);
        virtual void onTemplateSet(ofxDatGuiTemplate* t);
    
        virtual void setAlignment(ofxDatGuiAlignment align);
        virtual int  getWidth();
        virtual int  getHeight();
        virtual bool getIsExpanded();
        virtual void drawColorPicker();

        virtual void onFocus();    
        virtual void onFocusLost();
        virtual void onWindowResized();
        virtual void onKeyPressed(int key);
        virtual void onMouseEnter(ofPoint m);
        virtual void onMousePress(ofPoint m);
        virtual void onMouseDrag(ofPoint m);
        virtual void onMouseLeave(ofPoint m);
        virtual void onMouseRelease(ofPoint m);
        void onKeyPressed(ofKeyEventArgs &e);
        void onWindowResized(ofResizeEventArgs &e);
    
        static std::unique_ptr<ofxDatGuiTemplate> theme;
        static std::unique_ptr<ofxDatGuiTemplate> getTheme();
    
    protected:
    
        int x;
        int y;
        int mIndex;
        string mName;
        bool mFocused;
        bool mVisible;
        bool mEnabled;
        bool mMouseOver;
        bool mMouseDown;
        bool mRetinaEnabled;
        ofxDatGuiType mType;
        ofxDatGuiFont* mFont;
        ofxDatGuiAnchor mAnchor;
    
        struct{
            float width;
            float height;
            float padding;
            float vMargin;
            float opacity;
            struct{
                ofColor inputArea;
                ofColor background;
                ofColor onMouseOver;
                ofColor onMouseDown;
            } color;
            struct{
                int width;
                bool visible;
                ofColor color;
            } stroke;
            struct{
                int width;
                bool visible;
                ofColor color;
            } stripe;
            ofTrueTypeFont* font;
            ofColor guiBackground;
        } mStyle;
    
        struct{
            string text;
            bool visible;
            ofColor color;
            float width;
            float maxWidth;
            int marginRight;
            ofRectangle rect;
            bool forceUpperCase;
            ofxDatGuiAlignment alignment;
        } mLabel;
    
        struct {
            int x;
            int y;
            int size;
            ofColor color;
        } mIcon;
    
        struct {
            int width;
            int height;
        } mWindow;
    
        void drawLabel();
        void drawLabel(string label);
        void drawBkgd();
        void drawStripe();
    
};

