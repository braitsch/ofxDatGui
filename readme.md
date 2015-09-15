##ofxDatGui

**ofxDatGui** is a **simple to use**, lightweight, high-resolution graphical user interface for [openFrameworks](http://openframeworks.cc/) inspired by the popular JavaScript  [datgui](http://workshop.chromeexperiments.com/examples/gui/) interface.  

![ofxDatGui](./readme-img/ofxdatgui_03.png?raw=true)


##Features

**ofxDatGui** offers the following features & components:

* Click & Toggle (On/Off) Buttons
* Text Input Fields
* Color Pickers
* Range Sliders
* Dropdown Menus
* Button Matrices
* 2D Coordinate Pads
* Folders to group components together
* An optional header & footer that allow you to collapse and drag the Gui around

##Installation

**ofxDatGui** is built on top of C++11 and requires the new openFrameworks 0.9.0 pre-release which you can [download here](http://forum.openframeworks.cc/t/0-9-0-release-candidate-1/20434).

* Once you've downloaded [openFrameworks](http://forum.openframeworks.cc/t/0-9-0-release-candidate-1/20434), clone or download this repository into your openFrameworks/addons directory.

* Create a new project using the project generator and include **ofxDatGui** by selecting the ```addons``` button in the generator.

* Copy the ```ofxdatgui_assets``` directory in the root of this repository to your project's bin/data directory. This directory contains the fonts & icons used by **ofxDatGui**.

* Add **ofxDatGui** to your project by adding  ```#include "ofxDatGui.h"``` to the top of your ```ofApp.h``` file and you're ready to go!

##Getting Started

There are two ways to work with **ofxDatGui**. You can either instantiate each component on its own or consolidate them into a gui panel that you can drag around. The individual component examples included in this repository demonstrate how to use each on its own.


To create an **ofxDatGui** panel that groups components together simply pass in the X and Y coordinates where you would like it to live or use one of the convenient pre-defined anchors.

	ofxDatGui* gui = new ofxDatGui( 100, 100 );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
	ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );

Adding components to **ofxDatGui** is as simple as:

	gui->addButton("Click!");
	
This generates a Basic Button with the label "Click!"

![ofxDatGui](./readme-img/ofxdatgui_click.png?raw=true)

## Interactive Components
 
**ofxDatGui** currently offers the following components:
  
**Text Input**
 
	gui->addTextInput(string label, string value = "");
	
![ofxDatGui](./readme-img/ofxdatgui_input.png?raw=true)
  
**Basic Button**
	 	
	gui->addButton(string label);
	
![ofxDatGui](./readme-img/ofxdatgui_click.png?raw=true)	
	
**Toggle Button**

	gui->addToggle(string label, bool enabled = true);


![ofxDatGui](./readme-img/ofxdatgui_toggle.png?raw=true)

**Range Slider**

	gui->addSlider(string label, float min, float max);

![ofxDatGui](./readme-img/ofxdatgui_slider.png?raw=true)
	
You can also set the starting value of the slider.  
If this is not set it will default to halfway between the min and max values.

	gui->addSlider(string label, float min, float max, float value);
	
**Color Picker**	
	
	gui->addColorPicker(string label, ofColor color = ofColor::black);

![ofxDatGui](./readme-img/ofxdatgui_color.png?raw=true)
	
**Dropdown Menu**
	
	vector<string> options = {"ONE", "TWO", "THREE", "FOUR"};
	gui->addDropdown(options);
	
![ofxDatGui](./readme-img/ofxdatgui_dropdown.png?raw=true)

**Button Matrix**

	gui->addMatrix(string label, int numButtons)

![ofxDatGui](./readme-img/ofxdatgui_matrix.png?raw=true)

You can display numbered labels on the buttons by passing ``true`` as the third argument.

	gui->addMatrix(string label, int numButtons, bool showLabels)

![ofxDatGui](./readme-img/ofxdatgui_matrix_labels.png?raw=true)

**2D Coordinate Pad**

	gui->add2dPad(string label, ofRectangle bounds);

![ofxDatGui](./readme-img/ofxdatgui_2dpad.png?raw=true)

The bounds parameter is optional and will default to the window dimensions if omitted.

##Utility Components

**ofxDatGui** also provides a few non-interactive utility components to assist with layout and application health monitoring.

**Label**
  
 	gui->addLabel(string label);

![ofxDatGui](./readme-img/ofxdatgui_label.png?raw=true)

**FPS Monitor**
	
	gui->addFPS(float refreshFrequency = 1.0f);

![ofxDatGui](./readme-img/ofxdatgui_fps.gif?raw=true)

**Break**

	gui->addLabel("Above");
	gui->addBreak(float height = 10.0f);
	gui->addLabel("Stuck in the Middle");
	gui->addBreak(float height = 10.0f);
	gui->addLabel("Below");

![ofxDatGui](./readme-img/ofxdatgui_break.png?raw=true)
	
##Component Groups (Folders)

You can also group related components into folders. When constructing a folder pass in a label to name the folder and an optional color to help visually group its contents.

```cpp
ofxDatGuiFolder* folder = gui->addFolder("My White Folder", ofColor::white);
folder->addTextInput("** Input", "A Nested Text Input");
folder->addSlider("** Slider", 0, 100);
folder->addToggle("** Toggle", false);
```

![ofxDatGui](./readme-img/ofxdatgui_folder.png?raw=true)
	
You can also expand and collapse folders programmatically.

	folder->expand();
	folder->collapse();
	
## Manipulation

Every ``gui->add*`` method returns a pointer to an **ofxDatGuiItem** object that you can store in a variable for later manipulation.

	ofxDatGuiTextInput* myInput;
	myInput = gui->addTextInput("Name:", "Stephen");
	myInput->setText("Freddy");
	
Every **ofxDatGuiItem** has a mutable label that can easily be retrieved or changed via:

	item->getLabel();
	item->setLabel(string label);
	
In addition some components have methods (typically getters & setters) that allow for the retrieval and manipulation of its unique properties.
	
**Text Input**
 
```cpp
ofxDatGuiTextInput* myInput;
string myInput->getText();
myInput->setText(string text);
```	
**Toggle Button**

```cpp
ofxDatGuiToggle* myToggle;
myToggle->toggle();
myToggle->setEnabled(bool enable);
bool myToggle->getEnabled();
```
**Range Slider**

```cpp
ofxDatGuiSlider* mySlider;
float mySlider->getScale(); 
mySlider->setScale(float scale); // a value between 0 & 1 //
float mySlider->getValue();
mySlider->setValue(float value); // a value between min & max //
```

**Color Picker**
	
```cpp	
ofxDatGuiColorPicker* myColorPicker;
ofColor myColorPicker->getColor();
myColorPicker->setColor(int hexValue);
myColorPicker->setColor(int r, int g, int b);
myColorPicker->setColor(ofColor color);
```
	
**Dropdown Menu**

```cpp	
ofxDatGuiDropdown* myDropdown;
myDropdown->select(childIndex);
int myDropdown->getSelectedChildIndex();
myDropdown->expand();
myDropdown->collapse();
```
	
**ofxDatGuiMatrix**

```cpp	
ofxDatGuiMatrix* myMatrix;
vector<int> myMatrix->getSelected();
// returns a vector containing the indicies of the selected buttons //
```

**ofxDatGui2dPad**

```cpp	
ofxDatGui2dPad* my2dPad;
my2dPad->setBounds(ofRectangle bounds);
ofPoint my2dPad->getPosition();
// returns the current position within the bounds rectangle you gave it //
```	
	
**Note:** All indicies are zero based so the first item in your  **ofxDatGui** instance will have an index of 0, the second item will have an index of 1, the third item an index of 2 etc..
	
## Component Retrieval

If you're lazy and don't feel like storing your components in variables you can easily retrieve them by their non-case sensitive label.

	ofxDatGuiButton* gui->getButton("My Button"); // button label
	ofxDatGuiSlider* gui->getSlider("My Slider"); // slider label
	
If you have multiple components with the same label nested in separate folders you can specify the folder to search.

	ofxDatGuiButton* gui->getButton("Folder 1", "Reset Button");
	ofxDatGuiButton* gui->getButton("Folder 2", "Reset Button");
	
## Events

**ofxDatGuiEvents** are designed to be as easy as possible to interact with.

To listen for an event simply register a callback to be executed when an event you care about is fired:
	
	gui->onButtonEvent(this, &ofApp::onButtonEvent);
	void onButtonEvent(ofxDatGuiButtonEvent e)
	{
		cout << "A button was clicked!" << endl;
	}
    
Every callback you register will receive an event object that contains a pointer (called target) to the object that created the event. 

	gui->addButton("My Button");
	gui->onButtonEvent(this, &ofApp::onButtonEvent);
	void onButtonEvent(ofxDatGuiButtonEvent e)
	{
		cout << e.target->getLabel() << endl; // prints "My Button"
	}

If you saved the pointer returned by ``gui->add*`` in a variable you can compare it to the event target to decide how to handle the event. 

	ofxDatGuiButton* b1 = gui->addButton("Button 1");
	ofxDatGuiButton* b2 = gui->addButton("Button 2");
	gui->onButtonEvent(this, &ofApp::onButtonEvent);
	void onButtonEvent(ofxDatGuiButtonEvent e)
	{
		if (e.target == b1){
			cout << "Button 1 was clicked" << endl;
		} else if (e.target == b2){
		// 	button 2 was clicked, do something else //
		}
	}

All events also contain additonal properties that allow convenient access to the state of the component that dispatched the event.

**ofxDatGuiButtonEvent**

	ofxDatGuiButtonEvent e
	bool e.enabled // the enabled state of a toggle button
			
**ofxDatGuiSliderEvent**

	ofxDatGuiSliderEvent e
	float e.value // current value of the slider 
	float e.scale // current scale of the slider 

**ofxDatGuiTextInputEvent**
	
	ofxDatGuiTextInputEvent e
	string e.text // current text in the textfield
	
**ofxDatGuiColorPickerEvent**

	ofxDatGuiColorPickerEvent e
	ofColor e.color // the color of the picker
	
**ofxDatGui2dPadEvent**

	ofxDatGui2dPadEvent e
	float e.x // x coordinate within the pad's bounds rectangle
	float e.y // y coordinate within the pad's bounds rectangle
	 
**ofxDatGuiDropdownEvent**
	
	ofxDatGuiDropdownEvent e
	int e.child // the index of the selected option (zero based)
	
**ofxDatGuiMatrixEvent**
	
	ofxDatGuiMatrixEvent e
	int e.child // the index of the selected button (zero based)
	bool e.enabled // enabled state of the selected button
	
**Note:** You can also retrieve these properties directly from the event target itself.

	ofxDatGuiSliderEvent e
	float value = e.target->getValue();
	float scale = e.target->getScale();
	
		
##Headers & Footers

**ofxDatGui** also provides an optional header and footer that allows you to title your gui, drag it around and conveniently collapse and expand it. The ```GuiComponents``` example for offers a nice demonstration of their use.

	gui->addHeader(":: Drag Me To Reposition ::");
	
![ofxDatGui](./readme-img/ofxdatgui_header.png?raw=true)
	
	gui->addFooter();
 
![ofxDatGui](./readme-img/ofxdatgui_footer.png?raw=true)

##Automatic Rendering

**ofxDatGui** automatically updates draws itself on top of your application so there is no need to call ```update``` or ```draw``` on it. However you can easily disable this if you like via:

	gui->setAutoDraw(bool enabled);
 
##Label Alignment

You can easily set the label alignment for each component or on **ofxDatGui** itself via:

	gui->setAlignment(ofxDatGuiAlignment alignment);

Valid values are:
 
 	ofxDatGuiAlignment::LEFT
 	ofxDatGuiAlignment::CENTER
 	ofxDatGuiAlignment::RIGHT
 
##Customization

Aditionally all components provide the following instance methods.

 	gui->setWidth(int width);
 	gui->setOrigin(int x, int y);
	gui->setOpacity(float opacity); // between 0 & 1 //
	gui->setVisible(bool visible);
	gui->setEnabled(bool enabled);
	gui->setStripeColor(ofColor color);
	gui->setAlignment(ofxDatGuiAlignment alignment);

##Save & Load Settings

	Coming Soon


##Additonal Notes

Thanks for reading all this and checking the project out. 

I'm actively looking for people to help me test this and provide feedback to help shape ongoing development. If you'd like to see a feature prioritized or have any general questions or feedback please send me a message or open an issue here on Github.

Thanks!