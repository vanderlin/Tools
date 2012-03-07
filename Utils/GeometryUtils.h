/*
 *  GeometryUtils.h
 *  GeometryUtils
 *
 *  Created by Todd Vanderlin on 7/1/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

namespace GeometryUtils {
    
    //-------------------------------------------------------------------
    static float getTriangleRadius(ofVec2f v1, ofVec2f v2, ofVec2f v3) {
        
        float a = v1.distance(v2);
        float b = v2.distance(v3);
        float c = v3.distance(v1);
        
        float k = 0.5 * (a+b+c);
        
        float r = sqrt( k * ((k-a)*(k-b)*(k-c)) ) / k;
        return r;
    }
    
    //-------------------------------------------------------------------
    static ofVec2f getTriangleCenter(ofVec2f v1, ofVec2f v2, ofVec2f v3) {
        
        float a = v2.distance(v3);
        float b = v1.distance(v3);
        float c = v1.distance(v2);
        float d = a+b+c;
        
        float ix = ((a * v1.x) + (b * v2.x) + (c * v3.x)) / d;
        float iy = ((a * v1.y) + (b * v2.y) + (c * v3.y)) / d;
        
        return ofVec2f(ix, iy);
    }
    
    
    //-------------------------------------------------------------------
    static float getArea(const vector <ofVec2f> pts) {
        int i, j, n = pts.size();
        float polyArea = 0;
        for (i = 0; i < n; i++) {
            j = (i + 1) % n;
            polyArea += pts[i].x * pts[j].y;
            polyArea -= pts[j].x * pts[i].y;
        }
        polyArea /= 2.0;
        return polyArea;
    }
    
    //-------------------------------------------------------------------
    static float getTriangleArea(ofVec2f &a, ofVec2f &b, ofVec2f &c) {
        vector <ofVec2f> pts;
        pts.push_back(a);
        pts.push_back(b);
        pts.push_back(c);
        int i, j, n = pts.size();
        float polyArea = 0;
        for (i = 0; i < n; i++) {
            j = (i + 1) % n;
            polyArea += pts[i].x * pts[j].y;
            polyArea -= pts[j].x * pts[i].y;
        }
        polyArea /= 2.0;
        return polyArea;
    }
    
    
}













