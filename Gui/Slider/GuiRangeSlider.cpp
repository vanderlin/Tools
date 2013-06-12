/*
 *  GuiRangeSlider.cpp
 *  GuiDemo
 *
 *  Created by Todd Vanderlin on 8/12/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiRangeSlider.h"

GuiRangeSlider::GuiRangeSlider() {
	bDrawInfo = true;
	min	  = 0;
	max   = 0;
	offset = defaultGuiStyle.sliderOffset;
    setSize(defaultGuiStyle.sliderW, defaultGuiStyle.sliderH);

    minRect.set(0, 0, defaultGuiStyle.sliderH, defaultGuiStyle.sliderH);
    maxRect.set(defaultGuiStyle.sliderW-defaultGuiStyle.sliderH, 0, defaultGuiStyle.sliderH, defaultGuiStyle.sliderH);
    
    minPtr = NULL;
    maxPtr = NULL;
    
    bOverMin = false;
    bOverMax = false;
    bPressedMin = false;
    bPressedMax = false;
    bIsInt = false;
}

//--------------------------------------------------------------
void GuiRangeSlider::setValue(float newMin, float newMax) {
    if(minPtr) {
        *minPtr = newMin;//MIN(newMin, *maxPtr);
    }
    if(maxPtr) {
        *maxPtr = newMax;//MAX(newMax, *minPtr);
    }
    
    if(maxPtr && minPtr) {
        
        *minPtr = MIN(newMin, *maxPtr);
        *maxPtr = MAX(newMax, *minPtr);

        minRect.x = ofMap(*minPtr, min, max, 0, width-maxRect.width-minRect.width, true);
        maxRect.x = ofMap(*maxPtr, min, max, minRect.width, width-maxRect.width-minRect.width, true);
        
                            //, 0, maxRect.x-maxRect.width);
        
        //minRect.x = ofClamp(ofMap(mx, x, x+width, 0, width-maxRect.width, true), 0, maxRect.x-maxRect.width);
        //*minPtr = ofMap(minRect.x, 0, width-maxRect.width-minRect.width, min, max, true);
        
        //maxRect.x = ofClamp(ofMap(mx, x, x+width, minRect.width, width-maxRect.width, true), minRect.x+minRect.width, width-maxRect.width);
        //*maxPtr = ofMap(maxRect.x, minRect.width+maxRect.width, width-maxRect.width, min, max, true);
    }
}

//--------------------------------------------------------------
void GuiRangeSlider::setMinMaxRange(float min, float max) {
    this->min = min; this->max = max;
}

//--------------------------------------------------------------
void GuiRangeSlider::draw(float px, float py) {
    
	x = px+offset.x;
	y = py+offset.y;
   
    //minRect.setPosition(x+minx-minRect.width, y);
    //maxRect.setPosition(x+maxx+maxRect.width, y);
    
    
	ofFill();
	bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
	ofRect(x, y, width, height);
    
	ofSetColor(style.sliderBarColor);
	
    //ofRect(minx+x, y, minx+maxx, height);
	
    ofFill();
    bOverMin ? ofSetColor(10) : ofSetColor(90, 100);  ofRect((minRect.x+x), minRect.y+y, minRect.width, minRect.height);
    bOverMax ? ofSetColor(10) : ofSetColor(90, 100);  ofRect(maxRect.x+x, maxRect.y+y, maxRect.width, maxRect.height);
    
    ofSetColor(255);
    ofLine(x + minRect.x+minRect.width, y, x + minRect.x+minRect.width, y+height);
    ofLine(x + maxRect.x, y, x + maxRect.x, y+height);
    
    ofSetColor(255, 0 , 0);
    ofDrawBitmapString("a", minRect.x+x, minRect.y+y+8);
    ofDrawBitmapString("b", maxRect.x+x, maxRect.y+y+8);
    
	if(bDrawInfo) {
		float typeOffY = 10;
		ofSetColor(style.textColor);
        string str = name +" "+ ofToString(*minPtr, bIsInt?0:1)+"/"+ofToString(*maxPtr, bIsInt?0:1);
		if(GuiStyle::font.isLoaded()) {
			GuiStyle::font.drawString(str, x+width+13, y+typeOffY);
			//GuiStyle::font.drawString(name, x+5-offset.x, y+typeOffY);
		}
		else {
			ofDrawBitmapString(str, x+width+13, y+typeOffY);
			//ofDrawBitmapString(name, x+5-offset.x, y+typeOffY);
		}
	}
}

//--------------------------------------------------------------
void GuiRangeSlider::mouseMoved(int mx, int my ) {
	bOver = inside(mx, my);
    
    bOverMin = minRect.inside(mx, my);
    bOverMax = maxRect.inside(mx, my);
}

//--------------------------------------------------------------
void GuiRangeSlider::mousePressed(int mx, int my) {
	/*bPressed = inside(mx, my);
	if(bPressed) {
		setValue(ofMap(mx, x, width+x, 0.0, 1.0, true));
	}*/
    
    bPressedMin = minRect.inside(mx-x, my-y);
    bPressedMax = maxRect.inside(mx-x, my-y);
}

//--------------------------------------------------------------
void GuiRangeSlider::mouseDragged(int mx, int my) {
	
    if(bPressedMin) {
        minRect.x = ofClamp(ofMap(mx, x, x+width, 0, width-maxRect.width, true), 0, maxRect.x-maxRect.width);
        *minPtr = ofMap(minRect.x, 0, width-maxRect.width-minRect.width, min, max, true);
    }
    
    if(bPressedMax) {
        maxRect.x = ofClamp(ofMap(mx, x, x+width, minRect.width, width-maxRect.width, true), minRect.x+minRect.width, width-maxRect.width);
        *maxPtr = ofMap(maxRect.x, minRect.width+maxRect.width, width-maxRect.width, min, max, true);
    }
    
}

//--------------------------------------------------------------
void GuiRangeSlider::mouseReleased(int mx, int my) {
    bPressedMax = false;
    bPressedMin = false;
}




