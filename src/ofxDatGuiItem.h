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
    const ofColor label_color = ofColor::fromHex(0xEEEEEE);
    const ofColor slider_bkgd = ofColor::fromHex(0x303030);
    const ofColor slider_fill = ofColor::fromHex(0x2FA1D6);
    const ofColor button_over = ofColor::fromHex(0x222222);
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
        static uint16_t guiPadding;
        static uint16_t guiWidth;
        static uint16_t guiHeight;
        static ofPoint guiPosition;
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
        ofxDatGuiItem(int id, string label, bool centerLabel = false) : ofxDatGuiItem(id)
        {
            mLabel = label;
            ofRectangle labelRect = ofxDatGuiCore::font.getStringBoundingBox(label, 0, 0);
            labelPos = ofPoint(labelX, labelRect.height+ ((rowHeight-labelRect.height)/2));
        }
        
        virtual void draw() = 0;
        virtual bool hitTest(ofPoint m) = 0;
    
        virtual void onMouseEnter(ofPoint m);
        virtual void onMousePress(ofPoint m) = 0;
        virtual void onMouseDrag(ofPoint m);
        virtual void onMouseLeave(ofPoint m);
        virtual void onMouseRelease(ofPoint m);

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
        string mLabel;
        bool mMouseOver;
        ofPoint labelPos;
    
        void drawBkgd(ofColor bkgd_color = ofxDatGuiColor::item_bkgd);
        void drawLabel(ofColor label_color = ofxDatGuiColor::label_color);
    
        static const uint16_t labelX;
        static const uint16_t labelWidth;
        static const uint16_t sliderX;
        static const uint16_t sliderWidth;
        static const uint16_t sliderLabelX;
        static const uint16_t sliderLabelWidth;
    

};
