/*
 * CubeManager.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_CUBESYSTEM_CUBEMANAGER_H_
#define SRC_CUBESYSTEM_CUBEMANAGER_H_ 1

namespace Cube
{
	class CubeManager
	{
	public:
		CubeManager();
		void Intake();
		void HighShot();
		void LowShot();
		void Delivery();
	private:
		bool _isidle;
	};
}




#endif /* SRC_CUBESYSTEM_CUBEMANAGER_H_ */
