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

class ofxDatGuiWaveMonitor : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiWaveMonitor(string label, float min, float max, ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            mFill = true;
            mSpeed = 1.0f;
            mAmplitude = 0.0f;
            setRange(min, max);
            setTemplate(mTemplate);
            mType = ofxDatGuiType::WAVE_MONITOR;
        }
    
        void setRange(float min, float max)
        {
            mMin = min;
            mMax = max;
            mMid = (max+min)/2;
            setFrequency(mMid);
        }
    
        void setSpeed(float speed)
        {
            mSpeed = speed;
        }
    
        void setFrequency(float val)
        {
            mVal = val;
        // shift all points over before adding new value //
            for (int i=0; i<pts.size(); i++) {
                pts[i].x -= mSpeed;
        // this still allows two points to have the same x coordinate //
                if (pts[i].x <= mPlotterRect.x){
                    pts.erase(pts.begin());
                }   else if (pts[i].x <= mPlotterRect.x + mSpeed){
                    pts[i].x = mPlotterRect.x + mLineWeight/2;
                }
            }
            float scale = mVal/mMax;
            float height = ((mStepHeight*scale)*mAmplitude) * -1;
            pts.push_back(ofVec2f(mPlotterRect.x+mPlotterRect.width, mPlotterRect.y + mPlotterMidY + height));
        }
    
        void setAmplitude(float amp)
        {
            mAmplitude = amp;
            if (mAmplitude < 0) {
                mAmplitude = 0;
            }   else if (mAmplitude > MAX_AMPLITUDE){
                mAmplitude = MAX_AMPLITUDE;
            }
        }
    
        void drawFilled(bool fill)
        {
            mFill = fill;
        }
    
        bool hitTest(ofPoint m)
        {
        // this is called each frame within update //
            setFrequency(mVal);
            return false;
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
                ofSetColor(mTemplate->row.color.inputArea);
                ofDrawRectangle(mPlotterRect);
                glColor3ub(210, 210, 210);
                mFill ? drawPlotFilled() : drawPlotNoFill();
            ofPopStyle();
        }
    
        void drawPlotFilled()
        {
            float x = mPlotterRect.x;
            float y = mPlotterRect.y+mPlotterRect.height;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_TRIANGLE_STRIP);
            for (int i=0; i<pts.size(); i++) {
                glVertex2f(pts[i].x, y);
                glVertex2f(pts[i].x, pts[i].y);
            }
            glEnd();
        }
    
        void drawPlotNoFill()
        {
            float x = mPlotterRect.x;
            float y = mPlotterRect.y+mPlotterRect.height;
            glLineWidth(mLineWeight);
            glBegin(GL_LINE_LOOP);
            glVertex2f(x+mPlotterRect.width, y);
            glVertex2f(pts[0].x, y);
            for (int i=0; i<pts.size(); i++) {
                glVertex2f(pts[i].x, pts[i].y);
                if (i == pts.size()-1){
                    glVertex2f(pts[i].x, pts[i].y);
                }   else{
                    glVertex2f(pts[i+1].x, pts[i+1].y);
                }
            }
            glVertex2f(x+mPlotterRect.width, y);
            glEnd();
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            setTemplate(mTemplate);
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiComponent::setTemplate(tmplt);
            mRow.height = mTemplate->plotter.height;
            mLineWeight = mTemplate->plotter.lineWeight;
            mStripeColor = mTemplate->plotter.color.stripe;
            setWidth(mRow.width);
        }
    
        void setWidth(int w)
        {
            ofxDatGuiComponent::setWidth(w);
            mPlotterRect.x = x + mRow.inputX;
            mPlotterRect.y = y + mRow.padding;
            mPlotterRect.width = mRow.width - mRow.padding - mRow.inputX;
            mPlotterRect.height = mRow.height - (mRow.padding*2);
            mPlotterMidY = mPlotterRect.height/2;
            mStepHeight = mPlotterMidY / MAX_AMPLITUDE;
        }
    
    private:

        bool mFill;
        float mMin;
        float mMax;
        float mVal;
        float mMid;
        float mSpeed;
        int mLineWeight;
        float mAmplitude;
        vector<ofVec2f> pts;
        float mStepHeight;
        float mPlotterMidY;
        ofRectangle mPlotterRect;
    
        static const int MAX_AMPLITUDE = 10;

};


