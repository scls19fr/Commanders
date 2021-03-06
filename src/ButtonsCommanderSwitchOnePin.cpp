/*************************************************************
project: <Commanders>
author: <Thierry PARIS>
description: <Switch button with one pin only with debounce.>
*************************************************************/

#include <Commanders.h>
#ifndef NO_BUTTONSCOMMANDER
#ifndef NO_BUTTONSCOMMANDERSWITCH

ButtonsCommanderSwitchOnePin::ButtonsCommanderSwitchOnePin() : ButtonsCommanderButton(UNDEFINED_ID)
{
	this->debounceDelay = 50;
	this->lastSelectedPin = DP_INVALID;
}

void ButtonsCommanderSwitchOnePin::begin(unsigned long inId, int inPin)
{
	this->Pin = Arduino_to_GPIO_pin(inPin);
	this->Id = inId;

	pinMode2f(this->Pin, INPUT_PULLUP);
}

void ButtonsCommanderSwitchOnePin::beforeFirstLoop()
{
	if (this->Pin != DP_INVALID)
	{
		// Initialize first switch state at start
		this->lastButtonState = digitalRead2f(this->Pin);

		Commanders::RaiseEvent(this->Id, COMMANDERS_EVENT_MOVE, this->lastButtonState == LOW ? COMMANDERS_MOVE_ON : COMMANDERS_MOVE_OFF);
		if (this->lastButtonState == LOW)
			this->lastSelectedPin = this->Pin;
	}
}

unsigned long ButtonsCommanderSwitchOnePin::loop()
{ 
	return ButtonsCommanderSwitch::loopOnePin(this->Pin, this->Id, this->lastSelectedPin == DP_INVALID ? UNDEFINED_ID : this->Id,
		&this->debounceDelay, &this->lastSelectedPin,
		&this->lastButtonState, &this->lastDebounceTime);
}

#ifdef COMMANDERS_PRINT_COMMANDERS
void ButtonsCommanderSwitchOnePin::printCommander()
{
	Serial.print(F("    SwitchOnePin        Pin: "));
	Serial.print(GPIO_to_Arduino_pin(this->Pin));
	Serial.print(F(" / Id: "));
	Serial.print(this->Id);
	Serial.println(F(""));
}
#endif
#endif
#endif
