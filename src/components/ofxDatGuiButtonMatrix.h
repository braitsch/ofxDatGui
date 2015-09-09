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
#include "ofxDatGuiItem.h"

class ofxDatGuiMatrixButton {

    public:
        ofxDatGuiMatrixButton(ofxDatGuiGlobals *gui, int size, int index, bool showLabels)
        {
            mGui = gui;
            mIndex = index;
            mSelected = false;
            mRect = ofRectangle(0, 0, size, size);
            mColor = ofxDatGuiColor::LABEL;
            mLabelColor = ofxDatGuiColor::INPUT;
            mShowLabels = showLabels;
            mFontRect = mGui->font.getStringBoundingBox(ofToString(mIndex+1), 0, 0);
        }
    
        void draw(int x, int y)
        {
            mRect.x = x+origin.x;
            mRect.y = y+origin.y;
            ofPushStyle();
                ofFill();
                ofSetColor(mColor);
                ofDrawRectangle(mRect);
                if (mShowLabels) mGui->font.drawText(ofToString(mIndex+1), mLabelColor, mRect.x+mRect.width/2-mFontRect.width/2, mRect.y+mRect.height/2);
            ofPopStyle();
        }
    
        void hitTest(ofPoint m, bool mouseDown)
        {
            if (mRect.inside(m) && !mSelected){
                if (mouseDown){
                    mColor = ofxDatGuiColor::INPUT;
                    mLabelColor = ofxDatGuiColor::LABEL;
                }   else{
                    mColor = ofxDatGuiColor::SLIDER;
                    mLabelColor = ofxDatGuiColor::INPUT;
                }
            }   else{
                if (mSelected){
                    mColor = ofxDatGuiColor::INPUT;
                    mLabelColor = ofxDatGuiColor::LABEL;
                }   else{
                    mColor = ofxDatGuiColor::LABEL;
                    mLabelColor = ofxDatGuiColor::INPUT;
                }
            }
        }
    
        void setOrigin(int x, int y)
        {
            origin.x = x;
            origin.y = y;
        }
    
        void onMouseRelease(ofPoint m)
        {
            if (mRect.inside(m)) mSelected = !mSelected;
        }
    
    private:
        int x;
        int y;
        int mIndex;
        ofPoint origin;
        ofRectangle mRect;
        ofColor mColor;
        ofColor mLabelColor;
        bool mSelected;
        bool mShowLabels;
        ofRectangle mFontRect;
        ofxDatGuiGlobals* mGui;
};

class ofxDatGuiButtonMatrix : public ofxDatGuiItem {

    public:
    
        ofxDatGuiButtonMatrix(ofxDatGuiGlobals *gui, string label, int numButtons, bool showLabels) : ofxDatGuiItem(gui, label)
        {
            mHeight = 140;
            mButtonSize = 44;
            mButtonPadding = 4;
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
            for(int i=0; i<numButtons; i++) btns.push_back(ofxDatGuiMatrixButton(mGui, mButtonSize, i, showLabels));
            layoutMatrix();
        }
    
        void draw()
        {
            if (mGui->guiWidthChanged) layoutMatrix();
            ofxDatGuiItem::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe();
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(mMatrixRect);
            ofPopStyle();
            for(int i=0; i<btns.size(); i++) btns[i].draw(x+mGui->input.x, y);
        }
    
        void layoutMatrix()
        {
            mMatrixRect.x = x+mGui->input.x;
            mMatrixRect.y = y;
            mMatrixRect.width = mGui->width-mGui->input.x;
            mMatrixRect.height = mHeight;
            int nCols = floor(mMatrixRect.width/(mButtonSize+mButtonPadding));
            int nRows = ceil(btns.size()/float(nCols));
            float tx = mButtonSize+((mButtonSize+mButtonPadding)*(nCols-1));
            float dx = (mMatrixRect.width-tx)/2;
            for(int i=0; i<btns.size(); i++){
                float bx = dx + ((mButtonSize+mButtonPadding)*(i%nCols));
                float by = (mButtonSize+mButtonPadding)*(floor(i/nCols));
                btns[i].setOrigin(bx, by+mButtonPadding);
            }
            mHeight = (mButtonPadding*2) + ((mButtonSize+mButtonPadding)*(nRows-1)) + mButtonSize;
        }
    
        bool hitTest(ofPoint m)
        {
            if (mMatrixRect.inside(m)){
                for(int i=0; i<btns.size(); i++) btns[i].hitTest(m, mMouseDown);
                return true;
            }   else{
                return false;
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            for(int i=0; i<btns.size(); i++) btns[i].onMouseRelease(m);
        }
    
    private:
    
        int mButtonSize;
        int mButtonPadding;
        ofRectangle mMatrixRect;
        vector<ofxDatGuiMatrixButton> btns;

};



