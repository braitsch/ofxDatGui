#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class Circle {

    public:
        Circle(int radius)
        {
            x = 100;
            y = 100;
            mRadius = radius;
        }

        bool inside(ofPoint mouse)
        {
             return mouse.distance( ofPoint(x, y) ) <= mRadius;
        }

        void draw()
        {
            ofSetColor(ofColor::red);
            ofSetCircleResolution(100);
            ofDrawCircle(this->x, this->y, mRadius);
        }
    
        float x;
        float y;

    private:
        int mRadius;

};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void windowResized(int w, int h);
    
        bool mDragging;
        Circle* circle;
        ofxDatGui* gui;
        ofxDatGuiSlider* sx;
        ofxDatGuiSlider* sy;

};


