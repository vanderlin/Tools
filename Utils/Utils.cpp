/*
 *  Utils.cpp
 *  GetFiles
 *
 *  Created by Todd Vanderlin on 7/1/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "Utils.h"

map <string, ofPoint*>  Utils::pntData;
map <string, float*>    Utils::floatData;


//--------------------------------------------------------------
void Utils::saveWindowPosition() {
	ofstream f;
	f.open(ofToDataPath("windowpos.txt").c_str());
	f << ofGetWindowPositionX() << "," << ofGetWindowPositionY();
	f.close();
}

//--------------------------------------------------------------
void Utils::loadWindowPosition() {
	ifstream f;
	f.open(ofToDataPath("windowpos.txt").c_str());
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
void Utils::addPoint(string name, ofPoint * pt) {
    pntData[name] = pt;
}

void Utils::addFloat(string name, float * f) {
    floatData[name] = f;  
}



ofPoint Utils::getPoint(string name) {
  return ofPoint(*pntData[name]);
}
float Utils::getFloat(string name) {
    return *floatData[name];
}

//--------------------------------------------------------------
void Utils::loadAppSettings(string file) {
    
    ifstream f;
	f.open(ofToDataPath(file).c_str());
	string winstr;
	if(f!=0) {
        int lineNum = 0;
		while (!f.eof()) {
            string line;
			getline(f, line);
            
            // each line is a type 
            // 0 = points
            // 1 = floats
            
            vector<string> objs = ofSplitString(line, "*");
            for(int i=0; i<objs.size(); i++) {
                
                vector<string> obj = ofSplitString(objs[i], "|");
                if(obj.size() >= 2) {
                    
                    string name = obj[0];
                    vector<string>vals = ofSplitString(obj[1], ",");
                    ofPoint v;
                    for(int j=0; j<vals.size(); j++) {
                        v[j] = ofToFloat(vals[j]);
                    }
                    
                    if(lineNum == 0 &&  pntData[name]) pntData[name]->set(v);
                    if(lineNum == 1)                  *floatData[name] = v.x;
                }

            }
            
            lineNum ++;
		}
		f.close();
        
	}
    
}


//--------------------------------------------------------------
void Utils::saveAppSettings(string file) {
    ofstream f;
	f.open(ofToDataPath(file).c_str());
    
    
    // points
    map<string, ofPoint*>::iterator pntIter;
    
    for(pntIter = pntData.begin(); pntIter != pntData.end(); pntIter++) {
        if(pntIter->second) {
            cout << pntIter->second->x << endl;
            f << pntIter->first << "|";
            f << ofToString(pntIter->second->x) << "," << ofToString(pntIter->second->y) << "," << ofToString(pntIter->second->z) << "*";
        }
    }
    
    f << endl;

    // floats
    map<string, float*>::iterator floatItr;
    
    for(floatItr = floatData.begin(); floatItr != floatData.end(); floatItr++) {
        float val = *floatItr->second;
        f << floatItr->first << "|";
        f << ofToString(val) << "*";
    }
    
	f.close();
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


//--------------------------------------------------------------
void Utils::savePoints(vector <ofVec2f> &pts, string file) {
	ofstream f;
	f.open(ofToDataPath(file).c_str());
	for (int i=0; i<pts.size(); i++) {
		f << pts[i].x << "," << pts[i].y;
		if(i != pts.size()-1)  f << ",";
	}
	f.close();
}

//--------------------------------------------------------------
vector <ofVec2f> Utils::loadPoints(string file) {
	ifstream f;
	f.open(ofToDataPath(file).c_str());
	string str;
	vector <ofVec2f> pts;
	
	if(f!=0) {
		while (!f.eof()) {
			getline(f, str);
		}
		f.close();
		vector <string> p = ofSplitString(str, ",");
		for (int i=0; i<p.size(); i+=2) {
			pts.push_back(ofVec2f(ofToFloat(p[i]), ofToFloat(p[i+1])));
		}
	}
	
	return pts;
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
void Utils::saveData(string file, string data) {
	ofstream f;
	f.open(ofToDataPath(file).c_str());
	f << data;
	f.close();
}

//--------------------------------------------------------------
string Utils::loadData(string file) {
	ifstream f;
	f.open(ofToDataPath(file).c_str());
	string str;
	if(f!=0) {
		while (!f.eof()) {
			getline(f, str);
		}
		f.close();
	}	
	return str;
}

//--------------------------------------------------------------
vector <string> Utils::loadDataArray(string file) {
    vector <string> lines;
	ifstream f;
	f.open(ofToDataPath(file).c_str());
	if(f!=0) {
		while (!f.eof()) {
            string str;
			getline(f, str);
            lines.push_back(str);
		}
		f.close();
	}	
	return lines;
}



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



