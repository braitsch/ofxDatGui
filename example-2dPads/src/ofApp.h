#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void windowResized(int w, int h);
 
        ofRectangle bounds;
        ofxDatGui2dPad* pad;
        bool mUseCustomBounds;
    
        void setBounds();
        void on2dPadEvent(ofxDatGui2dPadEvent e);
    
};
