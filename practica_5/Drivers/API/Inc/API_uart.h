/*
 * API_uart.h
 *
 *  Created on: Apr 7, 2025
 *      Author: nicolas-porco
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include "stdbool.h"
#include "stdint.h"
#include "main.h"



typedef bool bool_t;

bool_t uartInit ( void );
void uartSendString ( uint8_t *pstring );
void uartSendStringSize ( uint8_t *pstring, uint16_t size );
void uartReceiveStringSize ( uint8_t *pstring, uint16_t size );




#endif /* API_INC_API_UART_H_ */
