//
//  threadInterface.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 09/12/2014.
//
//

#ifndef __MatriceLaser__threadInterface__
#define __MatriceLaser__threadInterface__

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "Utils.h"

class threadInterface {
    
    public :
    void setup();
    void draw();
    void update();
    bool mouseOn(int x,int y);
    void drawOffsetInterface();
    void setupOffsetInterface();
    
    //Main Panel
    ofxPanel threadPanel ;
    ofxLabel threadLabel ;
    ofxLabel warningLabel ;
    ofxToggle setSerialButton ; //used as a pushButton
    ofxToggle streamToggle ;
    ofxToggle debugToggle ;
    ofxToggle offsetToggle ;
    
    //Offsetting Panel
    ofxPanel offsetPanel ;
    ofxIntSlider chooseMirror ;
    bool offsetting ; //is he user offsetting ?
    int mirrorOffsetted = 0; //Current Mirror Offsetted
    int haveToBeSetted = -1 ; //last Mirror Offsetted, return the number of the mirror to be set, or -1 if none (set by thisclass::update and calculthread::update)
    
    //XYPad For Offsetting
    ofVec2f mousePos = ofGetWindowSize()/2; //Mouse position when dragged, set by offApp::mouseDragged and calculThread::update)
    ofVec2f cursorPos = ofGetWindowSize()/2; //Mouse position when dragged, set by offApp::mouseDragged and calculThread::update)
    ofRectangle XYPadRectangle = ofRectangle(ofGetWidth()/2-200, ofGetHeight()/2-200, 400, 400); //Shape of the Pad
    ofVec2f position = ofVec2f(0,0); //Position of the total offset for the current mirror in steps (read by calculThread)
    
    ofVec2f XYPadOffset = ofVec2f(0,0) ; //Speed offsetting up by increments steps when the Mouse is close to XYPad Boundaries (modified by ofApp.mousedragged and calculthread.update)
    ofRectangle XYPadSpeedRectangle = ofRectangle(ofGetWidth()/2-180, ofGetHeight()/2-180, 360, 360); //Outside of this rectangle, position increments (see ofApp.mousedragged)
    ofVec2f outOfBounds = ofVec2f(0,0); //Set the direction of incrementation : example (-1,1) will move the mirror ++ on X and -- on Y
    
};

#endif /* defined(__MatriceLaser__threadInterface__) */
