//
//  FontManager.cpp
//  TilesApp
//
//  Created by Todd Vanderlin on 12/4/12.
//
//

#include "FontManager.h"

map <string, TypeFace> FontManager::fonts;
map <int, string>      FontManager::fontKeyPaths;

//--------------------------------------------------------------
TypeFace * FontManager::loadFont(int face, string path, int size) {
    
    string key   = ofToString(face)+"_"+ofToString(size);
    if(FontManager::fonts.find(key) == FontManager::fonts.end()) {
        FontManager::fonts[key] = TypeFace();
        FontManager::fonts[key].face = face;
        FontManager::fonts[key].size = size;
        FontManager::fonts[key].font.loadFont(path, size);
        ofLog(OF_LOG_VERBOSE, "Need to load font:"+path);
    }
    return &FontManager::fonts[key];
}

//--------------------------------------------------------------
void FontManager::addFontKeyPath(int key, string path) {
    FontManager::fontKeyPaths[key] = path;
}
string FontManager::getPathFromKey(int key) {
    return FontManager::fontKeyPaths[key];
}

//--------------------------------------------------------------
TypeFace * FontManager::getFont(int face, int size) {
    string     key = ofToString(face)+"_"+ofToString(size);
    TypeFace * f   = loadFont(face, FontManager::getPathFromKey(face), size);
    
    // need load it
    if(f == NULL) {
        f = FontManager::loadFont(face, FontManager::getPathFromKey(face), size);
    }
    
    return f;
}


//--------------------------------------------------------------
string FontManager::fitStringInWidth(int face, int size, string inStr, float maxWidth) {
    
    
    TypeFace * f = getFont(face, size);

    float runningWidth = 0;
    string outString   = "";
    string currLine    = "";
    vector <string> words = ofSplitString(inStr, " ");
    int wordsInLine = 0;
    for(int i=0; i<words.size(); i++) {
        string word      = words[i];
        string lineBreak = " ";
        currLine += word + lineBreak;
        wordsInLine ++;
        ofRectangle rect = f->font.getStringBoundingBox(currLine+(i<words.size()-1?words[i+1]:""), 0, 0);

        ofDrawBitmapString(currLine+"  "+ofToString(rect.width)+"/"+ofToString(maxWidth)+"  "+ofToString(wordsInLine), 20, 20 + (i*25));//.c_str(), runningWidth);
        
        if(rect.width >= maxWidth) {
            bool bWordToLongForBox = false;
            if(wordsInLine == 1) {
                string newWord = "";
                string outWord = "";
                for(int j=0; j<currLine.size(); j++){
                    string letter = ""; letter += currLine[j];
                    string nextLetter = "";
                    if(j<currLine.size()-1)nextLetter += currLine[j];
                    ofRectangle wrdRect = f->font.getStringBoundingBox(newWord+nextLetter+"-", 0, 0);
                    if(wrdRect.width>maxWidth) {
                        newWord = "";
                        outWord += "-\n";
                    }
                    newWord += letter;
                    outWord += letter;
                }
                //printf("line --- %s\n", outWord.c_str());
                words[i] = outWord;
                bWordToLongForBox = true;

            }
            if(!bWordToLongForBox) {
                lineBreak = "\n";
            }
            currLine = "";
            runningWidth = 0;
            wordsInLine = 0;
        }
        
        runningWidth += rect.width;
        outString += words[i] + lineBreak;
    }
   
    return outString;
}


//--------------------------------------------------------------
void FontManager::draw(int face, string str, int size, float x, float y, int textAlign, int justify) {
    
    string key   = ofToString(face)+"_"+ofToString(size);
    TypeFace * f = NULL;
    
    if(FontManager::fonts.find(key) == FontManager::fonts.end()) {
        // load
        f = FontManager::loadFont(face, FontManager::getPathFromKey(face), size);
    }
    else {
        // found
        f = &FontManager::fonts[key];
    }
  
    if(f) {
        float th = f->font.stringHeight(str);
        if(textAlign==FontManager::ALIGN_TOP) y += th;
        if(textAlign==FontManager::ALIGN_MIDDLE) y += (th/2);
        
        if(justify==FontManager::JUSTIFY_RIGHT) x -= f->font.stringWidth(str);
        if(justify==FontManager::JUSTIFY_MIDDLE) x-= f->font.stringWidth(str) / 2;
        
        f->font.drawString(str, x, y);
    }
}

//--------------------------------------------------------------
void FontManager::drawCentered(int face, string str, int size, float x, float y, float centerWidth, int textAlign, int justify) {
    
    string key   = ofToString(face)+"_"+ofToString(size);
    TypeFace * f = getFont(face, size);
    float strW = f->font.stringWidth(str);
    float th = f->font.stringHeight(str);
    if(textAlign==FontManager::ALIGN_TOP) y += th;
    else if(textAlign==FontManager::ALIGN_MIDDLE) y += (th/2);
    
    if(justify==FontManager::JUSTIFY_RIGHT)  x -= f->font.stringWidth(str);
    if(justify==FontManager::JUSTIFY_MIDDLE) x-= f->font.stringWidth(str) / 2;
    
    f->font.drawString(str, x-(strW/2) + (centerWidth/2), y);
    
}

//--------------------------------------------------------------
void FontManager::drawRight(int face, string str, int size, float x, float y) {
    string key   = ofToString(face)+"_"+ofToString(size);
    TypeFace * f = getFont(face, size);
    float strW = f->font.stringWidth(str);
    ofRectangle b = f->font.getStringBoundingBox(str, 0, 0);
    
    f->font.drawString(str, x-b.width, y);
}

/*void FontManager::draw(int fontID, string str, int size, ofPoint pt) {
    FontManager::fonts[fontID].drawString(str, pt.x, pt.y);
}*/
