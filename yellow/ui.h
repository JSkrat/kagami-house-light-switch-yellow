/*
 * ui.h
 *
 * Created: 29.08.2021 18:25:27
 *  Author: Mintytail
 */ 


#ifndef UI_H_
#define UI_H_
#include <stdint.h>
#include <stdbool.h>

void ui_init();
void ui_error(uint8_t code);
void ui_rf_func(bool active);
void ui_heartbeat();

#endif /* UI_H_ */