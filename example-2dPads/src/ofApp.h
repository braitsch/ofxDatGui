#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofPoint circlePosition;
        ofRectangle bounds;
        ofxDatGui2dPad* pad;
        void on2dPadEvent(ofxDatGui2dPadEvent e);
    
};
