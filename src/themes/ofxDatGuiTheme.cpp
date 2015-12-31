/*
    Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ofxDatGuiTheme.h"

ofxDatGui2880x1800::ofxDatGui2880x1800()
{
    font.size *= 2;
    stripe.width *= 2;
    layout.width = 540;
    layout.height *= 2;
    layout.padding *= 2;
    layout.vMargin *= 2;
    layout.iconSize *= 2;
    layout.graph.height *=2;
    layout.pad2d.height *=2;
    layout.pad2d.ballSize *=2;
    layout.pad2d.lineWeight *=2;
    layout.matrix.height *=2;
    layout.matrix.buttonSize = 47;
    layout.textInput.highlightPadding *= 2;
    init();
}

ofxDatGui1440x900::ofxDatGui1440x900()
{
// just inherent all defaults //
    init();
}
