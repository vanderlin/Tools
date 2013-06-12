/*
 *  Utils.cpp
 *  GetFiles
 *
 *  Created by Todd Vanderlin on 7/1/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "Utils.h"

//--------------------------------------------------------------
void Utils::saveWindowPosition(string filename) {
	ofstream f;
	f.open(ofToDataPath(filename).c_str());
	f << ofGetWindowPositionX() << "," << ofGetWindowPositionY();
	f.close();
}

//--------------------------------------------------------------
void Utils::loadWindowPosition(string filename) {
	ifstream f;
	f.open(ofToDataPath(filename).c_str());
	string winstr;
	if(f!=0) {
		while (!f.eof()) {
			getline(f, winstr);
		}
		f.close();
		vector <string> p = ofSplitString(winstr, ",");
		if(p.size() >= 2) {
			ofSetWindowPosition(ofToInt(p[0]), ofToInt(p[1]));
		}
	}
}

//--------------------------------------------------------------
void Utils::pushMask(ofRectangle &r) {
	Utils::pushMask(r.x, r.y, r.width, r.height);
}
void Utils::pushMask(float x, float y, float width, float height) {
    ofPushMatrix();
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, (ofGetHeight()-(y+height)), width, height);
}

void Utils::popMask() {
	glDisable(GL_SCISSOR_TEST);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Utils::drawArrow(float x, float y, float w, float h, float angle) {
	ofPushMatrix();
	ofTranslate(x, y);
	ofRotateZ(angle-90);
	ofTriangle(-w/2, -h/2, 0, h/2, w/2, -h/2);
	ofPopMatrix();
}
void Utils::drawArrow(ofVec2f &p, float w, float h, float angle) {
	Utils::drawArrow(p.x, p.y, w, h, angle);
}
/*
//--------------------------------------------------------------
void Utils::savePolyPoints(vector <ofPolyline> &pts, string file) {
	ofstream f;
	f.open(ofToDataPath(file).c_str());
	for (int i=0; i<pts.size(); i++) {
		for (int j=0; j<pts[i].size(); j++) {
			f << pts[i][j].x << "," << pts[i][j].y;
			if(j != pts[i].size()-1)  f << ",";
		}
		if(i!=pts.size()-1) f << "|";
	}
	f.close();
}

//--------------------------------------------------------------
vector <ofPolyline> Utils::loadPolyPoints(string file) {
	ifstream f;
	f.open(ofToDataPath(file).c_str());
	
	string				str;
	vector <ofPolyline> pts;
	
	if(f!=0) {
		
		while (!f.eof()) {
			getline(f, str);
		}
		
		vector <string> lines = ofSplitString(str, "|");
		if(lines.size() > 0) {
			for (int i=0; i<lines.size(); i++) {
				vector <string> p = ofSplitString(lines[i], ",");
				if(p.size() >= 2) {
					pts.push_back(ofPolyline());
					for (int j=0; j<p.size(); j+=2) {
						pts.back().addVertex(ofToFloat(p[j]), ofToFloat(p[j+1]));
					}
				}
			}
		}
		
		f.close();
	}
	
	return pts;
}*/

//--------------------------------------------------------------
void Utils::drawGrid(float w, float h) {
	int nRows = 30;
	int nCols = 30;
	for (int i=0; i<nRows; i++) {
		for (int j=0; j<nCols; j++) {
			float x = ofMap(i, 0.0, nRows-1, 0.0, w);
			float y = ofMap(j, 0.0, nCols-1, 0.0, h);
			ofSetColor(255);
			ofLine(x, 0, x, h);
			ofLine(0, y, w, y);
		}
	}
	
}



