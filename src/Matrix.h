//
//  Matrix.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#ifndef __AppliMatriceLaser__Matrix__
#define __AppliMatriceLaser__Matrix__

#include <stdio.h>
#include "ofMain.h"
#include "Utils.h"
#include "Interface.h"

class Mirror {
    
    public :
    void setup();
    void draw();
    void update(ofVec3f Pos, ofVec3f vecXM0, ofVec3f vecYM0, ofVec3f vecZM0) ;
    
    int C ;         //dimension (mm)
    
    //Cordonnées des centres des miroirs dans le repère de la matrice :
    // [1] [2] [3] ^
    // [4] [5] [6] |Y        ou      [1] [2] [3] [4] [5] [6] [7] [8] [9]
    // [7] [8] [9] |----> X

    ofVec2f relPos = ofVec2f(0,0) ; //(FIXE) position dans le repère de la matrice
    ofVec3f absPos = ofVec3f(0,0,0) ; //(MOBILE) position dans le repère de la scène
    ofVec3f vI = ofVec3f(0,0,0) ;    //rayonIncident
    ofVec3f vN = ofVec3f(0,0,0) ;    //vecteurNormal
    ofVec3f vR = ofVec3f(0,0,0) ;    //rayonReflechi
    float alpha = 0;   // angle miroir.X
    float beta = 0;    //angle miroir.Y
    
    ofVec3f vecXMirror = ofVec3f(0,0,0); //repère du petit miroir,
    ofVec3f vecYMirror = ofVec3f(0,0,0); // le Z étant le vecteur Normal
    
} ;

class Matrix {
    
    public :
    void setup();
    void draw();
    void update(string mode, ofVec3f Laser, ofVec3f targetPoint, ofVec3f originPoint);
    
    vector<Mirror> Units ;
    
    //Caractéristiques ''Fixes''
    int C = 0 ;         //dimension (mm)
    int Nx = 0 ;        //nb Unités direction 1
    int Ny = 0 ;        //nb Unités direction 2
    int N = Nx*Ny ;     //nb Unités Total
    ofVec3f Pos = ofVec3f(0,0,0) ;   //position du centre de la matrice dans le repère de la scène
    float angleX = 0; //
    float angleY = 0; //ANGLES EN RADIANS
    float angleZ = 0; //
    ofVec3f vecXM0 = ofVec3f(0,0,0) ;
    ofVec3f vecYM0 = ofVec3f(0,0,0) ; //Repère de la matrice
    ofVec3f vecZM0 = ofVec3f(0,0,0) ;
    
    
} ;


#endif /* defined(__AppliMatriceLaser__Matrix__) */
