#include "AutoSelector.h"

AutoSelector::AutoSelector(int Channel) {

	autoDials = new AnalogInput(Channel);
}

robotAction AutoSelector::getAction() {

	double voltage = autoDials->GetVoltage();

	if (voltage >= rangeOneLow && voltage <= rangeOneHigh) {
		action = SCALE_SHOT;
	} else if (voltage >= rangeTwoLow && voltage <= rangeTwoHigh) {
		action = SWITCH_SHOT;
	} else if (voltage >= rangeThreeLow && voltage <= rangeThreeHigh) {
		action = DRIVE_FORWARD;
	} else action = NO_AUTO;

	return action;
}

robotStation AutoSelector::getFieldPosition()
{
	double voltage = autoDials->GetVoltage();

	if (voltage >= rangeOneLow && voltage <= rangeOneHigh) {
			fieldPosition = ONE;
		} else if (voltage >= rangeTwoLow && voltage <= rangeTwoHigh) {
			fieldPosition = TWO;
		} else if (voltage >= rangeThreeLow && voltage <= rangeThreeHigh) {
			fieldPosition = THREE;
		} else fieldPosition = ONE;
	return fieldPosition;
}

bool AutoSelector::getWaitSide() {
	double voltage = autoDials->GetVoltage();

	if (voltage >= rangeOneLow && voltage <= rangeOneHigh) {
		return true;
	} else return false;
}
