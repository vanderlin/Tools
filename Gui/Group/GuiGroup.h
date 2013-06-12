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
#include "GuiCheckBox.h"

enum {
    GUI_OVER_GROUP,
    GUI_PRESSED_GROUP,
    GUI_RELEASED_GROUP,
    GUI_VALUE_CHANGED
};

class GuiEventArgs : public ofEventArgs {

    public:
    int type;
    GuiElement * object;
    GuiEventArgs() {
        object = NULL;
    }
};

class GuiGroup : public ofRectangle {

private:
	
	string savepath;
    bool   bEnable;
    bool   bDownInside;
public:
	
    ofEvent <GuiEventArgs>      guiEvents;
	static vector <GuiGroup*>	groups;
	string						name;
	GuiStyle					style;
	vector <GuiElement*>		elements;
	bool						bHide;
	bool                        bDrawFPS;
    bool                        inGroup;
	static bool                 inAGroup;
    
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
	GuiRangeSlider * addRangeSlider(string name, float *minPtr, float *maxPtr, float min, float max, float defaultMin=0, float defaultMax=1, bool isInt=false);
	GuiImage	   * addImage(ofBaseDraws * bd, float drawWidth);
	GuiCheckBox    * addCheckBox(string name, map <string, int> &boxes, int *value, int initVal=0);
    GuiLabel       * addLabel(string name, string * info=NULL);
	GuiLabel       * addLabel(string name, float * value);
	GuiLabel       * addLabel(string name, int   * value);
    
	//--------------------------------------------------------------
	float getBottomPos() { return y+height; }
	bool  getMouseDownInside() {return bDownInside; }
    float getHeight() const {
        float gy		  = 14 + 8;
        float spaceH = defaultGuiStyle.spaceH;
        for (int i=0; i<elements.size(); i++) {
            GuiElement * e = elements[i];
            if(e->type == GUI_CHECKBOX) {
                GuiCheckBox * cb = (GuiCheckBox*)e;
                spaceH = cb->getHeight() + 5;
            }
            else spaceH = defaultGuiStyle.spaceH;
            gy += spaceH;
        }
        //height = gy; // auto resize (toggle?)
        return gy;
    }
    
	//--------------------------------------------------------------
    void loadDefaultFont();
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
	static void drawAllGroups() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->draw();
		}
	}
    
    //--------------------------------------------------------------
	static void loadAllGroups() {
		for(int i=0; i<GuiGroup::groups.size(); i++) {
			GuiGroup::groups[i]->load();
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
	
	static bool insideGroup(int x, int y) {
        
        bool mouseInsideGroup = false;
        for(int i=0; i<GuiGroup::groups.size(); i++) {
            if((GuiGroup::groups[i]->inside(x, y) && !GuiGroup::groups[i]->bHide) || GuiGroup::groups[i]->bDownInside) {
                mouseInsideGroup = true;
                break;
            }
        }
        return mouseInsideGroup;
    }
};