String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void initSerial()
{
  Serial.begin(115200);
  inputString.reserve(200);
}

void processSerial()
{
  while(Serial.available() > 0)
  {
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  if (stringComplete){
    processBuffer();
    inputString = "";
    stringComplete = false;
  }
}

void processBuffer()
{
//  Serial1.println(inputString);
  String cmd = inputString.substring(0, inputString.indexOf(' '));
  inputString = inputString.substring(inputString.indexOf(' ')+1);
  String idMot = inputString.substring(0, inputString.indexOf(' '));
  inputString = inputString.substring(inputString.indexOf(' ')+1);

//Serial.println(cmd);
//Serial.println(idMot);
//Serial.println(inputString);

  //Commandes de base
  if (cmd.compareTo("a")==0){
    //Serial.println("Recu !");
  }
  
  if (cmd.compareTo("stop")==0){
    fastStop(idMot.toInt());
  }
  
  if (cmd.compareTo("move")==0){
    //Serial.print ("move to ");
    moveTo(1, idMot.toInt());
    int i;
    for (i=2;i<=6;i++)
    {
    moveTo(i, inputString.toInt());
    inputString = inputString.substring(inputString.indexOf(' ')+1);
    }
    //Serial.println("OK");
  }
  
  if (cmd.compareTo("speed")==0){
    setSpeed(idMot.toInt(), inputString.toInt());
  }
  if (cmd.compareTo("acc")==0){
    setAcc(idMot.toInt(), inputString.toInt());
  }
  if (cmd.compareTo("0")==0){
    setzero(idMot.toInt());
  }
  if (cmd.compareTo("inv")==0){
    reverse(idMot.toInt(), inputString.toInt());
  }
    if (cmd.compareTo("mode")==0){
    mode(idMot.toInt(), inputString.toInt());
  }
      if (cmd.compareTo("set")==0){
    set(idMot.toInt(), inputString.toInt());
  }
//  //Commandes pour le PATH
//  if (cmd.compareTo("enablepath")==0){
//    if (idMot.compareTo("0")==0) Desactivate_Path();
//    if (idMot.compareTo("1")==0) Activate_Path();
//  }
//  if (cmd.compareTo("clearpath")==0) Clear_Path;
//  if (cmd.compareTo("addcurrentpoint")==0) Add_current_point();
//  if (cmd.compareTo("clearlastpoint")==0) Clear_last_point();
}

