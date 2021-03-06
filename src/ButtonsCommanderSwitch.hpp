//-------------------------------------------------------------------
#ifndef __buttonsCommanderSwitch_H__
#define __buttonsCommanderSwitch_H__
//-------------------------------------------------------------------

#include <Commanders.h>
#ifndef NO_BUTTONSCOMMANDER
#ifndef NO_BUTTONSCOMMANDERSWITCH
#include "Chain.hpp"

//-------------------------------------------------------------------

/** Event for the universal switch button event list.*/
struct EventPin
{
	GPIO_pin_t Pin; /**<Arduino pin in DIO2 format connected to this switch position.*/
	unsigned long Id; /**<id.*/
	COMMANDERS_EVENT_TYPE Event; /**<Event type.*/
	int Data; /**<Associated data.*/
};

/** This class describes a switch with a variable number of pins/positions. 
The common cases are handled by ButtonsCommanderSwitchOnePin and ButtonsCommanderSwitchTwoPins,
but if you have a switch with any other number of positions, this class is for you !

Events thrown:

        reason            |           id       |         type          | data
--------------------------|--------------------|-----------------------|--------------------
pin state to HIGH         | button id pin      | COMMANDERS_EVENT_MOVE | COMMANDERS_MOVE_ON
previous pin state to LOW | button id prev pin | COMMANDERS_EVENT_MOVE | COMMANDERS_MOVE_OFF
*/
class ButtonsCommanderSwitch : public ButtonsCommanderButton
{
 private:
	unsigned long debounceDelay;    // the debounce time; increase if the output flickers
	CMDRSCHAINEDLIST<EventPin> EventPins;
	GPIO_pin_t lastSelectedPin;

	int lastButtonState;   // the previous reading from the current input pin
	unsigned long lastDebounceTime;  // the last time the current output pin was toggled

public:
	/** Default constructor.*/
	ButtonsCommanderSwitch();
	
	/** Initialize the instance.*/
	void begin();
	/** Each position of the switch can be defined with an Arduino pin, and an event definition...
	In this case of switch, there is an event when one pin is activated, but there is no OFF event for the inactivated pin.
	@param inId			id of the position.
	@param inPin		Arduino pin connected to the button.
	@param inEvent		Event type used when the pin is activated. Default COMMANDERS_EVENT_MOVEPOSITIONID.
	@param inData		Associated data when the pin is activated. Default 0.
	*/
	EventPin *AddEvent(unsigned long inId, int inPin, COMMANDERS_EVENT_TYPE inEvent = COMMANDERS_EVENT_MOVEPOSITIONID, int inData = 0);
	/** This function will be called after sketch Setup(), but before the first call to loop().
	It will be called only one time.*/
	void beforeFirstLoop();
	/** Main loop function. */
	unsigned long loop();
	/** Gets the right id according to the activated pin.*/
	unsigned long GetId(GPIO_pin_t inPin) const;

	/** Check if a pin has changed its state, and send an event if necessary.
	@remark This is an internal function.
	*/
	static unsigned long loopOnePin(GPIO_pin_t inPin, unsigned long inId, unsigned long inPreviousId,
		unsigned long *apDebounceDelay, GPIO_pin_t *apLastSelectedPin,
		int *apLastButtonState, unsigned long *apLastDebounceTime, bool inSendEvent = true);

#ifdef COMMANDERS_PRINT_COMMANDERS
	/** Print this Commander on the console.
	@remark Only available if COMMANDERS_PRINT_COMMANDERS is defined.
	*/
	void printCommander();
#endif
};

//-------------------------------------------------------------------
#endif
#endif
#endif
