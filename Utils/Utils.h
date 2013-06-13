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
#include "ofxXmlSettings.h"
#include <map>

static float ofInToPx(float v) {
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
static ofVec3f ofGetNoiseForce( const ofVec3f& a_loc, float a_mult, float a_off ) {
	ofVec3f frc(ofSignedNoise(a_loc.x * a_mult, a_loc.z * a_mult, a_off),
				ofSignedNoise(a_loc.y * a_mult, a_loc.x * a_mult, a_off),
				ofSignedNoise(a_loc.x * a_mult, a_loc.y * a_mult, a_off));
	return frc;
}


//--------------------------------------------------------------
#pragma mark --- Random Helpers ---
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
#pragma mark --- App Helpers ---
// ------------------------------------------------
static float ofDist(const ofVec2f &a, const ofVec2f &b) {
    return ofDist(a.x, a.y, b.x, b.y);
}

// ------------------------------------------------
static float isPointInScreen(const ofPoint &pt, float padding=0) {
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

static ofVec3f ofRandomPointInSphere(float radius, float padding=0) {
    float theta1 = ofRandom(0, TWO_PI);
    float theta2 = ofRandom(0, TWO_PI);
    
    ofVec3f p;
    p.x = cos( theta1 ) * cos( theta2 );
    p.y = sin( theta1 );
    p.z = cos( theta1 ) * sin( theta2 );
    p *= (radius-padding);
    return p;
}

static ofVec2f ofGetMouseVel() {
    return ofVec2f(ofGetMouseX()-ofGetPreviousMouseX(),ofGetMouseY()-ofGetPreviousMouseY());
}

#pragma mark --- XML UTILS ---
//--------------------------------------------------------------
// XML Utils
//--------------------------------------------------------------
static void ofSetXmlRectangle(ofxXmlSettings &xml, ofRectangle &rect, string tag) {
    xml.setValue(tag+"_x", rect.x);
    xml.setValue(tag+"_y", rect.y);
    xml.setValue(tag+"_w", rect.width);
    xml.setValue(tag+"_h", rect.height);
}
static ofRectangle ofGetXmlRectangle(ofxXmlSettings &xml, string tag) {
    ofRectangle rect;
    rect.x      = xml.getValue(tag+"_x", rect.x);
    rect.y      = xml.getValue(tag+"_y", rect.y);
    rect.width  = xml.getValue(tag+"_w", rect.width);
    rect.height = xml.getValue(tag+"_h", rect.height);
    return rect;
}
static void ofSetXmlPoint(ofxXmlSettings &xml, ofPoint &pt, string tag) {
    xml.setValue(tag+"_x", pt.x);
    xml.setValue(tag+"_y", pt.y);
}
static ofPoint ofGetXmlPoint(ofxXmlSettings &xml, string tag) {
    ofPoint pt;
    pt.x = xml.getValue(tag+"_x", pt.x);
    pt.y = xml.getValue(tag+"_y", pt.y);
    return pt;
}


#pragma mark --- UTILS ---
//--------------------------------------------------------------
// Utils
//--------------------------------------------------------------
template<class T>
static int ofRandomIndex(vector<T>&items) {
    if(items.size()==0) return -1;
    return (int)ofRandom(0, (int)(items.size()));
}
template<class T>
static T& ofRandomItem(vector<T>&items) {
    if(items.size()==0) return;
    return items[(int)ofRandom((int)(items.size()-1))];
}

// save out poly points
static bool ofSavePolyPoints(ofPolyline &poly, string filename) {
    if(poly.size() == 0) return false;
    
    ofstream f;
	f.open(ofToDataPath(filename).c_str());
	for (int i=0; i<poly.size(); i++) {
		f << poly[i].x << "," << poly[i].y << "\n";
	}
	f.close();
    
    return true;
}

// load the poly points
static bool ofLoadPolyPoints(ofPolyline &poly, string filename) {
   	
    ifstream f;
	f.open(ofToDataPath(filename).c_str());
	if(f!=0) {
		while (!f.eof()) {
            string ptsStr;
			getline(f, ptsStr);
        
            vector <string> p = ofSplitString(ptsStr, ",");
            if(p.size() >= 2) {
                poly.addVertex(ofToFloat(p[0]), ofToFloat(p[1]));
            }
                
        }
		f.close();
	}

    return true;
}

static string ofGetUniqueString(string pre="", string post="") {
    string u = ofToString((int)ofGetUnixTime());
    if(pre!="" && post !="") return pre + u + post;
    else if(pre=="" && post !="") return u + post;
    else if(post=="" && pre != "") return pre + u;
    else return u;
}

static bool ofProbably(int chance=10) {
    return (int)ofRandom(chance)==0;
}

static ofPolyline ofPolylineFromVec2f(const vector<ofVec2f>&p) {
    ofPolyline poly;
    for(int i=0; i<p.size(); i++) poly.addVertex(p[i]);
    return poly;
}
static ofPolyline ofPolylineFromPoints(const vector<ofPoint>&p) {
    ofPolyline poly;
    for(int i=0; i<p.size(); i++) poly.addVertex(p[i]);
    return poly;
}

static string ofPadWithZero(int v, int nZeros=1) {
    string s = "";
    if(v<=9) for(int i=0; i<nZeros; i++) s += "0";
    s += ofToString(v);
    return s;
}

static string ofGetConcatenatedString(string &str, int maxLength, int nDots=3) {
    int len = str.size();
    string outstr = str;
    if(len > maxLength) {
        outstr = str.substr(0, maxLength);
        for(int i=0; i<nDots; i++) outstr += ".";
    }
    return outstr;
}

static string ofGetFPSstring() {
    return "FPS "+ofToString(ofGetFrameRate(), 0);
}
static ofColor ofHexColor(const int hex) {
    ofColor c;
    c.setHex(hex);
    return c;
}

static float cross(const ofPoint &O, const ofPoint &A, const ofPoint &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
static bool lexicographicallyPointCmp(const ofPoint &a, const ofPoint &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
static vector<ofPoint> ofGetConvexHull(const vector <ofPoint> &pts) {
    vector <ofVec2f> P;
    for (int i=0;i<pts.size();i++) P.push_back(pts[i]);
    
	int n = (int)P.size();
    int k = 0;
	vector <ofPoint> H(2*n);
	
	// Sort points lexicographically
	sort(P.begin(), P.end(), lexicographicallyPointCmp);
	
	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && (cross(H[k-2], H[k-1], P[i]) <= 0)) k--;
		H[k++] = P[i];
	}
	
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && (cross(H[k-2], H[k-1], P[i]) <= 0)) k--;
		H[k++] = P[i];
	}
	
	H.resize(k);
	return H;
}

