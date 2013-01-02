
#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle() {
    uniquef = ofRandomuf();
    uniquei = ofRandom(-1000000, 1000000);
    bRemove = false;
    attackEnergy = 0;
    
    bTaken = false;
    lover = NULL;
    letter = NULL;
    bFall = false;
    loverID = -1;
    alpha   = 1;
    
    drag        = ofRandom(0.95, 0.96);
    radius      = 10;
    fadeSpeed   = ofRandom(0.02, 0.006);
    drawRadius  = 3;
    maxSpeed    = ofRandom(3.0, 8.0);
    useHistory  = false;
    bFallTimer  = false;
    fallTimer   = 0;
    
    fadeInSpeed = 0.1;//ofRandom(0.01, 0.03);
    
    birthdate   = ofGetElapsedTimef();
    age         = 0;
    frameAge    = 0;
}

/*
//--------------------------------------------------------------
Particle::Particle(const Particle& other) {
    cout << other.lover << endl;
    this->lover  = other.lover;
    this->bTaken = other.bTaken;
}
*/

//--------------------------------------------------------------
bool Particle::shouldRemove(const Particle &p) {
    return p.bRemove;
}


//--------------------------------------------------------------
void Particle::resetForce() {
    frc.set(0,0);
}

//--------------------------------------------------------------
void Particle::update() {
    vel *= drag;
    vel += frc;
    pos += vel;
    
    age = ofGetElapsedTimef() - birthdate;
    frameAge++;
}

//--------------------------------------------------------------
void Particle::draw() {
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(color, alpha*255.0);
    ofCircle(pos, drawRadius);
}

//--------------------------------------------------------------
void Particle::drawHistory(int renderMode) {
    ofEnableAlphaBlending();
    if(useHistory && pts.size()>2) {
        ofNoFill();
        colors.clear();
        //for (int i=0; i<pts.size(); i++) {
            //float pct = ofMap(i, 0, pts.size()-1, 0, 0.8) * alpha;
            //colors.push_back(ofFloatColor(1,1,1,pct));
        //}
        //vbo.setColorData(&colors[0], colors.size(), GL_DYNAMIC_DRAW);
        vbo.setVertexData(&pts[0], pts.size(), GL_DYNAMIC_DRAW);
        vbo.draw(renderMode, 0, pts.size());
    }
}

//--------------------------------------------------------------
void Particle::setPosition(float x, float y) {
    pos.set(x, y);
}

//--------------------------------------------------------------
void Particle::setPosition(const ofVec2f &p) {
    pos.set(p);
}

//--------------------------------------------------------------
void Particle::setRadius(float radius, float drawRadius) {
    this->radius     = radius;
    this->drawRadius = drawRadius;
}

//--------------------------------------------------------------
void Particle::wrapScreen(float x, float y, float width, float height) {
    
    if (pos.x < -radius) pos.x = width+radius;
    if (pos.y < -radius) pos.y = height+radius;
    if (pos.x > width+radius) pos.x = -radius;
    if (pos.y > height+radius) pos.y = -radius;
}

//--------------------------------------------------------------
void Particle::bounceOffBounds(float x, float y, float width, float height) {
    float bounce = 1.0;
    bool  hit    = false;
    if (pos.x < -radius) {
        pos.x = -radius;
        vel.x *= -bounce;
        hit   = true;
    }
    else if (pos.y < -radius) { 
        pos.y = -radius;
        vel.y *= -bounce;
        hit   = true;
    }
    else if (pos.x > width+radius) { 
        pos.x = width+radius;
        vel.x *= -bounce;
        hit   = true;
    }
    else if (pos.y > height-radius) { 
        pos.y = height-radius;
        vel.y *= -bounce;
        hit   = true;
    }
   //     if(hit) vel *= drag * 0.85;
}

//--------------------------------------------------------------
void Particle::attractionPoint(ofVec2f pt, float scl) {
    ofVec2f vec = pt - pos;
    vec.normalize();
    frc += vec * scl;
}

//--------------------------------------------------------------
void Particle::avoidPoint(ofVec2f pt, float minRad, float scl) {
    ofVec2f vec = pt - pos;
    if(vec.length() < minRad) {
        vec.normalize();
        frc -= vec * scl;
    }
}

//--------------------------------------------------------------
void Particle::avoidMouse(float minRad, float scl) {
    ofVec2f mouseVec = ofGetMouse() - pos;
    if(mouseVec.length() < minRad) {
        mouseVec.normalize();
        frc -= mouseVec * scl;
    }
}

//--------------------------------------------------------------
void Particle::addNoiseForce(float scale) {
    ofVec2f noiseFrc;
    float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
    
    noiseFrc.x = ofSignedNoise(uniquef, pos.y * 0.006) * 0.06;
    noiseFrc.y = ofSignedNoise(uniquef, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.06;
    noiseFrc *= scale;
    frc += noiseFrc;
}
