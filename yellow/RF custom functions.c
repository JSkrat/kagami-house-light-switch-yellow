/*
 * RF_custom_functions.c
 *
 * Created: 19.08.2021 18:07:47
 *  Author: Mintytail
 */ 

#include "RF custom functions.h"
#include "../KagamiCore/RF functions.h"
#include "../KagamiCore/RF protocol.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void custom_functions_init() {
	
}

uint8_t readPin(const uint8_t unit, const uint8_t function, const scString *request, sString *response) {
	return ercOk;
}

const PROGMEM tRFCodeFunctionItem U1_functions[U1_F_COUNT] = {
	{ .functionCode = 0x10, .type.fields.input = edtNone, .type.fields.output = edtBool,
	.function = &readPin }
};

const PROGMEM tUnit Units[UNITS_COUNT] = {
	{
		.length = U1_F_COUNT, .functions = U1_functions, .description = 0
	}
};
