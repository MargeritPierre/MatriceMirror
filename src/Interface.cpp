//
//  Interface.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 26/11/2014.
//
//

#include "Interface.h"


void Interface::setup(){
    
    //Panel1
    fixedPanel.setup();
    fixedPanel.setPosition(10, 10);
    fixedPanel.add(fixedLabel.setup("Dimensions Fixes",""));
    fixedPanel.add(sceneXBoxSlider.setup("Scene.X",5000,0,10000));
    fixedPanel.add(sceneYBoxSlider.setup("Scene.Y",4000,0,10000));
    fixedPanel.add(sceneZBoxSlider.setup("Scene.Z",3000,0,10000));
    fixedPanel.add(C.setup("Cote Miroirs",110,0,1000));
    fixedPanel.add(nXSlider.setup("Nb.X", 3,1,10));
    fixedPanel.add(nYSlider.setup("Nb.Y", 1,1,10));
    
    //Panel2
    matrixPanel.setup();
    matrixPanel.setPosition(10, 20 + fixedPanel.getHeight());
    matrixPanel.add(matrixLabel.setup("Matrice","")) ;
    matrixPanel.add(matrixX.setup("Pos.x",0,0,10000)) ;
    matrixPanel.add(matrixY.setup("Pos.y",2000,0,10000)) ;
    matrixPanel.add(matrixZ.setup("Pos.z",970,0,10000)) ;
    matrixPanel.add(angleX.setup("Angle.x",0,-180,180)) ;
    matrixPanel.add(angleY.setup("Angle.y",90,-180,180)) ;
    matrixPanel.add(angleZ.setup("Angle.z",0,-180,180)) ;
    
    //Panel3
    laserPanel.setup();
    laserPanel.setPosition(10, 30 + fixedPanel.getHeight() + matrixPanel.getHeight());
    laserPanel.add(laserLabel.setup("Laser",""));
    laserPanel.add(laserX.setup("Laser.X",850,0,10000));
    laserPanel.add(laserY.setup("Laser.Y",2000,0,10000));
    laserPanel.add(laserZ.setup("Laser.Z",810,0,10000));
    laserPanel.add(fromPoint.setup("From Point", false));
    laserPanel.add(parallel.setup("Parallel",true));
    laserPanel.add(toPoint.setup("To Point",false));
    laserPanel.add(targetX.setup("Target.X",2100,0,10000));
    laserPanel.add(targetY.setup("Target.Y",2000,0,10000));
    laserPanel.add(targetZ.setup("Target.Z",1500,0,10000));
    laserPanel.add(originX.setup("Origin.X",0,0,10000));
    laserPanel.add(originY.setup("Origin.Y",2500,0,10000));
    laserPanel.add(originZ.setup("Origin.Z",1000,0,10000));
    
    //Panel4
    graphPanel.setup();
    graphPanel.setPosition(10, 40 + fixedPanel.getHeight() + matrixPanel.getHeight()
                           + laserPanel.getHeight());
    graphPanel.add(graphLabel.setup("Graphique",""));
    graphPanel.add(vI.setup("Vecteurs Incidents",true));
    graphPanel.add(vN.setup("Vecteurs Normaux",false));
    graphPanel.add(vR.setup("Vecteurs Reflechis",true));
    graphPanel.add(MirrorsCenters.setup("Centres Miroirs",false));
    graphPanel.add(Bases.setup("Reperes",false));
    
}

void Interface::draw(){
    fixedPanel.draw();
    matrixPanel.draw();
    laserPanel.draw();
    graphPanel.draw();
}

void Interface::update(){
    if (toPoint==true && mode!="toPoint"){
        mode="toPoint";
        parallel=false;
        fromPoint=false;
    }
    if (parallel==true && mode!="parallel"){
        mode="parallel";
        toPoint=false;
        fromPoint=false;
    }
    if (fromPoint==true && mode!="fromPoint"){
        mode="fromPoint";
        parallel=false;
        toPoint=false;
    }
}



bool Interface::mouseOn(int x,int y){ //Function to enable camera movings on interface
    if (mouseOnPanel(fixedPanel,x,y)) return true ;
    if (mouseOnPanel(laserPanel,x,y)) return true ;
    if (mouseOnPanel(matrixPanel,x,y)) return true ;
    if (mouseOnPanel(graphPanel,x,y)) return true ;
    else return false;
}


