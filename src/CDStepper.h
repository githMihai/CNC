#include <Arduino.h>

class CDStepper {
    public:
        CDStepper();

        CDStepper(int number_of_steps, int stepPin, int directionPin, int sleepPin);

        // speed setter method:
        void setSpeed(int speed);

        void step(int steps);

        // move forward method:
        void stepF();

        // move backward method:
        void stepB();

        // move forward3 method:
        void stepF3();

        // move backward3 method:
        void stepB3();

        // Stepper sleep
        void sleep();

        // Wake up
        void wake();

        // step number getter method:
        long getStepNumber();

    private:
        int direction;
        long step_delay;
        int number_of_steps;
        long step_number;

        int stepPin;
        int directionPin;
        int sleepPin;

        int state;

        int last_command;
};
