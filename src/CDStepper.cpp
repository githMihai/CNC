#include "CDStepper.h"

CDStepper::CDStepper() {}

CDStepper::CDStepper(int number_of_steps, int stepPin, int directionPin, int sleepPin) {
    this->number_of_steps = number_of_steps;
    this->stepPin = stepPin;
    this->directionPin = directionPin;
    this->sleepPin = sleepPin;
    this->direction = 1;
    this->step_delay = 400;
    this->step_number = 0;
    this->last_command = 1;
    this->state = LOW;

    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(sleepPin, OUTPUT);

    this->sleep();
}

void CDStepper::setSpeed(int speed) {
    this->step_delay = speed;
}

// void CDStepper::step(int steps) {
//     for (int i = 0; i < steps; i++) {
//         if (steps > 0) {
//             Serial.println("Here");
//             stepF();
//         } else {
//             Serial.println("try");
//             stepB();
//         }
//     }
// }

void CDStepper::stepF() {
    if (this->last_command != this->direction) {
        this->last_command = this->direction;
        this->step_number = 0;
    }
    digitalWrite(directionPin, LOW);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->step_number++;
}

void CDStepper::stepB() {
    if (this->last_command != this->direction) {
        this->last_command = this->direction;
        this->step_number = 0;
    }
    digitalWrite(directionPin, HIGH);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->step_number--;
}


void CDStepper::stepF3() {
    if (this->last_command != this->direction) {
        this->last_command = this->direction;
        this->step_number = 0;
    }
    digitalWrite(directionPin, LOW);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->step_number++;
}

void CDStepper::stepB3() {
    if (this->last_command != this->direction) {
        this->last_command = this->direction;
        this->step_number = 0;
    }
    digitalWrite(directionPin, HIGH);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->state = !this->state;
    digitalWrite(stepPin, this->state);
    delayMicroseconds(step_delay);
    this->step_number--;
}

void CDStepper::sleep() {
    digitalWrite(sleepPin, LOW);
}

void CDStepper::wake() {
    digitalWrite(sleepPin, HIGH);
}

long CDStepper::getStepNumber() {
    return this->step_number;
}
