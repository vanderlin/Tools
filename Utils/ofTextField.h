//
//  ofTextField.h
//  TextField
//
//  Created by Todd Vanderlin on 4/7/13.
//
//

#pragma once
#include "ofMain.h"
class ofTextField;
class ofTextFieldEvent : public ofEventArgs {
public:
    ofTextFieldEvent(ofTextField * who, int eventType) {
        item = who;
        type = eventType;
    }
    int type;
    ofTextField * item;
};
class ofTextField : public ofRectangle {

private:
    bool   isMultiLine;
    float  extraPadding;
    string text;
    ofTrueTypeFont * font;
public:

    enum {
        TEXT_FIELD_ENTER,
        TEXT_FIELD_ERROR
    };
    
    static ofEvent<ofTextFieldEvent>events;
    float  blinkTime;
    int textPos, linePos;
    float alpha;
    int   padding;
    ofColor fontColor;
    
    // ------------------------------------------
    ofTextField() {
        isMultiLine = false;
        extraPadding = 3;
        padding   = 10;
        font      = NULL;
        alpha     = 1.0;
        blinkTime = ofGetElapsedTimef();
        fontColor.set(0);
        textPos = 0;
        linePos = 0;
    }
    
    // ------------------------------------------
    void setMultiLine(bool useMultiLine) {
        isMultiLine = useMultiLine;
    }

    // ------------------------------------------
    void setFont(ofTrueTypeFont * fontToUse) {
        font = fontToUse;
    }
    
    // ------------------------------------------
    string getText() {
        return text;
    }
    
    // ------------------------------------------
    void setText(string s) {
        text = s;
        textPos = (int)text.size()-1;
    }
    
