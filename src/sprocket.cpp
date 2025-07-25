#include "main.h"

Sprocket::Sprocket() {
    sprocketBottom.set_brake_mode(MOTOR_BRAKE_COAST);
    sprocketTop.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Sprocket::set_state(State state) {
    this->state = state;
}

void Sprocket::move_motors() {
    switch (state) {
        case State::INTAKE_ONLY:
            sprocketBottom.move(Sprocket::VOLTAGE);
            sprocketTop.move(Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_LOW:
            sprocketBottom.move(-Sprocket::VOLTAGE);
            sprocketTop.move(Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_MIDDLE:
            sprocketBottom.move(Sprocket::VOLTAGE);
            sprocketTop.move(Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_HIGH:
            sprocketBottom.move(-Sprocket::VOLTAGE);
            sprocketTop.move(Sprocket::VOLTAGE);
            break;
        case State::STOPPED:
        default:
            sprocketBottom.brake();
            sprocketTop.brake();
            break;
    }
}

void Sprocket::opcontrol() {
    if (master.get_digital(DIGITAL_A)) {
        set_state(State::INTAKE_ONLY);
    } else if (master.get_digital(DIGITAL_UP)) {
        set_state(State::OUTPUT_HIGH);
    } else if (master.get_digital(DIGITAL_RIGHT)) {
        set_state(State::OUTPUT_MIDDLE);
    } else if (master.get_digital(DIGITAL_DOWN)) {
        set_state(State::OUTPUT_LOW);
    } else {
        set_state(State::STOPPED);
    }

    move_motors();
}
