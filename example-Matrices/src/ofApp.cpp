#include "ofApp.h"

/*
    Simple example to demonstrate the Matrix Component
    https://github.com/braitsch/ofxDatGui @braitsch
*/

void ofApp::setup()
{
// setup a resolution for a grid //
    numCols = 3;
    numRows = 7;
    ofSetWindowPosition(0, 0);
    font.load("ofxbraitsch/fonts/Verdana.ttf", 24);
    
// instantiate a matrix with a button for each box in our grid //
    matrix = new ofxDatGuiMatrix("MATRIX", numCols*numRows, true);
    
// matrices can also function as radio buttons (only 1 on at a time)
    matrix->setRadioMode(true);
    
// reduce the component opacity so it's easier to see behind it //
    matrix->setOpacity(.75);
    
// and optionally register to listen for events //
    matrix->onMatrixEvent(this, &ofApp::onMatrixEvent);
}

void ofApp::update()
{
    matrix->update();
    matrix->setPosition(ofGetWidth()/2 - matrix->getWidth()/2, ofGetHeight()/2 - matrix->getHeight()/2);
}

void ofApp::draw()
{
    float w = ofGetWidth()/numCols;
    float h = ofGetHeight()/numRows;

    for (int i=0; i<numRows*numCols; i++) {
        float x = w * (i%numCols);
        float y = h * (floor(i/numCols));
    // fill the box if the corresponding button in the matrix is selected //
        if (matrix->getButtonAtIndex(i)->getSelected() == true) {
            ofFill();
            ofSetColor(ofColor::fromHex(0xEEEEEE));
            ofDrawRectangle(x, y, w, h);
        }
    // draw wireframe /
        ofNoFill();
        ofSetColor(ofColor::fromHex(0x303030));
        ofDrawRectangle(x, y, w, h);
    // draw box number //
        ofRectangle bounds = font.getStringBoundingBox(ofToString(i+1), 0, 0);
        font.drawString(ofToString(i+1), x+w/2-bounds.width/2, y+h/2+bounds.height/2);
    }
    matrix->draw();
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
// remember all indices are zero based //
    cout << "onMatrixEvent : " << e.child << " was clicked" << endl;
}



