#include "Robot.h"

using namespace frc;
using namespace wml;

using hand = frc::XboxController::JoystickHand;

double currentTime;
double lastTimeStamp;
double dt; //stands for delta time 

//add other variables here
double rightSpeed;
double leftSpeed;
double constexpr deadzone = 0.1;

// Robot Logic
void Robot::RobotInit() {
	//init controllers 
	xbox = new frc::XboxController(0);

	//Motor examples 
	_victorMotorL = new wml::VictorSpx(8);
	_talonMotorL = new wml::TalonSrx(1);

	_talonMotorR = new wml::TalonSrx(2);
	_victorMotorR = new wml::VicorSpx(9);

	_victorMotorL->SetInverted(false);
	_talonMotorR->SetInverted(false);

	_talonMotorL->SetInverted(false);
	_victorMotorR->SetInverted(false);
}

void Robot::RobotPeriodic() {}

// Dissabled Robot Logic
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

// Auto Robot Logic
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

// Manual Robot Logic
void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
	currentTime = Timer::GetFPGATimestamp();
	dt = currentTime - lastTimeStamp;

	//motor examples


	leftSpeed = xbox->GetY(hand::kLeftHand);
	if (leftSpeed >= deadzone) { //acounts for the deadzone
		_talonMotorL->Set(0);
		_victorMotorL->Set(0)
	} else {
		_talonMotorL = 0;
		_victorMotor = 0;
	}
	
	rightSpeed = xbox->GetY(hand::kRightHand); //Sets the speed of the right db motor to the xbox left stick
    _talonMotorR->Set(rightSpeed);
    _victorMotorR->Set(rightSpeed);


	// ^ the equivilant using a conditional statement 
	//talonSpeed = xbox->GetTriggerAxis(hand::kRightHand) > deadzone ? xbox->GetTriggerAxis(hand::kRightHand) : 0; _talonMotor->Set(talonSpeed);

	if(xbox->GetXButton()) {
		_solenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
	} else {
		_solenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
	}

	_compressor.Update(dt);
	_solenoid.Update(dt);

	if (_solenoid.IsDone()) _solenoid.Stop();
	lastTimeStamp = currentTime;
}

// Test Logic
void Robot::TestInit() {}
void Robot::TestPeriodic() {}
