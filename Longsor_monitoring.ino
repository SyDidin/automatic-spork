// DS1307
#include <Wire.h>
#define DS1307_I2C_ADDRESS 0x68 //defining address
#include <String.h>



#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
int sensSmoothArray1 [filterSamples];   // array for holding raw sensor values for sensor1 
int sensSmoothArray2 [filterSamples]; 
int sensSmoothArray3 [filterSamples]; 
int smoothData1, smoothData2, smoothData3;  // variables for sensor1 data

int analog_x,analog_y,analog_z;
float vol_x,vol_y,vol_z,X0g,Y0g,Z1g,X1g, Y1g, Z0g ;
int Alarm=4, Ready=5, button=6, buttonState;
int mean_X0g = 0,mean_Y0g = 0,mean_Z1g = 0, state=0, i=0, n=0;
int mean_X1g = 0, mean_Y1g = 0, mean_Z0g = 0;
int Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
long buff_analog_x0=0,buff_analog_y0=0,buff_analog_z0=0,buff_analog_x1=0,buff_analog_y1=0,buff_analog_z1=0;

float percepatanX1=0, kecepatanX1=0, percepatanY1=0, kecepatanY1=0, percepatanZ1=0, kecepatanZ1=0, Sx1=0;

//float resultan;

  float percepatanX;
  float percepatanY;
  float percepatanZ;
  float kecepatanX;
  float kecepatanY;
  float kecepatanZ;
  float Sx;
  


String Tempat ="Bandung";
String Kondisi =" ";

unsigned long T_awal=0;
unsigned long interval = 1000;
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;


void setup(){
  Wire.begin();
  Serial1.begin(19200);   // the GPRS baud rate   
  Serial.begin(19200);    // the GPRS baud rate 
  pinMode (Alarm, OUTPUT);
  pinMode (Ready, OUTPUT);
  pinMode (button, INPUT);
//  Sim900power();
  //delay(500);
  // DS1307 seconds, minutes, hours, day, date, month, year
  //setDS1307time(00,45,16,5,9,06,16);
  }