static string ofCharToString(char c) {
    string s;
    s += c;
    return s;
}

static void ofPrintOpenGLCapabilities() {
  	
	//printf("Getting OpenGL Capabilities\n");
	
	// number of textures
	GLint ntex;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &ntex);
	printf("Num Textures: %i\n", ntex);
	// do we have point sprites
    
	if(glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite")) {
		printf("Point Sprites Enabled\n");
	}
    
#ifdef TARGET_WIN32
	if (WGLEW_ARB_pbuffer) {
		printf("WGLEW pbuffers Enabled\n");
	}
#endif
    
	// can we use vbo?
	if (glewIsSupported("GL_ARB_vertex_buffer_object")) {
		printf("VBO enabled\n");
	}
    
	// do we use shaders
	if(glewIsSupported("GL_ARB_vertex_shader")) {
		printf("Shaders are enabled\n");
	}
	//printf("\n\n----- DONE Getting OpenGL Capabilities -----\n");
}

#pragma mark --- IMAGES ---
//--------------------------------------------------------------
// Images
//--------------------------------------------------------------
static ofImage ofCropFromCenter(ofImage &img, float cropW, float cropH) {
    float cropX = 0;
    float cropY = 0;
    ofImage crop = img;
    float rt = img.getHeight()/img.getWidth();
    float cw = cropW;
    float ch = cropH * rt;
    
    if(ch < cw) {
        rt = img.getWidth()/img.getHeight();
        cw = (cropW) * rt;
        ch = cropH;
        
        cropX = -(cropW-cw)/2;
        cropY = -(cropH-ch)/2;
    }
    
    crop.resize(cw, ch);
    crop.crop(cropX, cropY, cropW, cropH);
    
    return crop;
}

static int ofGetGrayValue(const ofColor &c) {
    return (c.r+c.g+c.b)/3;
}

#pragma mark --- DRAWING ---
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

static void ofDot(const ofPoint &p) {
    ofDot(p.x, p.y, p.z);
}


