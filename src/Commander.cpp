/*************************************************************
project: <Commanders>
author: <Thierry PARIS>
description: <Base Commander>
*************************************************************/

#include "Commanders.h"

Commander *Commander::pFirstCommander = 0;

#ifdef COMMANDERS_DEBUG_MODE

#ifdef NO_CANCOMMANDER
	#pragma message ("Commanders : No CAN commander !")
#endif

#ifdef NO_DCCCOMMANDER
	#pragma message ("Commanders : No DCC commander !")
#endif

#ifdef NO_I2CCOMMANDER
	#pragma message ("Commanders : No I2C commander !")
#endif

#ifdef NO_BUTTONSCOMMANDER
	#pragma message ("Commanders : No Buttons commander !")
#endif

#ifdef NO_SERIALCOMMANDER
	#pragma message ("Commanders : No Serial commander !")
#endif

#define CHECK(val, text)	CheckIndex(val, F(text))
#else
#define CHECK(val, text)
#endif

void Commander::AddCommander(Commander *inCommander)
{
	if (Commander::pFirstCommander == NULL)
	{
		Commander::pFirstCommander = inCommander;
		return;
	}

	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr->pNextCommander != NULL)
		pCurr = pCurr->pNextCommander;

	pCurr->pNextCommander = inCommander;
}

void Commander::CommanderPriorityLoop()
{
	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr != NULL)
	{
		pCurr->PriorityLoop();
		pCurr = pCurr->pNextCommander;
	}
}

unsigned long Commander::loops()
{
	Commander *pCurr = Commander::pFirstCommander;

	while (pCurr != NULL)
	{
		unsigned long ret = pCurr->loop();
		if (ret != UNDEFINED_ID)
			return ret;
		pCurr = pCurr->pNextCommander;
	}

	return UNDEFINED_ID;
}

#ifdef COMMANDERS_DEBUG_MODE
#ifdef ARDUINO_ARCH_SAM
void Commander::CheckIndex(uint8_t inIndex, const char *inFunc)
{
}
#else
void Commander::CheckIndex(uint8_t inIndex, const __FlashStringHelper *inFunc)
{
}
#endif
#endif
