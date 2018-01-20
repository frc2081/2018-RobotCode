/*
 * IntakeStateMachine.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: Kyle Li
 */


state = 0;
switch(state) {
case 0:
	if(arm sensor == 1){
		state = 1
	}
	else {
		state = 0
	}
case 1:
	close hte arm;
	turn the motor inward;
	if(shooter sensor == 1){
		state = 2
	}
	else {
		state = 1
	}
case 2:
	stop motor;
	apen arms;
	state = 0;
}

