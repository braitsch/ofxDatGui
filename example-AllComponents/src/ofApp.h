#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGuiValuePlotter* plotter;
        vector<ofxDatGuiComponent*> components;
    
		void onButtonEvent(ofxDatGuiButtonEvent e);
        void onToggleEvent(ofxDatGuiToggleEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
    
};
