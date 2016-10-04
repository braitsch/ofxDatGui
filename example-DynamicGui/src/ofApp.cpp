#include "ofApp.h"

/*
    Simple example to demonstrate how to add and remove element from gui or folder
    https://github.com/avilleret/ofxDatGui @avilleret
*/

void ofApp::setup()
{
    gui = new ofxDatGui();
    gui->addHeader("gui");

    guiFolder = new ofxDatGui();
    guiFolder->addHeader("gui with folder");
    guiFolder->addButton("add a button");
    guiFolder->addButton("remove a button");
    // here we store the folder pointer to re-use it later to add some component
    folder = guiFolder->addFolder("folder");
    // setup event callback
    guiFolder->onButtonEvent(this, &ofApp::onButtonEventFolder);

// instantiate a basic button and a toggle button //
    add = new ofxDatGuiButton("add a button");
    remove = new ofxDatGuiButton("remove a button");

// position the components in the middle of the screen //
    positionButtons();

// and register to listen for events //
    add->onButtonEvent(this, &ofApp::onButtonEvent);
    remove->onButtonEvent(this, &ofApp::onButtonEvent);

    folder->expand();
}

void ofApp::update()
{
    add->update();
    remove->update();
}

void ofApp::draw()
{
    add->draw();
    remove->draw();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
// we have a couple ways to figure out which button was clicked //

// we can compare our button pointer to the target of the event //
    if (e.target == add){
      gui->addButton("button " + to_string(gui->getItems().size()));
    } else if ( e.target == remove ){
        string label =  "button " + to_string(gui->getItems().size() - 1);
        gui->removeComponent(ofxDatGuiType::BUTTON, label);
    }
}


void ofApp::onButtonEventFolder(ofxDatGuiButtonEvent e)
{

  // or we can check against the name of the event target //
    if (e.target->is("add a button") ){
      folder->addButton("button " + to_string(folder->children.size()));
      // folder->expand();
    } else if ( e.target->is("remove a button") ){
        string label =  "button " + to_string(folder->children.size() - 1);
        folder->removeComponent(ofxDatGuiType::BUTTON, label);
    }
}

void ofApp::positionButtons()
{
    add->setPosition(ofGetWidth()/2 - add->getWidth()/2, ofGetHeight()/2 - add->getHeight());
    remove->setPosition(add->getX(), add->getY() + add->getHeight() + 20);
    gui->setPosition(ofGetWidth()/4-gui->getWidth()/2,ofGetHeight()/4);
    guiFolder->setPosition(3*ofGetWidth()/4-guiFolder->getWidth()/2,ofGetHeight()/4);
}



