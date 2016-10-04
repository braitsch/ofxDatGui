#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

public:
        void setup();
	void update();
	void draw();

        ofxDatGuiButton* add;
        ofxDatGuiButton* remove;
        ofxDatGui *gui, *guiFolder;
        ofxDatGuiFolder * folder;
        void positionButtons();
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onButtonEventFolder(ofxDatGuiButtonEvent e);
        void onGuiButtonEvent(ofxDatGuiButtonEvent e);

};
