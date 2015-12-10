//
//  GUI.cpp
//
//
//  Created by Garrett on 10/31/15.
//
//

#include "GUI.h"

GUI::GUI(){
//    nordMed.loadFont("Nord Medium.otf", 20);
//    nordMedLarge.loadFont("Nord Medium.otf", 30);
    //nordMed.bMakeContours=true;
}
void GUI::update(){
    int panelWidth = ofGetWidth();
    int panelX = 0;
    int panelY = ofGetHeight()-100;
}
void GUI::draw(float selX, float selY, float selZ){
    
    // These strings display entry information.
    xString = "X: " + ofToString(selX);
    yString = "Y: " + ofToString((selY*-1));
    zString = "Z: " + ofToString(selZ*-1);
    
    //Text is drawn here first.//
//    ofSetColor(255);
//    nordMed.drawString(xString, panelX+20, ofGetHeight()-50);
//    nordMed.drawString(yString, panelX+120, ofGetHeight()-50);
//    nordMed.drawString(zString, panelX+220, ofGetHeight()-50);
//    nordMedLarge.drawString(modeToString(mode), ofGetWidth()-200, ofGetHeight()-40);
     ofSetColor(255);
    
    ofDrawBitmapStringHighlight(xString, panelX+20, ofGetHeight()-50, ofColor(0),ofColor(255));
    ofDrawBitmapString(yString, panelX+120, ofGetHeight()-50);
    ofDrawBitmapString(zString, panelX+220, ofGetHeight()-50);
    ofDrawBitmapString(modeToString(mode), ofGetWidth()-200, ofGetHeight()-40);
    
    //Paneling is drawn here//
    ofSetColor(130,130,130,255);
    ofRect(0, ofGetHeight()-100, ofGetWidth(), ofGetHeight());
}

string GUI::modeToString(int _mode){
    
    switch (_mode) {
        case 0:
            return "Still";
            break;
        case 1:
            return "Disperse";
            break;
        case 2:
            return "Fish";
            break;
        default:
            break;
    }
    
}
