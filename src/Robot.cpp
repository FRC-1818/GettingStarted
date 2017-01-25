#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotDrive.h>
#include <Timer.h>
#include "WPILib.h"
#include <XboxController.h>


class Robot: public frc::IterativeRobot {
public:
	Robot() {
		myRobot.SetExpiration(0.1);
		timer.Start();
		myRobot.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		// You may need to change or remove this to match your robot
		myRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	}

private:
	frc::RobotDrive myRobot { 1,2,3,4 };  // Robot drive system
	frc::XboxController leftstick { 0 };       // Only joystick
	frc::LiveWindow* lw = frc::LiveWindow::GetInstance();
	frc::Timer timer;


	void AutonomousInit() override {
		timer.Reset();
		timer.Start();
	}

	void AutonomousPeriodic() override {
		// Drive for 2 seconds
				if (timer.Get() < 2.5) {
					myRobot.MecanumDrive_Cartesian(0.0, -0.5, 0.0);  // Drive forwards half speed
				} else {
					if ((timer.Get() > 2.5) && (timer.Get() < 2.93)) {
						myRobot.MecanumDrive_Cartesian(0.0, 0.0, 1.0 ); // Drive full speed leftturn
					}
				else {
					if (timer.Get() > 2.93){
						myRobot.MecanumDrive_Cartesian(0.5, 0.0, 0.0);  // Stop robot
				}
			}
		}
	}

	void TeleopInit() override {

	}

	void TeleopPeriodic() override {
		// Drive with arcade style (use right stick)
		myRobot.MecanumDrive_Cartesian(leftstick.GetRawAxis(1),
				                       leftstick.GetRawAxis(0),
				                       leftstick.GetRawAxis(4));

	}

	void TestPeriodic() override {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
