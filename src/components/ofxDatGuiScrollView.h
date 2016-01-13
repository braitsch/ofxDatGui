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
#include "ofxDatGuiComponent.h"

class ofxDatGuiScrollView : public ofxDatGuiComponent {

    public:
    
        ofxDatGuiScrollView(int nVisible = 6) : ofxDatGuiComponent("")
        {
            mNumVisible = nVisible;
            setTheme(ofxDatGuiComponent::theme.get());
            ofAddListener(ofEvents().mouseScrolled, this, &ofxDatGuiScrollView::onMouseScrolled, OF_EVENT_ORDER_BEFORE_APP);
        }
    
    /*
        list manipulation
    */
    
        void add(string label)
        {
            int y = 0;
            if (children.size() > 0) y = children.back()->getY() + children.back()->getHeight() + mSpacing;
            children.push_back(new ofxDatGuiButton( label ));
            children.back()->setTheme(mTheme);
            children.back()->setWidth(mRect.width, 0);
            children.back()->setPosition(0, y);
            children.back()->setParentPosition(mRect.x, mRect.y);
            children.back()->onButtonEvent(this, &ofxDatGuiScrollView::onButtonEvent);
            cout << "ofxDatGuiScrollView :: total items = " << children.size() << endl;
            setHeight();
        }
    
        ofxDatGuiComponent* get(int index)
        {
        
        }
    
        ofxDatGuiComponent* get(string label)
        {
        
        }
    
        void move(ofxDatGuiComponent* item, int index)
        {
        
        }
    
        void remove(ofxDatGuiComponent* item)
        {
        
        }
    
        int getNumItems()
        {
            return children.size();
        }
    
    /*
        list presentation
    */

        void setTheme(ofxDatGuiTheme* theme)
        {
            mTheme = theme;
            mSpacing = theme->layout.vMargin;
            mBackground = theme->color.guiBackground;
            for (auto i:children) i->setTheme(theme);
            setWidth(theme->layout.width, theme->layout.labelWidth);
        }
    
        void setWidth(int width, float labelWidth = 1)
        {
            mRect.width = width;
            for (auto i:children) i->setWidth(mRect.width, labelWidth);
            setHeight();
        }

        void setPosition(int x, int y)
        {
            mRect.x = x;
            mRect.y = y;
            for(auto i:children) i->setParentPosition(x, y);
        }
    
        void setBackgroundColor(ofColor color)
        {
            mBackground = color;
        }
    
    /*
        update & draw
    */

        void update()
        {
            for(auto i:children) i->update();
        }
    
        void draw()
        {
        // draw a background behind the fbo //
            ofSetColor(ofColor::black);
            ofDrawRectangle(mRect);
        
        // draw into the fbo //
            mView.begin();
            ofClear(255,255,255,0);
            ofSetColor(mBackground);
            ofDrawRectangle(0, 0, mRect.width, mRect.height);
            for(auto i:children) i->draw();
            mView.end();

        // draw the fbo of list content //
            ofSetColor(ofColor::white);
            mView.draw(mRect.x, mRect.y);
        }


    private:
    
        ofFbo mView;
        ofRectangle mRect;
        ofColor mBackground;
        ofxDatGuiTheme* mTheme;
    
        int mSpacing;
        int mNumVisible;
    
        void setHeight()
        {
            mRect.height = ((mTheme->layout.height + mSpacing) * mNumVisible) - mSpacing;
            mView.allocate( mRect.width, mRect.height );
        }
    
        void onMouseScrolled(ofMouseEventArgs &e)
        {
            float sy = e.scrollY * 2;
            int topY = children.front()->getY();
            int btnH = children.front()->getHeight() + mSpacing;
            int minY = mRect.height + mSpacing  - (children.size() * btnH);
            bool allowScroll = false;
            if (sy < 0){
                if (topY > minY){
                    topY += sy;
                    if (topY < minY) topY = minY;
                    allowScroll = true;
                }
            }   else if (sy > 0){
                if (topY < 0){
                    topY += sy;
                    if (topY > 0) topY = 0;
                    allowScroll = true;
                }
            }
            if (allowScroll){
                children.front()->setPosition(0, topY);
                for(int i=0; i<children.size(); i++) children[i]->setPosition(0, topY + (btnH * i));
            }
        }
    
        void onButtonEvent(ofxDatGuiButtonEvent e)
        {
            cout << "ofxDatGuiScrollView :: " << e.target->getName() << " clicked" << endl;
        }

};
