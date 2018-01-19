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
		drvlb  = new WPI_VictorSPX(0);
		drvrb  = new WPI_VictorSPX(1);
		drvlf  = new WPI_VictorSPX(2);
		drvrf  = new WPI_VictorSPX(3);
		intakel = new WPI_VictorSPX(4);
		intaker = new WPI_VictorSPX(5);
		shooterl = new WPI_VictorSPX(6);
		shooterr = new WPI_VictorSPX(7);
		shooterangl = new WPI_VictorSPX(8);
		shooterangr = new WPI_VictorSPX(9);
		compressor = new Compressor();


	}
}

IO *IO::GetInstance() {
	return _instance;
}

IO::~IO() {
	// TODO Auto-generated destructor stub
}

