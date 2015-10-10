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

        ofxDatGuiHeader(string label, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiButton(label, tmplt)
        {
            mRow.height = mRow.height*.8;
            mLabelAlignment = ofxDatGuiAlignment::CENTER;
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiButton::drawLabel();
            ofPopStyle();
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiButton::setTemplate(tmplt);
            mRow.height = mRow.height*.8;
        }
    
        void onMousePress(ofPoint m)
        {
            dragOffset = ofPoint(m.x-this->x,m.y-this->y);
            ofxDatGuiComponent::onMousePress(m);
        }
    
        void onMouseRelease(ofPoint m)
        {
            dragOffset = m;
            ofxDatGuiComponent::onFocusLost();
            ofxDatGuiComponent::onMouseRelease(m);
        }

    // we override this to allow the panel to be dragged around //
        void onFocusLost() { }

        void setAlignment(ofxDatGuiAlignment align) {}
    
        ofPoint dragOffset;
    
    private:

};

class ofxDatGuiFooter : public ofxDatGuiButton {


    public:
    
        ofxDatGuiFooter(ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiButton("collapse controls", tmplt)
        {
            mGuiCollapsed = false;
            mLabelCollapsed = "expand controls";
            mLabelExpanded = "collapse controls";
            mRow.height = mRow.height*.8;
            mLabelAlignment = ofxDatGuiAlignment::CENTER;
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiButton::setTemplate(tmplt);
            mRow.height = mRow.height*.8;
        }
    
        void setLabelWhenExpanded(string label)
        {
            mLabelExpanded = label;
            if (!mGuiCollapsed) setLabel(mLabelExpanded);
        }
    
        void setLabelWhenCollapsed(string label)
        {
            mLabelCollapsed = label;
            if (mGuiCollapsed) setLabel(mLabelCollapsed);
        }

        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiButton::drawBkgd();
                ofxDatGuiButton::drawLabel();
            ofPopStyle();
        }
    
        void onMouseRelease(ofPoint m)
        {
            mGuiCollapsed = !mGuiCollapsed;
            ofxDatGuiComponent::onMouseRelease(m);
        // dispatch event out to main application //
            ofxDatGuiInternalEvent e(ofxDatGuiEventType::GUI_TOGGLED, mIndex);
            internalEventCallback(e);
            if (!mGuiCollapsed){
                setLabel(mLabelExpanded);
            }   else{
                setLabel(mLabelCollapsed);
            }
        }
    
    // force footer label to always be centered //
        void setAlignment(ofxDatGuiAlignment align) {}
    
    private:
        bool mGuiCollapsed;
        string mLabelExpanded;
        string mLabelCollapsed;
    
};
