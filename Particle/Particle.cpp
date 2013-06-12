
#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle() {
   
    uniquef     = ofRandomuf();
    uniquei     = ofRandom(-1000000, 1000000);
    bRemove     = false;
    
    bFirstPos   = false;
    bTaken      = false;
    alpha       = 1;
    
    drag        = ofRandom(0.95, 0.96);
    radius      = 10;
    fadeSpeed   = ofRandom(0.02, 0.006);
    drawRadius  = 3;
    useHistory  = false;
    bFirstPos   = true;
    fadeInSpeed = 0.1;//ofRandom(0.01, 0.03);
    
    birthdate   = ofGetElapsedTimef();
    age         = 0;
    frameAge    = 0;
    
    maxSpeed    = 4;//ofRandom(3.0, 8.0);
    maxForce    = 0.1;//ofRandom(3.0, 8.0);
    wanderTheta = 0.0f;
}

//--------------------------------------------------------------
Particle::~Particle() {
    // printf("Particle Destroyed\n");
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
#pragma mark --- UPDATES ---
//--------------------------------------------------------------
void Particle::resetForce() {
    frc.set(0,0);
}

//--------------------------------------------------------------
void Particle::addHistoryPoint() {
    pts.addVertex(pos);
}

// ---------------------------------------------------------
void Particle::calculatePerps(bool bResample, float res) {
    
    ofPolyline * points = &pts;
    if(bResample) {
        resammpled.clear();
        resammpled = pts.getResampledBySpacing(res);        
        points = &resammpled;
    }
    perps.clear();
    for(int i=0; i<points->size(); i++) {
        ofVec2f a,b,v;
        Perp p;
        if(i==0) {
            a = points->getVertices()[i];
            b = points->getVertices()[i+1];
            v = a-b;
        }
        else {
            a = points->getVertices()[i];
            b = points->getVertices()[i-1];
            v = b-a;
        }
        
        p.length = v.length();
        p.set(v.perpendicular());
        p.angle = ofRadToDeg(atan2(v.y, v.x));
        p.pos   = a;
        perps.push_back(p);
    }
    
}

//--------------------------------------------------------------
void Particle::update() {
    prevPos = pos;

    vel += frc;
    vel.limit(maxSpeed);
    pos += vel;
    
    age = ofGetElapsedTimef() - birthdate;
    frameAge++;
    
}

//--------------------------------------------------------------
void Particle::draw() {
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(color, alpha*255.0);
    ofCircle(pos, radius);
}

//--------------------------------------------------------------
void Particle::drawPolylineHistory() {
    if(useHistory && pts.size()>2) {
        pts.draw();
    }
}

//--------------------------------------------------------------
void Particle::drawHistory(int renderMode) {
    ofEnableAlphaBlending();
    if(useHistory && pts.size()>2) {
        ofNoFill();
        colors.clear();
        for (int i=0; i<pts.size(); i++) {
            float pct = ofMap(i, 0, pts.size()-1, 0, 0.8) * alpha;
            colors.push_back(ofFloatColor(1,1,1,pct));
        }
        vbo.setColorData(&colors[0], colors.size(), GL_DYNAMIC_DRAW);
        vbo.setVertexData(&pts[0], pts.size(), GL_DYNAMIC_DRAW);
        vbo.draw(renderMode, 0, pts.size());
    }
}

//--------------------------------------------------------------
void Particle::setPosition(const ofVec2f &p) {
    setPosition(p.x, p.y);
}

//--------------------------------------------------------------
void Particle::setPosition(float x, float y) {
    if(bFirstPos) {
        startingPoint.set(x, y);
        bFirstPos = false;
    }
    pos.set(x, y);
}

//--------------------------------------------------------------
void Particle::setRadius(float radius, float drawRadius) {
    this->radius     = radius;
    this->drawRadius = drawRadius;
}

//--------------------------------------------------------------
void Particle::wrapScreen(const ofRectangle &rect) {
    wrapScreen(rect.x, rect.y, rect.width, rect.height);
}

//--------------------------------------------------------------
void Particle::wrapScreen(float x, float y, float width, float height) {
    
    if (pos.x < x-radius)        pos.x = x+width;
    if (pos.y < y-radius)        pos.y = y+height;
    if (pos.x > x+width+radius)  pos.x = x;
    if (pos.y > y+height+radius) pos.y = y;
}

//--------------------------------------------------------------
void Particle::bounceOffBounds(const ofRectangle &rect) {
    bounceOffBounds(rect.x, rect.y, rect.width, rect.height);
}

//--------------------------------------------------------------
void Particle::bounceOffBounds(float x, float y, float width, float height) {
    float bounce = 1.0;
    bool  hit    = false;
    if (pos.x < x+radius) {
        pos.x = x+radius;
        vel.x *= -bounce;
        hit   = true;
    }
    if (pos.y < y+radius) {
        pos.y = y+radius;
        vel.y *= -bounce;
        hit   = true;
    }
    if (pos.x > (x+width)-radius) {
        pos.x = (x+width)-radius;
        vel.x *= -bounce;
        hit   = true;
    }
    if (pos.y > (y+height)-radius) {
        pos.y = (y+height)-radius;
        vel.y *= -bounce;
        hit   = true;
    }
   //     if(hit) vel *= drag * 0.85;
}


#pragma mark --- FLOCKING ---
//--------------------------------------------------------------
void Particle::seek(const ofVec2f &target, float minDis, bool slowDown) {
    seek(target.x, target.y, minDis, slowDown);
}

//--------------------------------------------------------------
void Particle::seek(float tx, float ty, float minDis, bool slowDown) {
    
    ofVec2f vec = ofVec2f(tx, ty) - pos;
    float   dis = vec.length();
    
    vec.normalize();
    if(slowDown) {
        if (dis < minDis) {
            float m = ofMap(dis,0,minDis,0,maxSpeed);
            vec *= m;
        }
        else {
            vec *= maxSpeed;
        }
    } else vec *= maxSpeed;
    
    ofVec2f f = vec - vel;
    f.limit(maxForce);
    
    frc += f;
}

//--------------------------------------------------------------
ofVec2f Particle::getSeekFrc(float tx, float ty, float minDis, bool slowDown) {
    ofVec2f vec = ofVec2f(tx, ty) - pos;
    float   dis = vec.length();
    
    vec.normalize();
    if(slowDown) {
        if (dis < minDis) {
            float m = ofMap(dis,0,minDis,0,maxSpeed);
            vec *= m;
        }
        else {
            vec *= maxSpeed;
        }
    } else vec *= maxSpeed;
    
    ofVec2f f = vec - vel;
    f.limit(maxForce);
    
    return f;
}

//--------------------------------------------------------------
ofVec2f Particle::getSeekFrc(const ofVec2f &target, float minDis, bool slowDown) {
    return getSeekFrc(target.x, target.y, minDis, slowDown);
}


//--------------------------------------------------------------
void Particle::steerAwayFromRect(const ofRectangle &rect, float scaleForce) {
    steerAwayFromRect(rect.x, rect.y, rect.width, rect.height, scaleForce);
}

//--------------------------------------------------------------
void Particle::steerAwayFromRect(float x, float y, float w, float h, float scaleForce) {
    
    ofVec2f desired;
    bool bApply = false;
    
    if(pos.x < x+radius) {
        desired.set(maxSpeed, vel.y);
        bApply = true;
    }
    else if(pos.x > (x+w)-radius) {
        desired.set(-maxSpeed, vel.y);
        bApply = true;
    }
    
    else if(pos.y < y+radius) {
        desired.set(vel.x, maxSpeed);
        bApply = true;
    }
    else if(pos.y > (y+h)-radius) {
        desired.set(vel.x, -maxSpeed);
        bApply = true;
    }
    
    
    if(bApply) {
        desired.normalize();
        desired *= maxSpeed;
        ofVec2f f = desired - vel;
        f.limit(maxForce);
        
        f *= scaleForce;;
        frc += f;
    }
    
}

//--------------------------------------------------------------
ofVec2f Particle::getSeperationFrc(const vector <Particle*> &particles, float mindDis, float scaleForce) {
    
    int c = 0;
    float seperationDis = mindDis;
    ofVec2f sum, sf;
    
    for(int i=0; i<particles.size(); i++) {
        
        float dis = pos.distance(particles[i]->pos);
        
        if(dis > 0 && dis < seperationDis) {
            ofVec2f vec = pos - particles[i]->pos;
                    vec.normalize();
                    vec /= dis;
                    sum += vec;
                    c ++;
        }
    }
    
    
    if(c > 0) {
        sum /= c;
        sum.normalize();
        sum *= maxSpeed;
        
        sf = sum - vel;
        sf *= scaleForce;
        sf.limit(maxForce);
    }
    
    return sf;
}

//--------------------------------------------------------------
ofVec2f Particle::getSeperationFrcFromParticle(const Particle &p, float scaleForce) {
    
    int c = 0;
    float seperationDis = p.radius + radius;
    ofVec2f sum, sf;
    float dis = pos.distance(p.pos);
    
    if(dis > 0 && dis < seperationDis) {
        ofVec2f vec = pos - p.pos;
        vec.normalize();
        vec /= dis;
        sum += vec;
        c ++;
    }
    
    
    if(c > 0) {
        sum /= c;
        sum.normalize();
        sum *= maxSpeed;
        
        sf = sum - vel;
        sf *= scaleForce;
        sf.limit(maxForce);
    }
    
    return sf;
}


//--------------------------------------------------------------
ofVec2f Particle::getAlignFrc(const vector <Particle*> &particles, float minDis, float scaleForce) {
    
    ofVec2f sum, steerFrc;
    int     c = 0;
    for(int i=0; i<particles.size(); i++) {
        ofVec2f v = pos - particles[i]->pos;
        float   d = v.length();
        if(d > 0 && d < minDis) {
            sum += particles[i]->vel;
            c++;
        }
    }
    if(c > 0) {
        sum /= (float)c;
        sum.normalize();
        sum *= maxSpeed;
        steerFrc = sum - vel;
        steerFrc.limit(maxForce);
    }
    return steerFrc;
    
    /*PVector align (ArrayList<Boid> boids) {
        float neighbordist = 50;
        PVector sum = new PVector(0,0);
        int count = 0;
        for (Boid other : boids) {
            float d = PVector.dist(location,other.location);
            if ((d > 0) && (d < neighbordist)) {
                sum.add(other.velocity);
                count++;
            }
        }
        if (count > 0) {
            sum.div((float)count);
            sum.normalize();
            sum.mult(maxspeed);
            PVector steer = PVector.sub(sum,velocity);
            steer.limit(maxforce);
            return steer;
        } else {
            return new PVector(0,0);
        }
    }*/
}

//--------------------------------------------------------------
ofVec2f Particle::getCohesionFrc(const vector <Particle*> &particles, float minDis, float scaleForce) {
    ofVec2f posSum, steerFrc;
    int     c = 0;
    for(int i=0; i<particles.size(); i++) {
        ofVec2f v = pos - particles[i]->pos;
        float   d = v.length();
        if(d > 0 && d < minDis) {
            posSum += particles[i]->pos;
            c++;
        }
    }
    if(c > 0) {
        posSum  /= (float)c;
        steerFrc = getSeekFrc(posSum);
    }
    return steerFrc;
}

//--------------------------------------------------------------
void Particle::flock(const vector <Particle*> &particles, float mindDis, float scaleForce) {
    
    frc += getSeperationFrc(particles, mindDis, scaleForce);
    frc += getAlignFrc(particles, mindDis, scaleForce);
    frc += getCohesionFrc(particles, mindDis, scaleForce);
    
}


#pragma mark --- HELPERS ---
//--------------------------------------------------------------
float Particle::getHeading2D(const ofVec2f &v) {
    float angle = (float) atan2(-v.y, v.x);
    return -1*angle;
}
Particle::Proximity Particle::getProximity(const Particle &p) {
    Proximity prox;
    prox.vec = p.pos - pos;
    prox.dis = prox.vec.length();
    prox.vec.normalize();
    
    return prox;
}


#pragma mark --- GETS ---
//--------------------------------------------------------------
float Particle::getAngle() {
    return 90 + ofRadToDeg( Particle::getHeading2D(vel) );
}

//--------------------------------------------------------------
float Particle::getAge() {
    return ofGetElapsedTimef() - birthdate;
}
//--------------------------------------------------------------
void Particle::wander(float wanderRadius, float wanderDistance, float randomAmount) {
    
    float wr = wanderRadius;
    float wd = wanderDistance;
    float ch = randomAmount;
    
    wanderTheta += ofRandom(-ch, ch);
    
    ofVec2f vec = vel;
    vec.normalize();
    vec *= wd;
    vec += pos;
    float h = Particle::getHeading2D(vel);
    ofVec2f offset = ofVec2f(cos(wanderTheta+h) * wr, sin(wanderTheta+h) * wr);
    ofVec2f target = vec - offset;
    seek(target);
}

//--------------------------------------------------------------
void Particle::addAttractionPoint(float x, float y, float scl) {
    ofVec2f vec = ofVec2f(x, y) - pos;
    vec.normalize();
    frc += vec * scl;
}

//--------------------------------------------------------------
void Particle::addAttractionPoint(ofVec2f pt, float scl) {
    addAttractionPoint(pt.x, pt.y, scl);
}

//--------------------------------------------------------------
void Particle::addRepulsionForce(float x, float y, float radius, float scale) {
    bool bAmCloseEnough = true;
	
	float scaleFromCenter = 0;
	
    if (radius > 0)
    {
		float dist = ((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y));
        if (dist > (radius*radius))
        {
			scaleFromCenter = dist / (radius*radius);
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
		
		
		
        ofVec2f forceVec = ofVec2f(0,0);
        forceVec.x = x-pos.x;
        forceVec.y = y-pos.y;
        forceVec.normalize();
        frc.x = frc.x - forceVec.x * scale * (1-scaleFromCenter);
        frc.y = frc.y - forceVec.y * scale * (1-scaleFromCenter);
    }
}

//--------------------------------------------------------------
void Particle::addRepulsionForce(Particle &p, float radius, float scale) {
    float x = p.pos.x;
    float y = p.pos.y;
    bool bAmCloseEnough = true;
	// fix ...
	
    if (radius > 0)
    {
        if (sqrt((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y)) > radius)
        {
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true)
    {
		
		float scaleMe = sqrt((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y)) / radius;
        ofVec2f forceVec = ofVec2f(0,0);
        forceVec.x = x-pos.x;
        forceVec.y = y-pos.y;
        forceVec.normalize();
        frc.x = frc.x - forceVec.x * scale * (1-scaleMe);
        frc.y = frc.y - forceVec.y * scale * (1-scaleMe);
        p.frc.x = p.frc.x + forceVec.x * scale * (1-scaleMe);
        p.frc.y = p.frc.y + forceVec.y * scale * (1-scaleMe);
    }
}

//--------------------------------------------------------------
void Particle::addAttractionForce(const ofPoint &pt, float radius, float scale) {
    addAttractionForce(pt.x, pt.y, radius, scale);
}

//--------------------------------------------------------------
void Particle::addAttractionForce(float x, float y, float radius, float scale) {
    
    bool bAmCloseEnough = true;
    if (radius > 0)
    {
        if (((x-pos.x)*(x-pos.x) + (y-pos.y)*(y-pos.y)) > (radius*radius))
        {
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true)
    {
        ofVec2f forceVec = ofVec2f(0,0);
        forceVec.x = x-pos.x;
        forceVec.y = y-pos.y;
        forceVec.normalize();
        frc.x = frc.x + forceVec.x * scale;
        frc.y = frc.y + forceVec.y * scale;
    }
}

//--------------------------------------------------------------
void Particle::addDampingForce() {
    float damping = 0.02;
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
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
