#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class Line : public ofPolyline{

    public:
        Line(int x, int y, ofColor c){
            init();
            ox = x;
            oy = y;
            color = c;
            addVertex(x, y);
            addVertex(x, y);
        }
        int dx;
        int dy;
        int cl;
        int ml;
        int ox;
        int oy;
        ofColor color;
        ofPoint* head;
        static int MinLength;
        static int MaxLength;
        void addVertex(int x, int y)
        {
            ofPolyline::addVertex(x, y);
            head = &getVertices()[size()-1];
        }
        void tick()
        {
            cl++;
            if (cl >= ml){
                rotate();
                addVertex(head->x, head->y);
            }
            constrain();
        }
        void init()
        {
            int x = round(ofRandom(1));
            if (x==0) x = -1;
            int y = round(ofRandom(1));
            if (y==0) y = -1;
            dx = x;
            dy = y;
            cl = 0;
            ml = round(ofRandom(MinLength, MaxLength));
        }
        void rotate()
        {
            if (dx == 1 && dy == 1){
                dx = -1;
            }   else if (dx == -1 && dy == 1){
                dy = -1;
            }   else if (dx == -1 && dy == -1){
                dx = 1;
            }   else if (dx == 1 && dy == -1){
                dy = 1;
            }
            cl = 0;
            ml = round(ofRandom(MinLength, MaxLength));
        }
        void reset()
        {
            ofPolyline::clear();
            addVertex(ox, oy);
            addVertex(ox, oy);
        }
        void constrain()
        {
            if (head->x <= 0 || head->x >= ofGetWidth()){
                dx *= -1;
                addVertex(head->x, head->y);
            }
            if (head->y <= 0 || head->y >= ofGetHeight()){
                dy *= -1;
                addVertex(head->x, head->y);
            }
        }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void update();
        void reset();
    
        int index;
        vector<Line> lines;
        int drawSpeed;
        int lineWeight;
        bool drawingPaused;
        ofImage bkgd;
    
        ofxDatGui* gui;
        ofxDatGuiTextInput*  i1;
        ofxDatGuiSlider* s1;
        ofxDatGuiSlider* s2;
        ofxDatGuiSlider* s3;
        ofxDatGuiSlider* s4;
        ofxDatGuiButton* b1;
        ofxDatGuiButton* t1;
        void onGuiEvent(ofxDatGuiEvent k);
    
};


