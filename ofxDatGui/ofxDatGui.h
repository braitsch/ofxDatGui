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
#include "ofMain.h"
#include "ofEvents.h"
#include "ofxDatGuiSettings.h"
#include "ofxDatGuiItem.h"
#include "ofxDatGuiInput.h"
#include "ofxDatGuiButton.h"
#include "ofxDatGuiSlider.h"
#include "ofxDatGuiDropdown.h"

class ofxDatGui
{
    
    public:
    
        ofxDatGui(ofVec2f position);
        ofxDatGui(uint8_t position);
    
        void draw();
        void setOpacity(float opacity);
        ofxDatGuiInput* addInput(string label, string value = "");
        ofxDatGuiButton* addButton(string label);
        ofxDatGuiToggle* addToggle(string label, bool state);
        ofxDatGuiSlider* addSlider(string label, float min, float max);
        ofxDatGuiSlider* addSlider(string label, float min, float max, float val);
        ofxDatGuiDropdown* addDropdown(vector<string> options);
    
        ofxDatGuiItem::onChangeEventCallback changeEventCallback;
    
    // template methods must be declared in header file //
        template<typename T, typename args, class ListenerClass>
        void onGuiEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            using namespace std::placeholders;
            changeEventCallback = std::bind(listenerMethod, owner, _1);
        }
    
    private:
    
        int mHeight;
        int mHeightMinimum;
        int mAnchorPosition;
        ofPoint mouse;
        bool mShowGui;
        bool mousePressed;
        ofxDatGuiItem* activeHover;
        ofxDatGuiItem* activeFocus;
        ofxDatGuiToggler* mGuiToggler;
        vector<ofxDatGuiItem*> items;
    
        void init();
        void onDraw(ofEventArgs &e);
        void onUpdate(ofEventArgs &e);
        bool isMouseOver(ofxDatGuiItem* item);
        void onKeyPressed(ofKeyEventArgs &e);
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);

        void expandGui();
        void collapseGui();
        void attachItem(ofxDatGuiItem* item);
        void adjustHeight(int index, int amount);
        void onGuiEventCallback(ofxDatGuiEvent e);

};
