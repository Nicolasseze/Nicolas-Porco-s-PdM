/*
 * API_delay.c
 *
 *  Created on: Mar 20, 2025
 *      Author: nicolas-porco
 */

/**
 * @brief Inicializa la estructura de delay con una duración dada.
 * @param delay Puntero a la estructura delay_t.
 * @param duration Duración del retardo en milisegundos (minimo 1ms).
 */
#include "API_delay.h"

void delayInit( delay_t * delay, tick_t duration ){

	if( delay != NULL){
		delay->running = false;
		if( delay->duration > 0)
			delay->duration = duration;
		else
			delay->duration = 1;
	}
}

/**
 * @brief Verifica si el retardo ha finalizado.
 * @param delay Puntero a la estructura delay_t.
 * @return true si el retardo ha finalizado, false en caso contrario.
 */
bool_t delayRead( delay_t * delay ){

	if( delay == NULL)
		return false;

	if( !delay->running ){
		// Si no esta en ejecucion, inicia el retardo
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	}
	else {
		//Si esta en ejecucion, verifica que haya pasado el tiempo definido
		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
			delay->running = false; // Reinicia el flag
			return true;
		}
	}

	return false;

}

/**
 * @brief Modifica la duración de un delay ya inicializado.
 * @param delay Puntero a la estructura delay_t.
 * @param duration Nueva duración del retardo en milisegundos. Minimo 1 ms
 */
void delayWrite( delay_t * delay, tick_t duration ){

    if (delay != NULL && duration > 0) {
        delay->duration = duration;
    }

}

