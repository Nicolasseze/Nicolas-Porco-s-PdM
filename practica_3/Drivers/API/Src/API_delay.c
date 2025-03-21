/*
 * API_delay.c
 *
 *  Created on: Mar 20, 2025
 *      Author: Nicolás Porco
 *
 *  @brief Implementación de funciones para manejo de retardos no bloqueantes.
 *  @details Este archivo contiene la lógica para inicializar, leer, actualizar
 *  y verificar el estado de un retardo utilizando el contador de sistema (HAL_GetTick()).
 */

#include "API_delay.h"

void delayInit(delay_t * delay, tick_t duration) {
	assert_param(delay);

	delay->running = false;

	// Asegura que la duración sea al menos 1ms
	if (duration > 0)
		delay->duration = duration;
	else
		delay->duration = 1;
}

bool_t delayRead(delay_t * delay) {
	assert_param(delay);

	if (!delay->running) {
		// Comienza el retardo si no estaba corriendo
		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;
	} else {
		// Verifica si transcurrió el tiempo
		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
			delay->running = false;
			return true;
		}
	}

	return false;
}

void delayWrite(delay_t * delay, tick_t duration) {
	assert_param(delay);

	// Solo actualiza si la nueva duración es válida
	if (duration > 0) {
		delay->duration = duration;
	}
}

bool_t delayIsRunning(delay_t * delay) {
	assert_param(delay);

	// Devuelve el estado actual del retardo
	return delay->running;
}

