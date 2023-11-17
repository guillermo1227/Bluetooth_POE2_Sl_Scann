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

#include "wiced_bt_mesh_models.h"
#include "wiced_bt_mesh_app.h"
#include "wiced_bt_mesh_core.h"
#include "config_timers_mio.h"


void start_BTimers2(void)
{
//	wiced_init_timer ( &beacon_timer,
//			beacon_data_update,
//			0, WICED_SECONDS_PERIODIC_TIMER);

	wiced_init_timer ( &beacon_timer2,
				prendido_led_uart,
				0, WICED_MILLI_SECONDS_PERIODIC_TIMER);

	wiced_start_timer( &beacon_timer2, 1 );
}

static int valor_timer=0;
/* Function called on timer */
void beacon_data_update(TIMER_PARAM_TYPE arg)
{

	//WICED_BT_TRACE("\n Variable desde mi timer %d",valor_timer);
			numbytes1 = wiced_hal_read_nvram( WICED_NVRAM_VSID_START+1, sizeof(data_ma_save), &data_ma_save[0], &status1 );
			//WICED_BT_TRACE("\n Lugar 51 %c \n",data_ma_save[51]);


			    //Poner las inicializaciones hechas en scanner
			    wiced_hal_read_nvram( WICED_NVRAM_VSID_START+2, sizeof(data2), &data2[0], &status2 );
			    wiced_hal_read_nvram( WICED_NVRAM_VSID_START+3, sizeof(data3), &data3[0], &status3 );
			    timer_init_scann(data2,data3);
			    //WICED_BT_TRACE("\n dejo la te ? %c\n",data_ma_save[69]);
			    valor_timer++;
			    if(valor_timer==1)wiced_stop_timer( &beacon_timer);
			    //cambio_mac();

}

void init_timer(void)
{
	wiced_start_timer( &beacon_timer2, 500);
}

void prendido_led_uart(TIMER_PARAM_TYPE arg)
{
	wiced_hal_gpio_configure_pin(reception_led, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
	wiced_stop_timer( &beacon_timer2);
}
