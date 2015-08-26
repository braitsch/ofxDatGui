ofxDatGui
-----------------
**ofxDatGui** is a simple to use, lightweight graphical user interface for [openFrameworks](http://openframeworks.cc/) modeled after the highly popular JavaScript  [datgui](workshop.chromeexperiments.com/examples/gui/) interface.<br><br> It also automatically renders at high resolution for retina displays.

---

### HOW TO USE

There are two ways to construct an **ofxDatGui** object.<br><br>
You can either pass in the X and Y coordinates where you would like the gui to live or use one of the convenient pre-defined anchors.

	ofxDatGui* gui = new ofxDatGui( 100, 100 );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

Adding items to **ofxDatGui** is as simple as:

	gui->addButton("Click!");
	
This generates a simple button with the label ``"Click!"``

---

### Components
 
**ofxDatGui** currently provides the following components:
  
**Basic Button**
	 	
	gui->addButton(string label);
	
**Toggle Button**

	gui->addToggle(string label, bool enabled = false);

**Text Input**
 
 	gui->addInput(string label, string value = "");

**Slider**

	gui->addSlider(string label, float min, float max);
	
Optionally you can set the starting value of the slider.<br>
If this is not set the slider will default to halfway between the min and max values.

	gui->addSlider(string label, float min, float max, float default_val);
	
**Dropdown Menu**
	
	vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
	gui->addDropdown(vector<string> options);
	
---
	
### Manipulation

Every ``gui->add*()`` method returns a pointer to an **ofxDatGuiItem** object that you can store in a variable for later manipulation.

	ofxDatGuiInput* myInput;
 	myInput = gui->addInput(string label, string value = "");
 	myInput->setText("Hello World");

You can also manipulate items directly on **ofxDatGui** itself. 

	gui->getItemAt(int itemIndex)->setText("Hello World");	
Below are the methods avaiable to each object:
	
**Basic Button**
	
	ofxDatGuiButton* myButton;
	// ofxDatGuiButton does not provide any instance methods //
	
**Toggle Button**

	ofxDatGuiButton* myButton;
	myButton->toggle();

**Text Input**
 
	ofxDatGuiButton* myInput;
	myInput->setText(string text);

**Slider**

	ofxDatGuiSlider* mySlider;
	mySlider->setScale(float scale);	// a value between 0 & 1 //
	mySlider->setValue(float value);	// a value between min & max //
	
**Dropdown**
	
	ofxDatGuiDropdown* myDropdown;
	myDropdown->select(int childIndex);
	
**Note:** All indicies are zero based so the first item in your  **ofxDatGui** instance will have an index of 0 and the second item will have an index of 1 etcetera.
	
---	
	
### Events

Every component dispatches a unique event when it is interacted with.
The simplest way to listen for these events is to register a single callback with your **ofxDatGui** instance.


	    gui->onGuiEvent(this, &ofApp::onGuiEvent);
	    void onGuiEvent(ofxDatGuiEvent e)
	    {
		    if (e.type == ofxDatGuiEventType::BUTTON_CLICKED){
	        cout << "item# " << e.index << " was clicked!" << endl;
	    }

As you might expect each event carries a unique payload that describes what happened.

**BUTTON_CLICKED**

       (int) event.index // the index of the button in the gui //
         
**BUTTON_TOGGLED**
       
       (int) event.index // the index of the button in the gui //
       (bool) event.enabled // whether the button is on or off //

**INPUT_CHANGED**
        
       (int) event.index // the index of the input in the gui //
       (string) event.text // the new text value of the input field //

**SLIDER_CHANGED**

       (int) event.index // the index of the slider in the gui //
       (float) event.value // the new numerical value of the slider //

**OPTION_SELECTED**

		(int) event.index // the index of the dropdown in the gui //
		(int) event.child // the index of the option in the dropdown // 
	
---
		
###ofxDatGui Methods

In addition to the various add* methods **ofxDatGui** currently provides two additional instance methods:

		gui->setOpacity(float opacity); // between 0 & 1 //
		gui->onGuiEvent(this, &ofApp::onGuiEventCallback);
 
**Note: ofxDatGui** internally updates and draws itself on top of your application so there is no need to call ``draw()`` or ``update()`` on it.
 
To show & hide **ofxDatGui** press the 'h' key.

---

###Planned Features

	* folders/groups
	* color pickers
	* save/load settings

---

###Additonal Notes

Feature requests, concerns and suggestions are all very welcome.<br>
Please use Github Issues so that others can participate rather than emailing me directly. Thanks!