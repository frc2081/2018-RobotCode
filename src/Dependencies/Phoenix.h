#pragma once
#include <Dependencies/ctre/phoenix/CANifier.h>
#include <Dependencies/ctre/phoenix/ErrorCode.h>
#include <Dependencies/ctre/phoenix/HsvToRgb.h>
#include <Dependencies/ctre/phoenix/LinearInterpolation.h>
#include <Dependencies/ctre/phoenix/Motion/MotionProfileStatus.h>
#include <Dependencies/ctre/phoenix/Motion/TrajectoryPoint.h>
#include <Dependencies/ctre/phoenix/MotorControl/CAN/TalonSRX.h>
#include <Dependencies/ctre/phoenix/MotorControl/CAN/VictorSPX.h>
#include <Dependencies/ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h>
#include <Dependencies/ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <Dependencies/ctre/phoenix/MotorControl/Faults.h>
#include <Dependencies/ctre/phoenix/MotorControl/IMotorController.h>
#include <Dependencies/ctre/phoenix/MotorControl/IMotorControllerEnhanced.h>
#include <Dependencies/ctre/phoenix/MotorControl/SensorCollection.h>
#include <Dependencies/ctre/phoenix/paramEnum.h>
#include <Dependencies/ctre/phoenix/Sensors/PigeonIMU.h>
#include <Dependencies/ctre/phoenix/Signals/MovingAverage.h>
#include <Dependencies/ctre/phoenix/Tasking/ButtonMonitor.h>
#include <Dependencies/ctre/phoenix/Tasking/ILoopable.h>
#include <Dependencies/ctre/phoenix/Tasking/IProcessable.h>
#include <Dependencies/ctre/phoenix/Tasking/Schedulers/ConcurrentScheduler.h>
#include <Dependencies/ctre/phoenix/Utilities.h>

using namespace ctre;
using namespace ctre::phoenix;
using namespace ctre::phoenix::motion;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::signals;
using namespace ctre::phoenix::tasking;
using namespace ctre::phoenix::tasking::schedulers;
