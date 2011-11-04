/*
 *  GuiMoviePlayer.h
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "GuiElement.h"
#include "GuiSlider.h"
#include "GuiButton.h"

class GuiMoviePlayer : public GuiElement {
	
private:
	
	float ratio;
	void drawArrow();
	void drawPause();
	ofVideoPlayer * player;
public:
	
	//--------------------------------------------------------------
	GuiMoviePlayer();
	GuiSlider prgSlider;
	GuiButton playPauseBtn;
	
	void draw(float px, float py);
	void setWidth(float w);
	void setPlayer(ofVideoPlayer * player);
	
	//--------------------------------------------------------------
	void mouseMoved(int mx, int my );
	void mouseDragged(int mx, int my);
	void mousePressed(int mx, int my);
	void mouseReleased(int mx, int my);
	
};