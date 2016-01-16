#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGuiSlider* slider;
        void onSliderEvent(ofxDatGuiSliderEvent e);
    
};
