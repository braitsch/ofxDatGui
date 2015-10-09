#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGui* g1;
        ofxDatGui* g2;
 
        ofxDatGuiToggle* g1t1;
        ofxDatGuiToggle* g1t2;
        ofxDatGuiSlider* g1s1;
        ofxDatGuiSlider* g1s2;
        ofxDatGuiWaveMonitor* g1m1;
        ofxDatGuiValuePlotter* p1;
    
        float angle1;
        void onGuiButtonEvent(ofxDatGuiButtonEvent e);
        void onGuiSliderEvent(ofxDatGuiSliderEvent e);
    
};
