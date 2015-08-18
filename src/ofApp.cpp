#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    gui = new ofxDatGui( ofxDatGuiPosition::TR );
    gui->addSlider("wavy x", .5);
    gui->addSlider("wavy y", .5);
    gui->addSlider("wavy z", .5);
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    cout << "onGuiEvent >> " << e.id << " :: "<<e.val << endl;
}

//--------------------------------------------------------------
void ofApp::update()
{
    gui->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    gui->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
