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
 
        ofxDatGuiSlider* g1s1;
        ofxDatGuiSlider* g1s2;
        ofxDatGuiWaveMonitor* g1m1;
    
        ofxDatGuiSlider* g2s1;
        ofxDatGuiSlider* g2s2;
        ofxDatGuiWaveMonitor* g2m1;
    
        float angle1;
        void onGui1SliderEvent(ofxDatGuiSliderEvent e);
        void onGui2SliderEvent(ofxDatGuiSliderEvent e);
    
};
