/*
 * RF_custom_functions.c
 *
 * Created: 19.08.2021 18:07:47
 *  Author: Mintytail
 */ 

#include "RF custom functions.h"
#include "KagamiCore/RF functions.h"
#include "KagamiCore/RF protocol.h"
#include "project settings.h"
#include "timer.h"
#include "led functions.h"
#include "buzzer functions.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void custom_functions_init() {
	led_init();
	timer_init();
	buzzer_init();
}

uint8_t readPin(const uint8_t unit, const uint8_t function, const scString *request, sString *response) {
	return ercOk;
}

#define U1_F_COUNT 5
// RGB LED
const PROGMEM tRFCodeFunctionItem U1_functions[U1_F_COUNT] = {
	{ .functionCode = 0x20, .type.fields.input = edtByteArray, .type.fields.output = edtNone, .function = &led_color },
	{ .functionCode = 0x21, .type.fields.input = edtNone, .type.fields.output = edtByteArray, .function = &led_color },
	{ .functionCode = 0x12, .type.fields.input = edtBool, .type.fields.output = edtNone, .function = &led_control_value },
	{ .functionCode = 0x13, .type.fields.input = edtNone, .type.fields.output = edtBool, .function = &led_control_value },
	{ .functionCode = 0x11, .type.fields.input = edtNone, .type.fields.output = edtBool, .function = &led_state },
};

#define U2_F_COUNT 1
const PROGMEM tRFCodeFunctionItem U2_functions[U2_F_COUNT] = {
	{ .functionCode = 0x10, .type.fields.input = edtNone, .type.fields.output = edtBool,
	.function = &readPin }
};

const PROGMEM tUnit Units[UNITS_COUNT] = {
	{
		.length = U1_F_COUNT, .functions = U1_functions, .description = esU1Description
	},
	{
		.length = U2_F_COUNT, .functions = U2_functions, .description = esU2Description
	}
};
