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
#include "ofxDatGuiThemes.h"
#include "ofxDatGuiEvents.h"
#include "ofxDatGuiConstants.h"

namespace ofxDatGuiMsg
{
    const string EVENT_HANDLER_NULL = "[WARNING] :: Event Handler Not Set";
    const string COMPONENT_NOT_FOUND = "[ERROR] :: Component Not Found";
    const string PANEL_ALREADY_HAS_FOCUS = "[WARNING] :: Panel Already Has Focus";
}

class ofxDatGuiLog {

    public:
        static void write(string m1, string m2="")
        {
            if (!mQuiet) {
                cout << m1;
                if (m2!="") cout << " : " << m2;
                cout << endl;
            }
        }
        static void quiet()
        {
            mQuiet = true;
        }
        static bool mQuiet;
};

inline static float ofxDatGuiScale(float val, float min, float max)
{
    if (min<0){
        float n = abs(min);
        float a = min+n;
        float b = max+n;
        float c = val+n;
        return (c-a)/(b-a);
    }   else{
        return (val-min)/(max-min);
    }
}

class ofxDatGuiInteractiveObject{

    public:

    // button events //
        typedef std::function<void(ofxDatGuiButtonEvent)> onButtonEventCallback;
        onButtonEventCallback buttonEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onButtonEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            buttonEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }

    // slider events //
        typedef std::function<void(ofxDatGuiSliderEvent)> onSliderEventCallback;
        onSliderEventCallback sliderEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onSliderEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            sliderEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // text input events //
        typedef std::function<void(ofxDatGuiTextInputEvent)> onTextInputEventCallback;
        onTextInputEventCallback textInputEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onTextInputEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            textInputEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // color picker events //
        typedef std::function<void(ofxDatGuiColorPickerEvent)> onColorPickerEventCallback;
        onColorPickerEventCallback colorPickerEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onColorPickerEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            colorPickerEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // dropdown events //
        typedef std::function<void(ofxDatGuiDropdownEvent)> onDropdownEventCallback;
        onDropdownEventCallback dropdownEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onDropdownEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            dropdownEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // 2d pad events //
        typedef std::function<void(ofxDatGui2dPadEvent)> on2dPadEventCallback;
        on2dPadEventCallback pad2dEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void on2dPadEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            pad2dEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // matrix events //
        typedef std::function<void(ofxDatGuiMatrixEvent)> onMatrixEventCallback;
        onMatrixEventCallback matrixEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onMatrixEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            matrixEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }
    
    // scrollview events //
        typedef std::function<void(ofxDatGuiScrollViewEvent)> onScrollViewEventCallback;
        onScrollViewEventCallback scrollViewEventCallback;
    
        template<typename T, typename args, class ListenerClass>
        void onScrollViewEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            scrollViewEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }

    // internal events //
        typedef std::function<void(ofxDatGuiInternalEvent)> onInternalEventCallback;
        onInternalEventCallback internalEventCallback;
        
        template<typename T, typename args, class ListenerClass>
        void onInternalEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            internalEventCallback = std::bind(listenerMethod, owner, std::placeholders::_1);
        }

};

