ofxDatGui
-----------------
A gui for [openFrameworks](http://openframeworks.cc/) modeled after [datgui](workshop.chromeexperiments.com/examples/gui/).

#### CONSTRUCTOR
-----------------

	ofxDatGui* gui = new ofxDatGui( 100, 100 );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TR );


------------------------------------------------------------------------------

#### COMPONENTS
 
 	ofxDatGuiInput* addInput(string label, string value = "");
	ofxDatGuiButton* addButton(string label);
	ofxDatGuiToggle* addToggle(string label, bool active = false);
	ofxDatGuiSlider* addSlider(string label, float min, float max);
	ofxDatGuiSlider* addSlider(string label, float min, float max, float val);
	ofxDatGuiDropdown* addDropdown(vector<string> options);