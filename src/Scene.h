//
//  Scene.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#ifndef __AppliMatriceLaser__Scene__
#define __AppliMatriceLaser__Scene__

#include <stdio.h>
#include "Matrix.h"
#include "Interface.h"
#include "Utils.h"

class Scene {
    
    public :
    void setup();
    void update();
    void draw();
    void drawSceneBox();
    void drawFloorGrid();
    void drawFloorFull();
    
    ofVec3f sceneBox = ofVec3f(5000,4000,3000) ;  //boite limitant la scène
    
    Matrix Matrix ;     //Matrice de miroirs
    
    ofVec3f Laser = ofVec3f(0,1000,1000) ;     //Position du laser
    ofVec3f originPoint = ofVec3f(1000,1000,0) ; //position du point "source virtuelle"
    ofVec3f targetPoint = ofVec3f(1000,0,1000) ; //position du point "cible"
    
    string mode = "parallel" ; // setting the behaviour of the matrix (=="parallel", "toPoint", "fromPoint")
    
    Interface Interface ;
};


#endif /* defined(__AppliMatriceLaser__Scene__) */