    // ------------------------------------------
    void keyPressed(int key) {
                
        if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
            if(text.size()>0 && textPos>0) {
                text.erase(textPos-1, 1);
                printf("Del\n");
                textPos --;
            }
        }
        else if(key == OF_KEY_LEFT) {
            if(textPos>0) textPos --;
        }
        else if(key == OF_KEY_RIGHT) {
            if(textPos<=text.size()-1) textPos ++;
        }
        if(key == 13) {
            if(isMultiLine) {
                text.insert(textPos, "\n");
                textPos ++;
            }
            else {
                static ofTextFieldEvent evt(this, TEXT_FIELD_ENTER);
                ofNotifyEvent(ofTextField::events, evt, this);
            }
        }
        else if(key >= 32 && key <= 126){
            string s;
            s += (char)key;
            text.insert(textPos, s);
            textPos ++;            
        }
    }
    
    // ------------------------------------------
    int getNumLettersThatFitInWidth() {
        if(font!=NULL) {
            float sw = font->getStringBoundingBox(getStringThatFits().substr(0, textPos),0,0).width;
            return ((width-(padding*2))+sw) / sw;
        }
        return (width-(padding*2)) / 8.0;
    }
    
    // ------------------------------------------
    void reizeToFitFont(bool ajustWidth=true) {
        if(font!=NULL) {
            if(ajustWidth) width  = (font->getSize() * 4) + (padding*2);
            height = font->getSize() + 20;
        }
    }
    
    // ------------------------------------------
    string getStringThatFits() {
        
        
        
        string outstr = text;
        if(font!=NULL) {
            
            string runningStr = "";
            
            if(isMultiLine) {
                
                vector <string> lines;
                string str  = "";
                string runW = "";
                if((int)text.size()>0) lines.push_back("");
                for (int i=0; i<text.size(); i++) {
                    
                    runW += text[i];
                    str  += text[i];
                    lines.back() += text[i];
                    float w = font->getStringBoundingBox(runW, 0, 0).width;
                    if(w>=width-(padding*2)) {
                        str.insert((int)str.size()-1, "\n");
                        lines.back() = runW.substr(0, (int)runW.size()-1);
                        runW = text[i];
                        lines.push_back(runW);
                    }
                }
                str = "";
                float runH = 0;
                int startIndex = 0;
                
                for(int i=lines.size()-1; i>=0; i--) {
                    str += lines[i];
                    str += "\n";
                    float h = font->getStringBoundingBox(lines[i], 0, 0).height;
                    runH += h;
                    if(runH >= (height-(padding*2))) {
                        startIndex = i+1;
                        break;
                    }
                }
                str = "";
                for (int i=startIndex; i<lines.size(); i++) {
                    str += lines[i] + "\n";
                }
                
                
                outstr = str;
            }
            else {
                int indexFromLeft = -1;
                for (int i=0; i<text.size(); i++) {
                    runningStr += text[i];
                    float w = font->getStringBoundingBox(runningStr, 0, 0).width;
                    if(w >= width-(padding*2)) {
                        indexFromLeft = i;
                        break;
                    }
                }
                
                
                if(textPos <= indexFromLeft) {
                    runningStr = "";
                    outstr = text.substr(0, indexFromLeft);
                }
                else {
                    runningStr = "";
                    int len = 0;
                    for (int i=textPos-1; i>=0; i--) {
                        runningStr += text[i];
                        string rev = string( runningStr.rbegin(), runningStr.rend() );
                        float w = font->getStringBoundingBox(rev, 0, 0).width;
                        string s;
                        s += text[i];
                        
                        //ofDrawBitmapString(runningStr, 30, 30);
                        //ofRect(x+padding, y-10, w, 10);
                        if(w >= (width-(padding*2))) {
                            runningStr = runningStr.substr(0, runningStr.size()-2);
                            outstr = string( runningStr.rbegin(), runningStr.rend() );
                            break;
                        }
                        len ++;
                    }
                }
            }
        }
        else {
            int lettersThatFit = getNumLettersThatFitInWidth();
            if(text.size()>lettersThatFit) {
                int cutoff = MAX(textPos-lettersThatFit, 0);
                outstr = text.substr(cutoff, lettersThatFit);
            }
        }
        
        return outstr;
        
    }
    
    // ------------------------------------------
    float getCursorPosX() {
        float textX = 0;
        if(font!=NULL) {
            string str = getStringThatFits().substr(0, textPos);
            float  w   = font->getStringBoundingBox(str, 0, 0).width;
            return padding + w + padding;
        }
        else {
            int lettersThatFit = getNumLettersThatFitInWidth();
            textX = ((padding+2) + (textPos * 8));
            if(textPos>lettersThatFit) textX = (padding+2) + (lettersThatFit*8);
        }
        return textX;
    }

    // ------------------------------------------
    int getTotalLineBreaksInHeight() {
        int nBreaks = 0;
        string runningStr="";
        for (int i=0; i<text.size(); i++) {
            runningStr += text[i];
            float h = font->stringHeight(runningStr);
            if(h>=height-(padding*2)) {
                break;
            }
            if(text[i]=='\n') {
                
                nBreaks ++;
            }
        }
        return nBreaks;
    }
    // ------------------------------------------
    float getCursorPosY() {
        float textY = 0;
        /*int nBreaks = 0;
        for (int i=0; i<text.size(); i++) {
            if(text[i]=='\n') nBreaks ++;
        }
        if(font!=NULL) {
            textY = (font->getLineHeight() * nBreaks) + padding;
        }
        else {
            float textY = ((padding+2) + (textPos * 8));
            if(textPos>lettersThatFit) textX = (padding+2) + (lettersThatFit*8);
        }*/
        return textY;
    }
    
    // ------------------------------------------
    int getLineHeight() {
        return font==NULL?8:font->stringHeight("p");
    }
    
    // ------------------------------------------
    void draw() {
        
        int lineHeight     = getLineHeight();
        int lettersThatFit = getNumLettersThatFitInWidth();
        string str         = getStringThatFits();
        //cout << getTotalLineBreaksInHeight() << endl;
        ofSetColor(90, alpha);
        ofNoFill();
        ofRect(x, y, width, height);

        ofSetColor(255, 0, 0);
        ofFill();
        ofLine(x+padding, y, x+padding, y+height);
        ofLine(x+(width-padding), y, x+(width-padding), y+height);

        
        ofSetColor(fontColor, alpha);
        if(font!=NULL) {
            float sw = font->getStringBoundingBox("A",0,0).width;
            float textY = y;
            if(isMultiLine) textY += (lineHeight+padding);
            font->drawString(str, x+padding, textY);
        }
        else {
            ofDrawBitmapString(str, x+padding, y+padding+(height-padding)/2);
        }
        
        float textX    = getCursorPosX();
        float typeSize = font==NULL?8:font->getSize();
        float textY    = y + (isMultiLine?lineHeight : height/2);
        if(ofGetElapsedTimef()-blinkTime>0.5) {
            if(ofGetElapsedTimef()-blinkTime>0.7) blinkTime=ofGetElapsedTimef();
            ofSetColor(255, alpha);
            ofLine(textX+x, textY-typeSize/2, textX+x, textY+typeSize/2);
        }
    }

    
};