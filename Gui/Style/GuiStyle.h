/*
 *  GuiStyle.h
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/14/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"


class GuiStyle {
public:
	
	inline GuiStyle();
	int		sliderW;
	int		sliderH;
	
	int		buttonW;
	int		buttonH;
	
	int		vidW, vidH;
	
	int		spaceH;
	ofColor	groupBackground;
	ofColor baseColor, baseHoverColor;
	ofColor sliderBarColor;
	ofColor textColor;

	ofColor	headerColor;
	ofColor	headerTextColor;
	ofVec2f sliderOffset;
    ofVec2f buttonOffset;
	ofVec2f typeOffset;
    ofVec2f labelOffset;
    bool    bDrawName;
    
	static ofTrueTypeFont font;
};



// defaults...
GuiStyle::GuiStyle() {
	
    bDrawName = true;
	spaceH  = 22;
	
	sliderW = 120;
	sliderH = 10;
	
	buttonW = 10;
	buttonH = 10;
	
	vidW	= 320/2;
	vidH	= 240/2;
	
	baseColor.setHex(0x2b2d2d);
	baseHoverColor.setHex(0x1b3c4b);
	groupBackground.setHex(0x184b68, 180);//0xf4f4f4, 240);
	sliderBarColor.setHex(0xb9cf7d);
	
	textColor.setHex(0xeaf7f7);
	headerColor.setHex(0xa3daea);
	headerTextColor.setHex(0x3d4747);	
	
    typeOffset.set(10, 8);
	sliderOffset.set(85, 0);
    buttonOffset.set(10, 0);
    labelOffset.set(0, 0);
}