/*
 *  GuiButton.h
 *  GuiDemo
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "GuiElement.h"

class GuiButton : public GuiElement {
	
public:
	

	//--------------------------------------------------------------
	GuiButton();
	void draw(float px, float py);
	void draw();
	
	bool isToggle;
	bool *valuePtr;
	bool value;
	bool isRectangle;
	
	void  mousePressed(int mx, int my);
	void  mouseDragged(int mx, int my);
	void  mouseMoved(int mx, int my );
	
	//--------------------------------------------------------------
	void setValue(bool val);
	bool getValue();
};