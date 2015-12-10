//
//  Orb.h
//
//
//  Created by Garrett on 10/3/15.
//
#ifndef ____Orb__
#define ____Orb__

#include "ofMain.h"
#include "ofxHoa.h"
#include "GUI.h"
#include "ofxStk.h"

class orb{
    
public:
    void update(ofVec3f selector, vector<orb> orbs, GUI::MODE _mode);
    void draw();
    void setup(float x,float y, float z, float _rad);
    void seek(ofVec3f target);
    //Constructor
    orb();
    //Positions
    
    //Sizing
    float orbRadius;
    
    //Appearance
    int resolution;
    ofVec3f position;
    stk::FileLoop file;
private:
    //private attributes go here if necessary.//
    float r;
    int red;
    int green;
    int blue;
    float posX;
    float posY;
    float posZ;
    
    
    ofVec3f velocity; //a velocity vertex
    ofVec3f acceleration;// an acceleration vertex.
    float maxForce;
    float maxSpeed;
    void applyForce(ofVec3f force);
    void separate(vector <orb> orbs);
    
    //MODES//
    
    void still();
    void disperse();
    void fish(ofVec3f target, vector <orb> orbs);
    
    
    
};


#endif /* defined(____Orb__) */
