#include "main.h"

Sprocket::Sprocket() {
    sprocketBottom.set_brake_mode(MOTOR_BRAKE_COAST);
    sprocketTop.set_brake_mode(MOTOR_BRAKE_COAST);
    sprocketIndexer.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void Sprocket::set_state(OutputState state) {
    this->state = state;
}

void Sprocket::set_state_and_move(OutputState state) {
    this->state = state;
    move_output_on_state();
}

void Sprocket::move_output_on_state() {
    switch (state) {
        case OutputState::LOWER:
            sprocketBottom.move(-Sprocket::VOLTAGE);
            sprocketTop.brake();
            sprocketIndexer.move(-Sprocket::VOLTAGE);
            break;
        case OutputState::MIDDLE:
            sprocketBottom.move(Sprocket::VOLTAGE);
            sprocketTop.move(-Sprocket::VOLTAGE);
            sprocketIndexer.move(-Sprocket::VOLTAGE);
            break;
        case OutputState::HIGHER:
            sprocketBottom.move(Sprocket::VOLTAGE);
            sprocketTop.move(Sprocket::VOLTAGE);
            sprocketIndexer.move(-Sprocket::VOLTAGE);
            break;
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
        move_output_on_state();
    } else if (master.get_digital(DIGITAL_R2)) {
        sprocketBottom.move(Sprocket::INTAKE_VOLTAGE);
        sprocketTop.move(Sprocket::VOLTAGE);
    } else {
        sprocketBottom.brake();
        sprocketTop.brake();
    }
}
