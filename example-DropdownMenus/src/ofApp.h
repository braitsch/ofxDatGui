#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        string getHex(int hex);
    
        vector<ofColor> colors;
        ofxDatGuiDropdown* menu;
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
};
