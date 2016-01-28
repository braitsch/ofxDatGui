### ofxDatGui Changelog

--
**v1.10** –– 01-28-16

* adding [scrollview](http://braitsch.github.io/ofxDatGui/index.html#scrollviews) component
* [ofParameter](http://openframeworks.cc/documentation/types/ofParameter/) support (sliders only)
* slider->bind() pass by reference
* slider->setMin & slider->setMax()
* draw methods refactored
* ofxDatGuiTextInput->setInputType()
* adding support for [component borders](http://braitsch.github.io/ofxDatGui/index.html#api)
* assets moved into **/bin/data/ofxbraitsch**
--
**v1.00** –– 01-04-16

* style templates rewritten into much simpler [themes](http://braitsch.github.io/ofxDatGui/themes.html)
* setOrigin -> setPosition
* setAlignment -> setLabelAlignment
* setWidth now also takes a value for the label width
* eliminating resolution specific themes
* textfields & fonts are now created on the stack
* adding component styling convenience methods

--
**v0.90** –– 11-29-15

* cursor added to ofxDatGuiInputField (thanks Jesse!)
* range sliders: limit range to integers
* range sliders: specify custom floating point precisions
* ofxDatGuiTextInputField->isKeyValid() rewrite

--
**v0.80** –– 10-23-15

* new documentation site!
* support for overlapping guis
* gui focus management rewrite
* matrices can now function as radio button groups

--
**v0.70** –– 10-10-15

* adding value plotters & waveform monitors
* introducing templates for component customization
* experimental variable binding on range sliders

--
**v0.60** –– 09-16-15

* color pickers!
* adding button matrices and 2d coordinate pads
* all components decoupled from gui container and can now stand alone

--
**v0.50** –– 08-31-15

* support for multiple dropdowns
* adding folders to group related components

--
**v0.40** –– 08-28-15

* range sliders now accept keyboard input
* text rendering broken out into its own font class
* support for window resizing
* adding draggable header to allow gui to be repositioned

--
**v0.30** –– 08-24-15

* adding text input fields
* support for transparent gui backgrounds
* adding footer to expand/collapse controls
* adding toggle button and support for retina displays

--
**v0.20** –– 08-21-15

* experimenting with dropdown menus
* adding ofxDatGuiEvents to dispatch state changes

--
**v0.10** –– 08-18-15

* capturing mouse events
* simple range sliders & buttons working 
* experimenting with anchors / corner registration

--