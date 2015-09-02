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
    
        enum ofxDatGuiTextInputFieldType
        {
            NUMERIC = 1,
            ALPHA_NUMERIC,
            COLORPICKER
        };
    
        ofxDatGuiTextInputField(int width)
        {
            mRect.width = width;
            mTextColor = ofxDatGuiColor::TEXT;
            mBkgdColor = ofxDatGuiColor::INPUT;
            mRect.height = ofxDatGuiGlobals::rowHeight - (ofxDatGuiGlobals::rowPadding*2);
            mTextChanged = false;
            mHighlightText = false;
            mMaxCharacters = 99;
            mType = ALPHA_NUMERIC;
            mTextActiveColor = ofxDatGuiColor::LABEL;
            mTextInactiveColor = ofxDatGuiColor::TEXT;
        }
    
        void draw(int x, int y)
        {
            mRect.x = x;
            mRect.y = y;
            ofPushStyle();
                ofSetColor(mBkgdColor);
                ofDrawRectangle(mRect);
                mTextColor = mHighlightText ? mTextActiveColor : mTextInactiveColor;
                ofxDatGuiFont::drawText(mType==COLORPICKER ? "#"+mText : mText, mTextColor, x+mTextIndent, y+mRect.height/2, mHighlightText);
            ofPopStyle();
        }
    
        int getWidth()
        {
            return mRect.width;
        }
    
        int getHeight()
        {
            return mRect.height;
        }
    
        bool hitTest(ofPoint m)
        {
            return (m.x>=mRect.x && m.x<=mRect.x+mRect.width && m.y>=mRect.y && m.y<=mRect.y+mRect.height);
        }
    
        void setText(string text)
        {
            mText = text;
            mTextChanged = true;
        }
    
        void setTextIndent(int indent)
        {
            mTextIndent = indent;
        }
    
        void setTextActiveColor(ofColor color)
        {
            mTextActiveColor = color;
        }
    
        void setTextInactiveColor(ofColor color)
        {
            mTextInactiveColor = color;
        }
    
        void setTextInputFieldType(ofxDatGuiTextInputFieldType type)
        {
            mType = type;
        }
    
        void setBackgroundColor(ofColor color)
        {
            mBkgdColor = color;
        }
    
        void setMaxNumOfCharacters(int max)
        {
            mMaxCharacters = max;
        }
    
        virtual void onFocus()
        {
            mTextChanged = false;
            mHighlightText = true;
            if (mType != COLORPICKER) mBkgdColor = ofxDatGuiColor::BUTTON_OVER;
        }
    
        virtual void onFocusLost()
        {
            mHighlightText = false;
            if (mTextChanged){
                mTextChanged = false;
                ofxDatGuiEvent e(ofxDatGuiEventType::INPUT_CHANGED, 0);
                e.text = mText;
                changeEventCallback(e);
            }
            if (mType != COLORPICKER) mBkgdColor = ofxDatGuiColor::INPUT;
        }
    
        void onKeyPressed(int key)
        {
            if (!keyIsValid(key)) return;
            if (mHighlightText) mText = "";
            if (key!=OF_KEY_BACKSPACE){
                mText += key;
            }   else {
                if (mText.size() > 0) mText.resize(mText.size()-1);
            }
            mTextChanged = true;
            mHighlightText = false;
            mText = ofToUpper(mText);
        }
    
        bool keyIsValid(int key)
        {
            if (mType == COLORPICKER){
               if (key==OF_KEY_BACKSPACE){
                    return true;
            // limit string length to six hex characters //
                } else if (!mHighlightText && mText.size() == 6){
                    return false;
            // allows numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
            // allows letters a-f & A-F //
                }   else if ((key>=97 && key<=102) || (key>=65 && key<=70)){
                    return true;
                }   else{
                    return false;
                }
            }   else if (mType == NUMERIC){
                if (key==OF_KEY_BACKSPACE){
                    return true;
            // allow dash (-) or dot (.) //
                }   else if (key==45 || key==46){
                    return true;
            // allows numbers 0-9 //
                }   else if (key>=48 && key<=57){
                    return true;
            // an invalid key was entered //
                }   else{
                    return false;
                }
            }   else{
            // allow anything //
                return true;
            }
        }
    
    private:
        string mText;
        ofRectangle mRect;
        int mTextIndent;
        bool mTextChanged;
        bool mHighlightText;
        int mMaxCharacters;
        ofColor mBkgdColor;
        ofColor mTextColor;
        ofColor mHighLightColor;
        ofColor mTextActiveColor;
        ofColor mTextInactiveColor;
        ofxDatGuiTextInputFieldType mType;
};


