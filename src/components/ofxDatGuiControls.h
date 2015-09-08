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
#include "ofxDatGuiButton.h"

class ofxDatGuiHeader : public ofxDatGuiButton {

    public:

        ofxDatGuiHeader(ofxDatGuiGlobals *gui, string label) : ofxDatGuiButton(gui, label)
        {
            mHeight = mGui->row.height*.8;
            mLabelWidth = mGui->font.getStringBoundingBox(mLabel, 0, 0).width;
        }
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiButton::drawBkgd();
                mGui->font.drawLabel(mLabel, x+mGui->width/2-mLabelWidth/2, y+mHeight/2);
            }
        }
    
        void onMousePress(ofPoint m)
        {
            dragOffset = ofPoint(m.x-this->x,m.y-this->y);
        }
    
        void onMouseRelease(ofPoint m)
        {
            dragOffset = m;
        }
    
        ofPoint dragOffset;
    
    private:
        int mLabelWidth;

};

class ofxDatGuiFooter : public ofxDatGuiButton {


    public:
    
        ofxDatGuiFooter(ofxDatGuiGlobals *gui) : ofxDatGuiButton(gui, "COLLAPSE CONTROLS")
        {
            mIsExpanded = true;
            mHeight = mGui->row.height*.8;
            mLabelWidth = mGui->font.getStringBoundingBox(mLabel, 0, 0).width;
        }
    
        bool getIsExpanded()
        {
            return mIsExpanded;
        }
    
        void draw()
        {
            ofxDatGuiButton::drawBkgd();
            mGui->font.drawLabel(mLabel, x+mGui->width/2-mLabelWidth/2, y+mHeight/2);
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiInternalEvent e(ofxDatGuiEventType::GUI_TOGGLED, mId);
            internalEventCallback(e);
            if (mIsExpanded){
                mIsExpanded = false;
                setLabel("EXPAND CONTROLS");
                mLabelWidth = mGui->font.getStringBoundingBox(mLabel, 0, 0).width;
            }   else{
                mIsExpanded = true;
                setLabel("COLLAPSE CONTROLS");
                mLabelWidth = mGui->font.getStringBoundingBox(mLabel, 0, 0).width;
            }
        }
    
    private:
        int mLabelWidth;
        bool mIsExpanded;
    
};
