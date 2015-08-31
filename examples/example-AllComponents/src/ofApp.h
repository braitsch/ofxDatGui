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
        void onGuiEvent(ofxDatGuiEvent e);
        void log(ofxDatGuiEvent e, string s);
    
};

