/*
 * IntakeStateMachine.cpp
 *
 *  Created on: Jan 18, 2018
 *      Author: Kyle Li
 */

	switch(state){
case 0 :
if(user_intake_EN == 1){
	state = 1;
	arm_CL = 0;
	intake_En = 0;
	shooter_EN = 0;
}
if(user_intake_EN == 0){
	state = 0;
	arm_CL = 0;
	intake_EN = 0;
	shooter_EN = 0;
}
break;
case 1 :
if((cube_NB == 1)&&(user_intake_EN == 1)){
	state = 2;
	arm_CL = 1;
	intake_EN = 1;
	shooter_EN = 1;
}
if((cube_NB == 0)&&(user_intake_EN == 1)){
	state = 1;
	arm_CL = 0;
	intake_EN = 0;
}
break;
case 2 :
if(user_intake_EN == 0){
	arm_CL = 0;
	intake_EN = 0;
	shooter_EN = 0;
	state = 0;
}
if((user_intake_EN == 1)&&(cube_DE)){
	state = 2;
	arm_CL = 1;
	intake_EN = 1;
}
break;
	}
