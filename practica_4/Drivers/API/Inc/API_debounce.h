/*
 * API_debounce.h
 *
 *  Created on: Mar 29, 2025
 *      Author: nicolas-porco
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "API_delay.h"

/* Typedef -------------------------------------------------------------------*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

typedef struct{
	debounceState_t state;
	delay_t debounceDelay;
} btn_t;


/* Function prototypes -------------------------------------------------------*/
void debounceFSM_init( debounceState_t *, tick_t);



void debounceFSM_update( debounceState_t * , tick_t);

bool_t readKey();



#endif /* API_INC_API_DEBOUNCE_H_ */
