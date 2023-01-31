#include <Keypad.h>
//#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <pitches.h>
#include <LCD_I2C.h>
#include <rgb_lcd.h>
#include <Wire.h>

//LCD_I2C lcd(0x27, 16, 2);
rgb_lcd lcd;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String niks;
String UUR, MIN, TAND, LIP, PARFUM, KAM;
int waardeU, waardeM, waardeT, waardeL, waardeP, waardeK;
int nummer = 0;
int enter = 0;
int weergave = 0;
const int knop_Ochtend = 11;
const int knop_Herinnering = 12;
int knopOchtend;
int knopHerinnering;
int status = 0;
int waardeDruksensor0;
int waardeDruksensor1;
int waardeDruksensor2;
int waardeDruksensor3;
int routinestatus = 0;
float ADCconstante = 5/1023;
float druksensor0, druksensor1, druksensor2, druksensor3;
int melodyBegin[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_E3, 0, NOTE_B3, NOTE_C4};
int melodyEind[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int nootduurBegin[] = {4, 8, 8, 4, 4, 4, 4, 4};


void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  //lcd.backlight();
  pinMode(knopOchtend, INPUT);
  pinMode(knopHerinnering, INPUT);
}

void loop() 
{
  
  int tijdinsec = (millis()/1000);
  int seconde;
  int minuten;
  int uren = 13;
  
  seconde = tijdinsec % 60;
  minuten = (tijdinsec / 60) + 11;
  
  if (minuten > 59)
  {
    uren = uren + 1;
    minuten = 0;
  }
  if (uren > 23)
  {
    uren = 0;
    routinestatus = 0;
  }

  if(weergave == 0)
  {
    lcd.setCursor(4, 0);
    lcd.print(uren);
      lcd.setCursor(6, 0);
    lcd.print(":");
      lcd.setCursor(7, 0);
    lcd.print(minuten);
      if(minuten < 10)
      {
      niks = " ";
      lcd.setCursor(8, 0);
      lcd.print(niks);
      }
      lcd.setCursor(9, 0);
    lcd.print(":");
      lcd.setCursor(10, 0);
    lcd.print(seconde);
      if(seconde < 10)
      {
      niks = " ";
      lcd.setCursor(11, 0);
      lcd.print(niks);
      }
  }

char key = keypad.getKey();
  
  if ((weergave == 1) && key != NO_KEY &&  (key=='0'||key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9')) 
  {
    switch(nummer)
    {
      case 0:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Gewicht in gram: ");
          TAND = TAND + key;
          lcd.setCursor(7, 1);
          lcd.print(TAND);
          enter = 0;
        break;
      case 1:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Gewicht in gram: ");
          LIP = LIP + key;
          lcd.setCursor(7, 1);
          lcd.print(LIP);
          enter = 1;
        break;
      case 2:
          UUR = UUR + key;
          lcd.setCursor(7, 1);
          lcd.print(UUR);
          enter = 2;
        break;
      case 3:
          MIN = MIN + key;
          lcd.setCursor(7, 1);
          lcd.print(MIN);
          enter = 3;
        break;
      case 4:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Gewicht in gram: ");
          KAM = KAM + key;
          lcd.setCursor(7, 1);
          lcd.print(KAM);
          enter = 4;
        break;
      case 5:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Gewicht in gram: ");          
          PARFUM = PARFUM + key;
          lcd.setCursor(7, 1);
          lcd.print(PARFUM);
          enter = 5;
    }
  }
  
    switch(key)
    {
      case 'A':
        weergave = 1;        
        UUR = "";
        MIN = "";
        TAND = "";
        LIP = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gewicht tanden-");
        lcd.setCursor(0, 1);
        lcd.print("borstel");
        nummer = 0;
        break;

      case 'B':
        weergave = 1;
        TAND = "";
        LIP = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Geef gewicht lip-");
        lcd.setCursor(0, 1);
        lcd.print("penstift");
        nummer = 1;
        break;

      case 'C':
        weergave = 1;
        TAND = "";
        LIP = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Geef gewicht kam");
        nummer = 4;
        break;

      case 'D':
        weergave = 1;
        TAND = "";
        LIP = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Geef gewicht par-");
        lcd.setCursor(0, 1);
        lcd.print("fum");
        nummer = 5;
        break;

      case '*':
        weergave = 1;
        UUR = "";
        MIN = "";
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Tijd in uur: ");
        nummer = 2;
        break;
    }
  if(key != NO_KEY && key == '#')
 {
    switch(enter)
    {
      case 0:
        waardeT = TAND.toInt();

        if((waardeT > 999))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht borstel: ");
          TAND = "";
          nummer = 0;
        }
        else if((waardeT < 20))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht borstel: ");
          TAND = "";
          nummer = 0;
        }
        else 
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gewicht borstel: ");
        lcd.setCursor(7, 1);
        lcd.print(waardeT);
        delay(3000);
        TAND = "";
        lcd.clear();
        weergave = 0;
        }         
        
        enter = 24;
            break;
      case 1:
        waardeL = LIP.toInt();          
        if((waardeL > 999))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht lipstick: ");
          LIP = "";
          nummer = 1;
        }
        else if((waardeT < 20))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht lipstick: ");
          LIP = "";
          nummer = 1;
        }
        else 
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gewicht lipstick: ");
        lcd.setCursor(7, 1);
        lcd.print(waardeL);
        delay(3000);
        LIP = "";
        lcd.clear();
        weergave = 0;
        }         
        enter = 24;
        break;
      case 2:
        waardeU = UUR.toInt();

        if(waardeU > 24)
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Tijd in uur: ");
          UUR = "";
          nummer = 2;
        }
        else 
        {
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Tijd in minuten: ");          
          nummer = 3;
        }
        enter = 24;
        break;
      case 3:
        waardeM = MIN.toInt();
        if(waardeM > 60)
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Tijd in minuten: ");
          MIN = "";
          nummer = 3;
        }
        else 
        {
          UUR = "";
          MIN = "";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Ingevoerde Tijd:");
          lcd.setCursor(0, 1);
          lcd.print(waardeU);
          lcd.setCursor(3, 1);
          lcd.print(":");
          lcd.setCursor(4, 1);
          lcd.print(waardeM);
          nummer = 4;
          delay(3000);
          lcd.clear();
          weergave = 0;
        }
        
        enter = 24;
        break;
      case 4:
        waardeK = KAM.toInt();          
        if((waardeK > 999))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht kam: ");
          KAM = "";
          nummer = 4;
        }
        else if((waardeT < 20))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht kam: ");
          KAM = "";
          nummer = 4;
        }
        else 
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gewicht kam: ");
        lcd.setCursor(7, 1);
        lcd.print(waardeK);
        delay(3000);
        KAM = "";
        lcd.clear();
        weergave = 0;
        }         
        enter = 24;
        break;
      case 5:
        waardeP = PARFUM.toInt();          
        if((waardeP > 999))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht parfum: ");
          PARFUM = "";
          nummer = 5;
        }
        else if((waardeP < 20))
        {
          lcd.setCursor(0, 1);
          lcd.print("Invalide waarde");
          delay(1500);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Gewicht parfum: ");
          PARFUM = "";
          nummer = 5;
        }
        else 
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gewicht parfum: ");
        lcd.setCursor(7, 1);
        lcd.print(waardeP);
        delay(3000);
        PARFUM = "";
        lcd.clear();
        weergave = 0;
        }         
        enter = 24;
        break;
    }
 }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  float mint, maxt, mink, maxk, minp, maxp, minl, maxl;    
    if(20 > waardeT < 100) {mint = 1,0; maxt = 2,0;};
    if(100 < waardeT < 200) {mint= 1,6; maxt = 2,25;};
    if(200 < waardeT < 300) {mint= 2,1; maxt = 2,6;};
    if(300 < waardeT < 400) {mint= 2,2; maxt = 2,7;};
    if(400 < waardeT < 500) {mint= 2,5; maxt = 3,0;};
    if(500 < waardeT < 600) {mint= 2,8; maxt = 3,2;};
    if(600 < waardeT < 700) {mint= 3,0; maxt = 3,25;};
    if(700 < waardeT < 1000) {mint= 3,0; maxt = 5,0;};
 
    if(20 > waardeK < 100) {mink = 1,0; maxk = 2,0;};
    if(100 < waardeK < 200) {mink= 1,6; maxk = 2,25;};
    if(200 < waardeK < 300) {mink= 2,1; maxk = 2,6;};
    if(300 < waardeK < 400) {mink= 2,2; maxk = 2,7;};
    if(400 < waardeK < 500) {mink= 2,5; maxk = 3,0;};
    if(500 < waardeK < 600) {mink= 2,8; maxk = 3,2;};
    if(600 < waardeK < 700) {mink= 3,0; maxk = 3,25;};
    if(700 < waardeK < 1000) {mink= 3,0; maxk = 5,0;};

    if(20 > waardeP < 100) {minp = 1,0; maxp = 2,0;};
    if(100 < waardeP < 200) {minp= 1,6; maxp = 2,25;};
    if(200 < waardeP < 300) {minp= 2,1; maxp = 2,6;};
    if(300 < waardeP < 400) {minp= 2,2; maxp = 2,7;};
    if(400 < waardeP < 500) {minp= 2,5; maxp = 3,0;};
    if(500 < waardeP < 600) {minp= 2,8; maxp = 3,2;};
    if(600 < waardeP < 700) {minp= 3,0; maxp = 3,25;};
    if(700 < waardeP < 1000) {minp= 3,0; maxp = 5,0;};

    if(20 > waardeL < 100) {minl = 1,0; maxl = 2,0;};
    if(100 < waardeL < 200) {minl= 1,6; maxl = 2,25;};
    if(200 < waardeL < 300) {minl= 2,1; maxl = 2,6;};
    if(300 < waardeL < 400) {minl= 2,2; maxl = 2,7;};
    if(400 < waardeL < 500) {minl= 2,5; maxl = 3,0;};
    if(500 < waardeL < 600) {minl= 2,8; maxl = 3,2;};
    if(600 < waardeL < 700) {minl= 3,0; maxl = 3,25;};
    if(700 < waardeL < 1000) {minl= 3,0; maxl = 5,0;};
    
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
int routine = 0;
int poetstijd = 3;
int kamtijd = 2;
int parfumtijd = 1;
int lippenstifttijd = 1;

  if((waardeU == uren) & (waardeM == minuten))
  {
    routine = 1;
  }

  if (routine == 1)
  {
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
    int noteDuration = 1000 / nootduurBegin[thisNote];
    tone(7, melodyBegin[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(7);
    }
    // "Het is tijd voor de ochtenroutine...."
    knopOchtend = digitalRead(knop_Ochtend);
    //
    if(knopOchtend == LOW)
    {
      switch(status)
      {
        case 0:
          tone(7, NOTE_C4, 1000);
          //Het is tijd om tanden te poetsen
          waardeDruksensor0 = analogRead(A0);
          druksensor0 = ADCconstante * waardeDruksensor0;
          if(minuten >= (waardeM + poetstijd))
          {
            if(druksensor0 < mint )
            {
              //tandenborstel mist
              delay(10000);
            }
            else if (waardeDruksensor0 > mint)
            {
              status = 1;
            }
          }
          break;
        
        case 1:
          tone(7, NOTE_C4, 300);
          delay(300);
          tone(7, NOTE_C4, 300);
          //Het is tijd om haren te kammen
          waardeDruksensor1 = analogRead(A1);
          druksensor1 = ADCconstante * waardeDruksensor1;
          if(minuten >= (waardeM + kamtijd+ poetstijd))
          {
            if(druksensor1 < mink)
            {
              // kam mist
              delay(10000);
            }
            else if(druksensor1 > mink)
            {
              status = 2;
            }
          }
          break;
        
        case 2:
          //Het is tijd om parfum op te doen
          waardeDruksensor2 = analogRead(A2);
          druksensor2 = ADCconstante * waardeDruksensor2;
          if(minuten >= (waardeM + parfumtijd + kamtijd + poetstijd))
          {
            if(druksensor2 < minp)
            {
              // parfum mist
              delay(10000);
            }
            else if(druksensor2 > minp)
            {
              status = 3;
            }
          }
          break;
        
        case 3:
          // Het is tijd op lippenstift op te doen
          waardeDruksensor3 = analogRead(A3);
          druksensor3 = ADCconstante * waardeDruksensor3;
          if(minuten >= (waardeM + lippenstifttijd + parfumtijd + kamtijd + poetstijd))
          {
            if(druksensor3 < minl)
            {
              // parfum mist
              delay(10000);
            }
            else if(druksensor3 > minl)
            {
              status = 4;
            }
          }
          break;

        case 4:
          // "De ochtendroutine is voorbij"
          routinestatus = 1;
          break;
      }
    }
  }
  if(knopHerinnering == HIGH)
  {
    if(routinestatus == 1)
    {
      // routine is geweest
    }
    else if(routinestatus == 0)
    {
      // routine moet nog komen
    }
  }
}
