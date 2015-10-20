#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGuiSlider* slider;
    // change this if you're on a non-retina display //
        ofxDatGui2880x1800 mTemplate;
        void onSliderEvent(ofxDatGuiSliderEvent e);
    
};
