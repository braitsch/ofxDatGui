#include "ofApp.h"

/*
    Save all gui components values
    https://github.com/avilleret/ofxDatGui @avilleret

    Parameter and folder on the same level should have unique name.
*/

void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);

    // instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

    circles.resize(2);

// randomize circle parameters
    for (auto c : circles){
        c.x = ofRandomWidth();
        c.y = ofRandomHeight();
        c.radius = ofRandom(150);
    }

// add some components //
    gui->addTextInput("message", "# open frameworks #");

    gui->addFRM();
    //gui->addBreak();

// add a folder to group a few components together //
    ofxDatGuiFolder* folder = gui->addFolder("control ball 0", ofColor::white);
    folder->addTextInput("0/name", "Ball/0");

    ofxDatGuiSlider* sx = folder->addSlider("0/posision X", 0, ofGetWidth());
    ofxDatGuiSlider* sy = folder->addSlider("0/position Y", 0, ofGetHeight());
    ofxDatGuiSlider* sz = folder->addSlider("0/size", 0, 100, 50);
    sx->bind(circles[0].x);
    sy->bind(circles[0].y);
    sz->bind(circles[0].radius);

    folder->addToggle("0/fill");
    folder->addColorPicker("0/color", ofColor::fromHex(0xFFD00B));
// let's have it open by default. note: call this only after you're done adding items //
    folder->expand();

    gui->addBreak();

// add a another folder to control second ball //
    folder = gui->addFolder("control ball 1", ofColor::white);
    folder->addTextInput("1/name", "Ball/1");

    sx = folder->addSlider("1/posision X", 0, ofGetWidth());
    sy = folder->addSlider("1/position Y", 0, ofGetHeight());
    sz = folder->addSlider("1/size", 0, 100, 50);
    sx->bind(circles[1].x);
    sy->bind(circles[1].y);
    sz->bind(circles[1].radius);

    folder->addToggle("1/fill");
    folder->addColorPicker("1/color", ofColor::fromHex(0xFFD00B));
// let's have it open by default. note: call this only after you're done adding items //
    folder->expand();

    gui->addBreak();

// and a slider to adjust the gui opacity //
    gui->addSlider("datgui opacity", 0, 100, 100);

// and a colorpicker //
    gui->addColorPicker("background color", ofColor::fromHex(0xeeeeee));

    gui->addBreak();

// add a dropdown menu //
    vector<string> opts = {"option - 1", "option - 2", "option - 3", "option - 4"};
    gui->addDropdown("select option", opts);

    gui->addBreak();

// add a 2d pad //
    gui->add2dPad("2d pad");

// a button matrix //
    gui->addMatrix("matrix", 21, true);

// adding the optional header allows you to drag the gui around //
    gui->addHeader(":: drag me to reposition ::");

// adding the optional footer allows you to collapse/expand the gui //
    gui->addFooter();

// once the gui has been assembled, register callbacks to listen for component specific events //
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onTextInputEvent(this, &ofApp::onTextInputEvent);
    gui->on2dPadEvent(this, &ofApp::on2dPadEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    gui->onMatrixEvent(this, &ofApp::onMatrixEvent);

    gui->setOpacity(gui->getSlider("datgui opacity")->getScale());
//  gui->setLabelAlignment(ofxDatGuiAlignment::CENTER);


// finally let's load up the stock themes, press spacebar to cycle through them //
    themes = {  new ofxDatGuiTheme(true),
                new ofxDatGuiThemeSmoke(),
                new ofxDatGuiThemeWireframe(),
                new ofxDatGuiThemeMidnight(),
                new ofxDatGuiThemeAqua(),
                new ofxDatGuiThemeCharcoal(),
                new ofxDatGuiThemeAutumn(),
                new ofxDatGuiThemeCandy()};
    tIndex = 0;

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getLabel() << endl;
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if ( e.target->is("0/fill") ) circles[0].filled = e.checked;
    else if ( e.target->is("1/fill") ) circles[1].filled = e.checked;
    cout << "onToggleEvent: " << e.target->getLabel() << " " << e.checked << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << "onSliderEvent: " << e.target->getLabel() << " "; e.target->printValue();
    if (e.target->is("datgui opacity")) gui->setOpacity(e.scale);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    if ( e.target->is("0/name") ) circles[0].name = e.target->getText();
    else if ( e.target->is("1/name") ) circles[1].name = e.target->getText();

    cout << "onTextInputEvent: " << e.target->getLabel() << " " << e.target->getText() << endl;
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    cout << "on2dPadEvent: " << e.target->getLabel() << " " << e.x << ":" << e.y << endl;
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.target->getLabel() << " Selected" << endl;
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    if ( e.target->is("0/color") ){
       circles[0].color = e.target->getColor();
    } else if ( e.target->is("1/color") ){
       circles[1].color = e.target->getColor();
    } else {
        ofSetBackgroundColor(e.color);
    }
    cout << "onColorPickerEvent: " << e.target->getLabel() << " " << e.target->getColor() << endl;
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    // cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
    // cout << "onMatrixEvent " << e.target->getLabel() << " : " << e.target->getSelected().size() << endl;
}

void ofApp::draw() {
    for (auto c : circles)
        c.draw();
}
void ofApp::update() { }

void ofApp::keyPressed(int key)
{
    if (key == ' ' && ofGetKeyPressed(OF_KEY_CONTROL)){
        tIndex = tIndex < themes.size()-1 ? tIndex+1 : 0;
        gui->setTheme(themes[tIndex]);
    } else if (key == 's' && ofGetKeyPressed(OF_KEY_CONTROL)) { // save settings
        settings.save("settings.xml", gui);
    } else if (key == 'l' && ofGetKeyPressed(OF_KEY_CONTROL)) { // load settings
        settings.load("settings.xml", gui);
    }
}
