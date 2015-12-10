#pragma once
#include "ofMain.h"
#include "orb.h"
#include "GUI.h"
#include "ofxOculusDK2.h"
#include "ofxHoa.h"
#include "ofxStk.h"

using namespace hoa;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut(float *output,int bufferSize,int nChannels);
    void drawScene();
    void setupSound();
    
    int getselX();
    int getselY();
    int getselZ();
    
    ofCamera cam;
    ofLight light;
    
    vector <orb> orbs;
    
    float camx,camy,camz;
    float selX=0,selY=0,selZ=0;
    float selRad =1;
    
    GUI gui;
    
    //sound//
    int nOutputs, nInputs, sampleRate, bufferSize, nBuffers;
    ofSoundStream stream;
    static int const hoaOrder = 7;
    static int const numberOfParticles=10;
    
    float * harmonic;
    float * input;
    
    float harmonicsBuffer[10];

    Encoder<Hoa3d, float>::Multi * encoder;
    Decoder<Hoa3d, float>::Binaural * decoder;
    
    ofxHoaCoord<Hoa3d, float> * hoaCoord;
    stk::Clarinet file[numberOfParticles];
    
    ofxOculusDK2 oculusRift;
    
private:
    float** harmonicMatrix;
    float*  outputMatrix[2];
    
    bool useOculus=false;
};
