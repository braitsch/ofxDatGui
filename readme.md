##ofxDatGui

**ofxDatGui** is a **simple to use**, lightweight, high-resolution graphical user interface for [openFrameworks](http://openframeworks.cc/) inspired by the popular JavaScript  [datgui](http://workshop.chromeexperiments.com/examples/gui/) interface.  

![ofxDatGui](./img/ofxdatgui_02.png?raw=true)


##Features

**ofxDatGui** offers the following features & components:

* Click & Toggle (On/Off) Buttons
* Text Input Fields
* Color Pickers
* Range Sliders
* Dropdown Menus
* Folders to group components together
* Optional header & footer that allows you to collapse and drag the Gui around

##Installation

**ofxDatGui** is built on top of C++11 and currently requires openFrameworks 0.9.0 or later which you can easily install by [cloning or downloading the repository on Github.](https://github.com/openframeworks/openFrameworks) 

* Once you've downloaded openFrameworks, clone or download this repository and unpack it into your openFrameworks/addons directory.

* Create a new project using the project generator and include **ofxDatGui** by selecting the ```addons``` button in the generator.

* Once your project has been created copy the ```ofxdatgui_assets``` directory in the root of this repository to your newly created project's bin/data directory.

* Now add **ofxDatGui** to your project by adding  ```#include "ofxDatGui.h"``` to the top of your ```ofApp.h``` file and you're ready to go!

##Setup

To create an **ofxDatGui** simply pass in the X and Y coordinates where you would like it to live or use one of the convenient pre-defined anchors.

	ofxDatGui* gui = new ofxDatGui( 100, 100 );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

Adding components to **ofxDatGui** is as simple as:

	gui->addButton("Click!");
	
This generates a Basic Button with the label "Click!"

![ofxDatGui](./img/ofxdatgui_click.png?raw=true)

## Components
 
**ofxDatGui** currently offers the following components:
  
**Text Input**
 
	gui->addTextInput(string label, string value = "");
	
![ofxDatGui](./img/ofxdatgui_input.png?raw=true)
  
**Basic Button**
	 	
	gui->addButton(string label);
	
![ofxDatGui](./img/ofxdatgui_click.png?raw=true)	
	
**Toggle Button**

	gui->addToggle(string label, bool enabled = false);


![ofxDatGui](./img/ofxdatgui_toggle.png?raw=true)

**Range Slider**

	gui->addSlider(string label, float min, float max);
	
Optionally you can set the starting value of the slider.  
If this is not set it will default to halfway between the min and max values.

	gui->addSlider(string label, float min, float max, float value);

![ofxDatGui](./img/ofxdatgui_slider.png?raw=true)
	
**Color Picker**	
	
	gui->addColorPicker(string label, ofColor color = ofColor::black);

![ofxDatGui](./img/ofxdatgui_color.png?raw=true)
	
**Dropdown Menu**
	
	vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
	gui->addDropdown(options);
	
![ofxDatGui](./img/ofxdatgui_dropdown.png?raw=true)

##Component Groups (Folders)

You can also group related components into folders. When constructing a folder pass in a label to name the folder and an optional color to help visually group its contents.

	ofxDatGuiFolder* folder = gui->addFolder(string label, ofColor color);
	folder->addButton("Nested Button");
	folder->addSlider("Nested Slider", 0, 100);
	folder->addTextInput("I am a Nested Text Input");
	folder->addColorPicker("I am a Nested Color Picker");

![ofxDatGui](./img/ofxdatgui_folder.png?raw=true)
	
## Manipulation

Every ``gui->add*`` method returns a pointer to an **ofxDatGuiItem** object that you can store in a variable for later manipulation.

	ofxDatGuiTextInput* myInput;
	myInput = gui->addTextInput("Name:", "Stephen");
	myInput->setText("Freddy");

You can also manipulate items directly on **ofxDatGui** itself. 

	gui->getItemAt(itemIndex)->setText("Hello World");	
Every **ofxDatGuiItem** has a mutable label that can easily be retrieved or changed via:

	item->getLabel();
	item->setLabel(string label);
	
In addition some components have methods (typically getters & setters) that allow for the retrieval and manipulation of its unique properties.
	
**Text Input**
 
	ofxDatGuiTextInput* myInput;
	myInput->getText();
	myInput->setText(string text);
	
**Toggle Button**

	ofxDatGuiToggle* myToggle;
	myToggle->toggle();
	myToggle->setEnabled(bool enable);
	myToggle->getEnabled(); // returns true or false

**Range Slider**

	ofxDatGuiSlider* mySlider;
	mySlider->getScale(); 
	mySlider->setScale(float scale); // a value between 0 & 1 //
	mySlider->getValue();
	mySlider->setValue(float value); // a value between min & max //

**Color Picker**
	
	ofxDatGuiColorPicker* myColorPicker;
	myColorPicker->getColor();
	myColorPicker->setColor(int hexValue);
	myColorPicker->setColor(int r, int g, int b);
	myColorPicker->setColor(ofColor color);
	
**Dropdown Menu**
	
	ofxDatGuiDropdown* myDropdown;
	myDropdown->select(childIndex);
	myDropdown->getSelectedChildIndex(); 
	
**Note:** All indicies are zero based so the first item in your  **ofxDatGui** instance will have an index of 0, the second item will have an index of 1, the third item an index of 2 etc..
	
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
        
	(int) event.index // the index of the text input in the gui //
	(string) event.text // the new text value of the text input field //

**SLIDER_CHANGED**

	(int) event.index // the index of the slider in the gui //
	(float) event.value // the new value of the slider //
	(float) event.scale // the position % of the slider (0 - 1) //

**OPTION_SELECTED**

	(int) event.index // the index of the dropdown in the gui //
	(int) event.child // the index of the option in the dropdown // 
	
---
		
##ofxDatGui Methods

In addition to the component add* methods **ofxDatGui** also provides a few extra instance methods:

	gui->addHeader(string label);
	gui->addFooter();
	gui->setOpacity(float opacity); // between 0 & 1 //
	gui->onGuiEvent(this, &ofApp::onGuiEventCallback);
 
**Note: ofxDatGui** internally updates and draws itself on top of your application so there is no need to call ``draw()`` or ``update()`` on it.
 
You can also show & hide **ofxDatGui** by pressing the 'h' key.

---

##Additonal Notes

Thanks for reading all this and checking the project out. 

I'm actively looking for people to help me beta test this and provide feedback to help shape the project's development. If you'd like to see a feature prioritized or have any general questions or feedback please send me a message or open an issue.

Thanks!