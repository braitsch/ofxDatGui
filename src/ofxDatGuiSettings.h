//
//  ofxDatGuiProps.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/19/15.
//
//

#pragma once
#include "ofMain.h"

namespace ofxDatGuiColor
{
    const ofColor GUI_BKGD          = ofColor::fromHex(0x303030);
    const ofColor ROW_BKGD          = ofColor::fromHex(0x1A1A1A);
    const ofColor LABEL             = ofColor::fromHex(0xEEEEEE);
    const ofColor INPUT             = ofColor::fromHex(0x303030);
    const ofColor SLIDER            = ofColor::fromHex(0x2FA1D6);
    const ofColor BUTTON_OVER       = ofColor::fromHex(0xFFD00B);
    const ofColor BUTTON_DOWN       = ofColor::fromHex(0x222222);
    
// stripe identifiers //
    const ofColor BUTTON_STRIPE     = ofColor::fromHex(0xE61D5F);
    const ofColor SLIDER_STRIPE     = ofColor::fromHex(0x2FA1D6);
    const ofColor DROPDOWN_STRIPE   = ofColor::fromHex(0x1ED36F);
}

namespace ofxDatGuiPosition
{
    extern int x;
    extern int y;
}

namespace ofxDatGuiAnchor
{
    enum ofxDatGuiAnchor{ TL = 0, TR = 1};
}

class ofxDatGuiEvent{
    
    public:
        ofxDatGuiEvent(int eType, int eTarget, float eValue = 0.0f){
            type = eType;
            target = eTarget;
            value = eValue;
            child = 0;
        };
        int type;
        int target;
        int child;
        float value;
};

namespace ofxDatGuiEventType
{
    enum ofxDatGuiEventType{
        BUTTON_PRESSED = 0,
        BUTTON_RELEASED,
        BUTTON_TOGGLED,
        SLIDER_CHANGED,
        OPTION_SELECTED,
        DROPDOWN_EXPANDED,
        DROPDOWN_COLLAPSED
    };
}

