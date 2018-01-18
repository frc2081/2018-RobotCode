/*
 * IO.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: 1800855
 */

#include <IO.h>

IO::IO() {
	// TODO Auto-generated constructor stub

}
void IO::Initialize() {
	if (_instance == NULL) {
		_instance = new IO();
		/* put all other instanciations here */
	}
}

IO *IO::GetInstance() {
	return _instance;
}

Encoder IO::GetEncoder(double index) {
	return _encoders[index];
}

Compressor IO::GetCompressor() {
	return _compressor;
}

Solenoid IO::GetSolenoid(double index) {
	return _solenoids[index];
}

WPI_TalonSRX IO::GetTalon(double index) {
	return _talons[index];
}

WPI_VictorSPX IO::GetVictor(double index) {
	return _victors[index];
}
IO::~IO() {
	// TODO Auto-generated destructor stub
}

