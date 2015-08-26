#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void update();
    
        ofxDatGui* gui;
        void onGuiEvent(ofxDatGuiEvent e);
    
};

