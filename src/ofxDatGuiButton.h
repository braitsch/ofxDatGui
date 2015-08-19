//
//  ofxDatGuiButton.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/18/15.
//
//

#pragma once
#include "ofxDatGuiItem.h"

class ofxDatGuiButton : public ofxDatGuiItem {

    public:
    
        ofxDatGuiButton(int index, string label) : ofxDatGuiItem(index, label) { }
    
        void draw()
        {
            ofxDatGuiItem::drawBkgd(mMouseOver ? ofxDatGuiColor::button_over : ofxDatGuiColor::item_bkgd);
            ofxDatGuiItem::drawLabel();
        }
    
        void onMousePress(ofPoint m)
        {
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, 1);
            changeEventCallback(evt);
        }
    
        void onMouseRelease(ofPoint m)
        {
        // dispatch event out to main application //
            ofxDatGuiEvent evt(mId, 0);
            changeEventCallback(evt);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+rowWidth && m.y>=y && m.y<= y+rowHeight);
        }
    
    protected:
    
    
    private:

};