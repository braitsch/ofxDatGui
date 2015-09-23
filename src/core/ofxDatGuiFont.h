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
#include "ofxDatGuiConstants.h"

class ofxDatGuiFont{

    public:
    
        ofxDatGuiFont(string file, int size, int padding, ofColor lc, ofColor hc)
        {
            tFont.load(OFXDG_ASSET_DIR+"/"+file, size);
            labelColor = lc;
            highlightColor = hc;
            highlightPadding = padding;
            labelHeight = getStringBoundingBox("ABCDEFG123456", 0, 0).height;
        }

        void drawLabel(string text, int xpos, int ypos)
        {
            ofPushStyle();
                ofSetColor(labelColor);
                if (tFont.isLoaded()){
                    tFont.drawString(text, xpos, ypos+labelHeight/2);
                }   else{
                    if (!mRetinaEnabled) ypos-=2;
                    ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
                }
            ofPopStyle();
        }
    
        void drawText(string text, ofColor color, int xpos, int ypos, bool highlight = false)
        {
            ofPushStyle();
                if (highlight){
                    ofRectangle hRect = getStringBoundingBox(text, xpos, ypos+labelHeight/2);
                    hRect.x -= highlightPadding;
                    hRect.width += highlightPadding*2;
                    hRect.y -= highlightPadding;
                    hRect.height += highlightPadding*2;
                    ofSetColor(highlightColor);
                    ofDrawRectangle(hRect);
                }
                ofSetColor(color);
                if (tFont.isLoaded()){
                    tFont.drawString(text, xpos, ypos+labelHeight/2);
                }   else{
                    if (mRetinaEnabled) ypos-=2;
                    ofDrawBitmapString(text, xpos, ypos+labelHeight/2);
                }
            ofPopStyle();
        }
    
        ofRectangle getStringBoundingBox(string str, int x, int y)
        {
            if (tFont.isLoaded()){
                return tFont.getStringBoundingBox(str, x, y);
            }   else{
                return bFont.getBoundingBox(str, x, y);
            }
        }
    
        int size;
        int labelX;
        int labelHeight;
        int highlightPadding;
    
    private:
    
        ofColor labelColor;
        ofColor highlightColor;
        ofBitmapFont bFont;
        ofTrueTypeFont tFont;
        bool mRetinaEnabled;
};


