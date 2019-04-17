//Sample using SD02C
#include <LiquidCrystal.h>

/*******************************************************

This program will use the LCD panel and the SD02C

********************************************************/

#define PULSE        11
#define DIRECTION    12
#define EN           13


// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void rotate(int pul);

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 /*
 if (adc_key_in < 100)  return btnRIGHT;  
 if (adc_key_in < 600)  return btnUP; 
 if (adc_key_in < 700)  return btnDOWN; 
 if (adc_key_in < 800)  return btnLEFT; 
 if (adc_key_in < 900)  return btnSELECT;  
*/
 // For V1.0 comment the other threshold and use the one below:

 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   



 return btnNONE;  // when all others fail, return this...
}

int i =0;

int pul = 0;
int dir = 0;
int enable =0;
int startrun = 0;
int ExpectedDegree =360;

const int STEPS_PER_REV = 200;
//const int pul = STEPS_PER_REV;

void setup()

{
   //pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);  
   pinMode(13, OUTPUT); 
  Serial.begin(9600);
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 
}
 
void loop()
{
         lcd.setCursor(0,0);
         lcd.print("En");
         lcd.setCursor(0,1);
         lcd.print(enable);
         
         lcd.setCursor(3,0);
         lcd.print("Run");
         lcd.setCursor(3,1);
         lcd.print(startrun);
         
         lcd.setCursor(7,0);
         lcd.print("DEGREE");
         lcd.setCursor(7,1);
         lcd.print(ExpectedDegree);
         lcd.print(" ");
         lcd.print((char)127);
         lcd.print((char)126);
         
         lcd.setCursor(13,0);
         lcd.print("Dir");
         lcd.setCursor(13,1);
         lcd.print(dir);
      
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
        dir ^=1;      
        delay(300);
        break;
     }
   case btnLEFT:
     {
       
        startrun ^=1;      
        delay(300);
        break;
     }
   case btnUP:
      
     { 
       
       if(ExpectedDegree<360)
       {
        lcd.setCursor(7,1);
        lcd.print("     ");
        ExpectedDegree++;
        delay(250);
      }
        
     break;
     }
   case btnDOWN:
        
      {  
        if(ExpectedDegree>0)                       // stop
      {
         lcd.setCursor(7,1);
         lcd.print("     ");
         ExpectedDegree--;
         delay(250);
       }
      break;
     }
   case btnSELECT:
     {       
        enable ^=1;      
        delay(300);
        break;
     }
     case btnNONE:
     {
      
        if(enable==1)                       // stop
        {
        digitalWrite(EN, HIGH);
        }
        else
        {
        digitalWrite(EN, LOW);      
        }
               
        if(dir==1)                       // stop
      {
        digitalWrite(DIRECTION, HIGH);
      }
        else
        {
        digitalWrite(DIRECTION, LOW);      
        }
        
        if(startrun==1)                       // stop
      {
        
         degree(ExpectedDegree);
         rotate(pul);
         
      }
        else
        {
         digitalWrite(PULSE, LOW);      
        }
     break;
     }
    }

  }
void degree(int ExpectedDegree)
{

  Serial.println(ExpectedDegree);
  Serial.println(pul);
 pul = ExpectedDegree/1.8;
}





void rotate(int pul){

for(int i = pul; i>=0; i--){

     if(pul==0)                       // stop
     {

      startrun= 0;
    digitalWrite(PULSE, LOW); 
     }
     else
     {
      Serial.println(pul);      
  pul--;
   digitalWrite(PULSE, HIGH);
    //Serial.println(PULSE);//set pulse pin on motor driver
    delay(50);
    digitalWrite(PULSE, LOW);       //clear pulse pin on motor driver
    delay(50);
      }

}
       
}




//void rotate(int pul)
//{
//for(i = pul; i>0; i--)
//{
//Serial.println(i);
//
//digitalWrite(PULSE, HIGH);
////Serial.println(PULSE);
//delay(i);
//digitalWrite(PULSE, LOW);
//delay(i);
//
//pul--;
//}
//startrun= 0;
//}

//   if(pul==0)                       // stop
//    {
//    //Serial.println(pul); 
//    digitalWrite(PULSE, LOW);
//    startrun= 0; 
//     }
//     else
//     {
//      
//    //Serial.println(pul);          //the higher the value of pul, the faster the steps change. multiply 100 to see speed incrememt
//    digitalWrite(PULSE, HIGH);                     //set pulse pin on motor driver
//    delay(pul--);
//    digitalWrite(PULSE, LOW);                     //clear pulse pin on motor driver
//    delay(pul--);
//    
//    }
//
//     } 
