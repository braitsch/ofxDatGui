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
        ofxDatGuiButton* clearAll;
        ofxDatGuiScrollView* view;
    
        void onScrollViewEvent(ofxDatGuiScrollViewEvent e);
        void onAddNewItemButtonClick(ofxDatGuiButtonEvent e);
        void onClearAllButtonClick(ofxDatGuiButtonEvent e);
    
};
