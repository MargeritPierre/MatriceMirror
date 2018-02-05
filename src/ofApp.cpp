#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    
    calculThread.Interface.setup();
    Scene.Interface.setup();
    Scene.setup();
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    ofBackground(255);
    ofEnableAntiAliasing();
    
    cam.setTarget(Scene.sceneBox/2);
    cam.setOrientation(ofVec3f(70,0,-20));
    cam.setDistance(10000);
    cam.setNearClip(100);
    cam.setFarClip(100000);
    
    calculThread.start();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    Scene.update();
    calculThread.update();
    if (Scene.Interface.mouseOn(mouseX,mouseY) || calculThread.Interface.mouseOn(mouseX,mouseY) || calculThread.Interface.offsetting) cam.disableMouseInput();
    else cam.enableMouseInput();
    
    calculThread.setN(Scene.Matrix.N);
    for (int i=1;  i<=Scene.Matrix.N; i++) {
        calculThread.setAngle(i, "alpha",Scene.Matrix.Units[i].alpha);
        calculThread.setAngle(i, "beta",Scene.Matrix.Units[i].beta);
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
        ofEnableDepthTest();
        cam.begin();
            Scene.draw();
        cam.end();
        ofDisableDepthTest();
    
    //LABELS ----------------------------------------------------------------------------------------
    ofDrawBitmapString("Laser", cam.worldToScreen(Scene.Laser)+10);
    ofDrawBitmapString("Origin", cam.worldToScreen(Scene.originPoint)+10);
    ofDrawBitmapString("Target", cam.worldToScreen(Scene.targetPoint)+10);
    ofDrawBitmapString("Matrix", cam.worldToScreen(Scene.Matrix.Pos)+10);

    //Numbers of Mirrors
    for (int i=1; i<=Scene.Matrix.N; i++) {
        ofDrawBitmapString(ofToString(i), cam.worldToScreen(Scene.Matrix.Units[i].absPos));
    }
    
    //Axes Labels (Matrix)
    if (Scene.Interface.Bases){
        ofDrawBitmapString("X", cam.worldToScreen(Scene.Matrix.Pos + Scene.Matrix.vecXM0*450)+10);
        ofDrawBitmapString("Y", cam.worldToScreen(Scene.Matrix.Pos + Scene.Matrix.vecYM0*450)+10);
        ofDrawBitmapString("Z", cam.worldToScreen(Scene.Matrix.Pos + Scene.Matrix.vecZM0*450)+10);
        //(Base)
        ofDrawBitmapString("X", cam.worldToScreen(ofVec3f(1,0,0)*450)+10);
        ofDrawBitmapString("Y", cam.worldToScreen(ofVec3f(0,1,0)*450)+10);
        ofDrawBitmapString("Z", cam.worldToScreen(ofVec3f(0,0,1)*450)+10);}
    //-----------------------------------------------------------------------------------------------
    
    //Framerate
    ofDrawBitmapStringHighlight("FrameRate : " + ofToString(floor(ofGetFrameRate())) , ofGetWidth()-130, ofGetWindowHeight()-20);
    
    
    if (!calculThread.Interface.offsetting) Scene.Interface.draw(); //Hide scene interface to lock settings during offsetting
    
    calculThread.Interface.draw() ;
}


//--------------------------------------------------------------
void ofApp::exit(){
    // make a smooth exit of the thread
    calculThread.stop();
    calculThread.waitForThread();
    cout << "ofApp Closed" << endl;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //Setting parameters for the XYPAD of offsetting
    if (calculThread.Interface.offsetting){
        if (!calculThread.Interface.mouseOn(x, y) ) calculThread.Interface.mousePos = ofVec2f(x, y) ;
        else calculThread.Interface.mousePos = ofVec2f(0,0) + ofGetWindowSize()/2 ;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //Setting parameters for the XYPAD of offsetting
    if (calculThread.Interface.offsetting){
        calculThread.Interface.outOfBounds = ofVec2f(0, 0);
        if (!calculThread.Interface.XYPadSpeedRectangle.inside(x, y)){
            calculThread.Interface.XYPadOffset += calculThread.Interface.mousePos - ofGetWindowSize()/2 ;
            calculThread.Interface.mousePos = ofVec2f(0, 0) + ofGetWindowSize()/2 ;}
    }
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
