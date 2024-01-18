/*
 * config_timers.c
 *
 *  Created on: 2 mar 2021
 *      Author: Jared
 */




#include "wiced_hal_wdog.h"
#include "wiced_hal_rand.h"
#include "wiced_hal_nvram.h"

#include "wiced_bt_trace.h"
//#include "wiced_bt_cfg.h"
#if ( defined(CYW20706A2) || defined(CYW20719B1) || defined(CYW20719B0) || defined(CYW20721B1) || defined(CYW20735B0) || defined(CYW43012C0) )
#include "wiced_bt_app_common.h"
#endif
#include "wiced_bt_stack.h"
#include "wiced_timer.h"
#include "wiced_bt_beacon.h"
#include "string.h"
#include "sparcommon.h"
//#include "GeneratedSource/cycfg_gatt_db.h"
#ifndef CYW43012C0
#include "wiced_bt_ota_firmware_upgrade.h"
#endif
#include "wiced_hal_puart.h"
#include "wiced_platform.h"
#include "wiced_transport.h"

#include <malloc.h>
#include "wiced_hal_gpio.h"
#include "wiced_bt_mesh_models.h"
#include "wiced_bt_mesh_app.h"
#include "wiced_bt_mesh_core.h"
#include "config_timers.h"


wiced_timer_t timer_count_RSSI; //Mi timer

wiced_timer_t timer_Online;
wiced_timer_t timer_st_Online;
wiced_timer_t timer_inspection;
wiced_timer_t timer_contM;
wiced_timer_t timer_Clear;
wiced_timer_t timer_Clear10;
wiced_timer_t timer_gap;
wiced_timer_t timer_return;
wiced_timer_t timer_returnfA;
wiced_timer_t timer_returnfAV;
wiced_timer_t timer_returnfB;
wiced_timer_t timer_alrm;
wiced_timer_t timer_EA;
wiced_timer_t timer_er;
wiced_timer_t timer_ach;
wiced_timer_t timer_cer;

wiced_timer_t timer_ip;
wiced_timer_t timer_ip_new;
wiced_timer_t timer_mac;
wiced_timer_t timer_coenction;
wiced_timer_t timer_error;
wiced_timer_t timer_NVRAM;


