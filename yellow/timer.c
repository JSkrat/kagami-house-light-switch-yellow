/*
 * timer.c
 *
 * Created: 20.08.2021 17:46:56
 *  Author: Mintytail
 */ 
#include "timer.h"
#include "project defines.h"
#include <avr/interrupt.h>
#include <stdint.h>

typedef struct {
	uint16_t timeout; // timer ticks left to call back
	void (*callback)();
} tTimeout;

#define TIMERS_COUNT 2
static tTimeout timers[TIMERS_COUNT];
uint8_t timer_leds[LED_COUNT];
const static uint8_t led_pins[LED_COUNT] = {LED_RED, LED_GREEN, LED_BLUE};
static uint8_t led_phase;

void dummy() {}

void timer_init() {
	// timer 1 initialization
	// CTC, count from 0 to OCR1A
	TCCR1A = (0 << WGM11) | (0 << WGM10);
	// clk/8
	TCCR1B = (1 << WGM12) | (0 << WGM13) | (0 << CS12) | (1 << CS11) | (0 << CS10);
	OCR1A = 0.0001 * F_CPU / 8; // interrupt every 100 us
	TIMSK1 = (1 << OCIE1A);
	for (int i = 0; i < LED_COUNT; i++) {
		timer_leds[i] = 0;
	}
	led_phase = 0;
	for (int i = 0; i < TIMERS_COUNT; i++) {
		timers[i].timeout = 0;
		timers[i].callback = &dummy;
	}
}

void set_timeout(uint16_t timeout, void (*callback)()) {
	for (int i = 0; i < TIMERS_COUNT; i++) {
		if (0 == timers[i].callback) {
			timers[i].callback = callback;
			timers[i].timeout = timeout;
			break;
		}
	}
}

ISR(TIMER1_COMPA_vect) {
	// pwm first
	// note: outputs are inverted, 0 for on
	led_phase++;
	if (LED_PERIOD <= led_phase) {
		led_phase = 0;
		// turn on non-zero leds
		for (int i = 0; i < LED_COUNT; i++) {
			if (0 < timer_leds[i]) LEDS_PORT &= ~_BV(led_pins[i]);
		}
	} else {
		for (int i = 0; i < LED_COUNT; i++) {
			if (timer_leds[i] < led_phase) LEDS_PORT |= _BV(led_pins[i]);
		}
	}
	// and now other callbacks
	for (int i = 0; i < TIMERS_COUNT; i++) {
		if (0 < timers[i].timeout && 0 >= --timers[i].timeout) {
			timers[i].callback();
			timers[i].callback = 0;
		}
	}
}
