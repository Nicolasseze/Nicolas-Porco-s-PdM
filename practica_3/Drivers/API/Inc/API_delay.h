/*
 * API_delay.h
 *
 *  Created on: Mar 20, 2025
 *      Author: nicolas-porco
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"

typedef uint32_t tick_t;

typedef bool bool_t;

typedef struct{
   tick_t startTime; // Marca de tiempo inicial
   tick_t duration;  // Duracion del retardo en ms
   bool_t running;   // Indica si el retardo esta en ejecucion
} delay_t;


void delayInit( delay_t * delay, tick_t duration );

bool_t delayRead( delay_t * delay );

void delayWrite( delay_t * delay, tick_t duration );

#endif /* API_INC_API_DELAY_H_ */
