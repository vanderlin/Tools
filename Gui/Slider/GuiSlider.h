/*
 *  GuiSlider.h
 *  PeopleTracker
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */
#pragma once
#include "GuiElement.h"

class GuiSlider : public GuiElement {

private:
            
public:

	GuiSlider();
	
    void    setStyle(GuiStyle &newStyle);
    
	void	draw(float px, float py);
	void	mousePressed(int mx, int my);
	void	mouseDragged(int mx, int my);
	void	mouseMoved(int mx, int my );
	
	void	setValue(float val);
	void	setValueNormal(float nVal);
	float	getValue();
	float	getValuef();
	void	setMinMax(float min, float max);
	
	float	min, max;
	float	value;
    float   smoothValue;
    
    bool    bIsInt;
	float * valuePtrF;
    int   * valuePtrI;
	bool	bDrawInfo;
};