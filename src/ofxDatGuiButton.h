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
    
        void onMouseRelease(ofPoint m)
        {
        // dispatch event out to main application //
            ofxDatGuiEvent evt(ofxDatGuiEventType::BUTTON_RELEASED, mId);
            changeEventCallback(evt);
        }
    
        void draw()
        {
            drawBkgd();
            ofxDatGuiItem::drawLabel();
            ofxDatGuiItem::drawStripe(ofxDatGuiColor::BUTTON_STRIPE);
        }
    
        void drawBkgd()
        {
        // anything that extends ofxDatGuiButton has the same rollover effect //
            ofxDatGuiItem::drawBkgd(mMouseOver ? ofxDatGuiColor::BUTTON_OVER : ofxDatGuiColor::ROW_BKGD);
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=x && m.x<= x+rowWidth && m.y>=y && m.y<= y+rowHeight);
        }
    
    protected:
    
    
    private:

};