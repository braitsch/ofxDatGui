#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        int numCols;
        int numRows;
        ofTrueTypeFont font;
        ofxDatGuiMatrix* matrix;
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
    
};
