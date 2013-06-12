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

class RangeValue {
public:
    float min, max;
    RangeValue() {
        
    }
    RangeValue(float min, float max):min(min), max(max) {
        
    }
    float getRandomValue() {
        return ofRandom(min, max);
    }
};

class GuiRangeSlider : public GuiElement {
	
public:
	
	GuiRangeSlider();
	
	void	draw(float px, float py);
	void	mousePressed(int mx, int my);
	void	mouseDragged(int mx, int my);
	void	mouseMoved(int mx, int my );
	void    mouseReleased(int mx=0, int my=0);
    
	void	setMinMaxRange(float min, float max);
	void	setValue(float newMin, float newMax);
	float * minPtr;
	float * maxPtr;
	float	min, max;
	bool	bDrawInfo;

    bool bOverMin, bOverMax;
    bool bPressedMin, bPressedMax;
    bool bIsInt;
    ofRectangle minRect, maxRect;
};