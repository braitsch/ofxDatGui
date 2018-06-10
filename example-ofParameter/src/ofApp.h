#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        ofxDatGui* gui;
        ofParameter<int> p1;
        ofParameter<float> p2;
        ofParameter<int> p3;
    
        ofxDatGuiLabel*  l1;
        ofxDatGuiSlider* s1;
        ofxDatGuiSlider* s2;
        ofxDatGuiSlider* s3;
    
        void onSliderEvent(ofxDatGuiSliderEvent e);
    
};
