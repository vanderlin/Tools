//
//  GuiLabel.h
//  emptyExample
//
//  Created by Todd Vanderlin on 10/23/11.
//  Copyright (c) 2011 vanderlin.cc. All rights reserved.
//


#pragma once
#include "GuiElement.h"

class GuiLabel : public GuiElement {
	
public:
	
    string * infoPtr;
    float  * valuePtrF;
    int    * valuePtrI;
	//--------------------------------------------------------------
	GuiLabel();
	void draw(float px, float py);
	void draw();
        
    
    //--------------------------------------------------------------
    // not used
    void mouseMoved(int mx, int my )  {};
    void mouseDragged(int mx, int my) {};
    void mousePressed(int mx, int my)      {};

};