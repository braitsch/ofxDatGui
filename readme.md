##ofxDatGui

**ofxDatGui** is a **simple to use**, fully customizable, high-resolution graphical user interface for [openFrameworks](http://openframeworks.cc/) inspired by the popular JavaScript [datgui](http://workshop.chromeexperiments.com/examples/gui/) interface.  

![ofxDatGui](./readme-img/ofxdatgui_03.png?raw=true)

##Features

**ofxDatGui** offers the following features & components:

* Click & Toggle (On/Off) Buttons
* Text Input Fields
* Color Pickers
* Range Sliders
* Dropdown Menus
* Button Matrices
* Coordinate Pads
* Variable Binding
* Framerate Monitor
* Completely Customizable
* Folders to group components together
* An optional header & footer that allow you to title the gui, collapse and drag it around

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
 
**ofxDatGui** currently offers the following interactive components:
  
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

**Framerate Monitor**
	
	gui->addFRM(float refreshFrequency = 1.0f);

![ofxDatGui](./readme-img/ofxdatgui_fps.gif?raw=true)

**Break**

	gui->addLabel("Above");
	gui->addBreak(float height = 10.0f);
	gui->addLabel("Stuck in the Middle");
	gui->addBreak(float height = 10.0f);
	gui->addLabel("Below");

![ofxDatGui](./readme-img/ofxdatgui_break.png?raw=true)

##Headers & Footers

**ofxDatGui** also provides an optional header and footer that allows you to title your gui, drag it around and conveniently collapse and expand it. The ```AllComponentsGui``` example offers a nice demonstration of their use.

	gui->addHeader(":: Drag Me To Reposition ::");
	
![ofxDatGui](./readme-img/ofxdatgui_header.png?raw=true)
	
	gui->addFooter();
 
![ofxDatGui](./readme-img/ofxdatgui_footer.png?raw=true)

You can change the header's label just like any other component by calling:

```cpp
gui->getHeader()->setLabel("PANEL 1");
```
Footers have two labels that each map to the gui's expanded and collapsed states.<br>By default these labels are "Collapse Controls" and "Expand Controls" however you can override these defaults by via:

```cpp
gui->getFooter()->setLabelWhenExpanded("CLOSE PANEL 1");
gui->getFooter()->setLabelWhenCollapsed("EXPAND PANEL 1");
```
##Component Groups (Folders)

You can also group related components into folders. When constructing a folder pass in a label to name the folder and an optional color to help visually group its contents.

```cpp
ofxDatGuiFolder* folder = gui->addFolder("My White Folder", ofColor::white);
folder->addTextInput("** Input", "A Nested Text Input");
folder->addSlider("** Slider", 0, 100);
folder->addToggle("** Toggle", false);
```

![ofxDatGui](./readme-img/ofxdatgui_folder.png?raw=true)
	
All components can be nested into folders with the exception of other folders and dropdowns.

---
	
Folders and dropdown menus can also be expanded and collapsed programmatically.

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
int myDropdown->size();
myDropdown->select(int index);
ofxDatGuiDropdownOption* getChildAt(int index);
ofxDatGuiDropdownOption* myDropdown->getSelected();
myDropdown->expand();
myDropdown->collapse();
```
	
**ofxDatGuiMatrix**

```cpp	
ofxDatGuiMatrix* myMatrix;
ofxDatGuiMatrixButton* myMatrix->getChildAt(int index);
vector<int> myMatrix->getSelected();
// returns a vector containing the indicies of the selected buttons //
myMatrix->clear(); // deselects all buttons in the matrix //
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

If you're lazy and don't feel like storing your components in variables you can easily retrieve them by name which by default is the same as whatever you set its label to.

	ofxDatGuiButton* gui->getButton("My Button"); // button name
	ofxDatGuiSlider* gui->getSlider("My Slider"); // slider name
	
Note: ``gui->getComponent`` performs a case-insensitive lookup against the component's name so the following works fine as well.

	ofxDatGuiButton* gui->getButton("my bUTTon"); // button name
	ofxDatGuiSlider* gui->getSlider("mY sLiDEr"); // slider name
	
To change a component's label or name simply:

	gui->getButton("My Button")->setName("b1");
	gui->getButton("b1")->setLabel("Your Button");
	
If you have multiple components with the same name nested in separate folders just specify the folder to search.

	ofxDatGuiButton* gui->getButton("Reset Button", "Folder 1");
	ofxDatGuiButton* gui->getButton("Reset Button", "Folder 2");
	
Otherwise the function will return the first component whose name & type match the query.
	
## Variable Binding

**ofxDatGui** sliders & coordinate pads can also be bound to object variables. Just pass a reference to the variable to the component and set a range by which to limit its movement.

For example the following snippet binds a circle's position to a range slider and limits its movement to the width & height of the screen.

```cpp
// draw a circle with a radius of 100px
// and position it in the middle of the screen //
	circle = new Circle(100);
	circle->x = ofGetWidth()/2;
	circle->y = ofGetHeight()/2;
    
// instantiate a gui and a couple of range sliders //
	gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
	ofxDatGuiSlider* sx = gui->addSlider("CIRCLE X", 0, 100);
	ofxDatGuiSlider* sy = gui->addSlider("CIRCLE Y", 0, 100);
    
// bind the circle's x & y movement to the sliders //
	sx->bind(&circle->x, 0, ofGetWidth());
	sy->bind(&circle->y, 0, ofGetHeight());
```
	
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
	
However a more convenient way of determining which component dispatched the event is by using the built in ``is`` operator.

	gui->addButton("Button 1");
	gui->addButton("Button 2");
		
	void onButtonEvent(ofxDatGuiButtonEvent e)
	{
		if (e.target->is("button 1")){
			cout << "Button 1 was clicked" << endl;
		} else if (e.target->is("button 2")){
		// 	button 2 was clicked, do something else //
		}
	}
	
This performs a case-insensitive search against the component's name which by default is the same as its label.

****

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
 
##Customization

Just about every aspect of **ofxDatGui's** appearance can be tailored to meet your needs.

Customization is accomplished via extensible templates where you define how you want **ofxDatGui** to render.

Just create a class that extends ``ofxDatGuiTemplate`` and pass it to **ofxDatGui** or any component via ``gui->setTemplate()``

```cpp
class myCustomTemplate : public ofxDatGuiTemplate
{
    public:
        myCustomTemplate() {
        // row characteristics //
            row.width	= 540;
            row.height	= 52;
            row.padding	= 4;
            row.spacing	= 2;
            row.stripeWidth = 4;
        // font characteristics //
            font.file	= "PillGothic-Light.ttf"
            font.size   = 12;
            font.highlightPadding = 4;
        // component colors //
            color.rowBkgd	= ofColor::lightGray;
            color.button	= ofColor::fromHex(0xFFD00B);
            color.slider	= ofColor::fromHex(0x2FA1D6);
            color.rowMouseOver = ofColor::fromHex(0x777777);
		// after everything is setup initialize the template // 
            init();
        }
};

// assign this template to a gui instance //
	gui = new ofxDatGui();
	gui->setTemplate(new myCustomTemplate());

```

Take a look at the [ofxDatGuiTemplate](./src/templates/ofxDatGuiTemplate.h) base class for a list of everything that can be customized.

---

Aditionally all components and gui instances provide the following instance methods.

 	setWidth(int width);
 	setOrigin(int x, int y);
	setOpacity(float opacity); // a value between 0 & 1 //
	setVisible(bool visible);
	setEnabled(bool enabled);
	setAlignment(ofxDatGuiAlignment alignment);

##Label Alignment

You can set the label alignment for each component or on **ofxDatGui** itself via:

	gui->setAlignment(ofxDatGuiAlignment alignment);

Valid values are:
 
 	ofxDatGuiAlignment::LEFT
 	ofxDatGuiAlignment::CENTER
 	ofxDatGuiAlignment::RIGHT

##Automatic Rendering

**ofxDatGui** automatically updates and draws itself on top of your application so there is no need to call ```update``` or ```draw``` on it. However you can easily disable this if you like via:

	gui->setAutoDraw(bool enabled);

##Logging

**ofxDatGui** will softly warn you if you forget to attach an event listener to a component you've created or if you attempt to perform an action on a component that does not exist.

	[ERROR] :: Component Not Found : GHOST BUTTON
	[WARNING] :: Event Handler Not Set : MY BUTTON

However you can easily suppress these warnings by calling:

	ofxDatGuiLog::quiet();

##Save & Load Settings

	Coming Soon


##Additonal Notes

Thanks for reading all this and checking the project out. 

I'm actively looking for people to help me test this and provide feedback to help shape ongoing development. If you'd like to see a feature prioritized or have any general questions or feedback please send me a message or open an issue here on Github.

Thanks!