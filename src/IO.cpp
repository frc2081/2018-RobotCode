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
}
IO::~IO() {
	// TODO Auto-generated destructor stub
}

