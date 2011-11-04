/*
 *  GuiMoviePlayer.cpp
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/13/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "GuiMoviePlayer.h"


GuiMoviePlayer::GuiMoviePlayer() {
	player = NULL;
	setSize(defaultGuiStyle.vidW, defaultGuiStyle.vidH);
}

//--------------------------------------------------------------
void GuiMoviePlayer::setPlayer(ofVideoPlayer * player) {
	this->player = player;	
	if(player) {
		player->play();
		
		prgSlider.setMinMax(0.0, 1.0);
		prgSlider.offset.set(20, 2);
		prgSlider.setSize(width-25, 12);
		prgSlider.bDrawInfo = false;
		
		ratio = (float)player->height / (float)player->width;
		playPauseBtn.setSize(8, 8);
	}
}

//--------------------------------------------------------------
void GuiMoviePlayer::setWidth(float w) {
	width  = w;
	height = w * ratio;
	
	prgSlider.setSize(width-25, 12);
}

//--------------------------------------------------------------
void GuiMoviePlayer::draw(float px, float py) {
	
	// maybe move this to a update...	
	if(!prgSlider.bPressed) prgSlider.setValue(player->getPosition());
	
	// drawing...
	ofSetColor(255);
	ofEnableAlphaBlending();

	x = px; y = py;
	if(player) {
		player->draw(x, y, width, height);
	}
	
	ofFill();
	ofSetColor(style.groupBackground);
	ofRect(x, y+height, width, 20);
	
	prgSlider.draw(x, y+height+1);
	

	playPauseBtn.x = x+5+5;
	playPauseBtn.y = y + height + 4 + 5;
	player->isPaused() ? drawPause() : drawArrow();	
	//playPauseBtn.draw();
	//ofNoFill();
	//ofCircle(playPauseBtn.x, playPauseBtn.y, playPauseBtn.width);
}

//--------------------------------------------------------------
void GuiMoviePlayer::drawArrow() {
	float w = 10;
	float h = 10;
	float ax = playPauseBtn.x;
	float ay = playPauseBtn.y;
	ofFill();
	playPauseBtn.bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
	ofPushMatrix();
	ofTranslate(ax, ay);
	ofRotateZ(-90);
	ofTriangle(-w/2, -h/2, 0, h/2, w/2, -h/2);
	ofPopMatrix();
}

//--------------------------------------------------------------
void GuiMoviePlayer::drawPause() {
	float w = 10;
	float h = 10;
	float ax = playPauseBtn.x;
	float ay = playPauseBtn.y;
	ofFill();
	playPauseBtn.bOver ? ofSetColor(style.baseHoverColor) : ofSetColor(style.baseColor);	
	ofPushMatrix();
	ofTranslate(ax, ay);
	ofRect(-w/2, -h/2, 3, h);
	ofRect(2, -h/2, 3, h);
	ofPopMatrix();
}



//--------------------------------------------------------------
void GuiMoviePlayer::mouseMoved(int mx, int my ) {
	prgSlider.mouseMoved(mx, my);
	playPauseBtn.mouseMoved(mx, my);
}
void GuiMoviePlayer::mouseDragged(int mx, int my) {
	prgSlider.mouseDragged(mx, my);
	
	if(prgSlider.bPressed && player) {
		player->setPaused(true);
		player->setPosition(prgSlider.getValue());
	}
}
void GuiMoviePlayer::mousePressed(int mx, int my) {
	prgSlider.mousePressed(mx, my);
	playPauseBtn.mousePressed(mx, my);
	
	if(prgSlider.bPressed && player) {
		player->setPosition(prgSlider.getValue());
	}
	
	if(playPauseBtn.bPressed) player->setPaused(playPauseBtn.value);
}
void GuiMoviePlayer::mouseReleased(int mx, int my) {
	if(!player) return;
	prgSlider.mouseReleased(mx, my);
	player->setPaused(playPauseBtn.value);
	playPauseBtn.mouseReleased(mx, my);
}




















