//
//  GUI.h
//
//
//  Created by Garrett on 10/31/15.

#ifndef ____GUI__
#define ____GUI__

#include <stdio.h>
#include "ofMain.h"

class GUI{
    
public:
    
    enum MODE
    {
        STILL, //default
        DISPERSE,
        FISH,
        SEEK,
        ARRIVE,
        FLOCK,
        ORBIT
    };
    MODE mode = STILL;
    void update();
    void draw(float selX, float selY,float selZ);
    string modeToString(int _mode);//a method to convert enum type Mode into strings for GUI.
    
    GUI();
    ofTrueTypeFont nordMed;
    ofTrueTypeFont nordMedLarge;
    
    //panel attributes
    int panelWidth = ofGetWidth();
    int panelHeight = 100;
    int panelX = 0;
    int panelY = ofGetHeight()-100;
    
private:
    string xString;
    string yString;
    string zString;
    string modeString;
};

#endif /* defined(____GUI__) */
