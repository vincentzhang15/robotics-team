///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
//// VEX C++ API: https://www.robotmesh.com/docs/vexv5-cpp/html/index.html                         ////
//// VCS Command Reference: https://help.vexcodingstudio.com/index.html                            ////
//// PROS Documentation: https://pros.cs.purdue.edu/v5/index.html                                  ////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// TopRightMove         motor         11              
// TopLeftMove          motor         12              
// BottomLeftMove       motor         13              
// BottomRightMove      motor         14              
// TowerMotor           motor         15              
// ArmMotor             motor         16              
// LeftClaw             motor         17              
// RightClaw            motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition; // A global instance of competition

void pre_auton(void)
{
  vexcodeInit(); // Initializing Robot Configuration. DO NOT REMOVE!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//   $$\    /////////////////////////////////////////////////////////////////////////////////////////////
// $$$$ |   /////////////////////////////////////////////////////////////////////////////////////////////
// \_$$ |   /////////////////////////////////////////////////////////////////////////////////////////////
//   $$ |   ////////////////////////////////// AUTONOMOUS CODE //////////////////////////////////////////
//   $$ |   /////////////////////////////////////////////////////////////////////////////////////////////
//   $$ |   /////////////////////////////////////////////////////////////////////////////////////////////
// $$$$$$\  /////////////////////////////////////////////////////////////////////////////////////////////
// \______| /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int pos = 2; // 1:Blue right, 2: Blue base, 3:Red base, 4:Red right, ELSE: skills =============== (1, 4, ELSE)
double circumference = 10.16 * M_PI;


void fwdDecelerate(int power)
{
  double degrees = 120;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void backDecelerate(int power)
{
  double degrees = -120;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void leftDecelerate(int power)
{
  double degrees = -60;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void rightDecelerate(int power)
{
  double degrees = 60;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}

void move(double dist, int power) // Positive power: forward, Negative power: backward
{
  double degrees = (dist/circumference)*360;
  TopLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  TopRightMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomRightMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct);
}
void noWaitMove(double dist, int power) // Positive power: forward, Negative power: backward
{
  double degrees = (dist/circumference)*360;
  TopLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  TopRightMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomRightMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
}
void moveTurn(double d1, int p1, int d2, int p2)
{
  double deg1 = (d1/circumference)*360;
  double deg2 = (d2/circumference)*360;
  TopLeftMove.rotateFor(deg1, rotationUnits::deg, p1, velocityUnits::pct, false);
  TopRightMove.rotateFor(deg2, rotationUnits::deg, p2, velocityUnits::pct, false);
  BottomLeftMove.rotateFor(deg1, rotationUnits::deg, p1, velocityUnits::pct, false);
  BottomRightMove.rotateFor(deg2, rotationUnits::deg, p2, velocityUnits::pct, false);
}
void turn(double dist, int power) // Positive power: right, Negative power: left
{
  double degrees = (dist/circumference)*360;
  TopLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  TopRightMove.rotateFor(-degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomLeftMove.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  BottomRightMove.rotateFor(-degrees, rotationUnits::deg, power, velocityUnits::pct);
}

void intake(double dist, int power) // Positive power: cube in, Negative power: cube out
{
  double degrees = ((dist/circumference)*360);
  LeftClaw.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
  RightClaw.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct, false);
}
void lift(double degrees, int power) // Positive power: arms up, Negative power: arms down
{
  /*
  if(!ArmMotor.isSpinning())
    ArmMotor.stop(brakeType::hold);
  else
    ArmMotor.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct);
  */    
    ArmMotor.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct);
    ArmMotor.stop(brakeType::hold);
}

void tower(double degrees, int power)
{
  /*
  if(!TowerMotor.isSpinning())
  {
    Controller1.Screen.print("T S");
    TowerMotor.stop(brakeType::hold);
  }
  else
  {
    Controller1.Screen.print("T %d %d",power, degrees);
    TowerMotor.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct);
  }
  */

    TowerMotor.rotateFor(degrees, rotationUnits::deg, power, velocityUnits::pct);

    TowerMotor.stop(brakeType::hold);
}



void expand()
{
  move(15, 70);
  move(-15, 40);
  intake(-100, 100);
  tower(200, 100);
  lift(-100, 100);
  lift(100, 100);
  tower(-200, 50);
}

void scoreStack()
{
}

void autonomous(void)
{
  if(pos == 1) // Blue Right
  {
    expand();
    
    intake(560, 100);
    move(50, 40);
    move(69, 20);
    wait(0.4, seconds);
    

    // Reverse to first tile
    move(-52, 70);

    // Turn to wall
    wait(0.2, seconds);
    turn(-36.9, 20);
    
    // Score tower
    
    wait(0.2, sec);
    TowerMotor.rotateFor(380, rotationUnits::deg, 55, velocityUnits::pct, false);
    move(43, 30);
    intake(-20, 100);

    TowerMotor.rotateFor(320, rotationUnits::deg, 30, velocityUnits::pct);
    //TowerMotor.rotateFor(0, rotationUnits::deg, 10, velocityUnits::pct);
    move(1, 40); // Reverse away from wall
    move(-30, 100); // Reverse away from wall
    TowerMotor.rotateFor(-560, rotationUnits::deg, 50, velocityUnits::pct);
    
    //scoreStack();
  }
  else if(pos == 2) // Blue base
  {
    move(50, 80);
    move(-100, 80);
    expand();

    /*
    expand();
    intake(560, 100);
    move(100, 80);
    move(10, 30);
    // Reverse to first tile

    // Turn to wall
    wait(0.2, seconds);
    turn(36.9, 20);
    intake(200, 100);
    move(60, 80);
    
    // Score tower
    
    wait(0.2, sec);
    TowerMotor.rotateFor(380, rotationUnits::deg, 55, velocityUnits::pct, false);
    move(50, 30);
    intake(-20, 100);

    TowerMotor.rotateFor(320, rotationUnits::deg, 30, velocityUnits::pct);
    //TowerMotor.rotateFor(0, rotationUnits::deg, 10, velocityUnits::pct);
    move(1, 40); // Reverse away from wall
    move(-30, 100); // Reverse away from wall
    TowerMotor.rotateFor(-560, rotationUnits::deg, 50, velocityUnits::pct);
    */
  }
  else if(pos == 3) // Red base
  {
/*    expand();
    
    intake(560, 100);
    move(50, 40);
    move(69, 20);
    wait(0.4, seconds);
    

    // Reverse to first tile
    move(-52, 70);

    // Turn to wall
    wait(0.2, seconds);
    turn(-36.9, 20);
    
    // Score tower
    
    wait(0.2, sec);
    TowerMotor.rotateFor(380, rotationUnits::deg, 55, velocityUnits::pct, false);
    move(43, 30);
    intake(-20, 100);

    TowerMotor.rotateFor(320, rotationUnits::deg, 30, velocityUnits::pct);
    //TowerMotor.rotateFor(0, rotationUnits::deg, 10, velocityUnits::pct);
    move(1, 40); // Reverse away from wall
    move(-30, 100); // Reverse away from wall
    TowerMotor.rotateFor(-560, rotationUnits::deg, 50, velocityUnits::pct);
*/

/*
    // Align with cube tower
    //expand();
    move(60.96, 80);
    wait(0.5, sec);
    turn(-8, 20);

    // Get 4 cube stack
    intake(120, 100);
    move(60, 100);

    // Get preload
    turn(-43, 40);
    intake(300, 100);
    move(85, 80);
*//*
    // Drive to base and score
    turn(30, 50);
    noWaitMove(60.96, 100);
    turn(10, 50);
    scoreStack();
*/  
move(50, 100);
move(-50, 100);
expand();
}
  else if(pos == 4) // Red right
  {
    expand();
    
    intake(560, 100);
    move(50, 40);
    move(69, 20);
    wait(0.4, seconds);
    

    // Reverse to first tile
    move(-52, 70);

    // Turn to wall
    wait(0.2, seconds);
    turn(36.9, 20);
    
    // Score tower
    
    wait(0.2, sec);
    TowerMotor.rotateFor(380, rotationUnits::deg, 55, velocityUnits::pct, false);
    move(43, 30);
    intake(-20, 100);

    TowerMotor.rotateFor(320, rotationUnits::deg, 30, velocityUnits::pct);
    //TowerMotor.rotateFor(0, rotationUnits::deg, 10, velocityUnits::pct);
    move(1, 40); // Reverse away from wall
    move(-30, 100); // Reverse away from wall
    TowerMotor.rotateFor(-560, rotationUnits::deg, 50, velocityUnits::pct);
  }
  else // Programming skills
  {
/*    expand();

    // Pick up 9 cubes, turn left, score
    intake(600, 100);
    move(250, 60);
    move(-50, 60);
    turn(-50, 60);
    move(50, 60);
    scoreStack();

    // Score cube in tower
    move(-50, 60);
    turn(50, 60);
    intake(50, 100);
    move(50, 60);
    move(-50, 60);
    turn(-50, 60);
    scoreLowTower();

    // Score second cube in tower
    move(-50, 60);
    turn(-30, 60);
    intake(50, 100);
    move(50, 60);
    scoreMidTower();

    // Score third cube in tower
    move(-100, 60);
    turn(-50, 60);
    intake(100, 100);
    move(100, 60);
    scoreMidTower();

    // Get more cubes and score
    move(-50, 60);
    turn(50, 60);
    intake(200, 100);
    move(200, 60);
    turn(50, 60);
    move(50, 60);
    scoreStack();

    // Score fourth cube in tower
    move(-100, 60);
    turn(-100, 60);
    intake(100, 100);
    move(100, 60);
    scoreMidTower();
    */
  }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  $$$$$$\   ///////////////////////////////////////////////////////////////////////////////////////////
// $$  __$$\  ///////////////////////////////////////////////////////////////////////////////////////////
// \__/  $$ | ///////////////////////////////////////////////////////////////////////////////////////////
//  $$$$$$  | //////////////////////////////// MACROS AND USER CONTROL //////////////////////////////////
// $$  ____/  ///////////////////////////////////////////////////////////////////////////////////////////
// $$ |       ///////////////////////////////////////////////////////////////////////////////////////////
// $$$$$$$$\  ///////////////////////////////////////////////////////////////////////////////////////////
// \________| ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void usercontrol(void)
{
  //double autoStackSpeed = 100;
  //double autoStackAcceleration = 0.9;
  //expand();
  
  while (1)
  {
    /*
    Brain.Screen.clearScreen();
    Brain.Screen.print("TopRightMove: %d", TopRightMove.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("TopLeftMove: %d", TopLeftMove.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("BottomLeftMove: %d", BottomLeftMove.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("BottomRightMove: %d", BottomRightMove.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("TowerMotor: %d", TowerMotor.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("ArmMotor: %d", ArmMotor.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("LeftClaw: %d", LeftClaw.temperature(celsius));
    Brain.Screen.newLine();
    Brain.Screen.print("RightClaw: %d", RightClaw.temperature(celsius));
    Brain.Screen.newLine();
*/
    //Controller1.Screen.print(TopLeftMove.temperature(celsius));
    // Joystick Control Drivetrain
    double moveAxisPercent = Controller1.Axis3.value()/127.0;
    double turnAxisPercent = Controller1.Axis4.value()/127.0;
    double movePower = moveAxisPercent*100;
    double turnPower = turnAxisPercent*100;

    TopLeftMove.spin(directionType::fwd, movePower+turnPower, velocityUnits::pct);
    BottomLeftMove.spin(directionType::fwd, movePower+turnPower, velocityUnits::pct);
    TopRightMove.spin(directionType::fwd, movePower-turnPower, velocityUnits::pct);
    BottomRightMove.spin(directionType::fwd, movePower-turnPower, velocityUnits::pct);


    // Intake
    if(Controller1.ButtonR1.pressing())
    {
      LeftClaw.spin(directionType::fwd, 100, velocityUnits::pct);
      RightClaw.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      LeftClaw.spin(directionType::fwd, -100, velocityUnits::pct);
      RightClaw.spin(directionType::fwd, -100, velocityUnits::pct);
    }
    else
    {
      LeftClaw.stop(brakeType::coast);
      RightClaw.stop(brakeType::coast);
    }

    // Arms
    if(Controller1.ButtonL1.pressing())
    {
      ArmMotor.spin(directionType::fwd, -100, velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      ArmMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    }
    else
    {
      ArmMotor.stop(brakeType::hold);
    }
/*
    // Auto score tower
    if(Controller1.ButtonX.pressing())
    {
      TowerMotor.spin(directionType::fwd, autoStackSpeed, velocityUnits::pct);
      autoStackSpeed -= autoStackAcceleration;
      autoStackSpeed = (autoStackSpeed<10)?(10):(autoStackSpeed);
    }
    else
    {
      autoStackSpeed = 100;
      TowerMotor.stop(brakeType::hold);
    }

*/
    // Forward full speed
    if(Controller1.ButtonUp.pressing())
    {
      TopLeftMove.spin(directionType::fwd, 100, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, 100, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, 100, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, 100, velocityUnits::pct);
    }

    // Stacker
    double stackAxisPercent = Controller1.Axis2.value()/127.0;
    double stackPower = stackAxisPercent*100;
    TowerMotor.spin(directionType::fwd, stackPower, velocityUnits::pct);

    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  $$$$$$\   ///////////////////////////////////////////////////////////////////////////////////////////
// $$ ___$$\  ///////////////////////////////////////////////////////////////////////////////////////////
// \_/   $$ | ///////////////////////////////////////////////////////////////////////////////////////////
//   $$$$$ /  /////////////////////// MAIN //////////////////////////////////////////////////////////////
//   \___$$\  ///////////////////////////////////////////////////////////////////////////////////////////
// $$\   $$ | ///////////////////////////////////////////////////////////////////////////////////////////
// \$$$$$$  | ///////////////////////////////////////////////////////////////////////////////////////////
//  \______/  ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() // Main will set up the competition functions and callbacks.
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

























/*
void brakeMove ()
{
  if(!TopLeftMove.isSpinning())
    TopLeftMove.stop(brakeType::hold);
  if(!TopRightMove.isSpinning())
    TopLeftMove.stop(brakeType::hold);
  if(!BottomLeftMove.isSpinning())
    TopLeftMove.stop(brakeType::hold);
  if(!BottomRightMove.isSpinning())
    TopLeftMove.stop(brakeType::hold);
}



void scoreLowTower()
{
  TowerMotor.rotateFor(300, rotationUnits::deg, 100, velocityUnits::pct, false);
  lift(100, 100);
  move(-50, 50);
  intake(-100, 100);
  wait(0.1, seconds);

  lift(-100, 100);
  TowerMotor.rotateFor(-300, rotationUnits::deg, 100, velocityUnits::pct);
}
void scoreMidTower()
{
  TowerMotor.rotateFor(300, rotationUnits::deg, 100, velocityUnits::pct, false);
  lift(140, 100);
  move(-50, 50);
  intake(-100, 100);
  wait(0.1, seconds);
  
  lift(-140, 100);
  TowerMotor.rotateFor(-300, rotationUnits::deg, 100, velocityUnits::pct);
}




void fwdDecelerate(int power)
{
  double degrees = 120;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void backDecelerate(int power)
{
  double degrees = -120;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void leftDecelerate(int power)
{
  double degrees = -60;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}
void rightDecelerate(int power)
{
  double degrees = 60;
  for(int i = power; i >= 0; i--)
  {
    TopLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    TopRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomLeftMove.rotateFor(degrees, rotationUnits::deg, i, velocityUnits::pct, false);
    BottomRightMove.rotateFor(-degrees, rotationUnits::deg, i, velocityUnits::pct, false);
  }
}







  double upSpeed = 0;
  double downSpeed = 0;
  double leftSpeed = 0;
  double rightSpeed = 0;
  double fwdAcceleration = 3;
  double turnAcceleration = 1;

    // Button Control Drivetrain
    if(Controller1.ButtonUp.pressing() && Controller1.ButtonLeft.pressing()) // Up left
    {
      upSpeed += fwdAcceleration;
      leftSpeed += turnAcceleration;
      upSpeed = (upSpeed>100)?(100):(upSpeed);
      leftSpeed = (leftSpeed>50)?(50):(leftSpeed);

      TopLeftMove.spin(directionType::fwd, upSpeed-leftSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, upSpeed-leftSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);

      downSpeed = 0;
      rightSpeed = 0;
    }
    else if(Controller1.ButtonUp.pressing() && Controller1.ButtonRight.pressing()) // Up right
    {
      upSpeed += fwdAcceleration;
      rightSpeed += turnAcceleration;
      upSpeed = (upSpeed>100)?(100):(upSpeed);
      rightSpeed = (rightSpeed>50)?(50):(rightSpeed);

      TopLeftMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, upSpeed-rightSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, upSpeed-rightSpeed, velocityUnits::pct);

      downSpeed = 0;
      leftSpeed = 0;
    }
    else if(Controller1.ButtonDown.pressing() && Controller1.ButtonLeft.pressing()) // Down left
    {
      downSpeed += fwdAcceleration;
      leftSpeed += turnAcceleration;
      downSpeed = (downSpeed>100)?(100):(downSpeed);
      leftSpeed = (leftSpeed>50)?(50):(leftSpeed);

      TopLeftMove.spin(directionType::fwd, -downSpeed+leftSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, -downSpeed+leftSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);

      upSpeed = 0;
      rightSpeed = 0;
    }
    else if(Controller1.ButtonDown.pressing() && Controller1.ButtonRight.pressing()) // Down right
    {
      downSpeed += fwdAcceleration;
      rightSpeed += turnAcceleration;
      downSpeed = (downSpeed>100)?(100):(downSpeed);
      rightSpeed = (rightSpeed>50)?(50):(rightSpeed);

      TopLeftMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, -downSpeed+rightSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, -downSpeed+rightSpeed, velocityUnits::pct);

      upSpeed = 0;
      leftSpeed = 0;
    }
    else if(Controller1.ButtonUp.pressing()) // Up
    {
      upSpeed += fwdAcceleration;
      upSpeed = (upSpeed>100)?(100):(upSpeed);

      TopLeftMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, upSpeed, velocityUnits::pct);

      downSpeed = 0;
      leftSpeed = 0;
      rightSpeed = 0;      
    }
    else if(Controller1.ButtonDown.pressing()) // Down
    {
      downSpeed += fwdAcceleration;
      downSpeed = (downSpeed>100)?(100):(downSpeed);

      TopLeftMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, -downSpeed, velocityUnits::pct);

      upSpeed = 0;
      leftSpeed = 0;
      rightSpeed = 0;
    }
    else if(Controller1.ButtonLeft.pressing()) // Left
    {
      leftSpeed += fwdAcceleration;
      leftSpeed = (leftSpeed>100)?(100):(leftSpeed);

      TopLeftMove.spin(directionType::fwd, -leftSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, -leftSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, leftSpeed, velocityUnits::pct);

      upSpeed = 0;
      downSpeed = 0;
      rightSpeed = 0;
    }
    else if(Controller1.ButtonRight.pressing()) // Right
    {
      rightSpeed += fwdAcceleration;
      rightSpeed = (rightSpeed>100)?(100):(rightSpeed);

      TopLeftMove.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
      BottomLeftMove.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
      TopRightMove.spin(directionType::fwd, -rightSpeed, velocityUnits::pct);
      BottomRightMove.spin(directionType::fwd, -rightSpeed, velocityUnits::pct);

      upSpeed = 0;
      downSpeed = 0;
      leftSpeed = 0;
    }
    else
    {
      upSpeed = 0;
      downSpeed = 0;
      leftSpeed = 0;
      rightSpeed = 0;
    }


*/