/*
 * ui.c
 *
 * Created: 29.08.2021 18:25:20
 *  Author: Mintytail
 */ 
#include "ui.h"
#include "KagamiCore/defines.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>

#define LED_HEARTBEAT UI_LED_YELLOW
#define LED_ERROR UI_LED_RED
#define LED_RF UI_LED_RED

static uint8_t ui_phase;
#define UI_PERIOD 50

void ui_init() {
	UI_LEDS_DDR |= _BV(UI_LED_RED) | _BV(UI_LED_YELLOW);
	UI_LEDS_PORT &= ~_BV(UI_LED_RED) & ~_BV(UI_LED_YELLOW);
	ui_phase = 0;
}

void ui_error(uint8_t code) {
	if (0x10 > code) {
		while (1) {
			uint8_t c = code;
			for (int i = 0; i < 4; i++) {
				UI_LEDS_PORT |= _BV(LED_ERROR);
				if (c & 1) _delay_ms(300);
				else _delay_ms(100);
				UI_LEDS_PORT &= ~_BV(LED_ERROR);
				c >>= 1;
				_delay_ms(200);
			}
			_delay_ms(300);
		}
	}
}

void ui_rf_func(bool active) {
	if (active) UI_LEDS_PORT |= _BV(LED_RF);
	else UI_LEDS_PORT &= ~_BV(LED_RF);
}

void ui_heartbeat() {
	//ui_phase += 1;
	//if (UI_PERIOD <= ui_phase) {
	//	ui_phase = 0;
		UI_LEDS_PORT ^= _BV(LED_HEARTBEAT);
	//}
}
