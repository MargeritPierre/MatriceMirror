//
//  Utils.h
//  MatriceLaser
//
//  Created by Pierre Margerit on 01/12/2014.
//
//

#ifndef __MatriceLaser__Utils__
#define __MatriceLaser__Utils__

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"


void drawPoint(ofVec3f p, ofColor Color);

float scalarProduct(ofVec3f a, ofVec3f b );

ofVec3f vectorialProduct(ofVec3f a, ofVec3f b );

void drawVector(string pointName, ofVec3f Point, ofVec3f Vector, ofColor Color);

void drawBase(ofVec3f Point, ofVec3f X, ofVec3f Y, ofVec3f Z, ofColor Color);

float norm(ofVec3f Vector);

ofVec3f normed(ofVec3f Vector);

void drawPlane(ofVec3f M,float C,ofVec3f vecX,ofVec3f vecY, ofColor Color);

bool mouseOnPanel(ofxPanel Panel, int x, int y);

#endif /* defined(__MatriceLaser__Utils__) */
