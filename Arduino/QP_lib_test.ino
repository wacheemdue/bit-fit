
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MPU6050 mpu6050(Wire);

long timer = 0;
double AcX = 0;
double AcY = 0;
double AcZ = 0;
double count = 0;
double position_changed = 0;
double position_orig = 0;
double position_now = 0;
double position_previous = 0;
int counter = 0;
int second = 0;
int cali_timer = 0;
double counter2 = 0;
double check = 0;
double checkcalc = 0;

void setup() {
 //Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(9, OUTPUT);
  
  AcX = mpu6050.getAccX();
  AcY = mpu6050.getAccY();
  AcZ = mpu6050.getAccZ();
  position_orig = sqrt( sq(AcX) + sq(AcY) + sq(AcZ) );
}

void loop() {
  mpu6050.update();
  lcd.begin(16, 2);
  
  AcX = mpu6050.getAccX();
  AcY = mpu6050.getAccY();
  AcZ = mpu6050.getAccZ();

  
  position_previous = position_now;
  position_now = sqrt( sq(AcX) + sq(AcY) + sq(AcZ) ) + position_previous;
  if(position_now - 1.6 < position_previous)
  {
    position_now = position_previous;
  }
  position_changed = position_orig - position_now;

  
  cali_timer ++;

  if ( abs(position_previous - position_now) < 1.1){
    counter++; 
  }
  else{

    counter2++;
  }
  
  second = (counter - 1)/61;
  double second2 = (counter2 - 1)/61;
  
  //if(millis() - timer > 1000){
    
   if ((cali_timer-1)/61 < 3){        
     lcd.print ("calibrating...");
    }
   if ((cali_timer-1)/61 == 3){
    lcd.print ("Done!");
   }
    if (second > 8 && second2 <= 1){
      lcd.print("Move Around");
      lcd.print(second2);
      //lcd.print("%");
      digitalWrite(9, HIGH); 
    }
    if(second2 > 1 && checkcalc < 8)
    {
      
      lcd.print("You may rest");
      lcd.print(checkcalc);
      check++;
      checkcalc = (check-1)/61;
 
      
    }
    else if(  checkcalc >= 8)
    {
      counter2 = 0;
      counter = 500;
      check = 0;
      checkcalc = 0;
      
    }
    
    
    
    
   
    
    /*Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(AcX);
    Serial.print("\taccY : ");Serial.print(AcY);
    Serial.print("\taccZ : ");Serial.println(AcZ);
    Serial.print("\toriginal position: ");Serial.println(position_orig);
    Serial.print("\tposition changed: ");Serial.println(position_changed);
    Serial.print("\tIt's been "); Serial.print(second); Serial.println(" seconds since you moved");
    Serial.println("=======================================================\n");*/
    //timer = millis();
   
//}

}
