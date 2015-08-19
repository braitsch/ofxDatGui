#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    gui = new ofxDatGui( ofxDatGuiAnchor::TR );
    gui->addSlider("WAVY X", 10, 20, 5);
    gui->addSlider("WAVY Y", -20, 60);
    gui->addSlider("WAVY Z", 0, 100, 75);
    gui->addButton("CLICK");
    vector<string> options = {"one", "two", "three", "four"};
    gui->addDropdown(options);
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
