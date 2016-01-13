#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        int width;
        ofxDatGuiTheme* theme;
        ofxDatGuiButton* addItem;
        ofxDatGuiScrollView* view;
    
        void onAddNewItemButtonClick(ofxDatGuiButtonEvent e);
    
};
