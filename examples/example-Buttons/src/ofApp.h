#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        int numClicks;
        bool isFullscreen;
        ofxDatGuiButton* button;
        ofxDatGuiButton* toggle;
        void positionButtons();
        void onButtonEvent(ofxDatGuiButtonEvent e);
    
};
