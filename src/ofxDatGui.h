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
#include "ofxDatGuiButton.h"
#include "ofxDatGuiSlider.h"
#include "ofxDatGuiDropdown.h"

class ofxDatGui
{
    
    public:
    
        ofxDatGui(int x, int y);
        ofxDatGui(uint8_t position);
    
        ofPoint mouse;
        bool dropdownIsOpen;
    
        void draw();
        void update();
        void addButton(string label);
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
    
        uint8_t mAnchorPosition;
        bool mousePressed;
        ofxDatGuiItem* activeItem;
        vector<ofxDatGuiItem*> items;
        vector<ofxDatGuiDropdown*> ddowns;
    
        void init(int x, int y);
        bool isMouseOver(ofxDatGuiItem* item);
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);
    
        void attachItem(ofxDatGuiItem* item);
        void onGuiEventCallback(ofxDatGuiEvent e);

};
