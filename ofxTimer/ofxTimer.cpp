/***********************************************************************
 
 Copyright (c) 2009, Todd Vanderlin, www.vanderlin.cc
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

#include "ofxTimer.h"

ofxTimer::ofxTimer() {
	bUpdateSetup = false;
}

ofxTimer::~ofxTimer() {
	printf("*** Timer Destroyed ***\n");
}

// ---------------------------------------

void ofxTimer::setup(float millSeconds, bool loopTimer) {
	
	count		= 0;
	bLoop		= loopTimer;
	bPauseTimer = false;
	
	//timer
	bStartTimer = true;
	delay		= millSeconds;	// mill seconds
	setupDelay	= delay;
	timer		= 0;
	timerStart	= 0;
	
	//events
	if(!bUpdateSetup) {
        ofAddListener(ofEvents.update, this, &ofxTimer::update);
        bUpdateSetup = false;
    }
}

// ---------------------------------------
void ofxTimer::reset() {
	count = 0;
	timer = 0;
	timerStart = 0;
	delay = setupDelay;
	bStartTimer = false;
}

// ---------------------------------------
void ofxTimer::loop(bool b) {
	bLoop = b;
}

// ---------------------------------------
void ofxTimer::update(ofEventArgs &e) {
	if(!bPauseTimer) {
		if(bStartTimer) {
			bStartTimer = false;
			timerStart  = ofGetElapsedTimef();
		}
		
		float time = ofGetElapsedTimef() - timerStart;
		time *= 1000.0;		
		if(time >= delay) {
			count ++;
			if(!bLoop) bPauseTimer = true;
			bStartTimer = true;
			static ofxTimerEventArgs timerEventArgs;
			ofNotifyEvent(events, timerEventArgs, this);
        }
	}
}

// ---------------------------------------
void ofxTimer::setTimer(float millSeconds) {
	delay = millSeconds;
}

void ofxTimer::start() {
	bPauseTimer = false;
}

void ofxTimer::stop() {
	bPauseTimer = true;
}