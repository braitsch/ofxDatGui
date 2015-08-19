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
    const ofColor slider_bkgd = ofColor::fromHex(0x303030);
    const ofColor slider_fill = ofColor::fromHex(0x2FA1D6);
};

namespace ofxDatGuiPosition{
    const uint8_t TL = 1;
    const uint8_t TR = 2;
}

class ofxDatGuiCore{

    public:
        static void init(int x, int y){
            guiPosition = ofPoint(x, y);
            font.load("verdana", 11, true, false, false, 0.3, 96);
        }
        static ofTrueTypeFont font;
        static ofPoint guiPosition;
        static uint16_t guiPadding;
        static uint16_t guiWidth;
        static uint16_t guiHeight;
    
};

class ofxDatGuiEvent{
    
    public:
        ofxDatGuiEvent(int itemId, float itemVal){
            id = itemId;
            val = itemVal;
        };
        int id;
        float val;
};

class ofxDatGuiItem
{
    public:
        ofxDatGuiItem(int id);
        virtual void draw();
        virtual bool hitTest(ofPoint m) = 0;
        virtual void onMousePress(ofPoint m) = 0;

    // this typedef is also used in ofxDatGui.h //
        typedef std::function<void(ofxDatGuiEvent)> onChangeEventCallback;
        onChangeEventCallback changeEventCallback;
        
        template<typename T, typename args, class ListenerClass>
        void onGuiEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            using namespace std::placeholders;
            changeEventCallback = std::bind(listenerMethod, owner, _1);
        }

        static const uint16_t rowWidth;
        static const uint16_t rowHeight;
        static const uint16_t rowPadding;
        static const uint16_t rowSpacing;

    protected:
        int x;
        int y;
        int mId;
        static const uint16_t labelX;
        static const uint16_t labelWidth;
        static const uint16_t sliderX;
        static const uint16_t sliderWidth;
        static const uint16_t sliderLabelX;
        static const uint16_t sliderLabelWidth;
    

};
