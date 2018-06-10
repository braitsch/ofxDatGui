/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once

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
        glm::tvec3<float, glm::precision::packed_highp>* head;
        static int MinLength;
        static int MaxLength;

    	void addVertex(int x, int y)
        {
            ofPolyline::addVertex(ofPoint(x, y));
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

