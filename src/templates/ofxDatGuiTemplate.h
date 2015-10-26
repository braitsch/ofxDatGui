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

class ofxDatGuiTemplate{

    public:
    
    /*
        This is the base class for all custom templates.
        The properites here can be overridden by any class that extends this class.
    */
    
        ~ofxDatGuiTemplate()
        {
            delete font.ttf;
        }
    
        void init()
        {
            font.ttf = new ofxDatGuiFont(font.file, font.size, font.highlightPadding, row.color.label, textInput.color.highlight);
        }
    
        struct {
            struct {
                ofColor bkgd = ofColor::fromHex(0x303030);
            } color;
        } gui;
    
        struct {
            float width = 320.0f;
            float height = 26.0f;
            float padding = 2.0f;
            float spacing = 1.0f;
            float stripeWidth = 2.0f;
            struct {
                float maxAreaWidth = 240.0f;
                bool forceUpperCase = true;
            } label;
            struct {
                ofColor bkgd = ofColor::fromHex(0x1A1A1A);
                ofColor label = ofColor::fromHex(0xEEEEEE);
                ofColor mouseOver = ofColor::fromHex(0x777777);
                ofColor mouseDown = ofColor::fromHex(0x222222);
                ofColor inputArea = ofColor::fromHex(0x303030);
            } color;
        } row;
    
        struct {
            int size = 6;
            int highlightPadding = 3;
            string file = "font-verdana.ttf";
            ofxDatGuiFont* ttf;
        } font;

        struct{
            struct{
                ofColor stripe = ofColor::fromHex(0xEEEEEE);
            } color;
        } label;
    
        struct{
            struct{
                ofColor stripe = ofColor::fromHex(0xFFD00B);
            } color;
        } button;
    
        struct{
            struct{
                ofColor stripe = ofColor::fromHex(0xFFD00B);
            } color;
        } toggle;
    
        struct{
            struct{
                ofColor fill = ofColor::fromHex(0x2FA1D6);
                ofColor text = ofColor::fromHex(0x2FA1D6);
                ofColor stripe = ofColor::fromHex(0x2FA1D6);
            } color;
        } slider;
    
        struct{
            struct{
                ofColor stripe = ofColor::fromHex(0xC63256);
            } color;
        } dropdown;
    
        struct{
            struct{
                ofColor stripe = ofColor::fromHex(0xFFD00B);
            } color;
        } colorPicker;
    
        struct {
            bool forceUpperCase = true;
            struct{
                ofColor stripe = ofColor::fromHex(0x1ED36F);
                ofColor text = ofColor::fromHex(0x00FF00);
                ofColor highlight = ofColor::fromHex(0x688EB5);
            } color;
        } textInput;
    
        struct {
            int height = 164;
            struct{
                ofColor stripe = ofColor::fromHex(0x9AF398);
                ofColor lines = ofColor::fromHex(0xEEEEEE);
                ofColor circle = ofColor::fromHex(0xEEEEEE);
            } color;
        } pad2d;
    
        struct {
            int height = 164;
            int buttonSize = 47;
            struct {
                ofColor stripe = ofColor::fromHex(0xB2770D);
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
            } color;
        } matrix;
    
        struct {
            int height = 140;
            int pointSize = 2;
            int lineWeight = 2;
            struct{
                ofColor stripe = ofColor::fromHex(0x9AF398);
                ofColor lines = ofColor::fromHex(0xEEEEEE);
            } color;
        } graph;

};
