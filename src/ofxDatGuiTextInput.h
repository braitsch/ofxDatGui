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

class ofxDatGuiTextInput : public ofxDatGuiItem {

    public:
        ofxDatGuiTextInput(int index, string label, string text) : ofxDatGuiItem(index, label)
        {
            mStripeColor = ofxDatGuiColor::INPUT_STRIPE;
            input = new ofxDatGuiTextInputField(mWidth-mPadding-inputX);
            input->setText(text);
            input->setTextIndent(ofxDatGuiFont::retinaEnabled ? TEXT_INDENT*2 : TEXT_INDENT);
            input->onGuiEvent(this, &ofxDatGuiTextInput::onInputChanged);
        }
    
        void onInputChanged(ofxDatGuiEvent e)
        {
            e.index = mId;
            changeEventCallback(e);
        }
    
        void draw()
        {
            if (mVisible){
                ofxDatGuiItem::drawBkgd();
                ofxDatGuiFont::drawLabel(mLabel, x, y + mHeight/2);
                ofxDatGuiItem::drawStripe();
                input->draw(x + inputX, y + mPadding);
            }
        }
    
        bool hitTest(ofPoint m)
        {
            return input->hitTest(m);
        }

        void onFocus()
        {
            input->onFocus();
        }
    
        void onFocusLost()
        {
            input->onFocusLost();
        }
    
        void onKeyPressed(int key)
        {
            if (key != OF_KEY_LEFT &&
                key != OF_KEY_RIGHT &&
                key != OF_KEY_UP &&
                key != OF_KEY_DOWN)
            input->onKeyPressed(key);
        }
    
    private:
        ofxDatGuiTextInputField* input;
        static int const TEXT_INDENT = 8;
    
};

