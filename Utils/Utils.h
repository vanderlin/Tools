/*
 *  Utils.h
 *  GetFiles
 *
 *  Created by Todd Vanderlin on 7/1/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

static void ofVertex(const ofVec2f &v) {
	ofVertex(v.x, v.y);
}
static void ofSetHexColor(int hexColor, int alpha) {
	int r = (hexColor >> 16) & 0xff;
	int g = (hexColor >> 8) & 0xff;
	int b = (hexColor >> 0) & 0xff;
	ofSetColor(r,g,b, alpha);
}

static ofColor ofRandomColor() {
	return ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}
static ofVec2f ofRandomVec2f(float min=-1, float max=1) {
	return ofVec2f(ofRandom(min, max), ofRandom(min, max));
}
static ofVec3f ofRandomVec3f(float min=-1, float max=1) {
	return ofVec3f(ofRandom(min, max), ofRandom(min, max), ofRandom(min, max));
}

static float ofDist(const ofVec2f &a, const ofVec2f &b) {
    return ofDist(a.x, a.y, b.x, b.y);
}

static void drawDot(float x, float y, float r=3) {
	ofFill();
	ofCircle(x, y, 1);
	ofNoFill();
	ofCircle(x, y, r);
}
static void drawDot(const ofVec2f &p, float r=3) { drawDot(p.x, p.y, r); }
static void printObject(const vector <string> &obj) {
    for (int i=0; i<obj.size(); i++) {
        printf("%s\n", obj[i].c_str());
    }

}

static void ofDot(float x, float y, float z=0) {
    GLfloat pt[] = {x, y, z};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pt);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
}
static void ofDot(ofPoint &p) {
    ofDot(p.x, p.y, p.z);
}


static void drawMouseCoords() {
    ofEnableAlphaBlending();
    ofPushMatrix();
    ofTranslate(ofGetMouseX(), ofGetMouseY());
    ofSetColor(10, 100);
    ofFill();
    ofRect(0, 0, 60, 30);
    ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetMouseX())+","+ofToString(ofGetMouseY()), 10, 10);
    ofPopMatrix();
}

static ofVec2f ofGetMouse() {
    return ofVec2f(ofGetMouseX(), ofGetMouseY());
}
static ofVec2f ofGetMouseNormal() {
    return ofVec2f(ofMap(ofGetMouseX(), 0.0, ofGetWidth(), 0.0, 1.0, true), ofMap(ofGetMouseY(), 0.0, ofGetHeight(), 0.0, 1.0, true));
}

static ofVec2f ofGetCenterScreen() {
    return ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
}

static string ofTruncate(string &str, int max, bool addDotDotDot=true) {
    if(str.length() >= max) {
        str = str.substr(0, max);
        if(addDotDotDot) str += "...";
    }
    return str;
}


static void drawFloor(float w, float h) {
    
    /*
     a     b
     
     x
     
     d     c
     */
    
    ofVec3f a(-w/2, -h/2, 0);
    ofVec3f b(w/2, -h/2, 0);
    ofVec3f c(w/2, h/2, 0);
    ofVec3f d(-w/2, h/2, 0);
    glBegin(GL_QUADS);
    glVertex3fv(&a[0]); glVertex3fv(&b[0]);
    glVertex3fv(&c[0]); glVertex3fv(&d[0]);
    glEnd();
    
}


static void drawGrid(float w, float h, int numCols=10, int numRows=10) {
    
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    ofRotateX(90);
    int gw = w;
    int gh = h;
    int nc = numCols;
    int nr = numRows;
    for (int i=0; i<nc; i++) {
        float x = ofMap(i,0,nc,-gw/2,(float)gw/2);
        ofLine(x, -gh/2, x, gh/2);
        for (int j=0; j<nr; j++) {
            float y = ofMap(j,0,nr,-gh/2,(float)gh/2);
            ofLine(-gw/2, y, gw/2, y);
        }
    }
    
    
    ofNoFill();
    ofRect(-gw/2, -gh/2, gw, gh);
    ofPopMatrix();
    
    
}

