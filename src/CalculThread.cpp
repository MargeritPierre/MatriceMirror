//
//  CalculThread.cpp
//  MatriceLaser
//
//  Created by Pierre Margerit on 08/12/2014.
//
//


//#include <stdio.h>
#include "CalculThread.h"

//These constants are from Units Geometry : don't need to be variables
#define R 43 // Distance point pivotmiroir-attachefil
#define H 55 // Hauteur du pointPivotMiroir
#define e 40  // Distance TrouFil => Centre supportMoteur.
#define L0 sqrt(H*H + (R-e)*(R-e)) //longueur du fil "à plat"
#define microStepping  8 //micropas
#define dShaft 5 //diamètre arbre moteur
#define dWire 0.6 //diamètre fil


//FIRST STEP : set the units Number
void calculThread::setN(int Nombre){
    N = Nombre ;
}

//SECOND STEP : Set the ANGLE
void calculThread::setAngle(int ID, string angleName, float Angle){
    if (Angle<30 && Angle>-30) { //Angle limits to protect mechanics
        Angle = round(Angle*1000)/1000 ;
        if (angleName=="alpha") Angles[2*ID - 1] = Angle ;
        if (angleName=="beta") Angles[2*ID] = Angle ;}
}


//THIRD STEP : set the LENGTH
void calculThread::setLength(int IDMotor){
    //Compute using unit geometry
    Lengths[IDMotor] = sqrt(    H*H + e*e + R*R
                            - 2*H*R*sin(ofDegToRad(Angles[IDMotor]))
                            - 2*e*R*cos(ofDegToRad(Angles[IDMotor]))
                            ) - L0 ;
}

//FOURTH STEP : Set the STEPS Position if it has changed
void calculThread::setSteps(int IDMotor){
    //Mathematical Computing
    int pos = round( Lengths[IDMotor] * 200 * microStepping / ((dShaft + dWire) * PI)) ;
    
    //IF Offsetting
    if (Interface.offsetting && 2*Interface.mirrorOffsetted-1==IDMotor) pos += Interface.position.x ;
    else if (Interface.offsetting && 2*Interface.mirrorOffsetted==IDMotor) pos += Interface.position.y ;
    
    //IF The motor has to move, set a flag
    if (pos!=Steps[IDMotor]) {
        Steps[IDMotor]=pos ;
        posChanged=true ;}
}

//LAST STEP : Speak to Arduino !
void calculThread::sendString(string msg){ //Found this on the net, the aim is to rewrite Serial.writebytes(string)
    for (int i = 0; i<=2; i++) if (serials[i].isInitialized()) { //Send the same message to the 3 serials, for the 9 units Matrix.
        unsigned char* msguc = new unsigned char[msg.size()];
        memcpy(msguc, msg.c_str(), msg.size());
        serials[i].writeBytes(msguc, msg.size());
        delete [] msguc;}
    if (Interface.debugToggle) cout << "sendString to serials : " << endl << msg ;
    sleep(40); //Let the Arduino eat the msg without indigest
}

//MAIN FUNCTION
void calculThread::threadedFunction(){
    while (isThreadRunning()){
        if (lock()) { //LOCKED
            onComputing = true; //this flag helps smooth closing (see ofApp.exit)
            
            //Compute the Steppers positions
            string msg = "move" ;
            posChanged = false ;
            for (int i=1; i<=N; i++) {
                setLength(2*i - 1) ;
                setSteps(2*i - 1) ;
                msg += " " + ofToString(Steps[2*i - 1]) ;
                
                setLength(2*i) ;
                setSteps(2*i) ;
                msg += " " + ofToString(Steps[2*i]) ;
            }
            msg += "\n" ;
            
            //Send Data to Serial ports
            if (Interface.streamToggle && serialSetted && posChanged) sendString(msg) ;
            
            //Show data on concole
            if (Interface.debugToggle && posChanged){
                cout << endl ;
                cout << "-----------------------" << endl ;
                cout << " Angles : " << endl ;
                for (int i=1; i<=2*N-1; i+=2) cout << "   " << i/2+1 << " : " << "Alpha = " << Angles[i] << ", Beta = " << Angles[i+1] << "" << endl ;
                cout << "-----------------------" << endl ;
                cout << endl ;
                cout << endl ;
                cout << "-----------------------" << endl ;
                cout << " Lengths : " << endl ;
                for (int i=1; i<=2*N; i++) cout << "   " << i << " : " << Lengths[i] << endl ;
                cout << "-----------------------" << endl ;
                cout << endl ;
                cout << msg ;
                cout << "haveToBeSetted = " << Interface.haveToBeSetted << endl ;
            }
            
            sleep(10); //Free some CPU time
            onComputing = false;
            unlock();
        } //UNLOCKED
    } //IS STOPPED
}

