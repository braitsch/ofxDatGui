#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    width = 540;
    theme = new ofxDatGuiThemeMidnight();

// create a button to attach items to the scroll view //
    addItem = new ofxDatGuiButton("click to add item");
    addItem->setStripeVisible(false);
    addItem->setWidth(width);
    addItem->setPosition(ofGetWidth()/2 - addItem->getWidth()/2, 240);
    addItem->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    addItem->onButtonEvent(this, &ofApp::onAddNewItemButtonClick);
    
// create a scroll view that displays eight items at a time //
    view = new ofxDatGuiScrollView("ScrollView #1", 8);
    view->setWidth(width);
    view->setPosition(addItem->getX(), addItem->getY() + addItem->getHeight() + 1);
    view->onScrollViewEvent(this, &ofApp::onScrollViewEvent);
    
// add a button to allow us to clear the scroll view out //
    clearAll = new ofxDatGuiButton("click to clear all items");
    clearAll->setStripeVisible(false);
    clearAll->setWidth(width);
    clearAll->setPosition(ofGetWidth()/2 - clearAll->getWidth()/2, view->getY() + view->getHeight() + 1);
    clearAll->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clearAll->onButtonEvent(this, &ofApp::onClearAllButtonClick);
    
// add a few items for testing //
    for(int i=0; i<12; i++) view->add("item " + ofToString(view->getNumItems() + 1));
    addItem->setLabel("click to add item - " + ofToString(view->getNumItems()) + " items");
}

void ofApp::update()
{
    view->update();
    addItem->update();
    clearAll->update();
}

void ofApp::draw()
{
    view->draw();
    addItem->draw();
    clearAll->draw();
}

void ofApp::onScrollViewEvent(ofxDatGuiScrollViewEvent e)
{
    cout << e.target->getLabel() << " [index " << e.index << "] selected in [" << e.parent->getName() << "]" << endl;
}

void ofApp::onAddNewItemButtonClick(ofxDatGuiButtonEvent e)
{
    view->add("item " + ofToString(view->getNumItems() + 1));
    addItem->setLabel("click to add item - " + ofToString(view->getNumItems()) + " items");
}

void ofApp::onClearAllButtonClick(ofxDatGuiButtonEvent e)
{
    view->clear();
    addItem->setLabel("click to add item");
}


