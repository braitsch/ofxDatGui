#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        string getHex(int hex);
    
        ofxDatGuiFolder* f1;
        ofxDatGuiFolder* f2;
    
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onToggleEvent(ofxDatGuiToggleEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
};
