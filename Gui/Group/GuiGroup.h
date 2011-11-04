/*
 *  GuiGroup.h
 *  PeopleTracker
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "GuiElement.h"

#include "GuiSlider.h"
#include "GuiRangeSlider.h"
#include "GuiButton.h"
#include "GuiImage.h"
#include "GuiLabel.h"

enum {
    GUI_OVER_GROUP,
    GUI_PRESSED_GROUP,
    GUI_RELEASED_GROUP,
};

class GuiEventArgs : public ofEventArgs {

    public:
    int type;
};

class GuiGroup : public ofRectangle {

private:
	
	string savepath;
    bool   bEnable;
    bool   bDownInside;
public:
	
    ofEvent <GuiEventArgs>       guiEvents;
	static vector <GuiGroup*>	groups;
	string						name;
	GuiStyle					style;
	vector <GuiElement*>		elements;
	bool						bHide;
	bool                        bDrawFPS;
    static bool					inGroup;
	
	GuiGroup();
    ~GuiGroup();
    
	void setup(string name, float x, float y, float w, float h);
	void draw();
	
	void save();
	void load();
	
	void hide() {bHide = true;  };
	void show() {bHide = false; };
	void toggleView() {bHide = !bHide;}
    void drawFPS(bool bDraw) {bDrawFPS = bDraw; }
    
	//--------------------------------------------------------------
	GuiElement	   * add(GuiElement*e, int type);
	GuiSlider	   * addSlider(string name, float*valuePtr, float min, float max, float initVal=0);
	GuiSlider	   * addSlider(string name, int*valuePtr, float min, float max, int initVal=0);
	GuiButton      * addButton(string name, bool*valuePtr, bool initVal=true, bool isToggle=false);
	GuiRangeSlider * addRangeSlider(string name, float *minPtr, float *maxPtr, float min, float max);
	GuiImage	   * addImage(ofBaseDraws * bd, float drawWidth);
	
    GuiLabel       * addLabel(string name, string * info=NULL);
	GuiLabel       * addLabel(string name, float * value);
	GuiLabel       * addLabel(string name, int   * value);
    
	//--------------------------------------------------------------
	float getBottomPos() { return y+height; }
	bool  getMouseDownInside() {return bDownInside; }
    
    
	//--------------------------------------------------------------
	void registerEvents();
    void enable();
    void disable();
	
	//--------------------------------------------------------------
	void mouseMoved(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);

	// static helper methods
	//--------------------------------------------------------------
	static void saveAllGroups() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->save();
		}
	}
	
	//--------------------------------------------------------------
	static void hideAll() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->hide();
		}
	}
	
	//--------------------------------------------------------------
	static void showAll() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->show();
		}
	}
	
	//--------------------------------------------------------------
	static void toggleAllView() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->toggleView();
		}
	}
	
	
};