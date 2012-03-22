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

static float inToPx(float v) {
    return v * 72.0; 
}

static void ofVertex(const ofVec2f &v) {
	ofVertex(v.x, v.y);
}
static void ofSetHexColor(int hexColor, int alpha) {
	int r = (hexColor >> 16) & 0xff;
	int g = (hexColor >> 8) & 0xff;
	int b = (hexColor >> 0) & 0xff;
	ofSetColor(r,g,b, alpha);
}

static float ofXeno(float val, float target, float amt) {
    return (amt * target) + ((1.0f - amt) * val);
}

// ------------------------------------------------
// Totally ripper from the Hodge!
// ------------------------------------------------
static float getRads(float val1, float val2, float mult, float div) {
	float minNoise = 0.499;
	float maxNoise = 0.501;
	float counter = 0;
	
    float rads = ofNoise(val1/div, val2/div, counter/div);
    
    if (rads < minNoise) minNoise = rads;
    if (rads > maxNoise) maxNoise = rads;
    
    rads -= minNoise;
    rads *= 1.0/(maxNoise - minNoise);
    
    return rads * mult;
}

//--------------------------------------------------------------
static ofVec3f getNoiseForce( const ofVec3f& a_loc, float a_mult, float a_off ) {
	ofVec3f frc(ofSignedNoise(a_loc.x * a_mult, a_loc.z * a_mult, a_off),
				ofSignedNoise(a_loc.y * a_mult, a_loc.x * a_mult, a_off),
				ofSignedNoise(a_loc.x * a_mult, a_loc.y * a_mult, a_off));
	return frc;
}

//--------------------------------------------------------------
// Random
//--------------------------------------------------------------
static ofColor ofRandomColor() {
	return ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}
static ofVec2f ofRandomVec2f(float min=-1, float max=1) {
	return ofVec2f(ofRandom(min, max), ofRandom(min, max));
}
static ofVec3f ofRandomVec3f(float min=-1, float max=1) {
	return ofVec3f(ofRandom(min, max), ofRandom(min, max), ofRandom(min, max));
}

// ------------------------------------------------
// Helpers
// ------------------------------------------------
static float ofDist(const ofVec2f &a, const ofVec2f &b) {
    return ofDist(a.x, a.y, b.x, b.y);
}

// ------------------------------------------------
static float isPointInScreen(const ofVec2f &pt, float padding=0) {
    ofRectangle screen(-padding, -padding, ofGetWidth()+(padding*2), ofGetHeight()+(padding*2)); 
    return screen.inside(pt);
}
/*
static float isPointInScreen(float x, float y, float padding=0) {
    return isPointInScreen(x, y);
}*/

static ofVec2f ofRandomPointInRect(float x, float y, float w, float h, float padding=0) {
    float rx = ofRandom(x+padding, x+(w-padding*2));
    float ry = ofRandom(y+padding, y+(h-padding*2));
    return ofVec2f(rx, ry);
}
static ofVec2f ofRandomPointInRect(const ofRectangle &r, float padding=0) {
    return ofRandomPointInRect(r.x, r.y, r.width, r.height, padding);
}

static ofVec2f ofRandomPointInCircle(float x, float y, float radius, float padding=0) {
    float r = ofRandom(radius);
    float n = ofRandomuf();
    r-= padding;
    return ofVec2f(x + (cos(n*TWO_PI) * r), y + (sin(n*TWO_PI) * r));
}
static ofVec2f ofRandomPointInCircle(const ofVec2f &pt, float radius, float padding=0) {
    return ofRandomPointInRect(pt.x, pt.y, radius, padding);
}


//--------------------------------------------------------------
// Utils
//--------------------------------------------------------------
template<class T>
static int ofRandomIndex(vector<T>&items) {
    if(items.size()==0) return -1;
    return (int)ofRandom(0, (int)(items.size()));
}


//--------------------------------------------------------------
// Drawing
//--------------------------------------------------------------
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

static void drawFPS(float x, float y, float w=60, float h=20) {
  
    string fps = "FPS "+ofToString(ofGetFrameRate(), 0);
    ofFill();
    ofSetColor(255, 100);
    ofRect(x, y, w, h);
    
    ofSetColor(0);
    ofDrawBitmapString(fps, x+8, y+(h/2)+4);
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

static void drawFloor(float w, float h) {
    
    /*
     a     b
     
     x
     
     d     c
     */
    
    ofPushMatrix();
    ofTranslate(0, 0, 0);
    ofRotateX(90);
    ofVec3f pa(-w/2, -h/2, 0);
    ofVec3f pb(w/2, -h/2, 0);
    ofVec3f pc(w/2, h/2, 0);
    ofVec3f pd(-w/2, h/2, 0);
    glBegin(GL_QUADS);
    glVertex3fv(&pa[0]); glVertex3fv(&pb[0]);
    glVertex3fv(&pc[0]); glVertex3fv(&pd[0]);
    glEnd();
    ofPopMatrix();
    
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


//--------------------------------------------------------------
// Mouse / Screen
//--------------------------------------------------------------
static ofVec2f ofGetMouse() {
    return ofVec2f(ofGetMouseX(), ofGetMouseY());
}
static ofVec2f ofGetMouseNormal() {
    return ofVec2f(ofMap(ofGetMouseX(), 0.0, ofGetWidth(), 0.0, 1.0, true), ofMap(ofGetMouseY(), 0.0, ofGetHeight(), 0.0, 1.0, true));
}

static ofVec2f ofGetCenterScreen() {
    return ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
// String
//--------------------------------------------------------------
static string ofTruncate(string &str, int max, bool addDotDotDot=true) {
    if(str.length() >= max) {
        str = str.substr(0, max);
        if(addDotDotDot) str += "...";
    }
    return str;
}

//-------------------------------------------------------------- (this may be making a bug)!!!
static void readDirectory(string path, vector<ofFile>&files, vector<string>allowedExt) {	
	
    ofDirectory dir;
	int nItems = dir.listDir(path);
    int MAX_FILES = 5000;
    
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

















