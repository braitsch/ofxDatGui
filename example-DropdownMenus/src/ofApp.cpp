#include "ofApp.h"

/*
    Simple example to demonstrate the Dropdown Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
    ofSetWindowPosition(0, 0);

// create a vector of colors to populate our dropdown //
    colors.push_back(ofColor::fromHex(0xFFD00B));
    colors.push_back(ofColor::fromHex(0x2FA1D6));
    colors.push_back(ofColor::fromHex(0x1ED36F));
    colors.push_back(ofColor::fromHex(0xC63256));
    
// convert the hex values of those colors to strings for the menu labels //
    vector<string> options;
    for (int i=0; i<colors.size(); i++) options.push_back(getHex(colors[i].getHex()));

// instantiate the dropdown //
    menu = new ofxDatGuiDropdown("SELECT A COLOR", options);
    
// and position it in the middle of the screen //
    menu->setPosition(ofGetWidth()/2 - menu->getWidth()/2, ofGetHeight()/2 - menu->getHeight()/2 - 100);
    
// let's set the stripe of each option to its respective color //
    for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(colors[i]);

// register to listen for change events //
    menu->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
// finally let's have it open by default //
    menu->expand();
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    ofSetBackgroundColor(colors[e.child]);
    menu->setStripeColor(ofColor::white);
}

string ofApp::getHex(int hex)
{
// convert decimal value to hex //
    std::stringstream ss;
    ss<< std::hex << hex;
    std::string res ( ss.str() );
    while(res.size() < 6) res+="0";
    return "#"+ofToUpper(res);
}

void ofApp::update()
{
    menu->update();
}

void ofApp::draw()
{
    menu->draw();
}

