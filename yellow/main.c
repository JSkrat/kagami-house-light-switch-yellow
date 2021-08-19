/*
 * yellow.c
 *
 * Created: 19.08.2021 17:54:54
 * Author : Mintytail
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "../KagamiCore/RF model.h"
#include "../KagamiCore/RF functions.h"
#include "../KagamiCore/advertisement.h"
#include "RF custom functions.h"

int main(void)
{
    ACSR |= _BV(ACD);
	rf_init();
	functions_init(Units, UNITS_COUNT);
	custom_functions_init();
	advertisement_init();
	// need timers going in sleep mode
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
    while (1) {
		advertisement_process();
		sleep_mode();
    }
}

