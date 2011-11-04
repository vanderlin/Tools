/*
 *  GuiRangeSlider.cpp
 *  GuiDemo
 *
 *  Created by Todd Vanderlin on 8/12/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiRangeSlider.h"

GuiRangeSlider::GuiRangeSlider() {
	bDrawInfo = true;
	min	  = 0;
	max   = 0;
	offset = defaultGuiStyle.sliderOffset;
		setSize(defaultGuiStyle.sliderW, defaultGuiStyle.sliderH);
}

//--------------------------------------------------------------
void GuiRangeSlider::setValue(float min, float max) {
//	value = val;
//	if(valuePtr) (*valuePtr) = getValue();
}

//--------------------------------------------------------------
void GuiRangeSlider::draw(float px, float py) {
	/*
	x = px+offset.x;
	y = py+offset.y;
	
	ofFill();
	bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
	ofRect(x, y, width, height);
	
	ofSetColor(style.sliderBarColor);
	ofRect(x, y, width*value, height);	
	
	if(bDrawInfo) {
		float typeOffY = 10;
		ofSetColor(style.textColor);
		
		if(GuiStyle::font.isLoaded()) {
			GuiStyle::font.drawString(ofToString(getValue(), 2), x+width+13, y+typeOffY);
			GuiStyle::font.drawString(name, x+5-offset.x, y+typeOffY);
		}
		else {
			ofDrawBitmapString(ofToString(getValue(), 2), x+width+13, y+typeOffY);
			ofDrawBitmapString(name, x+5-offset.x, y+typeOffY);
		}
	}*/
}

//--------------------------------------------------------------
void GuiRangeSlider::mouseMoved(int mx, int my ) {
	bOver = inside(mx, my);
}

//--------------------------------------------------------------
void GuiRangeSlider::mousePressed(int mx, int my) {
	/*bPressed = inside(mx, my);
	if(bPressed) {
		setValue(ofMap(mx, x, width+x, 0.0, 1.0, true));
	}*/
}

//--------------------------------------------------------------
void GuiRangeSlider::mouseDragged(int mx, int my) {
	/*if(bPressed) {
		setValue(ofMap(mx, x, width+x, 0.0, 1.0, true));
	}*/
}