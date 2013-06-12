//
//  Particle.h
//  MainApp
//
//  Created by Todd Vanderlin on 3/9/12.
//  Copyright (c) 2012 vanderlin.cc. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "Utils.h"

class Perp : public ofVec2f {
public:
    ofVec2f pos;
    float   angle;
    float   length;
    Perp(){}
    Perp(const ofVec2f &a, const ofVec2f &b) {
        ofVec2f v = a-b;
        length = v.length();
        angle  = atan2(v.y, v.x);
        set(v.perpendicular());
        pos = a;
    }
    Perp(const ofVec2f &perp, const ofVec2f &perPos, float perAngle, float perLength) {
        set(perp);
        pos = perPos;
        angle = perAngle;
        length = perLength;
    }
    ofVec2f getScaledPerp(float scale) {
        return pos + (*this*scale);
    }
};

class Particle {
    
public:
    
    typedef struct {
        float   dis = 0;
        ofVec2f vec;
    } Proximity;
   
    
    vector <Perp>        perps;
    vector<ofFloatColor> colors;
    ofPolyline           pts, resammpled;
    
    
    ofVbo vbo;
    ofColor     color;
    bool        bTaken, useHistory;
    int         uid;
    
    ofVec2f     pos, vel, frc;
    ofVec2f     prevPos;
    ofVec2f     startingPoint;
    float       maxForce;
    float       maxSpeed;
    
    float       radius, drawRadius;
    float       drag;
    float       age, birthdate;
    int         frameAge;
    float       uniquef;
    int         uniquei;
    int         type;
    bool        bRemove;
    float       energy;
    float       alpha, fadeSpeed, fadeInSpeed;
    float       wanderTheta;
    
    bool         bFirstPos;
    
    unsigned int bitFlagW;
    unsigned int bitFlagH;
	
	
    Particle();
    ~Particle();
    
    //Particle(const Particle& other);
    static bool  shouldRemove(const Particle &p);
    static float getHeading2D(const ofVec2f &v);
    Proximity    getProximity(const Particle &p);
    
    float getAngle();
    float getAge();
    
    void calculatePerps(bool bResample=false, float res=10);
    void update();
    void draw();
    void drawHistory(int renderMode=GL_LINE_STRIP);
    void drawPolylineHistory();
    
    void setPosition(float x, float y);
    void setPosition(const ofVec2f &p);
    void setRadius(float radius, float drawRadius=3);
    void addHistoryPoint();
    
    
    void bounceOffBounds(float x=0, float y=0, float width=ofGetWidth(), float height=ofGetHeight());
    void bounceOffBounds(const ofRectangle &rect);

    void wrapScreen(const ofRectangle &rect);
    void wrapScreen(float x=0, float y=0, float width=ofGetWidth(), float height=ofGetHeight());
    void steerAwayFromRect(float x, float y, float w, float h, float scaleForce=1.0);
    void steerAwayFromRect(const ofRectangle &rect, float scaleForce=1.0);
    
    void resetForce();
    void addAttractionPoint(float x, float y, float scl=1);
    void addAttractionPoint(ofVec2f pt, float scl=1);
    void addRepulsionForce(Particle &p, float radius, float scale);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addDampingForce();
    void addNoiseForce(float scale=1.0);
    void avoidPoint(ofVec2f pt, float minRad, float scl=1);
    void avoidMouse(float minRad, float scl=1);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addAttractionForce(const ofPoint &pt, float radius, float scale);

    // forces
    void seek(float tx, float ty, float minDis=100, bool slowDown=false);
    void seek(const ofVec2f &target, float minDis=100, bool slowDown=false);
    

    ofVec2f getSeperationFrcFromParticle(const Particle &p, float scaleForce=1);
    
    ofVec2f getSeekFrc(float tx, float ty, float minDis=100, bool slowDown=false);
    ofVec2f getSeekFrc(const ofVec2f &target, float minDis=100, bool slowDown=false);
    ofVec2f getSeperationFrc(const vector <Particle*> &particles, float mindDis=50.0, float scaleForce=1.0);
    ofVec2f getAlignFrc(const vector <Particle*> &particles, float minDis=50.0, float scaleForce=1.0);
    ofVec2f getCohesionFrc(const vector <Particle*> &particles, float minDis=50.0, float scaleForce=1.0);
    
    void flock(const vector <Particle*> &particles, float mindDis=50.0, float scaleForce=1.0);
    void wander(float wanderRadius=25, float wanderDistance=80, float randomAmount=0.4);
};









