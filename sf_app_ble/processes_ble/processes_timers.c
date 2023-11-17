/*
 * processes_timers.c
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
#include "wiced_rtos.h"
//#include "GeneratedSource/cycfg_gatt_db.h"
#ifndef CYW43012C0
#include "wiced_bt_ota_firmware_upgrade.h"
#endif
#include "wiced_hal_puart.h"
#include "wiced_platform.h"
#include "wiced_transport.h"

#include <malloc.h>

#include "wiced_bt_mesh_models.h"
#include "wiced_bt_mesh_app.h"
#include "wiced_bt_mesh_core.h"
#include "processes_timers.h"
#include "config_ports.h"

extern uint8_t timer_flag;
extern uint8_t timer_confirm;
extern uint8_t i_am_in;
extern uint16_t valores_dentro;
void f_count_RSSI(uint32_t data)
{
	if(valores_dentro >=2)   //Esta en 6 aun no lo muevo, movi a 4
	{
		WICED_BT_TRACE("\n Si hay mas de 4 valores en el RSSI \n");
		//Preguntare sobre lo que ha pasado en el observador
		i_am_in = 1;
		stop_count_RSSI(); //Apago el timer para que no se reinicie de nuevo
	}
	else
	{
		timer_flag = 0; //Vuelvo a bajar esta bandera para empezar de nuevo el timer
		timer_confirm = 10;
	}
}

void f_timer_Online( uint32_t data )
{
	if(value_rst == WICED_TRUE)
	{
		value_rst = WICED_FALSE;
		gap_transferA();
	}

	//WICED_BT_TRACE( "BLE Online\n" );
	start_TOnline();
    //wiced_start_timer( &timer_Online, clock_Online);
	//exam_gpio();
}

void f_timer_st_Online( uint32_t data )
{
   if(status_Online)
   {
	   WICED_BT_TRACE( "WiFi: Online\n" );
	   status_Online = WICED_FALSE;
	   start_TOnline_long();
	   //wiced_start_timer( &timer_st_Online, clock_st_Online);
   }
   else
   {
	   /*WICED_BT_TRACE( "PIN HIGTH\n" );
	   wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
	   wiced_rtos_delay_milliseconds( 1000, ALLOW_THREAD_TO_SLEEP );
	   wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	   WICED_BT_TRACE( "PIN LOW\n" );*/
	   status_Online = WICED_FALSE;
	   start_TOnline_long();
	   //wiced_start_timer( &timer_st_Online, clock_st_Online);
   }

}


void      f_timer_inspection( uint32_t data )
{
	extern void gap_out_f(void);
	WICED_BT_TRACE("Enter inspection\n");
	value_inspection =  !value_inspection ? WICED_TRUE : WICED_FALSE;
	WICED_BT_TRACE("Value inspection: %d\n", value_inspection);
    prevention_status2();
    //gap_out_f();
}

void f_timer_contM( uint32_t data )
{
	//WICED_BT_TRACE("limit\n");
	//datac_menviada=-1;
	//clear_cont();
}

void    f_clear( uint32_t data )
{
	WICED_BT_TRACE("CLEAAAR \n");
	//clear_SB01();
}

void    f_clear10( uint32_t data )
{
	WICED_BT_TRACE("CLEAAAR 10\n");
	//clear_SB10();
}

void      f_gap( uint32_t data )
{
	if(!value_le)
	{
	//WICED_BT_TRACE("GAP TR\n");
	if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_05 ) )
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
		 WICED_BT_TRACE( "GAP A\n\r" );
		 gap_transferA();
		 //gap_t1 = WICED_FALSE;

	}
	else
	{
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_HIGH);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_HIGH);
		 WICED_BT_TRACE( "GAP B\n\r" );
		 gap_transferB();
		 //gap_t1 = WICED_TRUE;
		 //value_gap =  WICED_TRUE;
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 //print_cst();

	}
	}

}

void      f_timer_return( uint32_t data )
{
	WICED_BT_TRACE("Enter return\n");
	gap_transferA();
	//wiced_hal_wdog_reset_system ();
	//beacon_set_app_advertisement_data4();
	wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
    value_gap = WICED_TRUE;
}

extern uint8_t i_am_in;
extern uint8_t timer_confirm;
void      f_timer_returnfA( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfA\n");
    value_AL=WICED_FALSE;
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
	i_am_in=0;
	timer_confirm = 10;  //El valor de 10 solo es una marca, n significa nada
}

void      f_timer_returnfAV( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfAV\n");
	  value_AV=WICED_FALSE;
	wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
}

void      f_timer_returnfB( uint32_t data )
{
	//WICED_BT_TRACE("Enter returnfB\n");
	wiced_hal_gpio_set_pin_output( LED_GPIO_03, GPIO_PIN_OUTPUT_LOW);
}

