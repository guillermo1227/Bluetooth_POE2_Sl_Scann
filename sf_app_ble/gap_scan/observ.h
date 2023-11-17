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

#define reception_led WICED_P26

//extern char nombre[12], UID[10],flag_name,flag_uid,flag_url;
//extern char URL[12];

void choos_what_scaner(char texto[], char data2[],char dara3[]);
void start_call_back_scanner(int savetime);
void stop_scanner(void);
extern void timer_init_scann(char data2[],char data3[]);
char scanner_name[5];


#endif /* LIBRERIAS_OBSERV_H_ */
