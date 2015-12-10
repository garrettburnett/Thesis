#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
   
    if(useOculus){
    
        oculusRift.baseCamera = &cam;
        oculusRift.setup();
    }
    setupSound(); //see this function for sounded related code.
    
    ofBackground(0);
    ofEnableDepthTest();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofHideCursor();
    camx=0;
    camy=0;
    camz=0;
 
    light.setPosition(10,-20,0);
    light.enable();
    
    ofToggleFullscreen();
    
    cam.begin();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0;i<orbs.size();i++){
        orbs[i].update(ofVec3f(selX,selY,selZ), orbs, gui.mode);
        hoaCoord->setSourcePositionDirect(i, orbs[i].position);//sets the respective position for each orb and sound source. Pairs them.
    }
    gui.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    if(useOculus){
    glEnable(GL_DEPTH_TEST);

    oculusRift.beginLeftEye();
    drawScene();
    oculusRift.endLeftEye();
    
    oculusRift.beginRightEye();
    drawScene();
    oculusRift.endRightEye();
    
    //pushes the render texture to the viewer
    oculusRift.draw();
   
        glDisable(GL_DEPTH_TEST);
    }
    
    else{
        cam.setVFlip(true);
        cam.begin();
        drawScene();
        cam.end();
        gui.draw(selX, selY, selZ);
    }
}

void ofApp::drawScene(){
    
    for(int i=0;i<orbs.size();i++)
    {
        orbs[i].draw();
    }
    
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofSetSphereResolution(10);
    
    ofDrawSphere(ofVec3f(selX,selY,selZ),selRad);
    ofPushMatrix();
    ofRotate(90, 0, 0, -1);
    ofTranslate(0, 0, 0);
    ofDrawGridPlane(500.0f, 10.0f, false );
    ofPopMatrix();
         gui.draw(selX, selY, selZ);
   // cam.end();
}

void ofApp::setupSound(){
    
    nOutputs = 2;
    nInputs = 0;
    sampleRate = 44100;
    bufferSize = 512;
    nBuffers = (nOutputs+nInputs)*2;
    
    stk::Stk::setSampleRate(44100.0);
    
    harmonic = new float[(hoaOrder+1)*(hoaOrder+1)];
    input =new float[numberOfParticles];
    
    encoder = new Encoder<Hoa3d, float>::Multi(hoaOrder, numberOfParticles);
    
    decoder = new Decoder<Hoa3d, float>::Binaural(hoaOrder);
    decoder->setCropSize(512);
    decoder->computeRendering(bufferSize);
    
    harmonicMatrix = new float * [(hoaOrder+1)*(hoaOrder+1) ];
    for(int i = 0; i < (hoaOrder+1)*(hoaOrder+1); i++){
        harmonicMatrix[i] = new float[bufferSize];}
    
    outputMatrix[0] = new float[bufferSize];
    outputMatrix[1] = new float[bufferSize];
    
    // CREATE HOACOORD AND SET RAMP IN MILLISECONDS
    hoaCoord = new ofxHoaCoord<Hoa3d, float>(numberOfParticles);
    hoaCoord->setRamp(50, sampleRate);
    
    // SET SPATIAL REFERENCE
    hoaCoord->setAmbisonicRadius(10000);
    hoaCoord->setAmbisonicCenter(ofVec3f(0,0,0));
    stream.setup(this, nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
    
    
    for(int i = 0; i<numberOfParticles;i++){
        clar[i].noteOn(i*300, 1);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
        {   orb tempOrb;
            tempOrb.setup(selX,selY,selZ,selRad);
            orbs.push_back(tempOrb);//using vector
    
        }
            break;
            
        case OF_KEY_LEFT:
        {
            selX=selX-100;
        }
            break;
            
        case OF_KEY_RIGHT:
        {
            selX=selX+100;
        }
            break;
            
        case 'w':
        {
            selY=selY-.1;
        }
            break;
        case 's':
        {
            selY=selY+.1;
        }
            break;
            
        case OF_KEY_UP:
        {
            selZ=selZ-1;
            
        }
            break;
            
        case OF_KEY_DOWN:
        {
            selZ=selZ+1 ;
            
        }
            break;
            
        case '[':
        {
            selRad=selRad-.1;
        }
            break;
        case ']':
        {
            selRad=selRad+.1;
        }
            break;
            
        case 'u':
        {
            gui.mode=GUI::STILL;
        }
            break;
        case 'i':
        {
            gui.mode=GUI::DISPERSE;
        }
            break;
        case 'o':
        {
            gui.mode=GUI::FISH;
        }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++)
    {
        
        for(int j = 0; j < numberOfParticles; j++)
        {
            input[j] = (clar[j].tick()/numberOfParticles)*0.3;
            encoder->setRadius(j, hoaCoord->getRadius(j));
            encoder->setAzimuth(j, hoaCoord->getAzimuth(j));
            encoder->setElevation(j, hoaCoord->getElevation(j));
        }
        
        encoder->process(input,harmonic);
        for (int j = 0; j < (hoaOrder+1)*(hoaOrder+1); j++)
        {
            harmonicMatrix[j][i] = harmonicsBuffer[j];
        }
    }
    
    decoder->processBlock(const_cast<const float **>(harmonicMatrix), outputMatrix);
    
    for (int i = 0; i < bufferSize; i++)
        
    {
        output[i*nChannels] = outputMatrix[0][i];
        output[i*nChannels+1] = outputMatrix[1][i];
    }
}
