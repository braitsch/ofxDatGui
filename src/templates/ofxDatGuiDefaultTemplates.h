//
// @author Minjie Zheng
//

#pragma once

#include "ofxDatGuiTemplate.h"

/*
    15" RETINA MACBOOK PRO
*/
class ofxDatGui2880x1800 : public ofxDatGuiTemplate{
 public:
    ofxDatGui2880x1800();
};

/*
    15" NON-RETINA MACBOOK PRO
*/
class ofxDatGui1440x900 : public ofxDatGuiTemplate{
 public:
    ofxDatGui1440x900();
};

class ofxDatGuiDefaultTemplates {
 public:
    static ofxDatGuiTemplate* get2880x1800();
    static ofxDatGuiTemplate* get1440x900();
 private:
    static unique_ptr<ofxDatGui2880x1800> retinaTemplate;
    static unique_ptr<ofxDatGui1440x900> nonRetinaTemplate;
};


