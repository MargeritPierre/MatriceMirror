//
//  Interface.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#ifndef __AppliMatriceLaser__Interface__
#define __AppliMatriceLaser__Interface__

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "Utils.h"


class Interface {
    public :
    void setup();
    void draw();
    void update();
    bool mouseOn(int x,int y);
    
    string mode = "parallel" ;
    
    //Panel1
    ofxPanel fixedPanel ;
    ofxLabel fixedLabel ;
    ofxIntSlider sceneXBoxSlider ;
    ofxIntSlider sceneYBoxSlider ;
    ofxIntSlider sceneZBoxSlider ;
    ofxIntSlider C ;
    ofxIntSlider nXSlider ;
    ofxIntSlider nYSlider ;
    
    //Panel2
    ofxPanel matrixPanel ;
    ofxLabel matrixLabel ;
    ofxIntSlider matrixX ;
    ofxIntSlider matrixY ;
    ofxIntSlider matrixZ ;
    ofxIntSlider angleX ;
    ofxIntSlider angleY ;
    ofxIntSlider angleZ ;
    
    //Panel3
    ofxPanel laserPanel ;
    ofxLabel laserLabel ;
    ofxIntSlider laserX ;
    ofxIntSlider laserY ;
    ofxIntSlider laserZ ;
    ofxToggle fromPoint ;
    ofxToggle parallel ;
    ofxToggle toPoint ;
    ofxIntSlider targetX ;
    ofxIntSlider targetY ;
    ofxIntSlider targetZ ;
    ofxIntSlider originX ;
    ofxIntSlider originY ;
    ofxIntSlider originZ ;
    
    //Panel4
    ofxPanel graphPanel ;
    ofxLabel graphLabel ;
    ofxToggle vI ;
    ofxToggle vN ;
    ofxToggle vR ;
    ofxToggle MirrorsCenters ;
    ofxToggle Bases ;
    
};


#endif /* defined(__AppliMatriceLaser__Interface__) */
