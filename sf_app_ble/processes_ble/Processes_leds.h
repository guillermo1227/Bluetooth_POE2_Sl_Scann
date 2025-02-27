/*
 * Processes_leds.h
 *
 *  Created on: 15 nov 2023
 *      Author: Usuario1
 */

#ifndef SF_APP_BLE_PROCESSES_BLE_PROCESSES_LEDS_H_
#define SF_APP_BLE_PROCESSES_BLE_PROCESSES_LEDS_H_
#include "wiced_bt_trace.h"
#include "wiced_rtos.h"
#include "wiced_hal_gpio.h"
#include <string.h>
#include "wiced_hal_puart.h"
#include "config_ports.h"

//#define LED_BLUE                          WICED_P08
//#define LED_GREEN                         WICED_P07
//#define LED_RED                          WICED_P04

/* Leds de tarjeta CYW920819EVB-02 */
//#define LED_BLUE                          WICED_P04
//#define LED_GREEN                         WICED_P05
//#define LED_RED                          WICED_P03

void process_led(char texto_global[]);
void wrong_configuration(char texto_global[]);
extern void start_Timer_led(uint8_t num);
extern void start_Timer_led2(void);
extern void start_Timer_led3(void);
extern void start_Timer_Error(uint8_t);

extern void stop_Timer_led(void);
extern void stop_Timer_led2(void);
extern void stop_Timer_led3(void);
extern void stop_Timer_Error(void);

wiced_bool_t   data_status;

#endif /* SF_APP_BLE_PROCESSES_BLE_PROCESSES_LEDS_H_ */
