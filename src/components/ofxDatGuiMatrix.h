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

class ofxDatGuiMatrixButton : public ofxDatGuiInteractiveObject {

    public:
        ofxDatGuiMatrixButton(int size, int index, bool showLabels, ofxDatGuiFont* font)
        {
            mFont = font;
            mIndex = index;
            mSelected = false;
            mRect = ofRectangle(0, 0, size, size);
            mColor = ofxDatGuiColor::LABEL;
            mLabelColor = ofxDatGuiColor::INPUT;
            mShowLabels = showLabels;
            mFontRect = mFont->getStringBoundingBox(ofToString(mIndex+1), 0, 0);
        }
    
        void draw(int x, int y)
        {
            mRect.x = x+origin.x;
            mRect.y = y+origin.y;
            ofPushStyle();
                ofFill();
                ofSetColor(mColor);
                ofDrawRectangle(mRect);
                if (mShowLabels) mFont->drawText(ofToString(mIndex+1), mLabelColor, mRect.x+mRect.width/2-mFontRect.width/2, mRect.y+mRect.height/2);
            ofPopStyle();
        }
    
        void hitTest(ofPoint m, bool mouseDown)
        {
            if (mRect.inside(m) && !mSelected){
                if (mouseDown){
                    mColor = ofxDatGuiColor::MATRIX_BUTTON;
                    mLabelColor = ofxDatGuiColor::LABEL;
                }   else{
                    mColor = ofxDatGuiColor::SLIDER;
                    mLabelColor = ofxDatGuiColor::INPUT;
                }
            }   else{
                onMouseOut();
            }
        }
    
        void setOrigin(float x, float y)
        {
            origin.x = x;
            origin.y = y;
        }
    
        void setSelected(bool selected)
        {
            mSelected = selected;
        }
    
        bool getSelected()
        {
            return mSelected;
        }
    
        void onMouseOut()
        {
            if (mSelected){
                mColor = ofxDatGuiColor::MATRIX_BUTTON;
                mLabelColor = ofxDatGuiColor::LABEL;
            }   else{
                mColor = ofxDatGuiColor::LABEL;
                mLabelColor = ofxDatGuiColor::INPUT;
            }
        }
    
        void onMouseRelease(ofPoint m)
        {
            if (mRect.inside(m)) {
                mSelected = !mSelected;
                ofxDatGuiInternalEvent e(ofxDatGuiEventType::MATRIX_BUTTON_TOGGLED, mIndex);
                internalEventCallback(e);
            }
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
        ofxDatGuiFont* mFont;

};

class ofxDatGuiMatrix : public ofxDatGuiItem {

    public:
    
        ofxDatGuiMatrix(string label, int numButtons, bool showLabels=false, ofxDatGuiFont* font=nullptr) : ofxDatGuiItem(label, font)
        {
            mButtonSize = 47;
            mStripeColor = ofxDatGuiColor::BUTTON_STRIPE;
            for(int i=0; i<numButtons; i++) {
                ofxDatGuiMatrixButton btn(mButtonSize, i, showLabels, mFont);
                btn.onInternalEvent(this, &ofxDatGuiMatrix::onButtonSelected);
                btns.push_back(btn);
            }
        }

        void setOriginX(int x)
        {
            ofxDatGuiItem::setOriginX(x);
            mMatrixRect.x = x + mRow.inputX;
            mMatrixRect.y = y + mRow.padding;
            mMatrixRect.width = mRow.width - mRow.padding - mRow.inputX;
            int nCols = floor(mMatrixRect.width/(mButtonSize+mMinPadding));
            int nRows = ceil(btns.size()/float(nCols));
            float padding = (mMatrixRect.width-(mButtonSize*nCols))/(nCols-1);
            for(int i=0; i<btns.size(); i++){
                float bx = (mButtonSize+padding)*(i%nCols);
                float by = (mButtonSize+padding)*(floor(i/nCols));
                btns[i].setOrigin(bx, by + mRow.padding);
            }
            mRow.height = (mRow.padding*2) + ((mButtonSize+padding)*(nRows-1)) + mButtonSize;
            mMatrixRect.height = mRow.height - (mRow.padding*2);
        }
    
        bool hitTest(ofPoint m)
        {
            if (mMatrixRect.inside(m)){
                for(int i=0; i<btns.size(); i++) btns[i].hitTest(m, mMouseDown);
                return true;
            }   else{
                for(int i=0; i<btns.size(); i++) btns[i].onMouseOut();
                return false;
            }
        }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe();
            ofPushStyle();
                ofSetColor(ofxDatGuiColor::INPUT);
                ofDrawRectangle(mMatrixRect);
            ofPopStyle();
            for(int i=0; i<btns.size(); i++) btns[i].draw(x+mRow.inputX, y);
        }
    
        void clear()
        {
            for (int i=0; i<btns.size(); i++) btns[i].setSelected(false);
        }
    
        void setSelected(vector<int> v)
        {
            clear();
            for (int i=0; i<v.size(); i++) btns[v[i]].setSelected(true);
        }
    
        vector<int> getSelected()
        {
            vector<int> selected;
            for(int i=0; i<btns.size(); i++) if (btns[i].getSelected()) selected.push_back(i);
            return selected;
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiItem::onMouseRelease(m);
            for(int i=0; i<btns.size(); i++) btns[i].onMouseRelease(m);
        }
    
        void onButtonSelected(ofxDatGuiInternalEvent e)
        {
            ofxDatGuiMatrixEvent ev(this, e.index, btns[e.index].getSelected());
            matrixEventCallback(ev);
        }
    
    private:
    
        int mButtonSize;
        ofRectangle mMatrixRect;
        static const int mMinPadding = 2;
        vector<ofxDatGuiMatrixButton> btns;

};



