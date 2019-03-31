#include <LiquidCrystal.h>
#include <AccelStepper.h>

double syringeRpm=15;
double glassRpm=50;

double syringeRevs=1000;
double glassRevs=1000;

boolean syringeMotion=false;
boolean glassMotion=false;


LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
AccelStepper glass(4, 10,11,12,13);
AccelStepper syringe(4, 6,7,8,9);


void setup()
{  
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.print("rpm ");
   lcd.setCursor(0,1);
   lcd.print("rev ");
   //lcd.print("  Glass Coater");
   
   //stepper1.setSpeed(stepper1Speed*3.33);//  1 rpm=200steps/60s=3.33
   syringe.setMaxSpeed(syringeRpm*3.33);
   syringe.setAcceleration(120*3.33);
   syringe.move(50*200);//1 rotation=200	 
   
   glass.setMaxSpeed(glassRpm*3.33);
   glass.setAcceleration(120*3.33);
   glass.move(50*200);   	
}

void loop()
{  
 
   if(syringeMotion)
   syringe.run();
   
   if(glassMotion)
   glass.run();
}

void serialEvent() {
  
  String s = Serial.readStringUntil(':');
  
        //syringeRpm:17&  syringe motor rpm
        if(s=="syringeRpm"){
            s = Serial.readStringUntil('&');
            int value=s.toInt();
            Serial.print("Syringe motor rpm= ");
            Serial.println(value);
            Serial.print("&");
            lcd.setCursor(4,0);
            lcd.print("    ");
            lcd.setCursor(4,0);
            lcd.print("S:");
            lcd.print(value);
            syringe.setMaxSpeed(value*3.33);
            syringe.move(1000*200);
            syringeMotion=false;
            glassMotion=false;

         }//end if
        
        
        //glassRpm:23& glass motor rpm
        if(s=="glassRpm"){
            s = Serial.readStringUntil('&');
            int value=s.toInt();
            Serial.print("Glass motor rpm= ");
            Serial.println(value);
            Serial.print("&");
            lcd.setCursor(9,0);
            lcd.print("    ");
            lcd.setCursor(9,0);
            lcd.print("G:");
            lcd.print(value);
            glass.setMaxSpeed(value*3.33);
            glass.move(1000*200);
            syringeMotion=false;
            glassMotion=false;
         }//end if            
        
        //syringeRevs:12&  syringe revs
        else if(s=="syringeRevs"){
            s = Serial.readStringUntil('&');
            int value=s.toInt();
            Serial.print("Syringe motor revs= ");
            Serial.println(value);
            lcd.setCursor(4,1);
            lcd.print("     ");
            lcd.setCursor(4,1);
            lcd.print("S:");
            lcd.print(value);
            syringe.move(value*200);
            
        }//end else if
        
        //glassRevs:45&  glass revs
        else if(s=="glassRevs"){
            s = Serial.readStringUntil('&');
            int value=s.toInt();
            Serial.print("Glass motor revs= ");
            Serial.println(value);
            lcd.setCursor(10,1);
            lcd.print("     ");
            lcd.setCursor(10,1);
            lcd.print("G:");
            lcd.print(value);
            glass.move(value*200);
        }//end else if
        
        //syringeStart:  start syringe motor
        else if(s=="syringeStart"){
            Serial.println("start syringe motor");
            syringeMotion=true;
        }//end else if
        
        //syringeStop:  stop syringe motor
        else if(s=="syringeStop"){
            Serial.println("stop syringe motor");
            syringeMotion=false;
        }//end else if
        
        //glassStart:  start glass motor
        else if(s=="glassStart"){
            Serial.println("start glass motor");
            glassMotion=true;
        }//end else if
        
        //glassStop:  stop glass motor
        else if(s=="glassStop"){
            Serial.println("stop glass motor");
            glassMotion=false;
        }//end else if
}
