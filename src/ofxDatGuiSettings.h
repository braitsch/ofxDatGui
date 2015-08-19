//
//  ofxDatGuiProps.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/19/15.
//
//

#pragma once
#include "ofMain.h"

namespace ofxDatGuiColor{
    const ofColor GUI_BKGD    = ofColor::fromHex(0x303030);
    const ofColor ROW_BKGD    = ofColor::fromHex(0x1A1A1A);
    const ofColor LABEL       = ofColor::fromHex(0xEEEEEE);
    const ofColor INPUT       = ofColor::fromHex(0x303030);
    const ofColor SLIDER      = ofColor::fromHex(0x2FA1D6);
    const ofColor BUTTON_OVER = ofColor::fromHex(0x222222);
}

namespace ofxDatGuiAnchor{
    const uint8_t TL = 1;
    const uint8_t TR = 2;
}

namespace ofxDatGuiPosition
{
    extern int x;
    extern int y;
}

static uint16_t         ofxDatGuiWidth = 270;
static uint16_t         ofxDatGuiHeight = 0;
static uint16_t         ofxDatGuiPadding = 0;

class ofxDatGuiEvent{
    
    public:
        ofxDatGuiEvent(int itemId, float itemVal){
            id = itemId;
            val = itemVal;
        };
        int id;
        float val;
};