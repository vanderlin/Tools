/*
 *  GuiGroup.cpp
 *  PeopleTracker
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiGroup.h"

vector <GuiGroup*> GuiGroup::groups;
bool GuiGroup::inGroup = false;

//--------------------------------------------------------------
GuiGroup::GuiGroup() {
    bDownInside       = false;
	bHide			  = false;
	GuiGroup::inGroup = false;
	savepath		  = "GIU_ADD_NAME_PLEASE.txt";
    bEnable           = true;
    bDrawFPS          = false;
	GuiGroup::groups.push_back(this);

}


//--------------------------------------------------------------
GuiGroup::~GuiGroup() {

    for (int i=0; i<elements.size(); i++) {
        delete elements[i];
        elements[i] = NULL;
    }
    elements.clear();

}

//--------------------------------------------------------------
void GuiGroup::setup(string name, float x, float y, float w, float h) {
	
	this->name	 = name;
	savepath	 = name + ".txt";
	
	style		 = defaultGuiStyle;
	this->x		 = x;
	this->y		 = y;
	this->width  = w;
	this->height = h;
	
	
	registerEvents();
}

//--------------------------------------------------------------
void GuiGroup::save() {
	ofstream f;
	f.open(ofToDataPath(savepath).c_str());
	
	//f << ofGetWindowPositionX() << "," << ofGetWindowPositionY();
	
	for (int i=0; i<elements.size(); i++) {
		
		f << elements[i]->type << "|";  
		f << elements[i]->name << "|";
		
		if(elements[i]->type == GUI_SLIDER) {
			GuiSlider * s = (GuiSlider*)elements[i];
			f << s->value;
		}
		
		if(elements[i]->type == GUI_BUTTON) {
			GuiButton * b = (GuiButton*)elements[i];
			f << b->value;
		}
		
		if(i!=elements.size()-1)f << ",";
	}
	
	f.close();
}

//--------------------------------------------------------------
void GuiGroup::load() {
	ifstream f;
	f.open(ofToDataPath(savepath).c_str());
	string gstr;
	if(f!=0) {
        
		while (!f.eof()) {
			getline(f, gstr);
		}
		f.close();
		vector <string> p = ofSplitString(gstr, ",");
		
		for (int i=0; i<p.size(); i++) {				
			vector <string> estr = ofSplitString(p[i], "|");
			if(estr.size() >= 3) {
				int		type  = ofToInt(estr[0]);
				string	name  = estr[1];
				float	value = ofToFloat(estr[2]);
				for (int k=0; k<elements.size(); k++) {
					
					// slider
                    if(elements[k]) {
                        if(elements[k]->name.compare(name) == 0  && elements[k]->type == GUI_SLIDER) {
                            GuiSlider * s = (GuiSlider*)elements[k];
                            s->setValueNormal(value);
                        }
                        
                        // button
                        if(elements[k]->name.compare(name) == 0 && elements[k]->type == GUI_BUTTON) {
                            GuiButton * s = (GuiButton*)elements[k];
                            s->setValue(value);
                        }
                    }
				}
                //printf("t:%i\nn:%s\nv:%f\n", type, name.c_str(), value);
			}
		}
		
		
	}
	
}

//--------------------------------------------------------------
void GuiGroup::draw() {
	
	if(bHide) return;
	
	ofEnableAlphaBlending();
    
    // haha maybe do something with dist to center
    style.groupBackground.a += ((inside(ofGetMouseX(), ofGetMouseY()) ? 255 : 90) - style.groupBackground.a) * 0.3;
    
    // the background the group
	ofFill();
	ofSetColor(style.groupBackground);
	ofRect(x, y, width, height);
	
	// top header bar
    ofSetColor(style.headerColor);
	ofRect(x, y, width, 14);

    ofSetColor(250, 130);
	ofRect(x, y+14, width, 2);
	
    // the title of the group
	ofSetColor(style.headerTextColor);
	if(GuiStyle::font.isLoaded()) {
		GuiStyle::font.drawString(name, round(x+5), round(y+11));
	}
	else ofDrawBitmapString(name, round(x+5), round(y+12));
	
    
    // now draw all the element in this group...
	float topPadding  = 0;
	float leftPadding = 0;
	float gy		  = 14 + 8;
	float spaceH = defaultGuiStyle.spaceH;
	for (int i=0; i<elements.size(); i++) {
		GuiElement * e = elements[i];
        
        
		if(e->type == GUI_IMAGE && i == 0) gy = 14;
		
        // bg
        ofSetColor(i%2==0 ? 200 : 255, 100);
        ofRect(x, (y+gy)-5, width, spaceH);
        
        // the element
        elements[i]->draw(x, y+gy);
		
        gy += spaceH;
	}
    
    height = gy; // auto resize (toggle?)   
    
    if(bDrawFPS) {
        ofSetColor(style.headerTextColor);
        if(GuiStyle::font.isLoaded()) {
            GuiStyle::font.drawString("FPS "+ofToString(ofGetFrameRate(), 0), round(x+5+(width-45)), round(y+11));
        }
        else ofDrawBitmapString("FPS "+ofToString(ofGetFrameRate(), 0), round(x+5+(width-60)), round(y+12));        
    }
}

//--------------------------------------------------------------
GuiElement * GuiGroup::add(GuiElement*e, int type) {
	e->type = type;
	elements.push_back(e);
	return e;
}

//--------------------------------------------------------------
GuiSlider * GuiGroup::addSlider(string name, float*valuePtr, float min, float max, float initVal) {

	GuiSlider * e = (GuiSlider*)add(new GuiSlider(), GUI_SLIDER);
	e->name       = name;
	e->valuePtrF  = valuePtr;
    e->bIsInt     = false;
	e->setMinMax(min, max);
	e->setValue(MAX(initVal, min));
	
	//printf("init val: %f\n", e->getValue());
	//printf("init val nf: %f\n", e->getValuef());
	
	return e;
}

//--------------------------------------------------------------
GuiSlider * GuiGroup::addSlider(string name, int*valuePtr, float min, float max, int initVal) {
	GuiSlider * e = (GuiSlider*)add(new GuiSlider(), GUI_SLIDER);
	e->name       = name;
	e->valuePtrI  = valuePtr;
    e->bIsInt     = true;
	e->setMinMax(min, max);
	e->setValue(MAX(initVal, min));
	//printf("init val: %f\n", e->getValue());
	//printf("init val nf: %f\n", e->getValuef());
	
	return e;
}

//--------------------------------------------------------------
GuiRangeSlider * GuiGroup::addRangeSlider(string name, float *minPtr, float *maxPtr, float min, float max) {
	GuiRangeSlider * e = (GuiRangeSlider*)add(new GuiRangeSlider(), GUI_RANGE_SLIDER);
	e->name = name;
	//e->valuePtr = valuePtr;
	return e;
}

//--------------------------------------------------------------
GuiButton * GuiGroup::addButton(string name, bool*valuePtr, bool initVal, bool isToggle) {
	GuiButton * e = (GuiButton*)add(new GuiButton(), GUI_BUTTON);
	e->isToggle = isToggle;
	e->name = name;
	e->valuePtr = valuePtr;
    e->setValue(initVal);
	return e;
}

//--------------------------------------------------------------
GuiImage * GuiGroup::addImage(ofBaseDraws * bd, float drawWidth) {
	GuiImage * e = (GuiImage*)add(new GuiImage(), GUI_IMAGE);
	e->name  = name;
	e->setImage(bd);
	e->setWidth(drawWidth);
	return e;	
}

//--------------------------------------------------------------
GuiLabel * GuiGroup::addLabel(string name, string * info) {
    GuiLabel * e = (GuiLabel*)add(new GuiLabel(), GUI_LABEL);
    e->name = name;
    e->infoPtr = info;
    return e;
}

//--------------------------------------------------------------
GuiLabel * GuiGroup::addLabel(string name, float * value) {
    GuiLabel * e = (GuiLabel*)add(new GuiLabel(), GUI_LABEL);
    e->name = name;
    e->valuePtrF = value;
    return e;
}

//--------------------------------------------------------------
GuiLabel * GuiGroup::addLabel(string name, int * value) {
    GuiLabel * e = (GuiLabel*)add(new GuiLabel(), GUI_LABEL);
    e->name = name;
    e->valuePtrI = value;
    return e;
}

//--------------------------------------------------------------
void GuiGroup::registerEvents() {
	ofAddListener(ofEvents().mouseMoved, this, &GuiGroup::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &GuiGroup::mouseDragged);
	ofAddListener(ofEvents().mousePressed, this, &GuiGroup::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &GuiGroup::mouseReleased);
}

//--------------------------------------------------------------
void GuiGroup::enable() {
    bEnable = true;
}

//--------------------------------------------------------------
void GuiGroup::disable() {
    bEnable = false;
}

//--------------------------------------------------------------
void GuiGroup::mouseMoved(ofMouseEventArgs &e) {
	if(!bEnable) return;
    for (int i=0; i<elements.size(); i++) {
		elements[i]->mouseMoved(e.x, e.y);
	}
    
    if(inside(e.x, e.y)) {
        static GuiEventArgs ge;
        ge.type = GUI_OVER_GROUP;
        ofNotifyEvent(guiEvents, ge, this);
    }	
}

//--------------------------------------------------------------
void GuiGroup::mouseDragged(ofMouseEventArgs &e) {
	if(!bEnable) return;
    for (int i=0; i<elements.size(); i++) {
		elements[i]->mouseDragged(e.x, e.y);
	}
}

//--------------------------------------------------------------
void GuiGroup::mousePressed(ofMouseEventArgs &e) {
	if(!bEnable) return;
    for (int i=0; i<elements.size(); i++) {
		elements[i]->mousePressed(e.x, e.y);
	}
    
    if(inside(e.x, e.y)) {
        bDownInside = true;
        static GuiEventArgs ge;
        ge.type = GUI_PRESSED_GROUP;
        ofNotifyEvent(guiEvents, ge, this);
    }
}

//--------------------------------------------------------------
void GuiGroup::mouseReleased(ofMouseEventArgs &e) {
    bDownInside = false;
    static GuiEventArgs ge;
    ge.type = GUI_RELEASED_GROUP;
    ofNotifyEvent(guiEvents, ge, this);
}