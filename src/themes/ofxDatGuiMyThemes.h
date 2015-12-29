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
#include "ofxDatGuiTheme.h"

/*
    Add your custom themes here and ensure they extend ofxDatGuiTheme
*/

class ofxDatGuiExampleCustomTheme : public ofxDatGui2880x1800{

    public:
    
        ofxDatGuiExampleCustomTheme()
        {
    // look inside of ofxDatGuiTheme for a full list of settings you can override //
            stripe.visible = false;
            color.label = ofColor::fromHex(0xF8F3F0);
            color.background = ofColor::fromHex(0x4C4743);
            color.inputAreaBackground = ofColor::fromHex(0xB5BCB2);
            color.slider.fill = ofColor::fromHex(0xFFB230);
            color.slider.text = ofColor::fromHex(0xF8F3F0);
            color.textInput.text = ofColor::fromHex(0xF8F3F0);
            color.colorPicker.border = ofColor::fromHex(0xEEEEEE);
    // and don't forget to call init when you're done //
            init();
        }
};


