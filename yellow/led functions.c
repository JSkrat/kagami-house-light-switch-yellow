/*
 * led_functions.c
 *
 * Created: 19.08.2021 23:29:19
 *  Author: Mintytail
 */ 
#include "KagamiCore/RF functions.h"
#include "KagamiCore/RF protocol.h"
#include "timer.h"
#include "project defines.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

typedef enum {
	essOn,
	essOff,
	essRising,
	essFalling,
} eSmoothSwitchState;

static uint8_t color[LED_COUNT] = {0, 0, 0};
static uint16_t smooth_switch_time = 0, smooth_switch_phase = 0;
#define SMOOTH_SWITCH_PHASE_MAX 65536
static eSmoothSwitchState essState = essOff;
static bool state = false, control = false;
static uint16_t manual_time = 0, manual_timeout = 0;
static uint8_t sensor_unit = 0; 

void led_init() {
	// PD5 blue
	// PD6 red
	// PD7 green
	DDRD |= _BV(LED_RED) | _BV(LED_GREEN) | _BV(LED_BLUE);
	// TODO load variables from eeprom here
}

void update_leds() {
	for (int i = 0; i < LED_COUNT; i++) {
		switch (essState) {
			case essOff: {
				timer_leds[i] = 0;
				break;
			}
			case essOn: {
				timer_leds[i] = color[i];
				break;
			}
			case essFalling:
			case essRising: {
				// color is [0; LED_PERIOD)
				// smooth_switch_phase is [0; SMOOTH_SWITCH_PHASE_MAX)
				timer_leds[i] = color[i] * smooth_switch_phase / SMOOTH_SWITCH_PHASE_MAX;
				break;
			}
		}
	}
}

uint8_t led_color(const uint8_t unit, const uint8_t function, const scString *request, sString *response) {
	// either input or output array of 3 bytes: RGB, values 0-255, autoconvert to available resolution
	if (0 < request->length) {
		if (LED_COUNT != request->length) return ercBadRequestData;
		for (int i = 0; i < LED_COUNT; i++) {
			color[i] = request->data[i] / (256/LED_PERIOD);
		}
		update_leds();
		return ercOk;
	} else {
		response->length = LED_COUNT;
		for (int i = 0; i < LED_COUNT; i++) {
			response->data[i] = color[i] * (256/LED_PERIOD);
		}
		return ercOk;
	}
}

uint8_t led_control_value(const uint8_t unit, const uint8_t function, const scString *request, sString *response) {
	// either input or output is bool
	if (0 < request->length) {
		if (1 != request->length) return ercBadRequestData;
		if (request->data[0]) essState = essOn;
		else essState = essOff;
		return ercOk;
	} else {
		response->length = 1;
		if (essOn == essState || essRising == essState) response->data[0] = 1;
		else response->data[0] = 0;
		return ercOk;
	}
}

uint8_t led_state(const uint8_t unit, const uint8_t function, const scString *request, sString *response) {
	response->length = 1;
	if (essOn == essState || essRising == essState) response->data[0] = 1;
	else response->data[0] = 0;
	return ercOk;
}
