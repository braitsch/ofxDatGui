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

class ofxDatGuiTheme1 : public ofxDatGui2880x1800{

    public:
    
        ofxDatGuiTheme1()
        {
            stripe.visible = false;
            color.label = hex(0xF8F3F0);
            color.background = hex(0x4C4743);
            color.inputAreaBackground = hex(0xB5BCB2);
            color.slider.fill = hex(0xFFB230);
            color.slider.text = hex(0xFFFFFF);
            color.textInput.text = hex(0xFFFFFF);
            color.colorPicker.border = hex(0xF8F3F0);
            color.matrix.hover.button = hex(0xC3A279);
            color.matrix.selected.button = hex(0x4C4743);
            init();
        }
};

class ofxDatGuiTheme2 : public ofxDatGui2880x1800{

    public:
    
        ofxDatGuiTheme2()
        {
            stripe.visible = false;
            color.guiBackground = hex(0x001727);
            color.label = hex(0xF8F3F0);
            color.background = hex(0x162C3A);
            color.inputAreaBackground = hex(0x61717D);
            color.slider.fill = hex(0xF8F3F0);
            color.slider.text = hex(0xFFFFFF);
            color.textInput.text = hex(0xFFFFFF);
            color.colorPicker.border = hex(0xF8F3F0);
            color.matrix.hover.button = hex(0x55666F);
            color.matrix.selected.button = hex(0x334553);
            init();
        }
};


