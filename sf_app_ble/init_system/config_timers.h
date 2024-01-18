/*
 * config_timers.h
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */

#ifndef SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_
#define SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_
#include "config_ports.h"

#define clock_Online       1000
#define clock_st_Online    8000
#define clock_Online_long  10000
#define clock_inspection   20
#define clock_clear5	   (5)
#define clock_gap1	        1
#define clock_return5      5
#define clock_alrm         350
#define clock_EA           4

//#define LED_BLUE                          WICED_P08
//#define LED_GREEN                         WICED_P07
//#define LED_RED                          WICED_P04

/* Tarjeta verde */
//#define LED_BLUE                          WICED_P04
//#define LED_GREEN                         WICED_P05
//#define LED_RED                          WICED_P03

void config_clk_timers(void);
void start_BTimers(void);
void start_TOnline(void);
void start_TOnline_long(void);
void stop_TOnline(void);
void prevention_inspection(void);
void stop_timer_st_online(void);
void Start_TimerCont(void);
void   timer_clr01(void);
void   timer_clr10(void);
void   init_gap(void);
void start_Treturn(void);
void start_TreturnfA(void);
void start_TreturnfAR(void);
void start_TreturnfAV(void);
void start_TreturnfAVR(void);
void start_TreturnfB(void);
void start_alrm(void);
void stop_alrm(void);
void start_TreturnEA(void);
void init_event_er(void);
void Start_Timerach(void);
void Stop_Timerach(void);
void start_TreturnCER(void);
void star_count_RSSI(void);  // Conteo del timepo de frecuencia de RSSI
void stop_count_RSSI(void);
void stop_Timer_led(void);

extern void      f_count_RSSI( uint32_t data );   // Funcion el timer externa
extern void      f_timer_Online( uint32_t data );
extern void      f_timer_st_Online( uint32_t data );
extern void      f_timer_inspection( uint32_t data );
extern void      f_timer_contM( uint32_t data );
extern void      f_clear( uint32_t data );
extern void      f_clear10( uint32_t data );
extern void      f_gap( uint32_t data );
extern void      f_timer_return( uint32_t data );
extern void      f_timer_returnfA( uint32_t data );
extern void      f_timer_returnfAV( uint32_t data );
extern void      f_timer_returnfB( uint32_t data );
extern void      f_timer_alrm( uint32_t data );
extern void      f_timer_EA( uint32_t data );
extern void      f_timer_er( uint32_t data );
extern void      f_timer_ach( uint32_t data );
extern void      f_timer_CER( uint32_t data );



/* Beacon timer */
static wiced_timer_t beacon_timer;
static wiced_timer_t beacon_timer2;
extern unsigned char data_ma_save[93]; //57 a 93 para nombre y URL y UID

extern void      f_timer_LedIP( uint32_t data );
extern void      f_timer_LedIP_new( uint32_t data );

extern void      f_timer_LedMAC( uint32_t data );
extern void      f_timer_LedConection( uint32_t data );
extern void      f_timer_LedError( uint32_t data );
extern void      f_timer_NVRAM( TIMER_PARAM_TYPE arg );
extern void 	 stop_timer_NVRAM(void);
extern void      f_timer_IPON( TIMER_PARAM_TYPE arg );
extern void      stop_timer_IPON( void );

extern uint16_t        numbytes1,numbytes2,numbytes3, numbytes_mac;
extern wiced_result_t  status1,status2,status3, status_mac;
void beacon_data_update(TIMER_PARAM_TYPE arg); //Mi timer
void prendido_led_uart(TIMER_PARAM_TYPE arg); //Mi timer

extern unsigned char data2[230]; // Se usara solo para guardar nomres
extern unsigned char data3[10];
void init_timer(void);

#endif /* SF_APP_BLE_INIT_SYSTEM_CONFIG_TIMERS_H_ */
