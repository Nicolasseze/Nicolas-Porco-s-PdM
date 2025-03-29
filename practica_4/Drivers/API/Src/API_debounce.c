/*
 * debounce.c
 *
 *  Created on: Mar 29, 2025
 *      Author: nicolas-porco
 */

#include "API_debounce.h"
#define BTN_CANT	1

static debounceState_t state[BTN_CANT] = {};
static bool_t btnFalling = false;
static delay_t debounceDelay;

void debounceFSM_init( debounceState_t *pState, delay_t *pDelay, tick_t timeDelay){

	assert_param( state );

	state = BUTTON_UP;
	btnFalling = false;
	delayInit( pDelay, timeDelay);

}


void debounceFSM_update(debounceState_t *state, delay_t *pDelay){

	switch( *state ){

	case BUTTON_UP:
		if( HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET )
			*state = BUTTON_FALLING;
		break;

	case BUTTON_FALLING:
		if( delayRead( pDelay ) ){
			if( HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET ){
				*state = BUTTON_DOWN;
				btnFalling = true;
			}
			else {
				*state = BUTTON_UP;
			}
		}
		break;

	case BUTTON_DOWN:
		if( HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET )
			*state = BUTTON_RAISING;
		break;

	case BUTTON_RAISING:
		if( delayRead( pDelay ) ){
			if( HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET ){
				*state = BUTTON_UP;
			}
			else {
				*state = BUTTON_DOWN;
			}
		}
		break;

	default:
		debounceFSM_init(state, pDelay);

	}
}

bool_t readKey( void ){

	if( btnFalling == true){
		btnFalling = false;
		return true;
	}
	else
		btnFalling = false;

	return false;

}
