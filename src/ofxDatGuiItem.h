//
//  ofxDatGuiItem.h
//  ofxDatGui
//
//  Created by Stephen Braitsch on 8/17/15.
//
//

#pragma once
#include "ofxDatGuiSettings.h"

class ofxDatGuiItem
{
    public:
    
        ofxDatGuiItem(int id);
        ofxDatGuiItem(int id, string label, bool centerLabel = false);
    
        vector<ofxDatGuiItem*> children;
    
        int getHeight();
        string getLabel();
        bool isExpanded();
        void setYPosition(int ypos);
        
        static void enableRetina(bool enable);
        static void init(ofVec2f position, bool enableRetina = false);
        static void init(uint8_t position, bool enableRetina = false);
    
        virtual void draw() = 0;
        virtual bool hitTest(ofPoint m) = 0;

        virtual void onFocus();    
        virtual void onFocusLost();
        virtual void onKeyPressed(int key);
        virtual void onMouseEnter(ofPoint m);
        virtual void onMousePress(ofPoint m);
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

        static uint16_t guiWidth;
        static uint16_t guiPadding;
        static uint16_t rowWidth;
        static uint16_t rowHeight;
        static uint16_t rowPadding;
        static uint16_t rowSpacing;

    protected:
    
        int x;
        int y;
        int mId;
        int originY;
        int mWidth;
        int mHeight;
        int mLabelX;
        int mLabelY;
        string mLabel;
        bool mMouseOver;
        bool mMouseDown;
        bool mIsExpanded;
        static vector<uint16_t> properties;
    
        void drawBkgd(ofColor color = ofxDatGuiColor::ROW_BKGD);
        void drawLabel(ofColor color = ofxDatGuiColor::LABEL);
        void drawStripe(ofColor color = ofxDatGuiColor::ROW_BKGD);
        void drawText(string text, ofColor color, int xpos);
    
        static uint16_t labelX;
        static uint16_t labelWidth;
        static uint16_t labelHeight;
        static uint16_t sliderX;
        static uint16_t sliderWidth;
        static uint16_t sliderLabelX;
        static uint16_t sliderLabelWidth;
        static uint16_t stripeWidth;
        static uint16_t dropdownIconX;
        static uint16_t dropdownIconY;

};

