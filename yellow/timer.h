/*
 * timer.h
 *
 * Created: 20.08.2021 17:47:03
 *  Author: Mintytail
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

void timer_init();
void set_timeout(uint16_t timeout, void (*callback)());
#define LED_COUNT 3
#define LED_PERIOD 16
extern uint8_t timer_leds[LED_COUNT];


#endif /* TIMER_H_ */