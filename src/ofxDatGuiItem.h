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
    const ofColor gui_bkgd = ofColor::fromHex(0x303030);
    const ofColor item_bkgd = ofColor(26,26,26);
    const ofColor font_fill = ofColor::fromHex(0xEEEEEE);
    const ofColor input_bkgd = ofColor::fromHex(0x303030);
    const ofColor input_fill = ofColor::fromHex(0x2FA1D6);
};

namespace ofxDatGuiPosition{
    const uint8_t TL = 1;
    const uint8_t TR = 2;
}

class ofxDatGuiCore{

    public:
        static void init(int x, int y){
            guiPosition = ofPoint(x, y);
            font.load("Swiss 721 Medium", 11);
        }
        static ofTrueTypeFont font;
        static ofPoint guiPosition;
        static uint16_t guiPadding;
        static uint16_t guiWidth;
        static uint16_t guiHeight;
    
};

class ofxDatGuiItem
{
    public:
        ofxDatGuiItem(int index);
        virtual void draw();
        bool hitTest(ofPoint m);
        virtual void onMousePress(ofPoint m) = 0;

    // this typedef is also used in ofxDatGui.h //
        typedef std::function<void(float)> onChangeEventCallback;
        onChangeEventCallback changeEventCallback;
        
        template<typename T, typename args, class ListenerClass>
        void setCallback(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            using namespace std::placeholders;
            changeEventCallback = std::bind(listenerMethod, owner, _1);
        }
    
        int x;
        int y;

        static const uint16_t itemWidth;
        static const uint16_t itemHeight;
        static const uint16_t itemPadding;
        static const uint16_t itemSpacing;

    protected:
        int mIndex;
        static const uint16_t labelX;
        static const uint16_t labelWidth;
        static const uint16_t inputX;
        static const uint16_t inputWidth;

};
