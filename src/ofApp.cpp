#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowPosition(100, 100);
    gui = new ofxDatGui( ofxDatGuiAnchor::TR, true );
    gui->addSlider("WAVY X", 10, 20, 5);
    gui->addSlider("WAVY Y", -20, 60);
    gui->addSlider("WAVY Z", 0, 100, 75);
    vector<string> options = {"OPTION - 1", "OPTION - 2", "OPTION - 3", "OPTION - 4"};
    gui->addDropdown(options);
    gui->addButton("CLICK");
    gui->addToggle("TOGGLE", true);
    gui->onGuiEvent(this, &ofApp::onGuiEvent);
}

void ofApp::onGuiEvent(ofxDatGuiEvent e)
{
    if (e.type == ofxDatGuiEventType::BUTTON_RELEASED){
        cout << "onGuiEvent::BUTTON_RELEASED " << e.target << endl;
    }   else if (e.type == ofxDatGuiEventType::SLIDER_CHANGED){
        cout << "onGuiEvent::SLIDER_CHANGED " << e.target << " :: " << e.value << endl;
    }   else if (e.type == ofxDatGuiEventType::OPTION_SELECTED){
        cout << "onGuiEvent::OPTION_SELECTED " << e.target << " :: " << e.child << endl;
    }   else if (e.type == ofxDatGuiEventType::BUTTON_TOGGLED){
        cout << "onGuiEvent::BUTTON_TOGGLED " << e.target << " :: " << e.value << endl;
    }
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
