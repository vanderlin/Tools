/*
 *  GuiSlider.cpp
 *  PeopleTracker
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiSlider.h"

GuiSlider::GuiSlider() {
    
    bIsInt      = false;
	bDrawInfo   = true;
	valuePtrF   = NULL;
    valuePtrI   = NULL;
    
    smoothValue = 0;
	value       = 0.0;
	min         = 0;
	max         = 0;
	offset      = defaultGuiStyle.sliderOffset;
	
    setSize(defaultGuiStyle.sliderW, defaultGuiStyle.sliderH);
}

//--------------------------------------------------------------
void GuiSlider::setStyle(GuiStyle &newStyle) {
    style = newStyle;
    offset = newStyle.sliderOffset;
	setSize(newStyle.sliderW, newStyle.sliderH);
    style.typeOffset = newStyle.typeOffset;
}

//--------------------------------------------------------------
void GuiSlider::setMinMax(float min, float max) {
	this->min = min;
	this->max = max;
}

//--------------------------------------------------------------
void GuiSlider::setValue(float val) {
	value = ofMap(val, min, max, 0.0, 1.0);
	if(valuePtrF) (*valuePtrF) = getValue();
    if(valuePtrI) (*valuePtrI) = getValue();
    
}

//--------------------------------------------------------------
void GuiSlider::setValueNormal(float nVal) {
	value = nVal;
	if(valuePtrF) (*valuePtrF) = getValue();
	if(valuePtrI) (*valuePtrI) = getValue();
	
}

//--------------------------------------------------------------
float GuiSlider::getValue() {
	return ofMap(value, 0.0, 1.0, min, max, true);
}

//--------------------------------------------------------------
float GuiSlider::getValuef() {
	return value;
}

//--------------------------------------------------------------
void GuiSlider::draw(float px, float py) {
	
  //  if(valuePtrF) setValue((*valuePtrF));
    // if(valuePtrI) setValue(*valuePtrI);
    
	x = px+offset.x;
	y = py+offset.y;
	
	ofFill();
	bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
	ofRect(x, y, width, height);
	
	ofSetColor(style.sliderBarColor);
	ofRect(x, y, (float)width*getValuef(), height);	
	if(bDrawInfo) {
        
		ofSetColor(style.textColor);
		string lb = "";
        if(style.bDrawName) lb = name;
        lb += " "+ofToString(getValue(), bIsInt?0:1);
        
		if(GuiStyle::font.isLoaded()) {
            GuiStyle::font.drawString(lb, x+width+10-offset.x+style.typeOffset.x, y+style.typeOffset.y);
		}
		else {
            ofDrawBitmapString(lb, x+width+10-offset.x+style.typeOffset.x, y+style.typeOffset.y);
		}
	}
    
    /*
    if(bUseLabel) {
        if(GuiStyle::font.isLoaded()) {
            ofSetColor(style.textColor);
            GuiStyle::font.drawString(name, x+width+10, (y+8)-cy);
        }
        else {
            ofSetColor(style.textColor);
            ofDrawBitmapString(name, x+width+10, (y+8)-cy);
        }
    }*/
}

//--------------------------------------------------------------
void GuiSlider::mouseMoved(int mx, int my ) {
	bOver = inside(mx, my);
}

//--------------------------------------------------------------
void GuiSlider::mousePressed(int mx, int my) {
	bPressed = inside(mx, my);
	if(bPressed) {
		setValueNormal(ofMap(mx, x, width+x, 0.0, 1.0, true));
	}
}

//--------------------------------------------------------------
void GuiSlider::mouseDragged(int mx, int my) {
	float msx = mx;
    if(bPressed) {
        if(ofGetKeyPressed(9)) {
            smoothValue += ( ofMap(msx, x, width+x, 0.0, 1.0, true) - smoothValue ) * .02;
        }
        else         {
            smoothValue = ofMap(msx, x, width+x, 0.0, 1.0, true);
        }
		setValueNormal(smoothValue);
	}
}