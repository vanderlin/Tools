/*
 *  GuiRangeSlider.h
 *  GuiDemo
 *
 *  Created by Todd Vanderlin on 8/12/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */
#pragma once
#include "GuiElement.h"

class GuiRangeSlider : public GuiElement {
	
public:
	
	GuiRangeSlider();
	
	void	draw(float px, float py);
	void	mousePressed(int mx, int my);
	void	mouseDragged(int mx, int my);
	void	mouseMoved(int mx, int my );
	
	void	setValue(float min, float max);
	float * minPtr;
	float * maxPtr;
	float	min, max;
	bool	bDrawInfo;
};