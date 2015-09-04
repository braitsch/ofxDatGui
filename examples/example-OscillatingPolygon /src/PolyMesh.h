
#pragma once
#include "ofMain.h"

class PolyMesh {

    public:
    
        void setOrigin(float x, float y)
        {
            origin.x = x;
            origin.y = y;
        }
    
        void setRadius(int r)
        {
            mRadius = r;
            layout();
        }
    
        void setNumSides(int n)
        {
            mNumSides = n;
            layout();
        }
    
        void setMargin(int n)
        {
            mMargin = n;
            layout();
        }
    
        void setLineColor(ofColor c)
        {
            mLineColor = c;
        }
    
        void setLineWeight(int n)
        {
            mLineWeight = n;
        }
    
        void reset(int margin, int radius, int sides)
        {
            mRadius = radius;
            mMargin = margin;
            mNumSides = sides;
            mLineWeight = 2;
            layout();
        }
    
        void draw()
        {
            ofPushStyle();
                ofSetLineWidth(mLineWeight);
                for (int i=0; i<mNumSides; i++) {
                    ofSetColor(mLineColor);
                    iPolys[i].draw();
                    pLines[i].draw();
                    oPolys[i].draw();
                    ofDrawCircle(pLines[i][1], 3);
                }
            ofPopStyle();
        }
    
    private:
        int mMargin;
        float mRadius;
        float mNumSides;
        ofPoint origin;
        ofColor mLineColor;
        int mLineWeight;
        vector<ofPolyline> iPolys;
        vector<ofPolyline> oPolys;
        vector<ofPolyline> pLines;
    
        void layout()
        {
            pLines.clear();
            iPolys.clear();
            oPolys.clear();
            float ang = 360/mNumSides;
            float a1 = 0;
            float a2 = ang;
            for (int i=0; i<mNumSides; i++)
            {
        /*
            draw the central polygon
        */
                ofPolyline poly;
                ofPoint a = getPointOnCircle(origin, mRadius, a1);
                ofPoint b = getPointOnCircle(origin, mRadius, a2);
                poly.addVertex(origin);
                poly.addVertex(a);
                poly.addVertex(b);

        /*
            draw line from origin to window edge that bisects each triangle
        */
                ofPolyline line;
                line.addVertex(origin);
            // calculate a point(p) that connects the origin to the wall
                ofPoint p = getPointOnCircle(origin, mRadius, (a1+a2)/2);
                float dx = (p.x-origin.x)/mRadius;
                float dy = (p.y-origin.y)/mRadius;

            // top right //
                if (p.x>origin.x && p.y<origin.y){
                    while(p.y>mMargin && p.x<ofGetWidth()-mMargin){
                        p.x+=dx;
                        p.y+=dy;
                    }
            // bottom right //
                }   else if (p.x>origin.x && p.y>origin.y){
                    while(p.y<ofGetHeight()-mMargin && p.x<ofGetWidth()-mMargin){
                        p.x+=dx;
                        p.y+=dy;
                    }
            // bottom left //
                }   else if (p.x<origin.x && p.y>origin.y){
                    while(p.y<ofGetHeight()-mMargin && p.x>mMargin){
                        p.x+=dx;
                        p.y+=dy;
                    }
            // top left //
                }   else if (p.x<origin.x && p.y<origin.y){
                    while(p.y>mMargin && p.x>mMargin){
                        p.x+=dx;
                        p.y+=dy;
                    }
            // if aligned with origin //
                }   else if (p.x==origin.x){
                    if (p.y<origin.y){
                        while(p.y>mMargin) p.y+=dy;
                    }   else if (p.y>origin.y) {
                        while(p.y<ofGetHeight()-mMargin) p.y+=dy;
                    }
                }   else if (p.y==origin.y){
                    if (p.x<origin.x){
                        while(p.x>mMargin) p.x+=dx;
                    }   else if (p.x>origin.x) {
                        while(p.x<ofGetWidth()-mMargin) p.x+=dx;
                    }
                }
                line.addVertex(p);
                pLines.push_back(line);
                
                ofPolyline edge;
                edge.addVertex(a);
                edge.addVertex(b);
                edge.addVertex(p);
                edge.close();
                oPolys.push_back(edge);
                
            // increment angle as we go around the circle //
                a1 = a2;
                a2+=ang;
                poly.close();
                iPolys.push_back(poly);
            }
            
        }
    
        ofPoint getPointOnCircle(ofPoint origin, float radius, float angle)
        {
        //  return a point on a circle at (angle) with distance(radius) from origin
        //  e.g. if origin(0, 0) & radius(100) & angle(90),
        //  this will return (0, 100) :: 100 pixels straight down from origin
            float a = ofDegToRad(angle);
            float x = (radius*cos(a))+origin.x;
            float y = (radius*sin(a))+origin.y;
            return ofPoint(x, y);
        }

};

