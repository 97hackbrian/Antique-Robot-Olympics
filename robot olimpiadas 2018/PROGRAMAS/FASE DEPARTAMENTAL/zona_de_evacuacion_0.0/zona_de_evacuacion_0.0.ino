int a,b,c,d,x;

int cm_der1=24;
int cm_der2=24;
int cm_adelan=45;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
   while(x==1)
   {
    while(a<=2)
    {
    
    if(cm4>cm_der1&&cm2>30)
    {
      mover_robot(50,0,0,0);
    }
    if(cm4<cm_der1&&cm2>30)
    {
      mover_robot(0,0,50,0);
    }
    if(cm2<30)
    {
      mover_robot(0,50,50,0);
      delay(600);
      while(true)
      {
        medir();
        if(cm4>cm_der&&cm2>30)
        {
          a++;
          break;
        }
       }
     }
    }   
  while(a==3)
  {
    if(cm4>cm_der2&&cm2>cm_adelan)
    {
      mover_robot(50,0,0,0);
    }
    if(cm4<cm_der2&&cm2>cm_adelan)
    {
      mover_robot(0,0,50,0);
    }
   
    if(cm2<cm_adelan)
    {
    if(b==0);
    {
      cm_der2=cm_der2+21;
    }
      mover_robot(0,50,50,0);
      delay(600);
      while(true)
      {
        medir();
        if(cm4>cm_der2&&cm2>cm_adelan)
        {
          b++;
          break;
        }
       }
     }
 
      if(b==4)
      {
        cm_der2 = cm_der2+15;
        cm_adelan=cm_adelan+15;
        if(cm3<10)
        {
          
          c++;
          mover_robot(0,0,0,0);
          delay(2000);
          break;
        }
      }
  }





   }
    
}
