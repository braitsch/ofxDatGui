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

#include "ofxDatGuiTemplate.h"

unique_ptr<ofxDatGui1440x900> ofxDatGui1440x900::tmplt = nullptr;
unique_ptr<ofxDatGui2880x1800> ofxDatGui2880x1800::tmplt = nullptr;

ofxDatGui2880x1800::ofxDatGui2880x1800()
{
    row.width   = 540;
    row.height  *= 2;
    row.padding *= 2;
    row.spacing *= 2;
    row.stripeWidth *= 2;
    font.size   *= 2;
    font.highlightPadding *= 2;
    matrix.buttonSize = 47;
    init();
}

ofxDatGui1440x900::ofxDatGui1440x900()
{
// just inherent all defaults //
    init();
}

ofxDatGuiTemplate* ofxDatGui1440x900::get()
{
    if (tmplt == nullptr) {
        tmplt = unique_ptr<ofxDatGui1440x900>(new ofxDatGui1440x900());
    }
    return tmplt.get();
}

ofxDatGuiTemplate* ofxDatGui2880x1800::get()
{
    if (tmplt == nullptr) {
        tmplt = unique_ptr<ofxDatGui2880x1800>(new ofxDatGui2880x1800());
    }
    return tmplt.get();
}
