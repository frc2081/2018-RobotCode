/*
 * CubeManagerIO.h
 *
 *  Created on: Jan 26, 2018
 *      Author: blzzrd
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGERIO_H_
#define SRC_CUBESYSTEM_CUBEMANAGERIO_H_

class CubeManagerIO {
	public:
		CubeManagerIO();

		enum class PokerPosition : bool {
			RETRACTED = false,
			EXTENDED = true
		};

		enum class ShooterArmPosition : bool {
			CLOSED = false,
			OPEN = true
		};


		//Variables to store the set point for each output in the cube system
		ShooterArmPosition shooterArmPos;
		PokerPosition pokerpos;
		double intakepowercmd;
		double shooterpowercmd;
		double shooteranglecmd;

		//Value to indicate to when the currently running subsystem has completed all tasks and is ready to hand control back to the cube manager
		bool isdone;
	};

#endif /* SRC_CUBESYSTEM_CUBEMANAGERIO_H_ */
