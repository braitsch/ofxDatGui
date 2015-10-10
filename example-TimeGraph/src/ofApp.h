#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGui* gui;
 
        ofxDatGuiSlider* s1;
        ofxDatGuiSlider* s2;
        ofxDatGuiDropdown* dd;
        ofxDatGuiWaveMonitor* m1;
        ofxDatGuiValuePlotter* p1;
        ofxDatGuiValuePlotter* p2;
    
        float ang1;
        float ang2;
        void onGuiSliderEvent(ofxDatGuiSliderEvent e);
        void onGuiDropdownEvent(ofxDatGuiDropdownEvent e);
    
};
