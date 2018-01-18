/*
 * StateInterface.h
 *
 *  Created on: Jan 17, 2018
 *      Author: Matthew
 */

#ifndef SRC_CUBESYSTEM_STATE_H_
#define SRC_CUBESYSTEM_STATE_H_

namespace Cube {

	class State {
	public:
		State();
		~State();
		void Abort();
		bool Initialize();
	};

} /* namespace Cube */

#endif /* SRC_CUBESYSTEM_STATE_H_ */
