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

void testPID(){
  chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void rightSideRed(){
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE);
  pros::delay(5000); // Wait for the piston to move
  sprockets.run_intake(true);
  pros::delay(1000);

  sprockets.run_intake(false);
  pros::delay(1000);

  sprockets.run_intake(true);
  pros::delay(1000);

  // chassis.odom_xyt_set(0_ft, 0_ft, 90_deg); // Set the odom position to 0,0,0
  // chassis.pid_drive_set(36_in, DRIVE_SPEED*0.8, true);
  // chassis.pid_wait();
  // chassis.pid_turn_set(180_deg, TURN_SPEED/2);
  // chassis.pid_wait();
  // //put down the match loader piston
  // matchLoader("down");
  // chassis.pid_drive_set(24_in, DRIVE_SPEED*0.8, true);
  // chassis.pid_wait();
  // //put up the match loader piston
  // matchLoader("up");
  // pros::delay(500);
  // matchLoader("down");
  // sprockets.set_state_and_move(Sprocket::OutputState::LOWER); // Move the lower output
  // pros::delay(5000);
  // sprockets.set_state_and_move(Sprocket::OutputState::NONE);
  // chassis.pid_turn_set(2_deg, TURN_SPEED/4);
  // chassis.pid_wait();

  // chassis.pid_drive_set(46_in, DRIVE_SPEED*0.8, true);
  // sprockets.set_state_and_move(Sprocket::OutputState::HIGHER);
  
  // pros::delay(5000);

  //rest of the code


}

void redAWP(){
  chassis.odom_xyt_set(0_ft, 0_ft, 0_deg); // Set the odom position to 0,0,0
  sprockets.run_intake(true);
  chassis.pid_turn_set(-10_deg, TURN_SPEED/2);
  chassis.pid_wait();
  chassis.pid_drive_set(31_in, DRIVE_SPEED*0.7, true);
  chassis.pid_wait();
  // chassis.pid_drive_set(-2_in, DRIVE_SPEED*0.7, true);
  // chassis.pid_wait();
  chassis.pid_turn_set(47_deg, TURN_SPEED/2);
  chassis.pid_wait();
  sprockets.run_intake(false);
  chassis.pid_drive_set(11_in, DRIVE_SPEED*0.7, true);
  chassis.pid_wait();
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 100.0);
  pros::delay(1000); // Wait to score balls
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 50.0);
  pros::delay(2000); // Wait to score balls
  chassis.pid_drive_set(-10_in, DRIVE_SPEED*0.5, true);
  chassis.pid_wait();
  chassis.pid_turn_set(92_deg, TURN_SPEED/2);
  chassis.pid_wait();
  sprockets.run_intake(true);
  chassis.pid_drive_set(45_in, DRIVE_SPEED*0.7, true);
  chassis.pid_wait_quick();
  chassis.pid_drive_set(6_in, DRIVE_SPEED*0.4, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-46_deg, TURN_SPEED/2);
  chassis.pid_wait();
  chassis.pid_drive_set(7_in, DRIVE_SPEED*0.7, true);
  chassis.pid_wait();
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 50.0);
  pros::delay(2000); // Wait to score balls
  chassis.pid_turn_set(158_deg, TURN_SPEED/2);
  chassis.pid_wait();
}

void leftSideAuto0(){
  chassis.odom_xyt_set(0_ft, 0_ft, -90_deg); // Set the odom position to 0,0,0
  chassis.pid_drive_set(32_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-180_deg, TURN_SPEED*0.8);
  chassis.pid_wait();
  //put down the match loader piston
  matchLoaderPiston.set(true);
  sprockets.run_intake(true);
  chassis.pid_drive_set(6_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  for (int i = 0; i < 2; i++) {
    //pros::delay(100); // actually prob not needed --> THIS NEED TO BE CHANGED SO THAT WE ONLY TAKE 3 BALLS. EXACT TIME WILL NEED TO BE TESTED AFTER PNEUMATICS ARE WIRED 
    chassis.pid_drive_set(-1.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(1.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();
  }

  chassis.pid_drive_set(-4_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick();
  //turn around  
  chassis.pid_turn_set(0_deg, TURN_SPEED*0.9);
  chassis.pid_wait();
  //drive forward to score
  matchLoaderPiston.set(false);
  chassis.pid_drive_set(22_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait_until(10_in);
  // SWITCH HOOD HERE
  hoodPiston.set(true);
  sprockets.set_state_and_move(Sprocket::OutputState::HIGHER);
  pros::delay(4000);

  hoodPiston.set(false);
  chassis.pid_drive_set(-12_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait();
  chassis.pid_turn_set(47_deg, TURN_SPEED*0.8);
  chassis.pid_wait();
  sprockets.run_intake(true);
  chassis.pid_drive_set(21_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(27_in, DRIVE_SPEED*0.7, true);
  chassis.pid_wait();
  sprockets.run_intake(false);
  hoodPiston.set(true);
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 0.8);
  chassis.pid_drive_set(-1.5_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  pros::delay(5000); // Wait to score balls
  sprockets.set_state_and_move(Sprocket::OutputState::MIDDLE, 0.5);

}

void rightSideAuto0(){
  chassis.odom_xyt_set(0_ft, 0_ft, 90_deg); // Set the odom position to 0,0,0
  chassis.pid_drive_set(30_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED*0.8);
  chassis.pid_wait();
  //put down the match loader piston
  matchLoaderPiston.set(true);
  pros::delay(200);
  sprockets.run_intake(true);

  // intake matchload
  chassis.pid_drive_set(10_in, DRIVE_SPEED*0.8, true);
  pros::delay(950); // TIME SPENT AT THINGY

  chassis.pid_drive_set(-4_in, DRIVE_SPEED*0.9, true);
  chassis.pid_wait_quick();

  //turn around  
  chassis.pid_turn_set(2_deg, TURN_SPEED*0.9);
  chassis.pid_wait();

  //drive forward to score
  hoodPiston.set(true);
  matchLoaderPiston.set(false);
  chassis.pid_drive_set(17.25_in, DRIVE_SPEED*0.8, true);
  chassis.pid_wait_until(16_in);

  sprockets.set_state_and_move(Sprocket::OutputState::HIGHER);
  pros::delay(4000);
}

#pragma region Template Included

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

#pragma endregion Template Included
