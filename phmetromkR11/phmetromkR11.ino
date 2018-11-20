#include <AnalogPHMeter.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int botaomenor = 2;
//int botaomaior = 3;
const int buttonPin = 3;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

int flag;

volatile int contador = 0;

AnalogPHMeter pHSensor(A0);
unsigned int pHCalibrationValueAddress = 0;

      float falaph = pHSensor.singleReading().getpH();
      String PH = " ph ";
      String fala;
float valor_atual;
float novo_valor;
unsigned long t;

void setup(void) {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.print("LPEQI - PH");
  mySerial.print("LPEQI - PH");
  
  pinMode (botaomenor, INPUT);
  pinMode (buttonPin, INPUT);
    lcd.noDisplay();
    delay(1000);
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("LPEQI - PH");
    delay (500);
  
  struct PHCalibrationValue pHCalibrationValue;
  EEPROM.get(pHCalibrationValueAddress, pHCalibrationValue);
 // pHSensor.initialize(pHCalibrationValue);
  pHSensor.initialize();
  valor_atual= pHSensor.singleReading().getpH();
 
  t = millis();
/*
  Serial.println("Analog PH Meter Calibration");
  Serial.println("The value will be saved on EEPROM");
  Serial.println("Procedure:");
  Serial.println(" - Put pH on pH 7 solution");
  Serial.println(" - Wait until stable");
  Serial.println(" - Press 'm' to calibrate");
  Serial.println(" - Same process for pH 4 and/or pH 10,");
  Serial.println("   except press 'l' for pH 4, and 'h' for pH 10");
  Serial.println();
  Serial.println("All calibration value will be reset after restart.");
  Serial.println("In this example, press 's' to save the value to EEPROM");
  Serial.println("You can freely change the storage.");
  Serial.println("It is not limited to EEPROM only");
  Serial.println();
  Serial.println("*to clear calibration value press 'c'");*/
  
}

void ponto_para_virgula(String texto){
  texto.replace(".",",");
  
  }




void loop(void) {
  novo_valor=  pHSensor.singleReading().getpH();
  if (abs(valor_atual-novo_valor) > 0.2 ){
              valor_atual=novo_valor;           
   }

   
    if (millis() - t > 1000) {
              lcd.begin(16, 2);
              lcd.setCursor(6, 0);
              lcd.print("LPEQI - PH");
              lcd.setCursor(0, 1);
              lcd.print(valor_atual);
              //Serial.println(pHSensor.singleReading().getpH());
              t = millis();   
    }



    buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        //mySerial.println(pHSensor.singleReading().getpH());
        //falaph = pHSensor.singleReading().getpH();
        fala=String(PH+valor_atual);
        fala.replace(".",",");
        Serial.println(fala);
        mySerial.println(fala);
        delay(500);
      }
    
 /*
  if (millis() - t > 1000) {
    lcd.begin(16, 2);
    lcd.setCursor(6, 0);
    lcd.print("LPEQI - PH");
    lcd.setCursor(0, 2);
    lcd.print(pHSensor.singleReading().getpH());
    //Serial.println(pHSensor.singleReading().getpH());
    t = millis();
  }
*/

  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'm') {
      pHSensor.calibrationMid(7.000f);
    } else if (c == 'l') {
      pHSensor.calibrationLow(4.000f);
    } else if (c == 'h') {
      pHSensor.calibrationHigh(10.000f);
    } else if (c == 'c') {
      pHSensor.calibrationClear();
    } else if (c == 's') {
      //EEPROM.put(pHCalibrationValueAddress, pHSensor.getCalibrationValue());
    }
  }
}