void loop(){  
//state_0  
  if (state==0){
    Serial.println(F("Placed the sensor in horizontal position (position A)\n"));
    delay(100);
    while (digitalRead(button)==0){
    Serial.println(F("Press the button if you have placed correctly.\n"));
    digitalWrite(Ready,HIGH);
    delay(500);
  }                

    Serial.println("\n Calibrating . . .X0g, Y0g and +Z1g");
    while (i<201){
    digitalWrite(Ready,LOW);
    int  analog_x0 = analogRead(0);
    int  analog_y0 = analogRead(1);
    int  analog_z1 = analogRead(2);
    
    if (i>100 && i<=(200)){ 
      buff_analog_x0=buff_analog_x0+analog_x0;
      buff_analog_y0=buff_analog_y0+analog_y0;
      buff_analog_z1=buff_analog_z1+analog_z1;
    }
    if (i==(200)){
      mean_X0g=buff_analog_x0/100;
      mean_Y0g=buff_analog_y0/100;
      mean_Z1g=buff_analog_z1/100;
      state++;
    }
    i++;
    delay(5);
  }
    
  delay(1000);
}
//state_1
if (state==1){
  Serial.println("\n Calibrating Offset");

  
  X0g = mean_X0g*5.0/1024;
  Y0g = mean_Y0g*5.0/1024;
  Z1g = mean_Z1g*5.0/1024;
  
  delay(1000);
  Serial.println("\nDevice have been calibrated");
  delay(100);
  Serial.print("Offset X0g:");
  Serial.print(mean_X0g); Serial.print("\t");
  Serial.print("Offset Y0g:");
  Serial.print(mean_Y0g); Serial.print("\t");
  Serial.print("Offset +Z1g:");
  Serial.print(mean_Z1g); Serial.print("\n");
  if (i == 201){
  i=0;
  state++;
  }
delay(2000);
}
//state_2
if (state==2){
  Serial.println(F("Placed the sensor at position B\n"));
  while (digitalRead(button)==0){
    Serial.println(F("Press the button if you have placed correctly.\n"));
    digitalWrite(Ready,HIGH);
    delay(500);
  }                
  while (i<201){
    digitalWrite(Ready,LOW);
    int  analog_x1 = analogRead(0);
    int  analog_z0 = analogRead(2);
    if (i>100 && i<=(200)){ 
      buff_analog_x1=buff_analog_x1+analog_x1;
      buff_analog_z0=buff_analog_z0+analog_z0;
    }
    if (i==(200)){
      mean_X1g=buff_analog_x1/100;
      mean_Z0g=buff_analog_z0/100;
      state++;
      delay(1000);
    }
    i++;
    delay(5);
    }
}
//state_3
if (state==3){
  Serial.println("\n Calibrating Offset");
  X1g = mean_X1g*5.0/1024;
  Z0g = mean_Z0g*5.0/1024;
  delay(1000);
  Serial.println("\nDevice have been calibrated");
  delay(100);
  Serial.print("Offset +X1g:");
  Serial.print(mean_X1g); Serial.print("\t");
  Serial.print("Offset Z0g:");
  Serial.print(mean_Z0g); Serial.print("\n");
  if (i == 201){
  i=0;
  state++;
  delay(2000);
  }
}
//state_4
if (state==4){
  Serial.println(F("Placed the sensor in position C\n"));
  while (digitalRead(button)==0){
  Serial.println(F("Press the button if you have placed correctly.\n"));
  digitalWrite(Ready,HIGH);
  delay(500);
}                 

  while (i<201){
    digitalWrite(Ready,LOW);
    int  analog_y1 = analogRead(1);
    
    if (i>100 && i<=(200)){ 
      buff_analog_y1=buff_analog_y1+analog_y1;
    }
    if (i==(200)){
      mean_Y1g=buff_analog_y1/100;
      state++;
      delay(1000);
    }
    i++;
    delay(5);   
  }
}
//state_5
if (state==5){
  Serial.println("\n Calibrating Offset");
  Y1g = mean_Y1g*5.0/1024;
  delay(1000);
  Serial.println("\nDevice have been calibrated");
  delay(100);
  Serial.print("Offset +Y1g:");
  Serial.print(mean_Y1g); Serial.print("\n");
  if (i == 201){
  state++;
  digitalWrite(Ready,HIGH);
  delay(5000);
  }
}
//
if (state==6){
 analog_x = analogRead(0); 
 analog_y = analogRead(1); 
 analog_z = analogRead(2);
 if (n<=100){
  smoothData1 = digitalSmooth(analog_x, sensSmoothArray1);
  smoothData2 = digitalSmooth(analog_y, sensSmoothArray2);
  smoothData3 = digitalSmooth(analog_z, sensSmoothArray3);
  n++;

 }
 else { 
  smoothData1 = digitalSmooth(analog_x, sensSmoothArray1);
  smoothData2 = digitalSmooth(analog_y, sensSmoothArray2);
  smoothData3 = digitalSmooth(analog_z, sensSmoothArray3);


  vol_x=smoothData1*5.0/1024;// change to sensSmoothArray1 for filtering
  vol_y=smoothData2*5.0/1024;
  vol_z=smoothData3*5.0/1024;


//Acceleration
  percepatanX=((vol_x-X0g)/(X1g-X0g))*10;
  percepatanY=((vol_y-Y0g)/(Y1g-Y0g))*10;
  percepatanZ=((vol_z-Z1g)/(Z1g-Z0g))*10;

//Velocity
  kecepatanX = kecepatanX1 + (0.01*((percepatanX+percepatanX1)/2));
  kecepatanX1 = kecepatanX;
 
  kecepatanY = kecepatanY1 + (0.01*((percepatanY+percepatanY1)/2));
  kecepatanY1 = kecepatanY;

  kecepatanZ = kecepatanZ1 + (0.01*((percepatanZ+percepatanZ1)/2));
  kecepatanZ1 = kecepatanZ;
  
if ((percepatanX<0.07) && (percepatanX>-0.07)){
    
    kecepatanX=0;
    kecepatanX1 = 0;
    
    }
  if ((percepatanY<0.07) && (percepatanY>-0.07)){
    
    kecepatanY=0;
    kecepatanY1 = 0; 
    }
  if ((percepatanZ<0.07) && (percepatanZ>-0.07)){
    
    kecepatanZ=0;
    kecepatanZ1 = 0;
  }




//Perpindahan
//  Sx = Sx1 + (0.1*kecepatanX);
//  Sx1 = Sx;
  
//Jam
   readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
 /* if(second%5==0){ 
     displayTime();
     delay(1000);
  }*/
   if((minute%59==0)&&(second==59)){
      //displayTime();
     // SubmitHttpRequest();
  }

//Percepatan
    Serial.print(" Ax:");
    Serial.print(percepatanX); Serial.print("\t");
    Serial.print(" Ay:");
    Serial.print(percepatanY); Serial.print("\t");
    Serial.print(" Az:"); 
    Serial.print(percepatanZ);Serial.print("\t");
    

//Kecepatan
    Serial.print(" Vx:");
    Serial.print(kecepatanX); Serial.print("\t");
    Serial.print(" Vy:");
    Serial.print(kecepatanY); Serial.print("\t");
    Serial.print(" Vz:"); 
    Serial.print(kecepatanZ);Serial.print("\n");

// perpindahan
// Serial.print(" perpindahanx:");
// Serial.print(Sx); Serial.print("\n");
     
//Raw Data
/*  Serial.print(" x:");
    Serial.print(analog_x); Serial.print("\t");
    Serial.print("y:");
    Serial.print(analog_y);Serial.print("\t");
    Serial.print("z:");
    Serial.print(analog_z);Serial.print("\t");
    Serial.println();*/

  percepatanX1=percepatanX;
  percepatanY1=percepatanY;
  percepatanZ1=percepatanZ;
  
  
  //Indikator Bahaya
if ( kecepatanX>0.05 || kecepatanX<-0.05 || kecepatanY>0.05 || kecepatanY<-0.05 || kecepatanZ>0.05 || kecepatanZ<-0.05) {
   Kondisi = "BAHAYA";
   // digitalWrite (Alarm, HIGH);
   // displayTime();
   // SubmitHttpRequest();
  }
  else {
    Kondisi = "AMAN";
    digitalWrite (Alarm, LOW);
  } 
   delay(10);
}
}
}

void ShowSerialData(){
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}
