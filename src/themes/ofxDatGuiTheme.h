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
#include "ofxDatGuiFont.h"

class ofxDatGuiTheme{

    public:
    
    /*
        This is the base class for all custom themes.
        The properites here can be overridden by any class that extends this class.
    */
    
        ~ofxDatGuiTheme()
        {
            delete font.ttf;
        }
    
        void init()
        {
            font.ttf = new ofxDatGuiFont(font.file, font.size, layout.textInput.highlightPadding, color.label, color.textInput.highlight);
        }
    
    /*
        gui & component colors
    */
    
        struct {
        
        // global gui background color //
            ofColor guiBackground = ofColor::fromHex(0x303030);
        
        // general colors that are shared by all components //
            ofColor label = ofColor::fromHex(0xEEEEEE);
            ofColor icons = ofColor::fromHex(0xEEEEEE);
            ofColor background = ofColor::fromHex(0x1A1A1A);
            ofColor backgroundOnMouseOver = ofColor::fromHex(0x777777);
            ofColor backgroundOnMouseDown = ofColor::fromHex(0x222222);
            ofColor inputAreaBackground = ofColor::fromHex(0x303030);
            
        // component specific colors //
            struct {
                ofColor fill = ofColor::fromHex(0x2FA1D6);
                ofColor text = ofColor::fromHex(0x2FA1D6);
            } slider;
            
            struct {
                ofColor text = ofColor::fromHex(0x00FF00);
                ofColor highlight = ofColor::fromHex(0x688EB5);
            } textInput;
            
            struct {
                ofColor border = ofColor::fromHex(0xEEEEEE);
            } colorPicker;
            
            struct {
                ofColor line = ofColor::fromHex(0xEEEEEE);
                ofColor ball = ofColor::fromHex(0xEEEEEE);
            } pad2d;
            
            struct{
                ofColor lines = ofColor::fromHex(0xEEEEEE);
                ofColor fills = ofColor::fromHex(0xEEEEEE);
            } graph;
            
            struct {
                struct{
                    ofColor label = ofColor::fromHex(0x303030);
                    ofColor button = ofColor::fromHex(0xEEEEEE);
                } normal;
                struct{
                    ofColor label = ofColor::fromHex(0xEEEEEE);
                    ofColor button = ofColor::fromHex(0x2FA1D6);
                } hover;
                struct{
                    ofColor label = ofColor::fromHex(0xEEEEEE);
                    ofColor button = ofColor::fromHex(0x555555);
                } selected;
            } matrix;
            
        } color;
    
    /*
        colored stripes that appear on the left edge of the component
    */
    
        struct {
            int width = 2.0f;
            bool visible = true;
            ofColor label = ofColor::fromHex(0xEEEEEE);
            ofColor button = ofColor::fromHex(0xFFD00B);
            ofColor toggle = ofColor::fromHex(0xFFD00B);
            ofColor slider = ofColor::fromHex(0x2FA1D6);
            ofColor pad2d = ofColor::fromHex(0x9AF398);
            ofColor matrix = ofColor::fromHex(0xB2770D);
            ofColor graph = ofColor::fromHex(0x9AF398);
            ofColor dropdown = ofColor::fromHex(0xC63256);
            ofColor textInput = ofColor::fromHex(0x1ED36F);
            ofColor colorPicker = ofColor::fromHex(0xFFD00B);
        } stripe;
    
    /*
        layout, sizing and rendering rules
    */
    
        struct {
        
        // general rules that are shared by all components //
            float width = 320.0f;
            float height = 26.0f;
            float padding = 2.0f;
            float vMargin = 1.0f;
            
        // component specific rules & settings //
        
            struct {
                float maxWidth = 240.0f;
                bool forceUpperCase = true;
            } label;
        
            struct {
                int highlightPadding = 3;
                bool forceUpperCase = true;
            } textInput;
        
            struct {
                int height = 164;
            } pad2d;
        
            struct {
                int height = 140;
                int pointSize = 2;
                int lineWeight = 2;
            } graph;
        
            struct {
                int height = 164;
                int buttonSize = 47;
            } matrix;
            
        } layout;

    /*
        the typography settings for this theme
    */
    
        struct {
            int size = 6;
            string file = "font-verdana.ttf";
            ofxDatGuiFont* ttf;
        } font;


};

/*
    15" RETINA MACBOOK PRO
*/

class ofxDatGui2880x1800 : public ofxDatGuiTheme
{
    public:
        ofxDatGui2880x1800();
        static ofxDatGuiTheme* get();
    private:
        static unique_ptr<ofxDatGui2880x1800> tmplt;
};

/*
    15" NON-RETINA MACBOOK PRO
*/

class ofxDatGui1440x900 : public ofxDatGuiTheme
{
    public:
        ofxDatGui1440x900();
        static ofxDatGuiTheme* get();
    private:
        static unique_ptr<ofxDatGui1440x900> tmplt;
};



