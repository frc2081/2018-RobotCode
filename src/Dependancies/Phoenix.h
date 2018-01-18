#pragma once
#include "phoenix/CANifier.h"
#include "phoenix/ErrorCode.h"
#include "phoenix/paramEnum.h"
#include "phoenix/HsvToRgb.h"
#include "phoenix/LinearInterpolation.h"
#include "phoenix/Motion/MotionProfileStatus.h"
#include "phoenix/Motion/TrajectoryPoint.h"
#include "phoenix/MotorControl/CAN/TalonSRX.h"
#include "phoenix/MotorControl/CAN/VictorSPX.h"
#include "phoenix/MotorControl/CAN/WPI_TalonSRX.h"
#include "phoenix/MotorControl/CAN/WPI_VictorSPX.h"
#include "phoenix/MotorControl/Faults.h"
#include "phoenix/MotorControl/SensorCollection.h"
#include "phoenix/MotorControl/IMotorController.h"
#include "phoenix/MotorControl/IMotorControllerEnhanced.h"
#include "phoenix/Sensors/PigeonIMU.h"
#include "phoenix/Signals/MovingAverage.h"
#include "phoenix/Tasking/Schedulers/ConcurrentScheduler.h"
#include "phoenix/Tasking/ILoopable.h"
#include "phoenix/Tasking/IProcessable.h"
#include "phoenix/Tasking/ButtonMonitor.h"
#include "phoenix/Utilities.h"

using namespace ctre;
using namespace ctre::phoenix;
using namespace ctre::phoenix::motion;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::signals;
using namespace ctre::phoenix::tasking;
using namespace ctre::phoenix::tasking::schedulers;
