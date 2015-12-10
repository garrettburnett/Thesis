//
//  Orb.cpp
//  Created by Garrett on 10/3/15.
#include "orb.h"  


orb::orb()
{
    ofSetColor(73, 222,205);
    //a = ofRandom(-1.5,1.5);
}
void orb::setup(float _x, float _y, float _z,float _rad){
    orbRadius = _rad;
    position.set(_x,_y,_z);
    acceleration.set(0,0,0);
    velocity.set(ofRandom(-2,2),ofRandom(-2,2),ofRandom(-2,2));
}
void orb::update(ofVec3f target, vector <orb> orbs, GUI::MODE _mode)
{
    ofSetColor(73,222,205);
    
    switch (_mode) {
        case 0:
            still();
            break;
        case 1:
            disperse();
            break;
        case 2:
            fish(target, orbs);
            break;
            
        default:
            break;
    }
}

void orb::draw()
{
    ofSetSphereResolution(50);
    ofFill();
    ofDrawSphere(position, orbRadius);
}

void orb::applyForce(ofVec3f force){
    // We could add mass here if we want A = F / M
    acceleration+=force;
}

//steers toward a given position
void orb::seek(ofVec3f target){
    //SEEK = desired - velocity//
    ofVec3f desired = target-position;
    //scale to maximum speed//
    
    ofVec3f steer = desired-velocity;
    steer.limit(maxForce);
    applyForce(steer);
}

//checks for nearby orbs and steers away.
void orb::separate(vector <orb> orbs)
{
    float desiredSeparation = r*2;
    ofVec3f sum;
    float count=0;
    //for every orb currently in the system, check if it's too close
    for(int i=0;i<orbs.size();i++)
    {
        float d = position.distance(orbs[i].position);
        if((d>0) && (d<desiredSeparation)){
            //calculate vector pointing away from neighbor.
            ofVec3f diff=position-orbs[i].position;
            diff.normalize();
            diff=diff/d;
            sum+=diff;
            count++;
        }//end if
    }//end loop
    
    if (count>0){
        ofVec3f steer = sum-velocity;
        steer.limit(maxForce);
        applyForce(steer);
    }//end if
}//end method


void orb::still(){
    //literally does nothing,
}

void orb::disperse(){
    
    maxSpeed =1;
    
    velocity+=acceleration;
    velocity.limit(maxSpeed);
    
    position+=velocity;
    acceleration=acceleration*0;
    
    
}

void orb::fish(ofVec3f _target, vector <orb> _orbs){
    //ofSetColor(201,73,73);
    r=30;
    maxForce =.03;
    maxSpeed =30;
    
    velocity+=acceleration;
    velocity.limit(this->maxSpeed);
    
    position+=velocity;
    acceleration=acceleration*0;
    
    this->separate(_orbs);
    this->seek(_target);
    
    
    
}

