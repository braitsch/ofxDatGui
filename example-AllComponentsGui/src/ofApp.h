#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
        void setup();
        void draw();
        void update();
    
        ofxDatGui* gui;
        bool mFullscreen;
        void refreshWindow();
        void toggleFullscreen();

        void keyPressed(int key);
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
    
        unsigned int tIndex;
        vector<ofxDatGuiTheme*> themes;

};
