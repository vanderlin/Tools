/*
 *  GuiImage.h
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/14/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "GuiElement.h"

class GuiImage : public GuiElement {
	
private:
	
	float ratio;
	ofBaseDraws * image;	
	
public:
	
	GuiImage();
	//--------------------------------------------------------------
	
	void setImage(ofBaseDraws * bd);
	void draw(float px, float py);
	void setWidth(float w);
	
	//--------------------------------------------------------------
	void mouseMoved(int mx, int my );
	void mouseDragged(int mx, int my);
	void mousePressed(int mx, int my);
	void mouseReleased(int mx, int my);
	
};
