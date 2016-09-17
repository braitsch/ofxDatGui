#pragma once

#include "ofMain.h"
#include "PolyMesh.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void reset();
    
        ofxDatGui* gui;
        PolyMesh poly;
        float oscillator;
        float zSpeed;
        int margin;
        int minRadius;
        int maxRadius;
        int numSides;
        int lineWeight;
        ofColor lineColor;
        ofColor bkgdColor;
    
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
};
