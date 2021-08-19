/*
 * RF_custom_functions.h
 *
 * Created: 19.08.2021 18:08:16
 *  Author: Mintytail
 */ 


#ifndef RF_CUSTOM_FUNCTIONS_H_
#define RF_CUSTOM_FUNCTIONS_H_

#include "../KagamiCore/RF functions.h"

#define UNITS_COUNT 1
extern const tUnit Units[UNITS_COUNT];

#define U1_F_COUNT 1
extern const tRFCodeFunctionItem U1_functions[U1_F_COUNT];

void custom_functions_init();

#endif /* RF CUSTOM FUNCTIONS_H_ */