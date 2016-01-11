#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1600, 800);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);
    
/*
    setup three ofParameters
*/

    p1.set("position X", 75, 0, 120);
    p2.set("position Y", 200.0f, -40.0f, 240.0f);
    p3.set("position Z", -40, -80, 120);
    
/*
    build a gui of sliders from three ofParameters
*/
    gui = new ofxDatGui();
    gui->addLabel("gui from of_parameters");
    gui->addSlider(p1);
    gui->addSlider(p2);
    gui->addSlider(p3);
    gui->setPosition(ofGetWidth()/2 - gui->getWidth() - 20, 100);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
 
/*
    create three sliders that use the same ofParameters as the gui
*/
    int x = gui->getPosition().x + gui->getWidth() + 40;
    l1 = new ofxDatGuiLabel("sliders from of_parameters");
    l1->setPosition(x, gui->getPosition().y);

    s1 = new ofxDatGuiSlider(p1);
    s1->setPosition(x, l1->getY() + l1->getHeight() + 2);

    s2 = new ofxDatGuiSlider(p2);
    s2->setPosition(x, s1->getY() + s1->getHeight() + 2);

    s3 = new ofxDatGuiSlider(p3);
    s3->setPosition(x, s2->getY() + s2->getHeight() + 2);

    s1->onSliderEvent(this, &ofApp::onSliderEvent);
    s2->onSliderEvent(this, &ofApp::onSliderEvent);
    s3->onSliderEvent(this, &ofApp::onSliderEvent);
}

void ofApp::update()
{
    s1->update();
    s2->update();
    s3->update();
}

void ofApp::draw()
{
    l1->draw();
    s1->draw();
    s2->draw();
    s3->draw();
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << e.target->getName() << " : " << e.value << endl;
}

