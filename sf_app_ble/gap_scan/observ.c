/*
 * observ.c
 *
 *  Created on: 20 jun 2023
 *      Author: temporal
 */

#include "observ.h"
#include "wiced_result.h"
#include <string.h>
#define maax_size 5

uint8_t 	dataFilt[10];   //5  usados en el nombre
uint8_t 	dataFiltm[6];   //6   usados en el nombre
uint8_t 	length3,length4;        //   usado en el UID
uint8_t *   p_data,* p_data4;


/*Funcion usada en el scanner de Bluetooth*/
static void Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data );


void stop_scanner(void){
	wiced_bt_ble_observe (0,0, Observer_scan_result_cback);
}

start_observe(void){
	WICED_BT_TRACE("\n Init scanner \n");
	wiced_bt_ble_observe (1,0, Observer_scan_result_cback);
	//wiced_bt_ble_scan( BTM_BLE_SCAN_TYPE_LOW_DUTY, WICED_TRUE, Observer_scan_result_cback);
}


void Observer_scan_result_cback( wiced_bt_ble_scan_results_t *p_scan_result, uint8_t *p_adv_data )
{
		    wiced_bt_device_address_t static_addr;    //arreglo de 6 unidades static_addr[6]
		    wiced_bt_dev_read_local_addr(static_addr );  //Read the local device address, means read the own device address

		    //Usado para el nombre, 		 URL              uid
		    uint8_t * p_name1=NULL,    * p_name2=NULL,    * p_name3=NULL;
		    uint8_t 	length3=0, 			length4=0,		  length5=0;

//		    p_name3=&p_adv_data[5];
//		    WICED_BT_TRACE("DATA: ");
//            wiced_hal_puart_print(p_name3);
//            WICED_BT_TRACE("\n");
		    /* Con p_sacn_reslt le lo que haya llegado, dar clic en para ver estructura wiced_bt_ble_scan_results_t*/
		    if( p_scan_result)
		    	{
		    	if(p_scan_result->rssi > -125)
		    	{
		    		memcpy(data_mac,p_scan_result->remote_bd_addr,6);
		    		if(data_mac[0]<1 || data_mac[1]<1 || data_mac[2]<1 || data_mac[3]<1 || data_mac[4]<1 || data_mac[5]<1)
		    		{
		    			data_mac[0]=0x1E;
		    			data_mac[1]=0x1E;
		    			data_mac[2]=0x1E;
		    			data_mac[3]=0x1E;
		    			data_mac[4]=0x1E;
		    			data_mac[5]=0x1E;
		    		}
		    		/****************** Serch name *********************/
		    		p_name1 = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_NAME_COMPLETE, &length3 );  //BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE
		    		if(p_name1 != NULL)
		    		{
		    			//Busco lamparas
		    			memcpy(scanner_name,p_name1,5);
		    			//WICED_BT_TRACE("\n ->%s ->%s\n",scanner_name,nombre[xn]);
		    			//WICED_BT_TRACE("\n %d %d ",strlen(nombre[xn]),strlen(scanner_name));

		    			if(memcmp(scanner_name , "L4SEC",5)==0 ||
		    			   memcmp(scanner_name , "L4SEC",5)==0 ||
					   	   memcmp(scanner_name , "LAIRD",5)==0 ||
						   memcmp(scanner_name , "LAIRD",5)==0)
		    			{
		    				//WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BSL\n", p_scan_result->remote_bd_addr[0],p_scan_result->remote_bd_addr[1],p_scan_result->remote_bd_addr[2],p_scan_result->remote_bd_addr[3],p_scan_result->remote_bd_addr[4],p_scan_result->remote_bd_addr[5],p_scan_result->rssi);
		    				WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BSL\n", data_mac[0],data_mac[1],data_mac[2],data_mac[3],data_mac[4],data_mac[5],p_scan_result->rssi);
		    			}
		    					memset(scanner_name,'\0',5);
		    		}
		    		/**************      Serch URL***************/
		    		p_name2 = wiced_bt_ble_check_advertising_data( p_adv_data, BTM_BLE_ADVERT_TYPE_SERVICE_DATA, &length4 );  //BTM_BLE_ADVERT_TYPE_128SRV_COMPLETE
		    		if(p_name2 != NULL)
		    		{
		    			//WICED_BT_TRACE("\n ---->%s: %B ---->%s \n",&p_name2[5],p_scan_result->remote_bd_addr, URL[0]); ----->
		    			if(memcmp("GEOSF",&p_name2[5],5)==0 ||
		    				memcmp("ACARO",&p_name2[5],5)==0 ||
							memcmp("SMART",&p_name2[5],5)==0)
		    			{
		    				WICED_BT_TRACE("MAC: %02X:%02X:%02X:%02X:%02X:%02X %d BEA\n", data_mac[0],data_mac[1],data_mac[2],data_mac[3],data_mac[4],data_mac[5],p_scan_result->rssi);
		    			}
		    		}
		    		memset(data_mac,NULL,6);
		    	}
		    	}
}

f_timer_Observ(uint32_t data)
{
	wiced_bt_ble_observe (0,0, Observer_scan_result_cback);
	/* Restar the observer */
	//WICED_BT_TRACE("\n Init scanner2 \n");
	wiced_bt_ble_observe (1,0, Observer_scan_result_cback);
	start_BTimers();
}

