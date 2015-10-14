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
#include "ofxDatGuiComponent.h"

class ofxDatGuiMatrixButton : public ofxDatGuiInteractiveObject {

    public:
        ofxDatGuiMatrixButton(int size, int index, bool showLabels, ofxDatGuiTemplate* tmplt)
        {
            mIndex = index;
            mSelected = false;
            mTemplate = tmplt;
            mShowLabels = showLabels;
            mRect = ofRectangle(0, 0, size, size);
            mFont = mTemplate->font.ttf;
            mBkgdColor = mTemplate->matrix.color.normal.button;
            mLabelColor = mTemplate->matrix.color.normal.label;
            mFontRect = mFont->getStringBoundingBox(ofToString(mIndex+1), 0, 0);
        }
    
        void setOrigin(float x, float y)
        {
            origin.x = x;
            origin.y = y;
        }
    
        void draw(int x, int y)
        {
            mRect.x = x+origin.x;
            mRect.y = y+origin.y;
            ofPushStyle();
                ofFill();
                ofSetColor(mBkgdColor);
                ofDrawRectangle(mRect);
                if (mShowLabels) mFont->drawText(ofToString(mIndex+1), mLabelColor, mRect.x+mRect.width/2-mFontRect.width/2, mRect.y+mRect.height/2);
            ofPopStyle();
        }
    
        void hitTest(ofPoint m, bool mouseDown)
        {
            if (mRect.inside(m) && !mSelected){
                if (mouseDown){
                    mBkgdColor = mTemplate->matrix.color.selected.button;
                    mLabelColor = mTemplate->matrix.color.selected.label;
                }   else{
                    mBkgdColor = mTemplate->matrix.color.hover.button;
                    mLabelColor = mTemplate->matrix.color.hover.label;
                }
            }   else{
                onMouseOut();
            }
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
                mBkgdColor = mTemplate->matrix.color.selected.button;
                mLabelColor = mTemplate->matrix.color.selected.label;
            }   else{
                mBkgdColor = mTemplate->matrix.color.normal.button;
                mLabelColor = mTemplate->matrix.color.normal.label;
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
        ofColor mBkgdColor;
        ofColor mLabelColor;
        bool mSelected;
        bool mShowLabels;
        ofRectangle mFontRect;
        ofxDatGuiFont* mFont;
        ofxDatGuiTemplate* mTemplate;

};

class ofxDatGuiMatrix : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiMatrix(string label, int numButtons, bool showLabels=false, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            mNumButtons = numButtons;
            mShowLabels = showLabels;
            mType = ofxDatGuiType::OFXDATGUI_MATRIX;
            mStripeColor = mTemplate->matrix.color.stripe;
            mButtonSize  = mTemplate->matrix.buttonSize;
            setButtons();
            setWidth(mRow.width);
        }
    
        static ofxDatGuiMatrix* getInstance()
        {
            return new ofxDatGuiMatrix("X", 0);
        }

        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            mMatrixRect.x = x + mRow.inputX;
            mMatrixRect.y = y + mRow.padding;
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiComponent::setTemplate(tmplt);
            mButtonSize  = mTemplate->matrix.buttonSize;
            mStripeColor = mTemplate->matrix.color.stripe;
            setButtons();
            setWidth(mRow.width);
        }
    
        void setButtons()
        {
            btns.clear();
            for(int i=0; i<mNumButtons; i++) {
                ofxDatGuiMatrixButton btn(mButtonSize, i, mShowLabels, mTemplate);
                btn.onInternalEvent(this, &ofxDatGuiMatrix::onButtonSelected);
                btns.push_back(btn);
            }
        }
    
        void setWidth(int w)
        {
            ofxDatGuiComponent::setWidth(w);
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
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
                ofSetColor(mTemplate->row.color.inputArea);
                ofDrawRectangle(mMatrixRect);
                for(int i=0; i<btns.size(); i++) btns[i].draw(x+mRow.inputX, y);
            ofPopStyle();
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
    
        ofxDatGuiMatrixButton* getChildAt(int index)
        {
            return &btns[index];
        }
    
        void onMouseRelease(ofPoint m)
        {
            ofxDatGuiComponent::onMouseRelease(m);
            for(int i=0; i<btns.size(); i++) btns[i].onMouseRelease(m);
        }
    
        void onButtonSelected(ofxDatGuiInternalEvent e)
        {
            if (matrixEventCallback != nullptr) {
                ofxDatGuiMatrixEvent ev(this, e.index, btns[e.index].getSelected());
                matrixEventCallback(ev);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
    private:
    
        int mButtonSize;
        int mNumButtons;
        bool mShowLabels;
        ofRectangle mMatrixRect;
        static const int mMinPadding = 2;
        vector<ofxDatGuiMatrixButton> btns;

};



