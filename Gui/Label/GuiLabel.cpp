//
//  GuiLabel.cpp
//  emptyExample
//
//  Created by Todd Vanderlin on 10/23/11.
//  Copyright (c) 2011 vanderlin.cc. All rights reserved.
//

#include "GuiLabel.h"
#include "Utils.h"

GuiLabel::GuiLabel() {
    infoPtr   = NULL;
    valuePtrI = NULL;
    valuePtrF = NULL;
    setSize(defaultGuiStyle.buttonW, defaultGuiStyle.buttonH);
}

void GuiLabel::draw(float px, float py) {

    bool bTruncate = true;
    x = px;
	y = py;// + cy) + style.buttonOffset.y;
	
    string info = " ";
    if(infoPtr != NULL) {
        info += (*infoPtr);    
        info = ofGetConcatenatedString(info, 20);
    }
    
    if(valuePtrF != NULL) {
        float v = (*valuePtrF);
        info += ofToString(v);
    }
    if(valuePtrI != NULL) {
        int v = (*valuePtrI);
        info += ofToString(v);
    }
    
    if(GuiStyle::font.isLoaded()) {
        ofSetColor(style.textColor);
        GuiStyle::font.drawString(name+info, x+width, (y+8));
    }
    else {
        ofSetColor(style.textColor);
        ofDrawBitmapString(name+info, x+width, (y+8));
    }
       
}
void GuiLabel::draw() {
    draw(x, y);
}
