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
#include "ofxDatGuiItem.h"
#include "ofxDatGuiSlider.h"

class ofxDatGui
{
    
    public:
    
        ofxDatGui(int x, int y);
        ofxDatGui(uint8_t position);
    
        ofPoint mouse;
        static ofPoint pos;
    
        void draw();
        void update();
        void addSlider(string label, float val);
    
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
    
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);
    
        void dispatchEvent(ofxDatGuiEvent k)
        {
            changeEventCallback(k);
        }

};