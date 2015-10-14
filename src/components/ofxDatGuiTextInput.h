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
#include "ofxDatGuiComponent.h"
#include "ofxDatGuiTextInputField.h"

class ofxDatGuiTextInput : public ofxDatGuiComponent {

    public:
        ofxDatGuiTextInput(string label, string text = "", ofxDatGuiTemplate* tmplt=nullptr) : ofxDatGuiComponent(label, tmplt)
        {
            mType = ofxDatGuiType::OFXDATGUI_TEXT_INPUT;
            mStripeColor = mTemplate->textInput.color.stripe;
            input = new ofxDatGuiTextInputField(mRow.height-(mRow.padding*2), mTemplate);
            input->setText(text);
            input->setTextInactiveColor(mTemplate->textInput.color.text);
            input->onInternalEvent(this, &ofxDatGuiTextInput::onInputChanged);
            setWidth(mRow.width);
        }
    
        ~ofxDatGuiTextInput()
        {
            delete input;
        }
    
        static ofxDatGuiTextInput* getInstance()
        {
            return new ofxDatGuiTextInput("X");
        }
    
        string getText()
        {
            return input->getText();
        }
    
        void setText(string text)
        {
            return input->setText(text);
        }
    
        void setWidth(int w)
        {
            ofxDatGuiComponent::setWidth(w);
            input->setOrigin(x + mRow.inputX, y + mRow.padding);
            input->setWidth(mRow.width-mRow.padding-mRow.inputX);
        }
    
        void setTemplate(ofxDatGuiTemplate* tmplt)
        {
            ofxDatGuiComponent::setTemplate(tmplt);
            input->setTemplate(tmplt);
            input->setTextInactiveColor(mTemplate->textInput.color.text);
            setWidth(mRow.width);
        }
    
        void setOrigin(int x, int y)
        {
            ofxDatGuiComponent::setOrigin(x, y);
            input->setOrigin(x + mRow.inputX, y + mRow.padding);
        }
    
        void draw()
        {
            if (!mVisible) return;
            ofPushStyle();
                ofxDatGuiComponent::drawBkgd();
                ofxDatGuiComponent::drawLabel();
                ofxDatGuiComponent::drawStripe();
                input->draw();
            ofPopStyle();
        }
    
        bool hitTest(ofPoint m)
        {
            return input->hitTest(m);
        }

        void onFocus()
        {
            input->onFocus();
            ofxDatGuiComponent::onFocus();
        }
    
        void onFocusLost()
        {
            input->onFocusLost();
            ofxDatGuiComponent::onFocusLost();
        }
    
        void onMouseLeave(ofPoint m)
        {
        // override the base call to retain focus //
            mMouseOver = false;
        }
    
        void onKeyPressed(int key)
        {
            if (key != OF_KEY_LEFT &&
                key != OF_KEY_RIGHT &&
                key != OF_KEY_UP &&
                key != OF_KEY_DOWN)
            input->onKeyPressed(key);
        }
    
    protected:
    
        virtual void onInputChanged(ofxDatGuiInternalEvent e)
        {
        // dispatch event out to main application //
            if (textInputEventCallback != nullptr) {
                ofxDatGuiTextInputEvent ev(this, input->getText());
                textInputEventCallback(ev);
            }   else{
                ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
            }
        }
    
        ofxDatGuiTextInputField* input;
    
};

