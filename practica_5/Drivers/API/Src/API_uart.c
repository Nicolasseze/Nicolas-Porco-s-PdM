/*
 * API_uart.c
 *
 *  Created on: Apr 7, 2025
 *      Author: nicolas-porco
 */

#include "API_uart.h"
#include "string.h"

// UART handle
static UART_HandleTypeDef huart2;

// Límites razonables
#define UART_MAX_SIZE 256


bool_t uartInit ( void ){

	 // Configuración UART2 (PA2: TX, PA3: RX en Nucleo-F446RE)
	    huart2.Instance = USART2;
	    huart2.Init.BaudRate = 9600;
	    huart2.Init.WordLength = UART_WORDLENGTH_8B;
	    huart2.Init.StopBits = UART_STOPBITS_1;
	    huart2.Init.Parity = UART_PARITY_NONE;
	    huart2.Init.Mode = UART_MODE_TX_RX;
	    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	    if (HAL_UART_Init(&huart2) != HAL_OK)
	        return false;

	    // Envío confirmación por terminal
	    char *msg = "UART2 inicializada: 9600 8N1\r\n";
	    if (HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY) != HAL_OK)
	        return false;

	    return true;

}

void uartSendString(uint8_t *pstring)
{
    assert_param( pstring );

    uint16_t len = strlen((char *)pstring);
    if (len > UART_MAX_SIZE)
        return;

    if( HAL_UART_Transmit(&huart2, pstring, len, HAL_MAX_DELAY) != HAL_OK )
    	return;
}

void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
	assert_param( pstring );
	if( size > 0 && size < UART_MAX_SIZE )
		if( HAL_UART_Transmit(&huart2, pstring, size, HAL_MAX_DELAY) != HAL_OK )
			return;

}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size)
{
	assert_param( pstring );

	if( size > 0 && size < UART_MAX_SIZE )
		if( HAL_UART_Receive(&huart2, pstring, size, HAL_MAX_DELAY) != HAL_OK )
			return;
}


