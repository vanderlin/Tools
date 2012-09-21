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

class Letter;
class Particle {
    
public:
    
    enum {
        KING   = 0,
        ROAMER = 1,
    };
    
    vector<ofFloatColor> colors;
    vector<ofVec2f>pts;
    ofVbo vbo;
    ofColor     color;
    bool        bTaken, useHistory;
    Particle *  lover;
    Letter *    letter;
    int         uid;
    int         loverID;
    float       maxSpeed;
    ofVec2f     pos, vel, frc;
    float       radius, drawRadius;
    float       drag;
    float       age, birthdate;
    float       uniquef;
    int         uniquei;
    int     type;
    bool    bRemove;
    bool    bFall;
    float   energy;
    float   attackEnergy;
    float   alpha, fadeSpeed, fadeInSpeed;

    bool    bFallTimer;
    float   fallTimer;
    int homeIndex;
    ofVec2f home;
    Particle();
    //Particle(const Particle& other);
    static bool shouldRemove(const Particle &p);
    
    void update();
    void draw();
    void drawHistory();
    
    void setPosition(float x, float y);
    void setPosition(const ofVec2f &p);
    void setRadius(float radius, float drawRadius=3);
    
    void bounceOffBounds(float x=0, float y=0, float width=ofGetWidth(), float height=ofGetHeight());
    void wrapScreen(float x=0, float y=0, float width=ofGetWidth(), float height=ofGetHeight());
    
    void resetForce();
    void attractionPoint(ofVec2f pt, float scl=1);
    
    void avoidPoint(ofVec2f pt, float minRad, float scl=1);
    void avoidMouse(float minRad, float scl=1);
};