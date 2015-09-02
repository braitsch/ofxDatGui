#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void update();
    
        ofxDatGui* gui;
        ofxDatGuiSlider* opacitySlider;

        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
};

