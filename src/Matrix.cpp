//
//  Matrix.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#include "Matrix.h"


void Mirror::setup(){
}


void Mirror::draw(){
    drawPlane(absPos, C, vecXMirror, vecYMirror, ofColor(0));
}


void Mirror::update(ofVec3f Pos, ofVec3f vecXM0, ofVec3f vecYM0, ofVec3f vecZM0){
    absPos = Pos + relPos.x * vecXM0 + relPos.y * vecYM0 ; //set position of mirror in the 0 Base
}


void Matrix::setup(){
    Nx = 3;
    Ny = 3;
    N = Nx*Ny ;
    Mirror iMirror;
    for (int i=1; i<=100;i++) Units.push_back(iMirror); //Full the mirror vector with defaults ones
}


void Matrix::draw(){
    //for (int i=1; i<=N;i++) Units[i].draw();
}


void Matrix::update(string mode, ofVec3f Laser, ofVec3f targetPoint, ofVec3f originPoint){
    N = Nx*Ny;
    
    //Setting the Matrix base
    vecXM0 = ofVec3f(cos(angleZ)*cos(angleY),
                     cos(angleX)*sin(angleZ)+sin(angleX)*sin(angleY)*cos(angleZ),
                     sin(angleX)*sin(angleZ)-cos(angleX)*sin(angleY)*cos(angleZ));
    vecYM0 = ofVec3f( -sin(angleZ)*cos(angleY),
                     cos(angleZ)*cos(angleX)-sin(angleX)*sin(angleZ)*sin(angleY),
                     cos(angleZ)*sin(angleX)+cos(angleX)*sin(angleZ)*sin(angleY));
    vecZM0 = ofVec3f( sin(angleY),
                     -cos(angleY)*sin(angleX),
                     cos(angleX)*cos(angleY));
    
    //Setting the positions of the mirrors in the M base
    for (int i=1; i<=Nx; i++) {
        for (int j=1; j<=Ny; j++) {
            Units[i+(j-1)*Nx].relPos = ofVec3f((i-1)*C-(Nx-1)*C/2, (j-1)*C-(Ny-1)*C/2, 0);
        }
    }
    
    //Setting the positions of the mirrors in the 0 base
    for (int i=1; i<=N;i++) Units[i].update(Pos,vecXM0,vecYM0,vecZM0);
    
    //Computing incident, reflected and normal vectors
    for (int i=1; i<=N;i++)
    {
        Units[i].C = C ;
        Units[i].vI = normed(Units[i].absPos - Laser) ;
        
        if (mode == "toPoint") Units[i].vR = normed(targetPoint - Units[i].absPos) ;
        if (mode == "parallel") Units[i].vR = normed(targetPoint - Pos) ;
        if (mode == "fromPoint") Units[i].vR = normed(Units[i].absPos - originPoint) ;
        
        Units[i].vN = normed(Units[i].vR - Units[i].vI) ;
        
        
        Units[i].alpha=180/PI*(asin(scalarProduct(Units[i].vN,vecXM0)));
        Units[i].beta=180/PI*(asin(scalarProduct(Units[i].vN,vecYM0)));
        
        Units[i].vecXMirror = cos(PI/180*Units[i].alpha)*vecXM0
                                - sin(PI/180*Units[i].alpha)*Units[i].vN;
        Units[i].vecYMirror = cos(PI/180*Units[i].beta)*vecYM0
                                - sin(PI/180*Units[i].beta)*Units[i].vN;
    }
    
}