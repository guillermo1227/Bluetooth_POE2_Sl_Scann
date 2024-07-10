/*
 * observ.h
 *
 *  Created on: 20 jun 2023
 *      Author: temporal
 */

#ifndef LIBRERIAS_OBSERV_H_
#define LIBRERIAS_OBSERV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wiced_bt_trace.h"
#include "wiced_bt_ble.h"
#include "wiced_result.h"
#include "wiced_hal_puart.h"
#include "wiced_hal_gpio.h"


void start_call_back_scanner(int savetime);
void stop_scanner(void);
void f_timer_Observ(uint32_t data);

extern void timer_init_scann(char data2[],char data3[]);
extern void init_timer(void);
extern void start_BTimers(void);

void start_observe(void);
char scanner_name[5];
uint8_t data_mac[6];

#endif /* LIBRERIAS_OBSERV_H_ */
