#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor TopRightMove = motor(PORT11, ratio18_1, true);
motor TopLeftMove = motor(PORT12, ratio18_1, false);
motor BottomLeftMove = motor(PORT13, ratio18_1, false);
motor BottomRightMove = motor(PORT14, ratio18_1, true);
motor TowerMotor = motor(PORT15, ratio36_1, false);
motor ArmMotor = motor(PORT16, ratio36_1, false);
motor LeftClaw = motor(PORT17, ratio18_1, false);
motor RightClaw = motor(PORT5, ratio18_1, true);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}