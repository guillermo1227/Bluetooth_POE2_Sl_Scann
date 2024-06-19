/*
 * Process_RSSI.h
 *
 *  Created on: 28 sep 2023
 *      Author: Usuario1
 */

#ifndef SF_APP_BLE_PROCESSES_BLE_PROCESS_RSSI_H_
#define SF_APP_BLE_PROCESSES_BLE_PROCESS_RSSI_H_

#include "wiced_bt_ble.h"   //libreria para el scanner
#include "wiced_bt_trace.h"
#include <wiced_rtos.h>
#include "wiced_hal_gpio.h"
#define LED_GPIO_01                              WICED_P01
#define LED_GPIO_02                              WICED_P02

//#define LED_GPIO_04                              WICED_P04

//void                            f_count_RSSI(uint32_t data );
extern void 					stop_count_RSSI(void);
void Value_processing_RSSI(wiced_bt_ble_scan_results_t *p_scan_result);

uint8_t timer_flag = 0;
uint8_t timer_confirm =0;
uint8_t count_values=0;
uint16_t valores_dentro = 0;

typedef struct
{
	int16_t global_rssi;
	BD_ADDR  bdaddr;    // Adress of the bluetoot
	uint8_t flags_of_macs; //Usada para saber si las macs estan puestas y en que posicion
	//uint32_t valores_dentro; //Con esta variable aumentare el numero de los RSSI vistos y de quienes son
	uint16_t array_valores[20]; //Donde guardo los 10 valores del RSI
	uint8_t valor_anterior;
	uint8_t valor_actual;
	union bits
	{
		struct
		{
			//Asignacion  de 1 bit a "a", es el tamaño total de la union es de 8 bits
			unsigned a : 1;
		}bitFlag;
	}headerFlag;
}aux_prom;

int count_to_tree=0;

#endif /* SF_APP_BLE_PROCESSES_BLE_PROCESS_RSSI_H_ */
