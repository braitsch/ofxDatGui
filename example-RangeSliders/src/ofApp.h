#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
 
        ofxDatGuiSlider* slider;
        ofxDatGuiSlider* sliderInt;
        ofxDatGuiSlider* sliderFloat;
    
        ofParameter<int> ofParamInt;
        ofParameter<float> ofParamFloat;
    
        void onParamIntChanged(int & pInt);
        void onParamFloatChanged(float & pFloat);
        void onSliderEvent(ofxDatGuiSliderEvent e);
};
