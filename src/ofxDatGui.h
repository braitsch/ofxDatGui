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
        void draw();
        void update();
        ofPoint mouse;
        static ofPoint pos;
    
        void addSlider(string label, float val);
    
    private:
        uint8_t mAnchorPosition;
        bool mousePressed;
        ofxDatGuiItem* activeItem;
        vector<ofxDatGuiItem*> items;
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);

};