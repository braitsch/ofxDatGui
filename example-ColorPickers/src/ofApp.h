#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        ofxDatGuiColorPicker* picker;
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
		
};
