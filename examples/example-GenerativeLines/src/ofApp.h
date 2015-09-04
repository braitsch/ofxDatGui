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
    
        ofxDatGui* gui;
        ofxDatGuiSlider* s1;
        ofxDatGuiSlider* s2;
        ofxDatGuiSlider* s3;
        ofxDatGuiSlider* s4;
        ofxDatGuiButton* b1;
        ofxDatGuiToggle* t1;
        ofxDatGuiColorPicker* p1;
        ofxDatGuiColorPicker* p2;
        ofxDatGuiColorPicker* p3;
        ofxDatGuiColorPicker* p4;

        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
};


