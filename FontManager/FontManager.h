//
//  FontManager.h
//  TilesApp
//
//  Created by Todd Vanderlin on 12/4/12.
//
//

#pragma once

#include "ofMain.h"
#include "Utils.h"

class TypeFace {
public:
    ofTrueTypeFont font;
    int size;
    int face;
};


class FontManager {

public:

    enum {
        ALIGN_TOP    = 0,
        ALIGN_BOTTOM = 1,
        ALIGN_MIDDLE = 2
        
    };
    enum {
        JUSTIFY_RIGHT  = 0,
        JUSTIFY_LEFT   = 1,
        JUSTIFY_MIDDLE = 2
    };
    static map <int, string>      fontKeyPaths;
    static map <string, TypeFace> fonts;
    static void addFontKeyPath(int key, string path);
    static string getPathFromKey(int key);
    static void draw(int face, string str, int size, float x, float y, int textAlign=FontManager::ALIGN_BOTTOM, int justify=FontManager::JUSTIFY_LEFT);
    static void draw(int face, string str, int size, ofPoint pt, int textAlign=FontManager::ALIGN_BOTTOM, int justify=FontManager::JUSTIFY_LEFT);
    static void drawCentered(int face, string str, int size, float x, float y, float centerWidth, int textAlign=FontManager::ALIGN_BOTTOM, int justify=FontManager::JUSTIFY_LEFT);
    static void drawRight(int face, string str, int size, float x, float y);
    static string fitStringInWidth(int face, int size, string inStr, float maxWidth);
    static TypeFace * loadFont(int face, string path, int size);
    static TypeFace * getFont(int face, int size);
    static ofRectangle getBoundingBox(int face, int size, string str);
};
