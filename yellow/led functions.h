/*
 * led_functions.h
 *
 * Created: 19.08.2021 23:29:40
 *  Author: Mintytail
 */ 


#ifndef LED_FUNCTIONS_H_
#define LED_FUNCTIONS_H_

void led_init();
uint8_t led_color(const uint8_t unit, const uint8_t function, const scString *request, sString *response);
uint8_t led_control_value(const uint8_t unit, const uint8_t function, const scString *request, sString *response);
uint8_t led_state(const uint8_t unit, const uint8_t function, const scString *request, sString *response);

#endif /* LED_FUNCTIONS_H_ */