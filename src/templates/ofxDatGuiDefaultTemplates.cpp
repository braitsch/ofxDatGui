//
// @author Minjie Zheng
//

#include "ofxDatGuiDefaultTemplates.h"

ofxDatGui2880x1800::ofxDatGui2880x1800() {
    row.width   = 540;//600
    row.height  *= 2;
    row.padding *= 2;
    row.spacing *= 2;
    row.stripeWidth *= 2;
    font.size   *= 2;
    font.highlightPadding *= 2;
    matrix.buttonSize = 47;//53;
    init();
}

ofxDatGui1440x900::ofxDatGui1440x900() {
    // just inherent all defaults //
    init();
}

unique_ptr<ofxDatGui2880x1800> ofxDatGuiDefaultTemplates::retinaTemplate = nullptr;
unique_ptr<ofxDatGui1440x900> ofxDatGuiDefaultTemplates::nonRetinaTemplate = nullptr;

ofxDatGuiTemplate* ofxDatGuiDefaultTemplates::get2880x1800() {
    if (retinaTemplate == nullptr) {
        retinaTemplate = unique_ptr<ofxDatGui2880x1800>(new ofxDatGui2880x1800());
    }
    return retinaTemplate.get();
}

ofxDatGuiTemplate* ofxDatGuiDefaultTemplates::get1440x900() {
    if (nonRetinaTemplate == nullptr) {
        nonRetinaTemplate = unique_ptr<ofxDatGui1440x900>(new ofxDatGui1440x900());
    }
    return nonRetinaTemplate.get();
}