void      f_timer_alrm( uint32_t data )
{
	//WICED_BT_TRACE("Enter ALRM\n");
	start_alrm();
	if(value_AL==WICED_FALSE && value_AV==WICED_FALSE)
	{
		value_alrm=WICED_TRUE;
		if(value_p1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
		}
		if(value_pV1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		stop_alrm();
	}
	else if(value_AL==WICED_FALSE && value_AV==WICED_TRUE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_02 ))
		{
			//WICED_BT_TRACE("Pin 09 LOW\n");
			 //wiced_hal_gpio_set_pin_output( LED_GPIO_14, GPIO_PIN_OUTPUT_LOW);
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 09 HIGH\n");
			//wiced_hal_gpio_set_pin_output( LED_GPIO_14, GPIO_PIN_OUTPUT_LOW);
			wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		if(value_p1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
		}


	}
	else if(value_AL==WICED_TRUE && value_AV==WICED_FALSE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_01 ))
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
			 //wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
			//wiced_hal_gpio_set_pin_output( LED_GPIO_09, GPIO_PIN_OUTPUT_LOW);
		}
		if(value_pV1==WICED_TRUE)
		{
			//WICED_BT_TRACE("Pin 14 HIGH\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}

	}
	else if(value_AL==WICED_TRUE && value_AV==WICED_TRUE)
	{
		if( GPIO_PIN_OUTPUT_HIGH == wiced_hal_gpio_get_pin_output(LED_GPIO_01 ))
		{
			//WICED_BT_TRACE("Pin 14, 09 LOW\n");
			 wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_LOW);
			 wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_LOW);
		}
		else
		{
			//WICED_BT_TRACE("Pin 14, 09 HIGH\n");
			wiced_hal_gpio_set_pin_output( LED_GPIO_01, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_GPIO_02, GPIO_PIN_OUTPUT_HIGH);
		}
	}

}


void      f_timer_EA( uint32_t data )
{
	  value_EA = WICED_FALSE;
	  WICED_BT_TRACE("EA  OFF\n");
}

void      f_timer_er( uint32_t data )
{

	if(!gap_t1)
	{
	if( value_le == WICED_FALSE )
	{
	 gap_transferER();
	 value_le = WICED_TRUE;
	 //wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_HIGH);
	 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	}
	else
	{
		 gap_transferA();
		 value_le = WICED_FALSE;
		 //wiced_hal_gpio_set_pin_output( LED_GPIO_17, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_05, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_04, GPIO_PIN_OUTPUT_LOW);
		 wiced_hal_gpio_set_pin_output( LED_GPIO_06, GPIO_PIN_OUTPUT_LOW);
	}
	}
}
void      f_timer_ach( uint32_t data )
{
	//evalue_ach();
}

void      f_timer_CER( uint32_t data )
{
	//clear_cer();
}

/*     Timers para LEEDS   */
extern void start_Timer_led(void);  //LED VERDE
void f_timer_LedIP( uint32_t data )
{
wiced_hal_gpio_set_pin_output( LED_GREEN, ~(wiced_hal_gpio_get_pin_input_status(LED_GREEN)));
start_Timer_led();
}

extern void start_Timer_led2(void);
void f_timer_LedMAC( uint32_t data)
{
	wiced_hal_gpio_set_pin_output( LED_BLUE, ~(wiced_hal_gpio_get_pin_input_status(LED_BLUE)));
	start_Timer_led2();
}

extern void start_Timer_led3(void);
extern void f_timer_LedConection( uint32_t data)
{
	//wiced_hal_gpio_set_pin_output( LED3, ~(wiced_hal_gpio_get_pin_input_status(LED3)));
	wiced_hal_gpio_set_pin_output( LED_RED, ~(wiced_hal_gpio_get_pin_input_status(LED_RED)));
	wiced_hal_gpio_set_pin_output( LED_BLUE, ~(wiced_hal_gpio_get_pin_input_status(LED_BLUE)));

		start_Timer_led3();
}

extern uint8_t type_error_take;
extern void start_Timer_Error(uint8_t);
extern void f_timer_LedError(uint32_t data)
{
	uint8_t a = type_error_take;
/* Only make time for the procces LED Error */
	//WICED_BT_TRACE("%d", a );
	start_Timer_Error(a);
}

///*  Restaurar valores guardados en la NVRAM */
//static int valor_timer=0;
///* Function called on timer */
//extern void f_timer_NVRAM(TIMER_PARAM_TYPE arg)
//{
//	wiced_hal_read_nvram( WICED_NVRAM_VSID_START+1, sizeof(data_ma_save), &data_ma_save[0], &status111 );
//}
