##ofxDatGui

**ofxDatGui** is a simple to use, lightweight graphical user interface for [openFrameworks](http://openframeworks.cc/) modeled after the popular JavaScript  [datgui](workshop.chromeexperiments.com/examples/gui/) interface.  

It also automatically renders at high resolution for retina displays o_O!

![ofxDatGui](./img/ofxdatgui_01.png?raw=true)

---

There are two ways to construct an **ofxDatGui** object.  

You can either pass in the X and Y coordinates where you would like it to live or use one of the convenient pre-defined anchors.

	ofxDatGui* gui = new ofxDatGui( 100, 100 );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

Adding components to **ofxDatGui** is as simple as:

	gui->addButton("Click!");
	
This generates a Basic Button with the label "Click!"

---

## Components
 
**ofxDatGui** currently provides the following components:
  
**Basic Button**
	 	
	gui->addButton(string label);
	
**Toggle Button**

	gui->addToggle(string label, bool enabled = false);

**Text Input**
 
 	gui->addInput(string label, string value = "");

**Range Slider**

	gui->addSlider(string label, float min, float max);
	
Optionally you can set the starting value of the slider.  
If this is not set it will default to halfway between the min and max values.

	gui->addSlider(string label, float min, float max, float value);
	
**Dropdown Menu**
	
	vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
	gui->addDropdown(options);
	
---
	
## Manipulation

Every ``gui->add*`` method returns a pointer to an **ofxDatGuiItem** object that you can store in a variable for later manipulation.

	ofxDatGuiInput* myInput;
 	myInput = gui->addInput("Name:", "Stephen");
 	myInput->setText("Freddy");

You can also manipulate items directly on **ofxDatGui** itself. 

	gui->getItemAt(itemIndex)->setText("Hello World");	
Every **ofxDatGuiItem** has a mutable label that can easily be changed via:

	item->setLabel(string label);
	(string) item->getLabel();
	
In addition every component has methods (typically getters & setters) that allow for the retrieval and manipulation of its unique properties.
	
**Toggle Button**

	ofxDatGuiToggle* myToggle;
	myToggle->toggle();
	(int) myToggle->getValue(); // returns the toggle state 0 or 1 // 

**Text Input**
 
	ofxDatGuiInput* myInput;
	myInput->setText(string text);
	(string) myInput->getText();

**Slider**

	ofxDatGuiSlider* mySlider;
	mySlider->setScale(float scale); // a value between 0 & 1 //
	(float) mySlider->getScale(); 	 // a value between 0 & 1 //
	mySlider->setValue(float value); // a value between min & max //
	(int) mySlider->getValue();		 // a value between min & max //
	
**Dropdown**
	
	ofxDatGuiDropdown* myDropdown;
	myDropdown->select(int childIndex);
	// retrieve the index of the selected child //
	(int) myDropdown->getSelectedIndex(); 
	
**Note:** All indicies are zero based so the first item in your  **ofxDatGui** instance will have an index of 0, the second item will have an index of 1, the third item and index of 2 etc..
	
---	
	
## Events

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
       (int) event.value // the new value of the slider //
       (float) event.scale // the position % of the slider (0 - 1) //

**OPTION_SELECTED**

		(int) event.index // the index of the dropdown in the gui //
		(int) event.child // the index of the option in the dropdown // 
	
---
		
##ofxDatGui Methods

In addition to the component add* methods **ofxDatGui** currently provides two additional instance methods:

		gui->setOpacity(float opacity); // between 0 & 1 //
		gui->onGuiEvent(this, &ofApp::onGuiEventCallback);
 
**Note: ofxDatGui** internally updates and draws itself on top of your application so there is no need to call ``draw()`` or ``update()`` on it.
 
You can also show & hide **ofxDatGui** by pressing the 'h' key.

---

##Planned Features

	* folders/groups
	* color pickers
	* save/load settings

---

##Additonal Notes

As this is a new project that is actively being developed, feature requests, concerns and suggestions are all very welcome.