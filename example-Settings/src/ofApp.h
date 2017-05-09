#pragma once

#include "ofMain.h"
#include "ofxDatGuiSettings.h"

class Circle {

    public:
        Circle()
        {
            x = ofRandomWidth();
            y = ofRandomHeight();
            radius = ofRandom(150);
            color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
            filled = true;
        }

        bool inside(ofPoint mouse)
        {
             return mouse.distance( ofPoint(x, y) ) <= radius;
        }

        void draw()
        {
            ofSetColor(color);
            ofSetCircleResolution(100);
            if(filled) ofFill();
            else ofNoFill();
            ofDrawCircle(x, y, radius);
            ofDrawBitmapString(name, x + radius + 10, y);
        }

        float x;
        float y;
        int radius;
        ofColor color;
        bool filled;
        string name;

};

class ofApp : public ofBaseApp{

    public:
        void setup();
        void draw();
        void update();

        ofxDatGui* gui;
        bool mFullscreen;
        void refreshWindow();
        void keyPressed(int key);
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onToggleEvent(ofxDatGuiToggleEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);

        uint tIndex;
        vector<ofxDatGuiTheme*> themes;
        ofxDatGuiSettings settings;

        vector<Circle> circles;
};
