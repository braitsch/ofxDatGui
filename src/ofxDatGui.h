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
#include "ofxDatGuiGroups.h"
#include "ofxDatGuiControls.h"

class ofxDatGui : public ofxDatGuiInteractiveObject
{
    
    public:
    
        ofxDatGui(int x, int y);
        ofxDatGui(uint8_t position);
    
        void draw();
        void update();
        void setWidth(int width);
        void setVisible(bool visible);
        void setDisabled(bool disable);
        void setOpacity(float opacity);
        void setPosition(int x, int y);
        void setAutoDraw(bool autodraw);
        int getWidth();
        int getHeight();
        ofPoint getPosition();
    
        ofxDatGuiHeader* addHeader(string label = "");
        ofxDatGuiFooter* addFooter();
        ofxDatGuiTextInput* addTextInput(string label, string value = "");
        ofxDatGuiButton* addButton(string label);
        ofxDatGuiToggle* addToggle(string label, bool state);
        ofxDatGuiSlider* addSlider(string label, float min, float max);
        ofxDatGuiSlider* addSlider(string label, float min, float max, float val);
        ofxDatGuiDropdown* addDropdown(vector<string> options);
        ofxDatGui2dPad* add2dPad(string label);
        ofxDatGui2dPad* add2dPad(string label, ofRectangle bounds);
        ofxDatGuiColorPicker* addColorPicker(string label, ofColor color = ofColor::black);
        ofxDatGuiMatrix* addMatrix(string label, int numButtons, bool showLabels = false);
        ofxDatGuiFolder* addFolder(string label, ofColor color = ofxDatGuiColor::LABEL);
    
    // experimental //
        ofxDatGuiButton* getButton(string key);
        ofxDatGuiSlider* getSlider(string key);
        ofxDatGui2dPad* get2dPad(string key);
        ofxDatGuiDropdown* getDropdown(string key);
        ofxDatGuiTextInput* getTextInput(string key);
        ofxDatGuiColorPicker* getColorPicker(string key);
    
    private:
    
        int mHeight;
        int mHeightMinimum;
        bool mVisible;
        bool mDisabled;
        bool mExpanded;
        bool mGuiChanged;
        bool mousePressed;
        ofPoint mouse;
        ofxDatGuiItem* activeHover;
        ofxDatGuiItem* activeFocus;
        ofxDatGuiGlobals mGui;
        ofxDatGuiHeader* mGuiHeader;
        ofxDatGuiFooter* mGuiFooter;
        vector<ofxDatGuiItem*> items;
        vector<ofxDatGuiItem*> trash;
    
        void init();
        void enableRetina();
        void layoutGui();
        void anchorGui();
        void onDraw(ofEventArgs &e);
        void onUpdate(ofEventArgs &e);
        bool isMouseOverRow(ofxDatGuiItem* row);
        bool isMouseOverGui();
        void onKeyPressed(ofKeyEventArgs &e);
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);
        void onWindowResized(ofResizeEventArgs &e);

        void moveGui(ofPoint pt);
        void expandGui();
        void collapseGui();
        void attachItem(ofxDatGuiItem* item);
        void adjustHeight(int index);
    
        ofxDatGuiItem* getComponent(string key);
        void onInternalEventCallback(ofxDatGuiInternalEvent e);
        void onButtonEventCallback(ofxDatGuiButtonEvent e);
        void onSliderEventCallback(ofxDatGuiSliderEvent e);
        void onTextInputEventCallback(ofxDatGuiTextInputEvent e);
        void onDropdownEventCallback(ofxDatGuiDropdownEvent e);
        void on2dPadEventCallback(ofxDatGui2dPadEvent e);
        void onColorPickerEventCallback(ofxDatGuiColorPickerEvent e);
        void onMatrixEventCallback(ofxDatGuiMatrixEvent e);

};
