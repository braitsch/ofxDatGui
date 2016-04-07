#include "ofApp.h"

/*
    Simple example to demonstrate the Range Slider Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
    
/*
    instantiate a slider using an ofParameter<int> instance
*/
    
    sliderInt = new ofxDatGuiSlider(ofParamInt.set("of_Paramater<int>", 120, 0, 300));
    sliderInt->setWidth(ofGetWidth(), .2); // make label area 20% of width //
    sliderInt->setPosition(0, ofGetHeight()*.50 - sliderInt->getHeight()/2 - 100);
    sliderInt->onSliderEvent(this, &ofApp::onSliderEvent);
    ofParamInt.addListener(this, &ofApp::onParamIntChanged);
   
/*
    instantiate a slider using an ofParameter<float> instance
*/

    sliderFloat = new ofxDatGuiSlider(ofParamFloat.set("of_Paramater<float>", 210.0f, 0.0f, 300.0f));
    sliderFloat->setPrecision(4, false);
    sliderFloat->setWidth(ofGetWidth(), .2); // make label area 20% of width //
    sliderFloat->setPosition(0, ofGetHeight()*.50 - sliderFloat->getHeight()/2);
    sliderFloat->onSliderEvent(this, &ofApp::onSliderEvent);
    ofParamFloat.addListener(this, &ofApp::onParamFloatChanged);
    
/*
    instantiate a slider with regular ol' floats or ints
*/
    
    slider = new ofxDatGuiSlider("BACKGROUND BRIGHTNESS", 0, 100, 20);
    slider->setWidth(ofGetWidth(), .2); // make label area 20% of width //
    slider->setPosition(0, ofGetHeight()*.50 - slider->getHeight()/2 + 100);
    slider->onSliderEvent(this, &ofApp::onSliderEvent);
    ofSetBackgroundColor(ofColor::white * slider->getScale());
}

void ofApp::onParamIntChanged(int & n)
{
    // cout << "onParamIntChanged "<< n << endl;
}

void ofApp::onParamFloatChanged(float & f)
{
    // cout << "onParamFloatChanged "<< f << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if(e.target == slider){
        ofSetBackgroundColor(ofColor::white*e.scale);
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == sliderInt){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == sliderFloat){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }
}

void ofApp::update()
{
    slider->update();
    sliderInt->update();
    sliderFloat->update();
}

void ofApp::draw()
{
    slider->draw();
    sliderInt->draw();
    sliderFloat->draw();
}

