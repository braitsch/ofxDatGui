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
        void draw();
        void update();
        ofPoint mouse;
        static ofPoint pos;
    
        void addSlider(string label, float val);
    
    private:
        bool mousePressed;
        ofxDatGuiItem* activeItem;
        vector<ofxDatGuiItem*> items;
        void onMousePressed(ofMouseEventArgs &e);
        void onMouseReleased(ofMouseEventArgs &e);

};