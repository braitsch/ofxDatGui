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
#include "ofxDatGuiTemplate.h"

/*
    Add your custom templates here and ensure they extend ofxDatGuiTemplate
*/

class ofxDatGuiExampleCustomTemplate : public ofxDatGui2880x1800{

    public:
    
        ofxDatGuiExampleCustomTemplate()
        {
    // look inside of ofxDatGuiTemplate for settings to override //
            row.color.bkgd = ofColor::fromHex(0xFFD00B);
    // don't forget to call init when you're done //
            init();
        }
};

class t1 : public ofxDatGui2880x1800{
    public:
        t1(){
            row.color.bkgd = ofColor::fromHex(0xFFD00B);
            row.color.label = ofColor::fromHex(0x303030);
            textInput.color.text = ofColor::fromHex(0xEEEEEE);
            init();
        }
};
class t2 : public ofxDatGui2880x1800{
    public:
        t2(){
            row.color.bkgd = ofColor::fromHex(0x2FA1D6);
            init();
        }
};
class t3 : public ofxDatGui2880x1800{
    public:
        t3(){
            row.color.bkgd = ofColor::fromHex(0xC63256);
            init();
        }
};
class t4 : public ofxDatGui2880x1800{
    public:
        t4(){
            row.color.bkgd = ofColor::fromHex(0xeeeeee);
            row.color.label = ofColor::fromHex(0x303030);
            init();
        }
};
//
//            ofColor button              = ofColor::fromHex(0xFFD00B);
//            ofColor toggle              = ofColor::fromHex(0xFFD00B);
//            ofColor slider              = ofColor::fromHex(0x2FA1D6);
//            ofColor textInput           = ofColor::fromHex(0x1ED36F);
//            ofColor matrix              = ofColor::fromHex(0xB2770D);
//            ofColor pad2d               = ofColor::fromHex(0x9AF398);
//            ofColor dropdown            = ofColor::fromHex(0xC63256);
//            ofColor colorPicker         = ofColor::fromHex(0xFFD00B);











