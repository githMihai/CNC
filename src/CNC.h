#include <Arduino.h>
#include "CDStepper.h"
#include <Servo.h>

// #define UP 90
// #define DOWN 128

class CNC{
    public:
        CNC(CDStepper stepperX, int limitX, CDStepper stepperY, int limitY, Servo servo);

        // move method
        int move(int coordX, int coordY);

        int move_m(float coordX, float coordY);

        int move_b(float coordX, float coordY);

        void far(int steps);

        void near(int steps);

        void left(int steps);

        void right(int steps);

        void up();

        void down();

        void calibreUp();

        void calibreDown();

        int getX();

        int getY();


    private:
        float coordX;
        float coordY;

        int limitX;
        int limitY;

        float stepsPerMillimeterX = 4.54;
        float stepsPerMillimeterY =  6.66;
        // float stepsPerMillimeterY =  15.66;

        int UP = 90;
        // int DOWN = 128;
        int DOWN = 139;

        CDStepper stepperX;
        CDStepper stepperY;
        Servo servo;

};
