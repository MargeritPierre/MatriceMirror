//
//  CalculThread.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 05/12/2014.
//
//

#ifndef __MatriceLaser__CalculThread__
#define __MatriceLaser__CalculThread__

#include <stdio.h>
#include "ofMain.h"
#include "ofThread.h"
#include "ofSerial.h"
#include "threadInterface.h"



class calculThread : public ofThread
{
    
public :
    bool onComputing = false ;
    ofSerial serials[3] ; //add serials if needed
    bool serialSetted = false ;

    void start();
    void stop();
    void update();
    
    void setAngle(int ID, string angleName, float Angle);
    void setLength(int IDMotor);
    void setSteps(int IDMotor);
    void setN(int Nombre);
    
    void threadedFunction();
    
    void sendString(string msg);
    
    int N = 10 ;
    float Angles[200] ;
    float Lengths[200] ;
    float Steps[200] ;
    bool posChanged = false ;
    
    threadInterface Interface ;
    
    
};


#endif /* defined(__MatriceLaser__CalculThread__) */
