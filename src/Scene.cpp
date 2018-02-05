//
//  Scene.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#include "Scene.h"

void Scene::drawFloorGrid(){ //not used function, drew a floor with grid
    ofNoFill();
    ofSetColor(0);
    for (int i=0; i<=5;i++){
        for (int j=0; j<=5;j++){
            ofRect(1000*i, 1000*j, 0, 1000, 1000);}}
}

void Scene::drawFloorFull(){ // the one used now
    ofFill();
    ofSetColor(240);
    ofRect(0,0,0,sceneBox.x,sceneBox.y);
}


void Scene::drawSceneBox(){
    ofSetColor(0);
    ofNoFill();
    ofDrawBox(sceneBox.x/2, sceneBox.y/2, sceneBox.z/2, sceneBox.x, sceneBox.y, sceneBox.z);
}

void Scene::setup(){
    Matrix.setup();
}


void Scene::draw(){
    
    drawFloorFull();
    drawSceneBox();
    
    //Positions of elements
    drawPoint(Laser, ofColor(150,0,0));
    drawPoint(targetPoint, ofColor(0,0,150));
    drawPoint(originPoint, ofColor(0,150,0));
    drawPoint(Matrix.Pos, ofColor(100));
    
    Matrix.draw();
    
    // draw Bases ?
    if (Interface.Bases==true){
        drawBase(Matrix.Pos, Matrix.vecXM0, Matrix.vecYM0, Matrix.vecZM0, ofColor(100));
        drawBase(ofVec3f(0,0,0), ofVec3f(1,0,0), ofVec3f(0,1,0), ofVec3f(0,0,1),ofColor(0));
    }
    
    //Draw mirrors's Centers ? Vectors ?
    for (int i=1; i<=Matrix.N; i++) {
        if (Interface.MirrorsCenters)
                drawPoint(Matrix.Units[i].absPos, ofColor(100));
        if (Interface.vR && (Interface.toPoint || Interface.parallel))
            drawVector("Start", Matrix.Units[i].absPos, Matrix.Units[i].vR, ofColor(0,0,200));
        if (Interface.vR && Interface.fromPoint)
            drawVector("Start", Matrix.Units[i].absPos, Matrix.Units[i].vR, ofColor(0,200,0));
        if (Interface.vI)
                drawVector("End", Matrix.Units[i].absPos, Matrix.Units[i].vI, ofColor(200,0,0));
        if (Interface.vN)
                drawVector("Start", Matrix.Units[i].absPos, Matrix.Units[i].vN, ofColor(100));
        //if (Interface.Mirrors)
            Matrix.Units[i].draw();
    }
    
}


void Scene::update(){
    Interface.update() ;
    mode = Interface.mode ;
    
    //Get the interface values
    
    sceneBox = ofVec3f(Interface.sceneXBoxSlider,Interface.sceneYBoxSlider,Interface.sceneZBoxSlider);
    Laser = ofVec3f(Interface.laserX,Interface.laserY,Interface.laserZ);
    targetPoint = ofVec3f(Interface.targetX,Interface.targetY,Interface.targetZ);
    originPoint = ofVec3f(Interface.originX,Interface.originY,Interface.originZ);
    
    Interface.matrixX.setMax(Interface.sceneXBoxSlider);
    Interface.matrixY.setMax(Interface.sceneYBoxSlider);
    Interface.matrixZ.setMax(Interface.sceneZBoxSlider);
    
    Interface.laserX.setMax(Interface.sceneXBoxSlider);
    Interface.laserY.setMax(Interface.sceneYBoxSlider);
    Interface.laserZ.setMax(Interface.sceneZBoxSlider);
    
    Interface.targetX.setMax(Interface.sceneXBoxSlider);
    Interface.targetY.setMax(Interface.sceneYBoxSlider);
    Interface.targetZ.setMax(Interface.sceneZBoxSlider);
    
    Interface.originX.setMax(Interface.sceneXBoxSlider);
    Interface.originY.setMax(Interface.sceneYBoxSlider);
    Interface.originZ.setMax(Interface.sceneZBoxSlider);
    
    Matrix.Pos = ofVec3f(Interface.matrixX,Interface.matrixY,Interface.matrixZ);
    Matrix.angleX = ofDegToRad(Interface.angleX) ;
    Matrix.angleY = ofDegToRad(Interface.angleY) ;
    Matrix.angleZ = ofDegToRad(Interface.angleZ) ;
    Matrix.C = Interface.C ;
    Matrix.Nx = Interface.nXSlider ;
    Matrix.Ny = Interface.nYSlider ;
    Matrix.N = Matrix.Nx*Matrix.Ny ;
    
    //let's go, Update !
    Matrix.update(mode, Laser, targetPoint, originPoint);
}


