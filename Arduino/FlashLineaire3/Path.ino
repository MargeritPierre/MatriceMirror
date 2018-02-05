//long XPath[100];
//long YPath[100];
//int i_path = 0;
//int length = 0;
//boolean Path_Enable;
//
//void Clear_Path()
//{ int i;
//
//  for (i = 0; i < 99; i = i + 1){
//    XPath[i]=0;
//    YPath[i]=0;
//  }
//  i_path = 0;
//  length = 0;
//  Path_Enable = false;
//  Serial.println("path cleared");
//}
//
//void Activate_Path()
//{
//  if (length>0)
//  {
//  Path_Enable = true;
//  moveTo(1,XPath[i_path-1]);
//  moveTo(2,YPath[i_path-1]);
//  Serial.println("path enabled");
//  }
//}
//
//void Desactivate_Path()
//{
//  Path_Enable = false;
//  fastStop(1);
//  fastStop(2);
//  Serial.println("path disabled");
//}
//
//void Follow_Path(long X, long Y)
//{
//  if (Path_Enable == true && length>0)
//  {
//    if ( X == XPath[i_path-1] && Y == YPath[i_path-1] )
//    {
//      if (i_path<length) i_path=i_path+1;
//      else i_path=1;
//      moveTo(1,XPath[i_path-1]);
//      moveTo(2,YPath[i_path-1]);
//      Serial.print("Reaching point n°");
//      Serial.println(i_path);
//    }
//  }
//}
//
//
//void Clear_last_point()
//{
//  XPath[length]=0;
//  YPath[length]=0;
//  length = length-1;
//  Serial.print("last point cleared, nbpts = ");
//  Serial.println(length);
//}
//
//void Add_current_point()
//{
//  length=length+1;
//  XPath[length-1]=currentX();
//  YPath[length-1]=currentY();
//  Serial.print("Point Added : X ");
//  Serial.print(stepper1.currentPosition());
//  Serial.print("- Y ");
//  Serial.print(stepper1.currentPosition());
//  Serial.print("- nbpts : ");
//  Serial.println(length);
//}

