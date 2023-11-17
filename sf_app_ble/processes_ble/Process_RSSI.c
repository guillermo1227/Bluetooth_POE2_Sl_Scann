/*
 * Process_RSSI.c
 *
 *  Created on: 28 sep 2023
 *      Author: Usuario1
 */
#include "Process_RSSI.H"


/* Auxiliary variable of my structure*/
aux_prom val_rsi, values_alone;

void Value_processing_RSSI(wiced_bt_ble_scan_results_t *rsi)
{
	//Busco inicializar el timper solo una vez
	if(timer_flag == 0) //Si ahora la condicion es que sea cero
	{
		WICED_BT_TRACE("\n ***********Inicializo el timer solo una vez************ \n");
		//Aqui necesito ponerle una opcion mas para que no se activen los dos timers al mismo tiempo

		star_count_RSSI();
		timer_flag = 1;
		valores_dentro = 0;
	}

	valores_dentro++; //veo un valor dentro, requiero por lo menos 5 valores

	/* Reafirmo el valor de timer flag, ya que aveces el timer se empalma, poniendolo a cero, pero se levanta de nuevo*/
	if(timer_confirm == 10 )
	{
		timer_flag = 0;
		valores_dentro = 0;
		timer_confirm = 5;
		stop_count_RSSI();
		WICED_BT_TRACE("\n 3.- ******Vuelvo a bajar timer_flag porque se trabo %d \n", timer_flag);
	}
}

//void f_count_RSSI(uint32_t data)
//{
//	timer_confirm = 5; //Aqui solo digo que ya entro a esta funcion
//
//	if(val_rsi.valores_dentro >=4 )   // Primero voy a ver la cantidad de valores que vio el RSSI
//	{
//		count_values = 1;   //Variable que se usa en el observador para que entre o no
//	}
//	else
//	{
//		count_values = 0;   //Variable que se usa en el observador para que entre o no
//		timer_confirm = 10; // Para que no se trabe
//	}
//
//	WICED_BT_TRACE("\n T -  Valores dentro son %d \n", val_rsi.valores_dentro);
//	val_rsi.valores_dentro=0;
//	stop_count_RSSI();
//}
