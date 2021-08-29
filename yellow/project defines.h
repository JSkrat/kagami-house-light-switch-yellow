#define F_CPU 8000000

// RF mode
#define BUILD_TYPE BT_SLAVE
// advertisement
#define USE_ADVERTISEMENT
#define ADV_BUTTON_PORT PIND
#define ADV_BUTTON_DDR DDRD
#define ADV_BUTTON_PIN PIND0
#define ADV_LED_PORT PORTC
#define ADV_LED_DDR DDRC
#define ADV_LED_PIN PORTC2
// transciever
#define portTransiever PORTB
#define PORT_IN_TRANSIEVER PINB
#define poTransiever_IRQ PORTB0
// we have buzzer on OC2B
#define RF_TIMER 2
// LEDS
#define LEDS_PORT PORTD
#define LEDS_DDR DDRD
#define LED_RED PORTD6
#define LED_GREEN PORTD7
#define LED_BLUE PORTD5
// ui leds
#define UI_LEDS_PORT PORTC
#define UI_LEDS_DDR DDRC
#define UI_LED_RED PORTC0
#define UI_LED_YELLOW PORTC1
// show error codes
#ifndef __ASSEMBLY__
#include <stdint.h>
void ui_error(uint8_t code);
#undef RF_ERROR
#define RF_ERROR(code) ui_error(code)

#include <stdbool.h>
void ui_rf_func(bool active);
#undef RF_FUNCTION
#define RF_FUNCTION(enter, unit, function) ui_rf_func(enter)
#endif
