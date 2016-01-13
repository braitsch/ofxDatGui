#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    width = 800;
    theme = new ofxDatGuiThemeMidnight();

    addItem = new ofxDatGuiButton("click to add item");
    addItem->setTheme(theme);
    addItem->setWidth(width);
    addItem->setPosition(ofGetWidth()/2 - addItem->getWidth()/2, 240);
    addItem->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    addItem->onButtonEvent(this, &ofApp::onAddNewItemButtonClick);
    
// create a scroll view that displays eight items at a time //
    view = new ofxDatGuiScrollView(8);
    view->setTheme(theme);
    view->setWidth(width);
    view->setPosition(addItem->getX(), addItem->getY() + addItem->getHeight() + 1);
}

void ofApp::update()
{
    view->update();
    addItem->update();
}

void ofApp::draw()
{
    view->draw();
    addItem->draw();
}

void ofApp::onAddNewItemButtonClick(ofxDatGuiButtonEvent e)
{
    view->add("item " + ofToString(view->getNumItems() + 1));
    addItem->setLabel("click to add item - " + ofToString(view->getNumItems()) + " items");
}


