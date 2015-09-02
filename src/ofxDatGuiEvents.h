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
#include <string>
#include <iostream>

class ofxDatGuiButton;
class ofxDatGuiSlider;

class ofxDatGuiEvent{
    
    public:
        ofxDatGuiEvent(int eType, int eIndex){
            type = eType;
            index = eIndex;
            child = 0;
            value = 0;
            scale = 0;
            text = "";
            enabled = 0;
        };
        int type;
        int index;
        int child;
        float value;
        float scale;
        std::string text;
        bool enabled;
};

class ofxDatGuiButtonEvent{

    public:
        ofxDatGuiButtonEvent(ofxDatGuiButton* t)
        {
            target = t;
        }
    ofxDatGuiButton* target;
};

namespace ofxDatGuiEventType
{
    enum ofxDatGuiEventType{
        GUI_TOGGLED = 0,
        BUTTON_PRESSED,
        BUTTON_RELEASED,
        BUTTON_CLICKED,
        BUTTON_TOGGLED,
        INPUT_CHANGED,
        COLOR_CHANGED,
        SLIDER_CHANGED,
        OPTION_SELECTED,
        DROPDOWN_TOGGLED
    };
}