void config_clk_timers(void)
{

    wiced_init_timer( &timer_gap, f_gap, 0, WICED_SECONDS_TIMER);
    wiced_init_timer( &timer_ip, f_timer_LedIP, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer( &timer_ip_new, f_timer_LedIP_new, 0, WICED_MILLI_SECONDS_TIMER);

    wiced_init_timer( &timer_mac, f_timer_LedMAC, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer( &timer_coenction, f_timer_LedConection, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer( &timer_error, f_timer_LedError, 0, WICED_MILLI_SECONDS_TIMER);
    wiced_init_timer ( &timer_NVRAM, f_timer_NVRAM, 0, WICED_SECONDS_PERIODIC_TIMER);


}

void star_count_RSSI(void)
{
	wiced_start_timer( &timer_count_RSSI, 700); // Estaba en 600, pero ya lo puse en 550
}

void stop_count_RSSI(void)
{
	wiced_stop_timer( &timer_NVRAM);
}

void start_BTimers(void)
{
//    wiced_start_timer( &timer_Online, 3000);
//    //wiced_start_timer( &timer_st_Online, clock_st_Online);
//	wiced_start_timer( &timer_contM, 4000);
	 wiced_start_timer( &timer_NVRAM, 1 );
}


void start_TOnline(void)
{
	 wiced_start_timer( &timer_Online, clock_Online);
}

void start_TOnline_long(void)
{
	//wiced_start_timer( &timer_st_Online, clock_st_Online);
}

void stop_TOnline(void)
{
	wiced_stop_timer(&timer_Online);
	wiced_start_timer( &timer_Online, clock_Online_long);
}

void prevention_inspection(void)
{
	  /* if (wiced_init_timer(&timer_inspection, f_timer_inspection, 0, WICED_SECONDS_TIMER) == WICED_SUCCESS)
	    {
		   WICED_BT_TRACE("Init timer inspection\n");
		   wiced_start_timer( &timer_inspection, clock_inspection);
	    }*/
	   WICED_BT_TRACE("Init timer inspection\n");
	   wiced_start_timer( &timer_inspection, clock_inspection);
}

void stop_timer_st_online(void)
{
	wiced_stop_timer( &timer_st_Online);
}

void Start_TimerCont(void)
{
	wiced_start_timer( &timer_contM, 4000);
}
void   timer_clr01(void)
{
	wiced_start_timer( &timer_Clear, clock_clear5);
	//wiced_stop_timer( &timer_Online);
	//wiced_start_timer( &timer_Online, clock_Online);
}

void   timer_clr10(void)
{
	wiced_start_timer( &timer_Clear10, clock_clear5);
	//wiced_stop_timer( &timer_Reportcxn_ncr);
	//wiced_start_timer( &timer_Reportcxn_ncr, clock_cxn_ncr1);
}

void   init_gap(void)
{
	wiced_start_timer( &timer_gap, clock_gap1);
}

void start_Treturn(void)
{
	wiced_start_timer( &timer_return, clock_return5);
}

void start_TreturnfA(void)
{
	wiced_start_timer( &timer_returnfA, 1000);
}

void start_TreturnfAR(void)
{
	wiced_start_timer( &timer_returnfA, 6000);
}

void start_TreturnfAV(void)
{
	wiced_start_timer( &timer_returnfAV, 1000);
}

void start_TreturnfAVR(void)
{
	wiced_start_timer( &timer_returnfAV, 6000);
}

void start_TreturnfB(void)
{
	wiced_start_timer( &timer_returnfB, 10);
}

void start_alrm(void)
{
	wiced_start_timer( &timer_alrm, clock_alrm);
}

void stop_alrm(void)
{
	 wiced_stop_timer( &timer_alrm);
}

void start_TreturnEA(void)
{
	wiced_start_timer( &timer_EA, clock_EA);
}

void init_event_er(void)
{
	wiced_start_timer( &timer_er, clock_gap1);
}

void Start_Timerach(void)
{
	wiced_start_timer( &timer_ach, 1000);
}
void Stop_Timerach(void)
{
	wiced_stop_timer( &timer_ach);
}

void start_TreturnCER(void)
{
	wiced_start_timer( &timer_cer, 7000);
}
/*  -------------------------------------------*/ /*   Timers used in the aplication of POE   */
void start_Timer_led(uint8_t num)
{
	if(num==1)
	wiced_start_timer(&timer_ip, 200);
	else
	wiced_start_timer(&timer_ip_new, 500);
}

void stop_Timer_led(void)
{
	wiced_stop_timer(&timer_ip);
}

void start_Timer_led2(void)
{
	wiced_start_timer(&timer_mac, 800);
}

void stop_Timer_led2(void)
{
	wiced_stop_timer(&timer_mac);
}

void start_Timer_led3(void)
{
	wiced_start_timer(&timer_coenction, 1000);
}

void stop_Timer_led3(void)
{
	wiced_stop_timer(&timer_coenction);
}

static int error = 0;
extern uint8_t flag_error, queue;
uint8_t type_error_take;

/**
 * This function evaluates the type of error
 * that is present in the POE, type_error
 * defines the type of error.
 *
 * @param uint8_t type_error
 *
 * return none
 */
void start_Timer_Error(uint8_t type_error)
{
	type_error_take = type_error;
	//WICED_BT_TRACE("\n Type of Error %d \n", type_error_take);
	if(type_error == 1)
	{
			if(error != 5)
			{
				wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
				wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
				wiced_start_timer(&timer_error, 1000);
			}

			else if(error == 5)
			{
				wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
				wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
				wiced_start_timer(&timer_error, 1000);
				error = -1;
				//WICED_BT_TRACE("\n Bajo la bandera en TE1 \n");
				flag_error=0;
				queue=2;
			}
	}
	if(type_error == 2)
		{
				if(error != 2 && error != 4 && error != 5)
				{
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_start_timer(&timer_error, 1000);
				}
				else if(error == 2)
				{
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
					wiced_start_timer(&timer_error, 1000);
				}
				else if(error == 4)
				{
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
					wiced_start_timer(&timer_error, 1000);
				}
				else if(error == 5)
				{
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_start_timer(&timer_error, 1000);
					flag_error=0;
					/* Under the flag in TE2 */
					error = -1;
					queue=2;
				}
		}
	if(type_error == 3)
			{
					if(error != 1 && error != 3 && error != 5)
					{
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
						wiced_start_timer(&timer_error, 1000);
					}
					else if(error == 1)
					{
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						wiced_start_timer(&timer_error, 1000);
					}
					else if(error == 3)
					{
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						wiced_start_timer(&timer_error, 1000);
					}
					else if(error == 5)
					{
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						wiced_start_timer(&timer_error, 1000);
						error = -1;
						/* Under the flag in TE3 */
						flag_error=0;
						queue=2;
					}
			}

	error++;
}

void stop_Timer_Error(void)
{
	wiced_stop_timer(&timer_error);
}

extern void 	 stop_timer_NVRAM(void)
{
	wiced_stop_timer( &timer_NVRAM);
}

