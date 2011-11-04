/*
 *  GuiImage.cpp
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/14/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiImage.h"

GuiImage::GuiImage() {
	ratio = 1.0;
	image = NULL;
	setSize(defaultGuiStyle.vidW, defaultGuiStyle.vidH);
}

//--------------------------------------------------------------
void GuiImage::setImage(ofBaseDraws * bd) {
	if(bd) {
		image = bd;
		ratio = bd->getHeight() / bd->getWidth();
		printf("r:%f - %f/%f\n", ratio, bd->getWidth(), bd->getHeight());
	}
}

//--------------------------------------------------------------
void GuiImage::setWidth(float w) {
	width  = w;
	height = w * ratio;
	printf("%f %f\n", width, height);
	setSize(width, height);	
}

//--------------------------------------------------------------
void GuiImage::draw(float px, float py) {
	ofSetColor(255);
	if(image) image->draw(px, py, width, height);
}

//--------------------------------------------------------------
void GuiImage::mouseMoved(int mx, int my) {
}
void GuiImage::mouseDragged(int mx, int my) {
}
void GuiImage::mousePressed(int mx, int my) {
}
void GuiImage::mouseReleased(int mx, int my) {
}
