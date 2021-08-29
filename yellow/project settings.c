
#include "project settings.h"
#include "KagamiCore/defines.h"
#include <stdint.h>

const static uint16_t settingsSize[esAmount] = {
    [esChannel] = 1,
    [esMode] = 1,
    [esAddress] = 8,
    [esKey] = 32,
    [esU0Description] = 24,
    [esU1Description] = 24,
    [esU2Description] = 24
};

const static uint16_t settingsAddress[esAmount] = {
    [esChannel] = 0,
    [esMode] = 1,
    [esAddress] = 2,
    [esKey] = 10,
    [esU0Description] = 42,
    [esU1Description] = 66,
    [esU2Description] = 90
};
