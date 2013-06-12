//
//  GuiCheckBox.cpp
//  Gui
//
//  Created by Todd Vanderlin on 2/1/13.
//
//

#include "GuiCheckBox.h"


//--------------------------------------------------------------
GuiCheckBox::GuiCheckBox() {
    valuePtr = NULL;
    selectedBoxName = "None";
    setSize(defaultGuiStyle.buttonW, defaultGuiStyle.buttonH);
}

//--------------------------------------------------------------
void GuiCheckBox::draw(float px, float py) {
    
    float rightOff = offset.x;
	float cx = width;
	float cy = 0;//defaultGuiStyle.sliderH-height;
    float by = 20;
    
	x = (px+style.buttonOffset.x);
	y = (py + cy) + style.buttonOffset.y;

    // title of check boxes
    if(bUseLabel) {
        string titleStr = name + " : " + selectedBoxName;
        
        if(GuiStyle::font.isLoaded()) {
            ofSetColor(style.textColor);
            GuiStyle::font.drawString(titleStr, x, (y+8)-cy);
        }
        else {
            ofSetColor(style.textColor);
            ofDrawBitmapString(titleStr, x, (y+8)-cy);
        }
    }
    
    for(int i=0; i<boxes.size(); i++) {
        
        boxes[i].set(x, by + y, defaultGuiStyle.buttonW, defaultGuiStyle.buttonH);
        
        ofFill();
        boxes[i].bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);
        ofRect(boxes[i]);
        
        if(boxes[i].bPressed) {
            ofSetColor(style.sliderBarColor);
            ofLine(x, y+by, x+boxes[i].width, y+by+boxes[i].height);
            ofLine(x+boxes[i].width, y+by, x, by+y+boxes[i].height);
        }
        /*if(value) {
            ofSetColor(style.sliderBarColor);
            ofLine(x, y, x+width, y+height);
            ofLine(x+width, y, x, y+height);
        }*/
        
        // title
        if(bUseLabel) {
            if(GuiStyle::font.isLoaded()) {
                ofSetColor(style.textColor);
                GuiStyle::font.drawString(boxes[i].name, x+width+10, by + (y+8)-cy);
            }
            else {
                ofSetColor(style.textColor);
                ofDrawBitmapString(boxes[i].name, x+width+10, by + (y+8)-cy);
            }
        }
        
        by += defaultGuiStyle.buttonH + 5;
    }
    
    height = by;
}

//--------------------------------------------------------------
float GuiCheckBox::getHeight() const {
    float by = 20;
    for(int i=0; i<boxes.size(); i++) {
        by += defaultGuiStyle.buttonH + 5;
    }
    return by;
}

//--------------------------------------------------------------
void GuiCheckBox::draw() {
    draw(x, y);
}

//--------------------------------------------------------------
void GuiCheckBox::addBox(string name, int value) {
    boxes.push_back(CheckBox(name, value));
    boxes.back().set(0, 0, defaultGuiStyle.buttonW, defaultGuiStyle.buttonH);
}

//--------------------------------------------------------------
int GuiCheckBox::getSelectedBox() {
    return *valuePtr;
}

//--------------------------------------------------------------
void GuiCheckBox::selectBox(int value) {
    
    for(int i=0; i<boxes.size(); i++) {
        if(boxes[i].value == value) {
            boxes[i].bPressed = true;
            selectedBoxName = boxes[i].name;
            *valuePtr = boxes[i].value;
        }
        else {
            boxes[i].bPressed = false;
        }
    }

}

//--------------------------------------------------------------
void GuiCheckBox::mousePressed(int mx, int my) {
    int pressedSomethingIndex = -1;
    
    for(int i=0; i<boxes.size(); i++) {
        if(boxes[i].inside(mx, my)) {
            pressedSomethingIndex = i;
        }
    }
    if(pressedSomethingIndex != -1) {
        for(int i=0; i<boxes.size(); i++) {
            if(pressedSomethingIndex == i) {
                boxes[i].bPressed = true;
                selectedBoxName = boxes[i].name;
                *valuePtr = boxes[i].value;
            }
            else boxes[i].bPressed = false;
        }
    }
}

//--------------------------------------------------------------
void GuiCheckBox::mouseDragged(int mx, int my) {}

//--------------------------------------------------------------
void GuiCheckBox::mouseMoved(int mx, int my )  {
    for(int i=0; i<boxes.size(); i++) {
        boxes[i].bOver = boxes[i].inside(mx, my);
    }
}




