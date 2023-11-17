/*
 * config_timers.h
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_
#define SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_

#define reception_led WICED_P26


/* Beacon timer */
static wiced_timer_t beacon_timer;
static wiced_timer_t beacon_timer2;
extern unsigned char data_ma_save[93]; //57 a 93 para nombre y URL y UID



extern uint16_t        numbytes1,numbytes2,numbytes3, numbytes_mac;
extern wiced_result_t  status1,status2,status3, status_mac;
void beacon_data_update(TIMER_PARAM_TYPE arg); //Mi timer
void prendido_led_uart(TIMER_PARAM_TYPE arg); //Mi timer

extern unsigned char data2[230]; // Se usara solo para guardar nomres
extern unsigned char data3[10];
void init_timer(void);


#endif /* SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_ */
