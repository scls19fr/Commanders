/*************************************************************
project: <Commanders>
author: <Thierry PARIS>
description: <Commanders DCC sample by macros>
*************************************************************/

#include "Commanders.h"

/* INTERRUPT values as macro argument :
Board			int.0	int.1	int.2	int.3	int.4	int.5
Uno, Ethernet	2		3
Mega2560		2		3		21		20		19		18
Leonardo		3		2		0		1		7
*/
#define kDCC_INTERRUPT	2

void ReceiveEvent(unsigned long inId, COMMANDERS_EVENT_TYPE inEvent, int inData)
{
	DccCommander.printEvent(inId, inEvent, inData);
}

//////////////////////////////////
//
// Setup
//
void setup()
{
	Commanders::StartSetup(ReceiveEvent, LED_BUILTIN);

	DccCommander.begin(0x0, 0x0, kDCC_INTERRUPT);

	Commanders::EndSetup();
}

void loop()
{
	Commanders::loop();
}