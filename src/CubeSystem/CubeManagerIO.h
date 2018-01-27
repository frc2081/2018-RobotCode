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

		ShooterArmPosition shooterArmPos;
		PokerPosition pokerpos;

		double intakepowercmd;
		double shooterpowercmd;
		double shooteranglecmd;
	};

#endif /* SRC_CUBESYSTEM_CUBEMANAGERIO_H_ */
