/*
    Copyright (C) 2016 Antoine Villeret

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
#pragma once

#include "ofxXmlSettings.h"
#include "ofxDatGui.h"

class ofxDatGuiSettings {
public:
    void save(const string filename, ofxDatGui* gui){
        if ( !gui ) return;
        xml.clear();
        xml.addTag("ofxDatGuiSettings");
        xml.pushTag("ofxDatGuiSettings");
        writeItems(gui->getItems());
        xml.popTag();
        xml.saveFile(filename);
    }

    void load(const string filename, ofxDatGui* gui){
        if ( !gui ){
            ofLogWarning("ofxDatGuiSettings") << "ofxDatGui pointer is null";
            return;
        }
        if ( !xml.loadFile(filename) ){
            ofLogWarning("ofxDatGuiSettings") << "Can't find file: " << filename;
            return;
        }
        xml.pushTag("ofxDatGuiSettings");
        readItems(gui->getItems());
        xml.popTag();
    }

private:
    void writeItems(vector<ofxDatGuiComponent*> & items){
        int tagNum=0;
        for (auto item : items){
            string name = item->getName();
            switch (item->getType()){
            case ofxDatGuiType::LABEL:
            case ofxDatGuiType::BREAK:
            case ofxDatGuiType::BUTTON:
                break;
            case ofxDatGuiType::TOGGLE:
                tagNum = xml.addTag("TOGGLE");
                xml.setValue("TOGGLE:name", name, tagNum);
                xml.setValue("TOGGLE:value", static_cast<ofxDatGuiToggle*> (item)->getChecked(), tagNum);
                break;
            case ofxDatGuiType::PAD2D:
                tagNum = xml.addTag("PAD2D");
                xml.setValue("PAD2D:name", name, tagNum);
                xml.setValue("PAD2D:x", static_cast<ofxDatGui2dPad*> (item)->getPoint().x, tagNum);
                xml.setValue("PAD2D:y", static_cast<ofxDatGui2dPad*> (item)->getPoint().y, tagNum);
                break;
            case ofxDatGuiType::HEADER:
            case ofxDatGuiType::FOOTER:
                break;
            case ofxDatGuiType::MATRIX:
                tagNum = xml.addTag("MATRIX");
                xml.setValue("MATRIX:name", name, tagNum);
                { // some braces to reduce the focus of the following declaration
                    stringstream selected;
                    for ( int i : static_cast<ofxDatGuiMatrix*> (item)->getSelected() ){
                        selected << i << " ";
                    }
                    xml.setValue("MATRIX:selected", selected.str(), tagNum);
                }
                break;
            case ofxDatGuiType::SLIDER:
                tagNum = xml.addTag("SLIDER");
                xml.setValue("SLIDER:name", name, tagNum);
                xml.setValue("SLIDER::value", static_cast<ofxDatGuiSlider*> (item)->getValue(), tagNum);
                break;
            case ofxDatGuiType::FOLDER:
                tagNum = xml.addTag("FOLDER");
                xml.setValue("FOLDER:name", name, tagNum);
                xml.pushTag("FOLDER",tagNum);
                writeItems(static_cast<ofxDatGuiFolder*> (item)->children);
                xml.popTag();
                break;
            case ofxDatGuiType::DROPDOWN:
                tagNum = xml.addTag("DROPDOWN");
                xml.setValue("DROPDOWN:name", name, tagNum);
                xml.setValue("DROPDOWN:value", static_cast<ofxDatGuiDropdown*> (item)->getSelected()->getName(), tagNum);
                break;
            case ofxDatGuiType::DROPDOWN_OPTION:
                break;
            case ofxDatGuiType::TEXT_INPUT:
                tagNum = xml.addTag("TEXT_INPUT");
                xml.setValue("TEXT_INPUT:name", name, tagNum);
                xml.setValue("TEXT_INPUT:value", static_cast<ofxDatGuiTextInput*> (item)->getText(), tagNum);
                break;
            case ofxDatGuiType::FRAME_RATE:
                break;
            case ofxDatGuiType::COLOR_PICKER:
                tagNum = xml.addTag("COLOR_PICKER");
                xml.setValue("COLOR_PICKER:name", name, tagNum);
                xml.setValue("COLOR_PICKER:r", static_cast<ofxDatGuiColorPicker*> (item)->getColor().r, tagNum);
                xml.setValue("COLOR_PICKER:g", static_cast<ofxDatGuiColorPicker*> (item)->getColor().g, tagNum);
                xml.setValue("COLOR_PICKER:b", static_cast<ofxDatGuiColorPicker*> (item)->getColor().b, tagNum);
                break;
            case ofxDatGuiType::WAVE_MONITOR:
            case ofxDatGuiType::VALUE_PLOTTER:
                break;
            default:
                ofLogWarning("ofxDatGuiSettings") << "This component will be not saved : " << name;
                break;
            }
        }
    }

    void readItems(vector<ofxDatGuiComponent*> & items){
        int tagNum=0;
        for (auto item : items){
            string name = item->getName();
            if (item->getType() == ofxDatGuiType::TOGGLE){
                tagNum = xml.getNumTags("TOGGLE");
                ofxDatGuiToggle* tog = static_cast<ofxDatGuiToggle*> (item);
                for ( int i = 0; i < tagNum ; i++ ){
                    if (xml.getValue("TOGGLE:name", "ofxDatGui-default-name-string", i) == name) {
                        tog->setChecked(xml.getValue("TOGGLE:value",tog->getChecked(), i));
                        // TODO we may need to trig some callback here
                        break;
                    }
                }
            } else if (item->getType() == ofxDatGuiType::PAD2D){
                tagNum = xml.getNumTags("PAD2D");
                ofxDatGui2dPad* pad = static_cast<ofxDatGui2dPad*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("PAD2D:name", "ofxDatGui-default-name-string", i) == name) {
                        ofPoint pt;
                        pt.x = xml.getValue("PAD2D:x",pad->getPoint().x, i);
                        pt.y = xml.getValue("PAD2D:y",pad->getPoint().y, i);
                        pad->setPoint(pt);
                        // TODO we may need to trig some callback here
                        break;
                    }
                }
            } else if (item->getType() == ofxDatGuiType::MATRIX){
                tagNum = xml.getNumTags("MATRIX");
                ofxDatGuiMatrix* mat = static_cast<ofxDatGuiMatrix*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("MATRIX:name", "ofxDatGui-default-name-string", i) == name) {
                        stringstream ss;
                        ss.str(xml.getValue("MATRIX:selected", " ", i));
                        vector<int> selected;
                        int n;
                        while ( ss >> n ){
                            selected.push_back(n);
                        }
                        mat->setSelected(selected);
                        // TODO we may need to trig some callback here
                        break;
                    }
                }
            } else if (item->getType() == ofxDatGuiType::SLIDER) {
                tagNum = xml.getNumTags("SLIDER");
                ofxDatGuiSlider* slider = static_cast<ofxDatGuiSlider*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("SLIDER:name", "ofxDatGui-default-name-string", i) == name) {
                        stringstream ss;
                        slider->setValue(xml.getValue("SLIDER:value", slider->getValue(), i));
                        // TODO we may need to trig some callback here
                        break;
                    }
                }
            } else if ( item->getType() == ofxDatGuiType::FOLDER){
                tagNum = xml.getNumTags("FOLDER");
                ofxDatGuiFolder* folder = static_cast<ofxDatGuiFolder*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("FOLDER:name", "ofxDatGui-default-name-string", i) == name){
                        xml.pushTag("FOLDER",i);
                        readItems(folder->children);
                        xml.popTag();
                        break;
                    }
                }
            } else if ( item->getType() == ofxDatGuiType::DROPDOWN){
                tagNum = xml.getNumTags("DROPDOWN");
                ofxDatGuiDropdown* dropdown = static_cast<ofxDatGuiDropdown*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("DROPDOWN:name", "ofxDatGui-default-name-string", i) == name){
                        string selected = xml.getValue("DROPDOWN:value", dropdown->getSelected()->getName(), 1);
                        for ( int j = 0; j < dropdown->children.size(); j++){
                            if ( dropdown->children[i]->getName() == selected ){
                                dropdown->select(i);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else if ( item->getType() == ofxDatGuiType::TEXT_INPUT ){
                tagNum = xml.getNumTags("TEXT_INPUT");
                ofxDatGuiTextInput* txtinput = static_cast<ofxDatGuiTextInput*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("TEXT_INPUT:name", "ofxDatGui-default-name-string", i) == name){
                        txtinput->setText(xml.getValue("TEXT_INPUT:value", txtinput->getText(),i));
                        break;
                    }
                }
            } else if ( item->getType() == ofxDatGuiType::COLOR_PICKER){
                tagNum = xml.getNumTags("COLOR_PICKER");
                ofxDatGuiColorPicker* picker = static_cast<ofxDatGuiColorPicker*> (item);
                for (int i = 0; i < tagNum ; i++){
                    if (xml.getValue("COLOR_PICKER:name", "ofxDatGui-default-name-string", i) == name){
                        ofColor col;
                        col.r = xml.getValue("COLOR_PICKER:r", picker->getColor().r, i);
                        col.g = xml.getValue("COLOR_PICKER:g", picker->getColor().g, i);
                        col.b = xml.getValue("COLOR_PICKER:b", picker->getColor().b, i);
                        picker->setColor(col);
                        break;
                    }
                }
            }
        }
    }

    ofxXmlSettings xml;
};
