#pragma once

/// @brief Controls and keeps track of all sprockets in the robot.
class Sprocket {
    public:
        enum class State {
            STOPPED,
            INTAKE_ONLY,
            OUTPUT_LOW,
            OUTPUT_MIDDLE,
            OUTPUT_HIGH
        };

        Sprocket();

        void set_state(State state);

        void move_motors();
        void opcontrol();
    private:
        static const int VOLTAGE = 60;
        State state = State::STOPPED;
};
