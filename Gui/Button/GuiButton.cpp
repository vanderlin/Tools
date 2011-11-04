/*
 *  GuiButton.cpp
 *  GuiDemo
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiButton.h"


GuiButton::GuiButton() {
	valuePtr    = NULL;
	isRectangle = true;
	isToggle	= true;
	value		= false;
	setSize(defaultGuiStyle.buttonW, defaultGuiStyle.buttonH);
}

//--------------------------------------------------------------
void GuiButton::setValue(bool val) {
	value = val;
	if(valuePtr) (*valuePtr) = getValue();
}

//--------------------------------------------------------------
bool GuiButton::getValue() {
	return value;
}

//--------------------------------------------------------------
void GuiButton::draw() {
	draw(x, y);
}

//--------------------------------------------------------------
void GuiButton::draw(float px, float py) {
	
	float rightOff = offset.x;
	float cx = width;
	float cy = 0;//defaultGuiStyle.sliderH-height;
	
	x = (px+style.buttonOffset.x);
	y = (py + cy) + style.buttonOffset.y;
	
	if(!isRectangle) {
		ofFill();
		bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
		ofCircle(x, y, width);
		
		if(value) {
			ofSetColor(style.sliderBarColor);
			ofCircle(x, y, 2);
		}
	}
	else {
		ofFill();
		bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
		ofRect((*this));	
		
		if(value) {
			ofSetColor(style.sliderBarColor);
			ofLine(x, y, x+width, y+height);
			ofLine(x+width, y, x, y+height);
		}
	}
	
	// title
    if(bUseLabel) {
        if(GuiStyle::font.isLoaded()) {
            ofSetColor(style.textColor);
            GuiStyle::font.drawString(name, x+width+10, (y+8)-cy);
        }
        else {
            ofSetColor(style.textColor);
            ofDrawBitmapString(name, x+width+10, (y+8)-cy);
        }
    }
}

void GuiButton::mousePressed(int mx, int my) {
	bPressed = isRectangle ? inside(mx, my) : ofDist(mx, my, x, y) < width;
	if (bPressed) {
		value = !value;
	}
	if(valuePtr) (*valuePtr) = value;	
}

void GuiButton::mouseDragged(int mx, int my) {
}


void GuiButton::mouseMoved(int mx, int my) {
	bOver = isRectangle ? inside(mx, my) : ofDist(mx, my, x, y) < width;
}