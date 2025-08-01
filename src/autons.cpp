#include "main.h"

// These are out of 127
const int DRIVE_SPEED = 127;
const int TURN_SPEED = 100;
const int SWING_SPEED = 110;


///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(28.0, 1, 250.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 35.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  
  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void left_side_auto() {
  chassis.odom_xyt_set(0_ft, 0_ft, -90_deg); // Set the odom position to 0,0,0
  chassis.pid_drive_set(31_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED*0.8);
  chassis.pid_wait();

  //put down the match loader piston
  matchLoaderPiston.set(true);
  pros::delay(200);
  sprockets.run_intake(true);

  // intake matchload
  chassis.pid_drive_set(11_in, DRIVE_SPEED*0.8, true);
  pros::delay(1000); // TIME SPENT AT THINGY

  chassis.pid_drive_set(-10_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick();
  matchLoaderPiston.set(false);

  //turn around  
  chassis.pid_turn_set(0_deg, TURN_SPEED*0.9);
  chassis.pid_wait();

  //drive forward to score
  hoodPiston.set(true);
  chassis.pid_drive_set(15.5_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait_until(16_in);

  sprockets.set_state_and_move(Sprocket::OutputState::HIGHER);
  pros::delay(3000);
  sprockets.set_state_and_move(Sprocket::OutputState::NONE);

  hoodPiston.set(false);
  chassis.pid_drive_set(-12_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait();
  chassis.pid_turn_set(45_deg, TURN_SPEED*0.7);
  sprockets.run_intake(true);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(28_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  sprockets.run_intake(false);
  hoodPiston.set(true);
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 1);
  pros::delay(4000);
}

void right_side_auto() {
  chassis.odom_xyt_set(0_ft, 0_ft, 90_deg); // Set the odom position to 0,0,0
  chassis.pid_drive_set(31_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED*0.8);
  chassis.pid_wait();
  //put down the match loader piston
  matchLoaderPiston.set(true);
  pros::delay(200);
  sprockets.run_intake(true);

  // intake matchload
  chassis.pid_drive_set(11_in, DRIVE_SPEED*0.85, true);
  pros::delay(1000); // TIME SPENT AT THINGY

  chassis.pid_drive_set(-10_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick();

  //turn around  
  chassis.pid_turn_set(2_deg, TURN_SPEED*0.9);
  chassis.pid_wait();

  //drive forward to score
  hoodPiston.set(true);
  matchLoaderPiston.set(false);
  chassis.pid_drive_set(15.6_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait_until(16_in);

  sprockets.set_state_and_move(Sprocket::OutputState::HIGHER);
  pros::delay(3000);
  sprockets.set_state_and_move(Sprocket::OutputState::NONE);

  // diag0-_)SI()(I)ASIIASFI)AI)(FS(A))

  hoodPiston.set(false);
  chassis.pid_drive_set(-12_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-45_deg, TURN_SPEED*0.7);
  sprockets.run_intake(true);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(27_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  pros::delay(1000);
  sprockets.run_intake(false);
  hoodPiston.set(true);
}
