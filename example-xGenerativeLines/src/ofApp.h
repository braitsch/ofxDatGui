#pragma once

#include "Line.h"
#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void update();
        void reset();
        void keyPressed(int key);
    
        int drawSpeed;
        int lineWeight;
        bool drawingPaused;
        ofImage bkgd;
        vector<Line> lines;
        bool isFullscreen;
    
        ofxDatGui* gui;
        ofxDatGuiSlider* s1;
        ofxDatGuiSlider* s2;
        ofxDatGuiSlider* s3;
        ofxDatGuiSlider* s4;

        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onToggleEvent(ofxDatGuiToggleEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
};