static void ofDrawCenteredTriangle(float x, float y, float w=10, float h=10) {
    ofTriangle(-w/2 + x, h/2 + y, x, -h/2 + y, w/2 + x, h/2 + y);
}
static void ofDrawCenteredTriangle(const ofPoint &pt, float w=10, float h=10) {
    ofDrawCenteredTriangle(pt.x, pt.y, w, h);
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
    
#ifndef TARGET_OF_IPHONE
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
#endif
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

static void ofDrawBorderRect(float x, float y, float w, float h, const ofColor &fillColor=ofColor::gray, const ofColor &strokeColor=ofColor::white) {
    
    ofFill();
    ofSetColor(fillColor, fillColor.a);
    ofRect(x, y, w, h);
    
    ofNoFill();
    ofSetColor(strokeColor, strokeColor.a);
    ofRect(x, y, w, h);
    
}
static void ofDrawBorderRect(const ofPoint &p, float w, float h, const ofColor &fillColor=ofColor::gray, const ofColor &strokeColor=ofColor::white) {
    ofDrawBorderRect(p.x, p.y, w, h, fillColor, strokeColor);
}
static void ofDrawBorderRect(const ofRectangle &rec, const ofColor &fillColor=ofColor::gray, const ofColor &strokeColor=ofColor::white) {
    ofDrawBorderRect(rec.x, rec.y, rec.width, rec.height, fillColor, strokeColor);
}

static void ofDrawBitmapStringCentered(const string &s, float x, float y, float widthToCenter, float heightToCenter=0) {
    const static int  bitmapPixelW = 8;
    const static int  bitmapPixelH = 9;
    int   n  = s.size();
    float sw = n * bitmapPixelW;
    float sh = bitmapPixelH;
    if(n==1)sw -= 2;
    ofDrawBitmapString(s, x+(widthToCenter-sw)/2, (y+(heightToCenter-sh)/2) + sh);
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

static ofPoint ofGetCenterScreen() {
    return ofPoint(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
// String
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
  
public:
	
	//--------------------------------------------------------------
	static void saveWindowPosition(string filename="windowpos.txt");
	static void loadWindowPosition(string filename="windowpos.txt");
	
	//--------------------------------------------------------------
	static void pushMask(ofRectangle &r);
	static void pushMask(float x, float y, float width, float height);
	static void popMask();

	//--------------------------------------------------------------
	static void drawArrow(float x, float y, float w, float h, float angle=0);
	static void drawArrow(ofVec2f &p, float w, float h, float angle=0);
	static void drawGrid(float w, float h);
	
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
    
    //--------------------------------------------------------------
    static vector<ofVec2f>getArc(float cx, float cy, float radius, float startAngle, float arcAngle, int numSegments=10) {
        
        float theta             = ofDegToRad(arcAngle) / float(numSegments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor  = tanf(theta);
        float radial_factor     = cosf(theta);
        
        float x = radius * cosf(ofDegToRad(startAngle));    //we now start at the start angle
        float y = radius * sinf(ofDegToRad(startAngle));
        
        vector<ofVec2f>outPts;
        for(int i=0; i<numSegments; i++) {
            outPts.push_back(ofVec2f(x + cx, y + cy));
            
            float tx = -y;
            float ty = x;
            
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            
            x *= radial_factor;
            y *= radial_factor;
        }
        return outPts;
    }
    
    //--------------------------------------------------------------
    static void drawArc(float cx, float cy, float innerArc, float outerArc, float startAngle, float arcAngle, int numSegments, ofColor startColor, ofColor endColor) {
#ifndef TARGET_OF_IPHONE
        vector<ofVec2f> inner = Utils::getArc(cx, cy, innerArc, startAngle, arcAngle, numSegments);
        vector<ofVec2f> outer = Utils::getArc(cx, cy, outerArc, startAngle, arcAngle, numSegments);
        
        glBegin(ofGetFill()==OF_FILLED?GL_QUAD_STRIP:GL_LINE_STRIP);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        for (int i=0; i<numSegments; i++) {
            glColor4f(startColor.r/255.0, startColor.g/255.0, startColor.b/255.0, startColor.a/255.0);
            glVertex2f(inner[i].x, inner[i].y);
            
            glColor4f(endColor.r/255.0, endColor.g/255.0, endColor.b/255.0, endColor.a/255.0);
            glVertex2f(outer[i].x, outer[i].y);
            
        }
        glEnd();
#endif
    }
    static void drawArc(ofPoint pt, float innerArc, float outerArc, float startAngle, float arcAngle, int numSegments, ofColor startColor, ofColor endColor) {
        Utils::drawArc(pt.x, pt.y, innerArc, outerArc, startAngle, arcAngle, numSegments, startColor, endColor);
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

//--------------------------------------------------------------
class JsonMaker {
  
public:
    
    map <string, string> keyPairs;
    
    void add(string key, bool val) {
        keyPairs[key] = val?"true":"false";
    }
    void add(string key, int val) {
        keyPairs[key] = ofToString(val);
    }
    void add(string key, float val) {
        keyPairs[key] = ofToString(val);
    }
    void add(string key, const char* val) {
        keyPairs[key] = val;
    }
    
    string getJsonString() {
        string json = "{";
        int inc = 0;
        for (map<string,string>::iterator it=keyPairs.begin(); it!=keyPairs.end(); ++it) {
            json += "\""+it->first+"\":"+"\""+it->second+"\"";
            if(inc!=keyPairs.size()-1) json += ",";
            inc ++;
        }
        json += "}";
        cout << json << endl;
        return json;
    }

};