//STARTS THREAD
void calculThread::start(){
    
    //Show settings in console
    cout << endl ;
    cout << "-----------------------" << endl ;
    cout << " Settings : " << endl ;
    cout << "   R = " << R << " mm" << endl ;
    cout << "   H = " << H << " mm" << endl ;
    cout << "   e = " << e << " mm" << endl ;
    cout << "   L0 = " << L0 << " mm" << endl ;
    cout << "   dShaft = " << dShaft << " mm" << endl ;
    cout << "   dWire = " << dWire << " mm" << endl ;
    cout << "   Microstep = " << microStepping << endl ;
    cout << "-----------------------" << endl ;
    cout << endl ;
    
    //Initialisation
    serialSetted = false ;
    posChanged = false ;
    startThread(); //GO !!
}

//INTERFACE UPDATING
void calculThread::update(){
    
    Interface.chooseMirror.setMax(N) ;
    Interface.update() ;
    
    //SETTING OFFSET OF ONE MIRROR
    if (Interface.haveToBeSetted!=-1) {
        int IDMotor ;
        int pos ;
        string msg ;
        //Set X
            IDMotor = 2*Interface.haveToBeSetted-1 ;
            pos = round( Lengths[IDMotor] * 200 * microStepping / ((dShaft + dWire) * PI)) ;
            msg = "set " + ofToString(IDMotor) + " " + ofToString(pos) + "\n" ;
            sendString(msg);
        //Set Y
            IDMotor = 2*Interface.haveToBeSetted ;
            pos = round( Lengths[IDMotor] * 200 * microStepping / ((dShaft + dWire) * PI)) ;
            msg = "set " + ofToString(IDMotor) + " " + ofToString(pos) + "\n" ;
            sendString(msg);
        //OK, The Mirror is Setted
        Interface.haveToBeSetted = -1 ;
        //Return Cursor to 0 and set XYPadOffset to 0
        Interface.position = ofVec2f(0,0) ;
        Interface.XYPadOffset = ofVec2f(0,0) ;
        Interface.mousePos = ofVec2f(0,0)+ ofGetWindowSize()/2 ;
    }
    
    //ERROR MESSAGES
    if (Interface.streamToggle && !serialSetted) {
        Interface.streamToggle = false ;
        cout << "Error : Serial not setted !" << endl ;
    }
    
    //SETTING THE SERIALS
        if (Interface.setSerialButton==true) {
            serialSetted=false;
            //Scna Serial Devices
            serials[0].listDevices();
            vector <ofSerialDeviceInfo> deviceList = serials[0].getDeviceList();
            
            //Show dialog Box to Choose Ports
            for (int i = 0; i<=2; i++) {
                int serialPort = -1 ;
                while (serialPort<0 || serialPort>(int)deviceList.size()) {
                    string question = "" ;
                    if (serialPort!=-1) question = "Error : You Typed a wrong Serial Number \n Serial List :" ;
                    else question = "Serial List :" ;
                    for(int k = 0; k < (int)deviceList.size(); k++) question += "\n   [" + ofToString(deviceList[k].getDeviceID()) + "] = " + ofToString(deviceList[k].getDeviceName().c_str());
                    serialPort = ofToInt(ofSystemTextBoxDialog(question));
                }
                serials[i].setup(serialPort, 230400);
                cout << "Serial n°" << i << " sat on port " <<deviceList[serialPort].getDeviceName() << endl ;;
            }

            Interface.setSerialButton = false ;
            serialSetted = true;
            cout << "Serial setted with success !" << endl ;
        }
}

//STOPS THREAD
void calculThread::stop(){
    for (int i = 0; i<=2; i++) if (serials[i].isInitialized()) serials[i].close(); //Close Serials
    stopThread();
}



