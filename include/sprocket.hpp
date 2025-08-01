#pragma once

/// @brief Controls sprockets in the robot.
class Sprocket {
    public:
        /// @brief Keeps track of currently selected output
        enum class OutputState {
            NONE, // No output selected
            LOWER, // Lower output
            MIDDLE, // Middle output
            HIGHER // Higher output
        };

        Sprocket();

        void set_state(OutputState state);
        void set_state_and_move(OutputState state);

        void move_motors_on_state();
        void opcontrol();
        void run_intake(bool isRunning);
        void move_motors_on_state(OutputState state, double voltagePercentage);
        void set_state_and_move(OutputState state, double voltagePercentage);
    private:
        static const int INTAKE_VOLTAGE = 127;
        static const int VOLTAGE = 105;

        OutputState state = OutputState::NONE;
};
