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

class ofxDatGuiGlobals{

    public:
        static int guiX;
        static int guiY;
        static int guiAlpha;
        static int guiWidth;
        static int rowHeight;
        static int rowPadding;
        static int rowSpacing;
        static int anchorPosition;
};

class ofxDatGuiInteractiveObject{

    public:

        typedef std::function<void(ofxDatGuiEvent)> onChangeEventCallback;
        onChangeEventCallback changeEventCallback;
        
        template<typename T, typename args, class ListenerClass>
        void onGuiEvent(T* owner, void (ListenerClass::*listenerMethod)(args))
        {
            using namespace std::placeholders;
            changeEventCallback = std::bind(listenerMethod, owner, _1);
        }

};

class ofxDatGuiFont{

    public:

        static int fontSize;
        static int labelX;
        static int labelHeight;
        static int highlightPadding;
        static bool retinaEnabled;

        static ofBitmapFont bFont;
        static ofTrueTypeFont tFont;

        static void load(string file);
        static void drawLabel(string text, int xpos, int ypos, bool center = false);
        static void drawText(string text, ofColor color, int xpos, int ypos, bool highlight = false);
        static ofRectangle getStringBoundingBox(string str, int x, int y);

};

class ofxDatGuiTextInputField : public ofxDatGuiInteractiveObject{

    public:
        ofxDatGuiTextInputField(int width)
        {
            mRect.width = width;
            mTextColor = ofxDatGuiColor::TEXT;
            mBkgdColor = ofxDatGuiColor::INPUT;
            mRect.height = ofxDatGuiGlobals::rowHeight - (ofxDatGuiGlobals::rowPadding*2);
            mTextChanged = false;
            mHighlightText = false;
        }
    
        void draw(int x, int y)
        {
            mRect.x = x;
            mRect.y = y;
            ofPushStyle();
                ofSetColor(mBkgdColor);
                ofDrawRectangle(mRect);
                ofxDatGuiFont::drawText(mText, mTextColor, x+mTextIndent, y+mRect.height/2, mHighlightText);
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            return mRect.inside(m);
        }
    
        void setText(string text)
        {
            mText = text;
        }
    
        void setTextIndent(int indent)
        {
            mTextIndent = indent;
        }
    
        void onFocus()
        {
            mHighlightText = true;
            mTextColor = ofxDatGuiColor::LABEL;
            mBkgdColor = ofxDatGuiColor::BUTTON_OVER;
        }
    
        void onFocusLost()
        {
            mHighlightText = false;
            mTextColor = ofxDatGuiColor::TEXT;
            mBkgdColor = ofxDatGuiColor::INPUT;
            if (mTextChanged){
                ofxDatGuiEvent e(ofxDatGuiEventType::INPUT_CHANGED, 0);
                e.text = mText;
                changeEventCallback(e);
            }
        }
    
        void onKeyPressed(int key)
        {
            if (mHighlightText) mText = "";
            if (key != OF_KEY_BACKSPACE){
                mText += key;
            }   else {
                if (mText.size() > 0) mText.resize(mText.size()-1);
            }
            mTextChanged = true;
            mHighlightText = false;
            mText = ofToUpper(mText);
        }
    
    private:
        string mText;
        ofRectangle mRect;
        int mTextIndent;
        bool mTextChanged;
        bool mHighlightText;
        ofColor mBkgdColor;
        ofColor mTextColor;
        ofColor mHighLightColor;
};

