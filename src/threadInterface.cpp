//
//  threadInterface.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 09/12/2014.
//
//

#include "threadInterface.h"


void threadInterface::setupOffsetInterface(){
    offsetPanel.setup() ;
    offsetPanel.setPosition(ofGetWidth()-210, 20 + threadPanel.getHeight());
    offsetPanel.add(chooseMirror.setup("CHOOSE MIRROR", 1,1,2)) ;
}


void threadInterface::drawOffsetInterface(){
    offsetPanel.draw();
    
    //Draw XYPAD
    ofSetColor(230,230,230, 80);
    ofFill();
    ofRect(XYPadRectangle);
    ofSetColor(0);
    ofNoFill();
    ofRect(XYPadRectangle);
    ofRect(XYPadSpeedRectangle);
    
    //draw Cursor
    ofCircle(cursorPos,5);
    
    //Draw Infos
    ofDrawBitmapString("MIRROR n°"+ ofToString((int)chooseMirror) + " :", ofGetWidth()/2-200, ofGetHeight()/2-205);
    ofDrawBitmapString("X : "+ ofToString(position.x), ofGetWidth()/2-200, ofGetHeight()/2+215);
    string msg = "Y : "+ ofToString(position.y) ;
    ofDrawBitmapString(msg, ofGetWidth()/2+200-8*msg.length(), ofGetHeight()/2+215);
}


void threadInterface::setup(){
    threadPanel.setup() ;
    threadPanel.setPosition(ofGetWidth()-210, 10);
    threadPanel.add(threadLabel.setup("Thread", " ")) ;
    threadPanel.add(warningLabel.setup("SET YOUR SCENE BEFORE", " ")) ;
    threadPanel.add(setSerialButton.setup("1 : Set Serial Ports",false)) ;
    threadPanel.add(streamToggle.setup("2 : Stream To Serial",false)) ;
    threadPanel.add(debugToggle.setup("3 : Debug",false)) ;
    threadPanel.add(offsetToggle.setup("SETTING OFFSET",false)) ;
    
    setupOffsetInterface() ;
    //haveToBeSetted = -1 ;
}


void threadInterface::draw(){
    threadPanel.draw() ;
    if (offsetting) drawOffsetInterface() ;
}


void threadInterface::update(){
    
    if (offsetToggle){
    //Activation de la phase d'offset
    if (offsetToggle && !offsetting) {
        offsetting = true ;
        mirrorOffsetted = chooseMirror ;
    }
    
    //Quand on change de miroir, set un flag pour que le thread envoie le message de set à l'arduino.
    if (mirrorOffsetted!=chooseMirror && offsetting)
    {
        haveToBeSetted = mirrorOffsetted ;
        mirrorOffsetted = chooseMirror ;
    }
    
    //Normal Offsetting
    if (offsetting && !XYPadSpeedRectangle.inside(mousePos)) {
            if (XYPadSpeedRectangle.getMinX()>mousePos.x){
                outOfBounds.x = round((mousePos.x - XYPadSpeedRectangle.getMinX())/20) ;
                cursorPos.x = XYPadSpeedRectangle.getMinX() ;}
            else if (XYPadSpeedRectangle.getMaxX()<mousePos.x){
                outOfBounds.x = round((mousePos.x - XYPadSpeedRectangle.getMaxX())/20) ;
                cursorPos.x = XYPadSpeedRectangle.getMaxX() ;}
            else {
                outOfBounds.x = 0 ;
                cursorPos.x = mousePos.x ;}
        
            if (XYPadSpeedRectangle.getMinY()>mousePos.y){
                outOfBounds.y = round((mousePos.y - XYPadSpeedRectangle.getMinY())/20) ;
                cursorPos.y = XYPadSpeedRectangle.getMinY() ;}
            else if (XYPadSpeedRectangle.getMaxY()<mousePos.y) {
                outOfBounds.y = round((mousePos.y - XYPadSpeedRectangle.getMaxY())/20) ;
                cursorPos.y = XYPadSpeedRectangle.getMaxY() ;}
            else {
                outOfBounds.y = 0 ;
                cursorPos.y = mousePos.y ;}
    }
    else if (offsetting) {
        outOfBounds = ofVec2f(0,0) ;
        cursorPos = mousePos ;}

    XYPadOffset += outOfBounds ;
    position = mousePos + XYPadOffset - ofGetWindowSize()/2 ;
    }
    
    if (!offsetToggle) offsetting = false ;
}


bool threadInterface::mouseOn(int x,int y){
    if (mouseOnPanel(threadPanel,x,y)) return true ;
    if (mouseOnPanel(offsetPanel,x,y) && offsetting) return true ;
    //if (XYPadRectangle.inside(x,y) && offsetting) return true ;
    else return false ;
}