//-------------------------------------------------------------- (this may be making a bug)!!!
static void readDirectory(string path, vector<ofFile>&files, vector<string>allowedExt) {	
	
    ofDirectory dir;
	int nItems = dir.listDir(path);
    int MAX_FILES = 1000;
    
	if(nItems > 0) {
		for (int i=0; i<nItems; i++) {
			if(dir.getFile(i).isDirectory()) {
				readDirectory(dir.getPath(i), files, allowedExt);
			}
			else if(dir.getFile(i).isFile()) {
				if(files.size() >= MAX_FILES) return;
				ofFile f = dir.getFile(i);
                bool bAdd = false;
                for (int k=0; k<allowedExt.size(); k++) {
                    if(f.getExtension() == allowedExt[k]) bAdd = true;
                }
                if(bAdd) files.push_back(f);                
			}
		}
	}
}
static void readDirectory(string path, vector<ofFile>&files, string allowedExt) {	
    vector<string> ext = ofSplitString(allowedExt, ",");
    readDirectory(path, files, ext);
}

//--------------------------------------------------------------
class Utils {

    static map <string, ofPoint*>   pntData;
    static map <string, float*>     floatData;
    
public:
	
	//--------------------------------------------------------------
	static void saveWindowPosition();
	static void loadWindowPosition();
	
	static void             saveData(string file, string data);
	static string           loadData(string file);
	static vector <string>  loadDataArray(string file);

    //--------------------------------------------------------------
    static void     addPoint(string name, ofPoint * pt);
    static void     addFloat(string name, float * f);

    static ofPoint  getPoint(string name);
    static float    getFloat(string name);
    
	static void loadAppSettings(string file="settings.txt");
    static void saveAppSettings(string file="settings.txt");
    
	//--------------------------------------------------------------
	static void pushMask(ofRectangle &r);
	static void pushMask(float x, float y, float width, float height);
	static void popMask();

	//--------------------------------------------------------------
	static void drawArrow(float x, float y, float w, float h, float angle=0);
	static void drawArrow(ofVec2f &p, float w, float h, float angle=0);
	static void drawGrid(float w, float h);
	
	//--------------------------------------------------------------
	static void savePoints(vector <ofVec2f> &pts, string file);
	static vector <ofVec2f> loadPoints(string file);
	
	static void savePolyPoints(vector <ofPolyline> &pts, string file);
	static vector <ofPolyline> loadPolyPoints(string file);
	
	static void drawRect3d(float x, float y, float w, float h, float d) {
		ofPushMatrix();
		ofTranslate(x, y);
		// bottom
		/*
		glBegin(GL_QUADS);
		glVertex3f(-w/2, 0, -w/2);
		glVertex3f(w/2, 0, -w/2);
		glVertex3f(w/2, 0, w/2);
		glVertex3f(-w/2, 0, w/2);
		glEnd();*/
		
		/*glBegin(GL_QUADS);
		glVertex3f(-w/2, -h/2, -d/2);
		glVertex3f(w/2, -h/2, -d/2);
		glVertex3f(w/2, h/2, d/2);
		glVertex3f(-w/2, h/2, d/2);
		glEnd();*/
		ofPopMatrix();
	}
	
    //--------------------------------------------------------------
    static void findAndReplace(string &haystack, string needle, string replace) {

        size_t findLen = needle.length();
        size_t replaceLen = replace.length();
        size_t pos = 0;
        while ((pos = haystack.find( needle, pos)) != std::string::npos) {
            haystack.replace( pos, findLen, replace );
            pos += replaceLen;
        }
    
    }
    
    
};



//--------------------------------------------------------------
class DragPoint : public ofVec3f {
    public :
    
    bool bInside;
    bool bPressed;
    
    DragPoint() {
        bInside  = false;
        bPressed = false;
    }
    
    bool inside(float px, float py, float mindis) {
        bInside = ofDist(px, py, x, y) < mindis;
        return bInside;  
    }
    bool mouseInside(float mindis) {
        return inside(ofGetMouseX(), ofGetMouseY(), mindis);
    }
    
    void dragged(float px, float py) {
        if(bPressed) {
            set(px, py);
        }
    }
    void pressed(float px, float py, float mindis) {
        bPressed = inside(px, py, mindis);
    }
    void release() {
        bInside = false;
    }
};

















