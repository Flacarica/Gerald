#include <PS4Controller.h>

#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

#define MA1 12
#define MA2 14
#define MB1 25
#define MB2 26
#define MC1 33
#define MC2 32
#define MD1 34
#define MD2 35


#define PWMA 4
#define PWMB 17
#define PWMC 18
#define PWMD 5

void printDeviceAddress() {
  const uint8_t* point = esp_bt_dev_get_address();
  for (int i = 0; i < 6; i++) {
    char str[3];
    sprintf(str, "%02x", (int)point[i]);
    Serial.print(str);
    if (i < 5) {
      Serial.print(":");
    }
  }
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.println("\n\n");

  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(PWMD, OUTPUT);

  Serial.println("Outputs enabled ...");

  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);

  Serial.println("Outputs set to low ...");

  PS4.begin();
  
  Serial.print("This device MAC is: ");
  printDeviceAddress();
  Serial.println("\n");

  Serial.println("Ready.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(PS4.isConnected()){
    Serial.println("Dualshock 4 connected.");
  } else {
    Serial.println("Looking for the controller ... ");
  }
  while(PS4.isConnected()){
      if(PS4.R2Value()>0 && PS4.L2Value()>0){
        digitalWrite(MA1, LOW);
        digitalWrite(MA2, LOW);
        digitalWrite(MB1, LOW);
        digitalWrite(MB2, LOW);
        digitalWrite(MC1, LOW);
        digitalWrite(MC2, LOW);
        digitalWrite(MD1, LOW);
        digitalWrite(MD2, LOW);
        analogWrite(PWMA, 0);
        analogWrite(PWMB, 0);
        analogWrite(PWMC, 0);
        analogWrite(PWMD, 0);
      } else {
        while(PS4.R2Value()>0){
          //  Setam motoarele pe directia inainte
          digitalWrite(MA1, HIGH);
          digitalWrite(MA2, LOW);
          digitalWrite(MB1, HIGH);
          digitalWrite(MB2, LOW);
          digitalWrite(MC1, HIGH);
          digitalWrite(MC2, LOW);
          digitalWrite(MD1, HIGH);
          digitalWrite(MD2, LOW);
          //  Acceleram cu cat citim de la butonul R2 de pe controller
          analogWrite(PWMA, PS4.R2Value());
          analogWrite(PWMB, PS4.R2Value());
          analogWrite(PWMC, PS4.R2Value());
          analogWrite(PWMD, PS4.R2Value());

          Serial.printf("R2 is at %d\n", PS4.R2Value());

        }
        while(PS4.L2Value()>0){
          //  Setam motoarele pe directia inapoi
          digitalWrite(MA1, LOW);
          digitalWrite(MA2, HIGH);
          digitalWrite(MB1, LOW);
          digitalWrite(MB2, HIGH);
          digitalWrite(MC1, LOW);
          digitalWrite(MC2, HIGH);
          digitalWrite(MD1, LOW);
          digitalWrite(MD2, HIGH);
          //  Acceleram cu cat citim de la butonul L2 de pe controller
          analogWrite(PWMA, PS4.L2Value());
          analogWrite(PWMB, PS4.L2Value());
          analogWrite(PWMC, PS4.L2Value());
          analogWrite(PWMD, PS4.L2Value());

          Serial.printf("L2 is at %d\n", PS4.L2Value());

        }
        digitalWrite(MA1, LOW);
        digitalWrite(MA2, LOW);
        digitalWrite(MB1, LOW);
        digitalWrite(MB2, LOW);
        digitalWrite(MC1, LOW);
        digitalWrite(MC2, LOW);
        digitalWrite(MD1, LOW);
        digitalWrite(MD2, LOW);
        analogWrite(PWMA, 0);
        analogWrite(PWMB, 0);
        analogWrite(PWMC, 0);
        analogWrite(PWMD, 0);
    }
  }
  //  Daca s-a deconectat controllerul, oprim motoarele
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
