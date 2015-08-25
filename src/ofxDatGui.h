//
//  ofxDatGui.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

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
        void update();
        void addInput(string label, string value = "");
        void addButton(string label);
        void addToggle(string label, bool state);
        void addSlider(string label, float min, float max);
        void addSlider(string label, float min, float max, float val);
        void addDropdown(vector<string> options);
    
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
