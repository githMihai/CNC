//#include "CDStepper.h"
#include "CNC.h"

#define stepPinX 7
#define dirPinX 6
#define sleepPinX 5

#define stepPinY 9
#define dirPinY 8
#define sleepPinY 11

#define limitX 160
#define limitY 250

volatile char readedByte;

String command[100];
String buffer;
//volatile int coordX[100];
//volatile int coordY[100];
volatile int lineIndex;

//int xCoord;
//int yCoord;


//const int stepPin1 = 7;
//const int dirPin1 = 6;
//
//const int stepPin2 = 9;
//const int dirPin2 = 8;

int ok = 0;

CDStepper stepperX(200, stepPinX, dirPinX, sleepPinX);
CDStepper stepperY(200, stepPinY, dirPinY, sleepPinY);
Servo servo;

CNC cnc(stepperX, limitX, stepperY, limitY, servo);

void setup() {
  // put your setup code here, to run once:

  stepperX.setSpeed(400);
  stepperY.setSpeed(400);

  // stepperX.sleep();
  // stepperY.sleep();

  Serial.begin(9600);
  servo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
//  stepper.stepF();
//  Serial.println(stepper.getStepNumber());
//  if (ok == 0) {
//    cnc.move(160, 250);
//     cnc.move(10, 10);
//    cnc.up(1);
//    Serial.println(cnc.getX());
//    Serial.println(cnc.getY());
//    ok = 1;
//  }
    lineIndex = 0;
//    cnc.move(xCoord, yCoord);
//    Serial.println(command[lineIndex]);
//    delay(1000);
}

void process(String *command) {
  int index = 0;
  int instrIndex = 0;
  int zIndex = 0;
  int iIndex = 0;
  int xIndex = 0;
  int yIndex = 0;

  float xCoord;
  float yCoord;
  while (command[index] != "") {
    instrIndex = command[index].indexOf('G');
    if (instrIndex != -1) {
      switch (command[index].substring(instrIndex + 1).toInt()) {
        case 1:
          xIndex = command[index].indexOf('X');
          if (xIndex != -1) {
            xCoord = command[index].substring(xIndex + 1).toFloat();
          }
          else Serial.println("X not detected");

          yIndex = command[index].indexOf('Y');
          if (yIndex != -1) {
            yCoord = command[index].substring(yIndex + 1).toFloat();
          }
          else Serial.println("Y not detected");

          Serial.print("xCoord = "); Serial.print(xCoord);
          Serial.print(" yCoord = "); Serial.println(yCoord);
        //   cnc.move((int)xCoord, (int)yCoord);
        //   cnc.move_m(xCoord, yCoord);
        cnc.move_b(xCoord, yCoord);
          break;
        case 2:
          zIndex = command[index].indexOf('Z');
          if (zIndex != -1) {
            if (command[index].substring(zIndex + 1).toInt() == 1) {
              cnc.up();
              Serial.println(command[index]);
            }
            else {
              cnc.down();
              Serial.println(command[index]);
            }
          }
          else {
            zIndex = command[index].indexOf('I');
            if (iIndex != -1) {
                if (command[index].substring(iIndex + 1).toInt() == 1) {
                    cnc.calibreUp();
                    Serial.println(command[index]);
                } else {
                    cnc.calibreDown();
                    Serial.println(command[index]);
                }
            //   Serial.println(command[index]);
            }
            else {
                Serial.println("Z or I not detected");
            }
          }
      }
    }
    // else Serial.println("G not detected");
    else {
        instrIndex = command[index].indexOf('M300 S');
        if (instrIndex != -1) {
            if (command[index].substring(instrIndex + 1).toInt() == 50) {
                cnc.up();
                Serial.println(command[index]);
            }
            else if (command[index].substring(instrIndex + 1).toInt() == 30) {
                cnc.down();
                Serial.println(command[index]);
            }
        }
        else Serial.println("G not detected");
    }
//    Serial.println(command[index]);
    index++;
    if (index > 99) {
        index = 0;
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    readedByte = Serial.read();
//    Serial.print(readedByte);
    if (( readedByte == '\n') || (readedByte == '\r')) {
//      Serial.print("Este");
      command[lineIndex] = buffer;
      lineIndex++;
      if (lineIndex > 99) {
          lineIndex = 0;
      }
      buffer = "";
      process(command);
    } else {
//      readedByte = Serial.read();
      buffer += readedByte;
//      readedBytes[readedByteNo] = atoi(readedByte);  /*(int)readedByte - 48*/;
//      readedByteNo++;
    }
  }
}
