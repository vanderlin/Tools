//
//  GuiCheckBox.h
//  Gui
//
//  Created by Todd Vanderlin on 2/1/13.
//
//

#pragma once

#include "GuiElement.h"
#include "GuiButton.h"

class CheckBox : public ofRectangle {
public:
    int value;
    string name;
    bool bOver;
    bool bPressed;
    CheckBox(string boxName, int boxValue) {
        name = boxName;
        value = boxValue;
        bOver = false;
        bPressed = false;
    }
};

class GuiCheckBox : public GuiElement {
	
public:
	
    vector <CheckBox> boxes;
    int * valuePtr;
    string selectedBoxName;
    
	//--------------------------------------------------------------
	GuiCheckBox();
	void draw(float px, float py);
	void draw();
    
	void  mousePressed(int mx, int my);
	void  mouseDragged(int mx, int my);
	void  mouseMoved(int mx, int my );
	
	//--------------------------------------------------------------
    void addBox(string name, int value);
    void selectBox(int value);
    int  getSelectedBox();
    float getHeight() const;
    
	//void setValue(bool val);
	//bool getValue();
};