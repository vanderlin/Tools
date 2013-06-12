/*
 *  GuiElement.h
 *  PeopleTracker
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "GuiStyle.h"

// types
enum {
	GUI_SLIDER,
	GUI_RANGE_SLIDER,
	GUI_BUTTON,
	GUI_MOVIE_PLAYER,
	GUI_IMAGE,
    GUI_LABEL,
    GUI_CHECKBOX
};

// default...
extern GuiStyle defaultGuiStyle;

class GuiElement : public ofRectangle {

public:
	
	GuiStyle	style;
	bool		bOver;
	bool		bPressed;
    bool        bUseLabel;
	int			type;
	string		name;
	ofVec2f		offset;

	GuiElement()  {
		style	  = defaultGuiStyle;
		bOver	  = false;
		bPressed  = false;
        bUseLabel = true;
	};
	
	void setSize(float w, float h) {
		width = w; height = h;
	}
	
	~GuiElement()		{};
	virtual void draw(float px, float py)	{}
	virtual void load()						{}
	virtual void save()						{}
	
	virtual void mouseMoved(int mx, int my )  = 0;
	virtual void mouseDragged(int mx, int my) = 0;
	virtual void mousePressed(int mx, int my) = 0;
	virtual void mouseReleased(int mx=0, int my=0) {
		bOver	 = false;
		bPressed = false;
	}
};
