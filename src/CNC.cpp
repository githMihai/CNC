#include "CNC.h"

CNC::CNC(CDStepper stepperX, int limitX, CDStepper stepperY, int limitY, Servo servo) {
    this->stepperX = stepperX;
    this->stepperY = stepperY;

    this->limitX = limitX;
    this->limitY = limitY;

    this->coordX = 0;
    this->coordY = 0;

    this->servo = servo;
    // Serial.begin(9600);
}

int  CNC::move(int coordX, int coordY) {
    if (coordX < 0 || coordX > limitX || coordY < 0 || coordY > limitY) {
        return -1;
    }
    this->stepperX.wake();
    this->stepperY.wake();
    delay(1);
    while(coordX != (int)this->coordX || coordY != (int)this->coordY) {

        if (coordX > (int)this->coordX) {
            CNC::right((int)coordX);
        }

        if (coordX < (int)this->coordX) {
            CNC::left((int)coordX);
        }

        if ((int)(coordY) > (int)(this->coordY)) {
            CNC::far((int)(coordY));
        }

        if ((int)(coordY) < (int)(this->coordY)) {
            CNC::near((int)(coordY));
        }
        delay(5);

        // sleep
        if (coordX == (int)this->coordX) {
            this->stepperX.sleep();
        }
        if (coordY == (int)this->coordY) {
            this->stepperY.sleep();
        }
    }
    this->stepperX.sleep();
    this->stepperY.sleep();
    return 0;
}

int CNC::move_m(float coordX, float coordY) {
    if (coordX < 0 || coordX > limitX / this->stepsPerMillimeterX || coordY < 0 || coordY > limitY / this->stepsPerMillimeterY) {
        return -1;
    }
    this->stepperX.wake();
    this->stepperY.wake();
    delay(1);
    while((int)coordX != (int)(this->coordX / stepsPerMillimeterX) || (int)coordY != (int)(this->coordY / stepsPerMillimeterY)) {

        if ((int)coordX > (int)(this->coordX / stepsPerMillimeterX)) {
            Serial.println((coordX * this->stepsPerMillimeterX));
            CNC::right((int)(coordX * this->stepsPerMillimeterX));
        } else
        if ((int)coordX < (int)(this->coordX / stepsPerMillimeterX)) {
            CNC::left((int)(coordX * this->stepsPerMillimeterX));
        }

        if ((int)coordY > (int)(this->coordY / stepsPerMillimeterY)) {
            CNC::far((int)(coordY * this->stepsPerMillimeterY));
        } else
        if ((int)coordY < (int)(this->coordY / stepsPerMillimeterY)) {
            CNC::near((int)(coordY * this->stepsPerMillimeterY));
        }
        delay(5);

        // sleep
        if ((int)coordX == (int)(this->coordX / stepsPerMillimeterX)) {
            this->stepperX.sleep();
        }
        if ((int)coordY == (int)this->coordY / stepsPerMillimeterY) {
            this->stepperY.sleep();
        }
    }
    this->stepperX.sleep();
    this->stepperY.sleep();
    return 0;
}

int CNC::move_b(float coordX, float coordY) {
    if (coordX < 0 || coordX > limitX / this->stepsPerMillimeterX || coordY < 0 || coordY > limitY / this->stepsPerMillimeterY) {
        return -1;
    }
    this->stepperX.wake();
    this->stepperY.wake();


    //  Convert coordinates to steps
    int x1 = (int)(coordX*this->stepsPerMillimeterX);
    int y1 = (int)(coordY*this->stepsPerMillimeterY);
    float x0 = this->coordX;
    float y0 = this->coordY;

    //  Let's find out the change for the coordinates
    long dx = abs(x1-x0);
    long dy = abs(y1-y0);
    int sx = x0<x1 ? 1 : -1;
    int sy = y0<y1 ? 1 : -1;

    long i;
    long over = 0;

    if (dx > dy) {
        for (i=0; i<dx; ++i) {
            // this->stepperX.step(sx);
            sx>0 ? this->stepperX.stepF() : this->stepperX.stepB();
            over+=dy;
            if (over>=dx) {
                over-=dx;
                // this->stepperY.step(sy);
                sy>0 ? this->stepperY.stepF() : this->stepperY.stepB();
            }
            delay(3);
        }
    }
    else {
        for (i=0; i<dy; ++i) {
            // this->stepperY.step(sy);
            sy>0 ? this->stepperY.stepF() : this->stepperY.stepB();
            over+=dx;
            if (over>=dy) {
                over-=dy;
                // this->stepperX.step(sx);
                sx>0 ? this->stepperX.stepF() : this->stepperX.stepB();
            }
            delay(3);
        }
    }

  // if (verbose)
  // {
  //   Serial.print("dx, dy:");
  //   Serial.print(dx);
  //   Serial.print(",");
  //   Serial.print(dy);
  //   Serial.println("");
  // }
  //
  // if (verbose)
  // {
  //   Serial.print("Going to (");
  //   Serial.print(x0);
  //   Serial.print(",");
  //   Serial.print(y0);
  //   Serial.println(")");
  // }

  //  Delay before any next lines are submitted
    // delay(10);
    //  Update the positions
    this->coordX = x1;
    this->coordY = y1;
    // Serial.print("Line X = "); Serial.print(sx);
    // Serial.print(" Y = "); Serial.println(sy);

    // this->stepperX.sleep();
    // this->stepperY.sleep();
    return 0;
}

void CNC::far(int steps) {
    // for (int i = 0; i < steps; i++) {
        this->stepperY.stepF3();
        // this->stepperY.stepF();
        this->coordY++;
        // if (this->stepperY.getStepNumber() % 3 == 0) {
        //     this->stepperY.stepF();
        // }
        // Serial.print('currentY = ');
        // Serial.print(this->coordY);
        // Serial.print(' targetY = ');
        // Serial.println(coordY);
    // }
}

void CNC::near(int steps) {
    // for (int i = 0; i < steps; i++) {
        this->stepperY.stepB3();
        // this->stepperY.stepB();
        this->coordY--;
        // if (this->stepperY.getStepNumber() % 5 == 0) {
        //     this->stepperY.stepB();
        // }
    // }
}

void CNC::right(int steps) {
    // for (int i = 0; i < steps; i++) {
        this->stepperX.stepB();
        this->coordX++;
    // }
}

void CNC::left(int steps) {
    // for (int i = 0; i < steps; i++) {
        this->stepperX.stepF();
        this->coordX--;
    // }
}

void CNC::up() {
    this->stepperX.sleep();
    this->stepperY.sleep();
    servo.write(this->UP);
}

void CNC::down() {
    this->stepperX.sleep();
    this->stepperY.sleep();
    servo.write(this->DOWN);
}

void CNC::calibreUp() {
    this->DOWN += 2;
    this->down();
}

void CNC::calibreDown() {
    this->DOWN -= 2;
    this->down();
}

// int CNC::millimetersToSteps(float millimeters, float ratio) {
//     return millimeters * ratio
// }

int CNC::getX() {
    return this->coordX;
}

int CNC::getY() {
    return this->coordY;
}
