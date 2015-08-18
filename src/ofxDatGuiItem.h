//
//  ofxDatGuiItem.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#pragma once
#include "ofMain.h"

namespace ofxDatGuiColor{
    const ofColor item_bkgd = ofColor(26,26,26);
    const ofColor input_bkgd = ofColor::fromHex(0x303030);
    const ofColor input_fill = ofColor::fromHex(0x2FA1D6);
};

class ofxDatGuiCore{

    public:
        static void init(int x, int y){
            guiPosition = ofPoint(x, y);
            font.load("Effra_Std_Bd.ttf", 12);
        }
        static ofTrueTypeFont font;
        static ofPoint guiPosition;
};

class ofxDatGuiItem
{
    public:
        ofxDatGuiItem(int index);
        virtual void draw();
        bool hitTest(ofPoint m);
        virtual void onMousePress(ofPoint m) = 0;

        int x;
        int y;
        int index;

    protected:
        static const uint16_t itemWidth;
        static const uint16_t itemHeight;
        static const uint16_t itemPadding;
        static const uint16_t itemSpacing;
        static const uint16_t labelX;
        static const uint16_t labelWidth;
        static const uint16_t inputX;
        static const uint16_t inputWidth;

};
