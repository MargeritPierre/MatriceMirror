//
//  Utils.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 01/12/2014.
//
//

#include "Utils.h"

float scalarProduct(ofVec3f a, ofVec3f b ){
    return a.x*b.x + a.y*b.y + a.z*b.z ;
}

ofVec3f vectorialProduct(ofVec3f a, ofVec3f b ){
    return ofVec3f(a.y*b.z - a.z*b.y, a.z*b.x - a.z*b.z, a.x*b.y - a.y*b.x) ;
}


void drawPoint(ofVec3f p, ofColor Color){
    ofSetColor(Color);
    ofSphere(p.x, p.y, p.z, 20); //to be replaced ??
}


void drawVector(string pointName, ofVec3f Point, ofVec3f Vector, ofColor Color) {
    int Taille = 500; //Can Be changed
    ofSetColor(Color);
    if (pointName=="Start")
        ofDrawArrow(Point, Point + Vector*Taille, 30) ;
    else ofDrawArrow(Point - Vector*Taille, Point, 30) ;
}

void drawBase(ofVec3f Point, ofVec3f X, ofVec3f Y, ofVec3f Z, ofColor Color) {
    ofSetColor(Color);
    drawVector("Start", Point, X, Color);
    drawVector("Start", Point, Y, Color);
    drawVector("Start", Point, Z, Color);
}

float norm(ofVec3f Vector){
    return sqrt(Vector.x*Vector.x + Vector.y*Vector.y + Vector.z*Vector.z);
}

ofVec3f normed(ofVec3f Vector){
    return Vector/norm(Vector) ;
}

void drawPlane(ofVec3f M,float C,ofVec3f vecX,ofVec3f vecY, ofColor Color){ //used to draw mirrors
    ofSetColor(Color);
    ofFill();
    ofVec3f Point1 = M - C/2*vecX + C/2*vecY  ;
    ofVec3f Point2 = M + C/2*vecX + C/2*vecY  ;
    ofVec3f Point3 = M + C/2*vecX - C/2*vecY  ;
    ofVec3f Point4 = M - C/2*vecX - C/2*vecY  ;
    ofLine(Point1,Point2);
    ofLine(Point2,Point3);
    ofLine(Point3,Point4);
    ofLine(Point4,Point1);
    ofNoFill();
}


bool mouseOnPanel(ofxPanel Panel, int x, int y){
    ofRectangle Rect = ofRectangle(Panel.getPosition(), Panel.getWidth(), Panel.getHeight());
    if ( Rect.x<x+40 && Rect.y<y+40 && x-40<Rect.x+Rect.width && y-40<Rect.y+Rect.height ) return true ;
    else return false ;
}