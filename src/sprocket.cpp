#include "main.h"

Sprocket::Sprocket() {
    sprocket.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Sprocket::set_state(State state) {
    this->state = state;
}

void Sprocket::move_motors() {
    switch (state) {
        case State::INTAKE_ONLY:
            sprocket.move(Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_LOW:
            sprocket.move(-Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_MIDDLE:
            sprocket.move(Sprocket::VOLTAGE);
            break;
        case State::OUTPUT_HIGH:
            sprocket.move(-Sprocket::VOLTAGE);
            break;
        case State::STOPPED:
        default:
            sprocket.brake();
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
