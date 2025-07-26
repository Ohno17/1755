#include "main.h"

Sprocket::Sprocket() {
    sprocketBottom.set_brake_mode(MOTOR_BRAKE_COAST);
    sprocketTop.set_brake_mode(MOTOR_BRAKE_COAST);
}

void Sprocket::set_state(OutputState state) {
    this->state = state;
}

void Sprocket::output_motors() {
    switch (state) {
        case OutputState::LOWER:
            sprocketBottom.move(-Sprocket::REGULAR_VOLTAGE);
            sprocketTop.brake();
            break;
        case OutputState::MIDDLE:
            sprocketBottom.move(Sprocket::REGULAR_VOLTAGE);
            sprocketTop.move(-Sprocket::REGULAR_VOLTAGE);
            break;
        case OutputState::HIGHER:
            sprocketBottom.move(Sprocket::REGULAR_VOLTAGE);
            sprocketTop.move(Sprocket::REGULAR_VOLTAGE);
            break;
        // Should never happen except after initalization
        case OutputState::NONE:
        default:
            sprocketBottom.brake();
            sprocketTop.brake();
            break;
    }
}

void Sprocket::opcontrol() {
    if (master.get_digital(DIGITAL_UP)) {
        set_state(OutputState::HIGHER);
    } else if (master.get_digital(DIGITAL_RIGHT)) {
        set_state(OutputState::MIDDLE);
    } else if (master.get_digital(DIGITAL_DOWN)) {
        set_state(OutputState::LOWER);
    }

    if (master.get_digital(DIGITAL_R1)) {
        output_motors();
    } else if (master.get_digital(DIGITAL_R2)) {
        // Only Intake
        sprocketBottom.move(Sprocket::INTAKE_VOLTAGE);
        sprocketTop.move(Sprocket::REGULAR_VOLTAGE);
    } else {
        // Stop if neither are pressed
        sprocketBottom.brake();
        sprocketTop.brake();
    }
}
