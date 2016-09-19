#pragma once

#include "ofMain.h"
#include "ofxDatGuiSettings.h"

class Circle {

    public:
        Circle(int _radius)
        {
            x = 100;
            y = 100;
            radius = _radius;
        }

        bool inside(ofPoint mouse)
        {
             return mouse.distance( ofPoint(x, y) ) <= radius;
        }

        void draw()
        {
            ofSetColor(ofColor::red);
            ofSetCircleResolution(100);
            ofDrawCircle(this->x, this->y, radius);
        }

        float x;
        float y;
        int radius;

};

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

        Circle* circle;
};
