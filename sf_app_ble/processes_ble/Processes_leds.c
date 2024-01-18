/*
 * Processes_leds.c
 *
 *  Created on: 15 nov 2023
 *      Author: Usuario1
 */

#include "Processes_leds.h"
uint8_t tart_color_same_time = 0,flag_error=0, queue=0, data_queue[11]={0,0,0,0,0,0,0,0,0,0,0}; /* Data queue es lamemoria de los comandos */
char text[15];
uint8_t interador=0, key=0; /* interador Variabe para llevar el flugo de mi arreglo, key para llevar los tiempos del arreglo */
/**
 * Function name: process_led(char texto_global[])
 *
 * Summary: In this function I carry out the indications
 * of the POE status through Bluetooth,
 * it initializes with the LED on RED
 *
 * Note: flag_error is only used inside the blink if, dont access
 * to another function at less the value flag_error change
 * @queue its value to differentiate incoming messages
 *
 *               IP/ON  IP/NEW  ARP/ON
 *@data_queue[]={ 1   ,   1   ,   1   ,   1 , 1 , 1 , 1 , 1}
 *
 * @param char: Array of characters where the information
 * sent by the UART is stored
 *
 * @return none
 */
void process_led(char texto_global[])     //At the beginning of the process the LED is red
{
	if(data_status != WICED_TRUE)
	{
			memcpy(text,&texto_global[8],strlen(&texto_global[8]));
			if(memcmp("IP/ON",text,strlen("IP/ON"))==0)							/* ESTADO: IP/ON = 1 */
			{
				queue = 4;
				flag_error=0;
				stop_Timer_led2();
				stop_Timer_led3();
				stop_Timer_Error();
				start_Timer_led(1);
				wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW is HIGH
				wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
				wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
				tart_color_same_time = 0;
				start_Timer_led(1);
			}
			if(queue != 4)
			{
				//else if(memcmp("IP/NEW",text,strlen("IP/NEW"))==0)					/* ESTADO: IP/NEW   Blinkeo red = 2 */
				if(memcmp("IP/NEW",text,strlen("IP/NEW"))==0)					/* ESTADO: IP/NEW   Blinkeo red = 2 */
				{
					flag_error=0;
					stop_Timer_led2();
					stop_Timer_led3();
					stop_Timer_Error();
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					start_Timer_led(2);
					tart_color_same_time = 0;
				}
				/*  Led de Mac */
				else if(memcmp("ARP/ON",text,strlen("ARP/ON"))==0)						/* ESTADO ARP/ON=3 */
				{
					flag_error=0;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					stop_Timer_Error();
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
					tart_color_same_time = 0;
				}
				else if(memcmp("Error01",text,strlen("Error01"))==0)				/* ESTADO: ERROR01 */
				{
					flag_error=1;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					start_Timer_Error(1);
					tart_color_same_time = 0;
				}
				else if(memcmp("Error02",text,strlen("Error02"))==0)				/* ESTADO: Error02 */
				{
					flag_error=1;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					start_Timer_Error(2);
					tart_color_same_time = 0;
				}
				if(memcmp("CLIENTE/WFC",text,strlen("CLIENTE/WFC"))==0)				/* ESTADO: CLIENTE/WFC =toogle purple= */
				{
					if(flag_error==0 || queue==2)  /* Will do this if you haven't entered an error */
					{
						stop_Timer_led();
						stop_Timer_led2();
						stop_Timer_Error();
						wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						start_Timer_led3();
						tart_color_same_time = 0;
						flag_error=0;                                  /* Changes the value of flag_error after the timer is terminated */
						queue=0;
					}
					else
						queue=1;  /* 1.- I put 1 that indicates that a WFC arrived but the error still does not end */
				}
				else if(memcmp("CLIENTE/ON",text,strlen("CLIENTE/ON"))==0)			/* ESTADO: CLIENTE/ON =Purple= */
				{
					flag_error=0;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					stop_Timer_Error();
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
					tart_color_same_time = 0;
				}
				else if(memcmp("CLIENTE/OFF",text,strlen("CLIENTE/OFF"))==0)		/* The service was disconnected ESTADO: CLIENTE/OFF =RED= */
				{
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					stop_Timer_Error();
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_rtos_delay_milliseconds(2000,ALLOW_THREAD_TO_SLEEP);

					tart_color_same_time = 0;
					//WICED_BT_TRACE("\n Bajo bandera en CLIENTE/OFF \n");
					flag_error=0;                                                  /* --->Asign the flag_error value<--- */
					queue=2;													   /* --->Asign the queue value<--- */
				}

				else if(memcmp("CLIENTE/BLINK",text,strlen("CLIENTE/BLINK"))==0)	/* ESTADO: CLIENTE/OFF =Light Blue= */
				{
					flag_error=1;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					stop_Timer_Error();
					if(tart_color_same_time == 0)
					{
						wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  /* Asignacion de IP */
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_rtos_delay_milliseconds(500,ALLOW_THREAD_TO_SLEEP);
						wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);  //LOW es encenndido
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_rtos_delay_milliseconds(500,ALLOW_THREAD_TO_SLEEP);

						wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
						wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);
						wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
						tart_color_same_time=1;
					}
					/* Toogle LED light blue */
					wiced_hal_gpio_set_pin_output( LED_GREEN, ~(wiced_hal_gpio_get_pin_input_status(LED_GREEN)));
					wiced_hal_gpio_set_pin_output( LED_BLUE, ~(wiced_hal_gpio_get_pin_input_status(LED_BLUE)));
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
				}
				else if(memcmp("Error03",text,strlen("Error03"))==0 && queue<=1)	/* ESTADO: Error03  CANNOT LINK TO THE SERVER =Turn HIGH the LED RED= */
				{
					flag_error=1;
					stop_Timer_led();
					stop_Timer_led2();
					stop_Timer_led3();
					wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
					wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
					start_Timer_Error(3);
					tart_color_same_time = 0;
				}
			}
	}
	memset(text,'\0',15);
}



char text2[15], text3[15], text4[15];
/**
 * Function name: wrong_configuration(char texto_global[])
 *
 * Summary: In this function when you send a good/bad configuration
 * the LED turns red or green, notifying the configuration status
 *
 * @param char: character array where the data sent through the uart is stored
 *
 * return none
 *
 */
void wrong_configuration(char texto_global[])
{
	/*ServerIP is good   or ServerIP is wrong*/
WICED_BT_TRACE("\n :%s \n",texto_global);
	if(strstr(texto_global,"ServerIPW") || strstr(texto_global,"IPW") || strstr(texto_global,"DHCPW"))// || texto_global[10] == 'g' || texto_global[11] == 'g' || texto_global[12] =='g' || texto_global[13] == 'g' || letra == 'g')
		{
			data_status = WICED_TRUE; 		//------------------>
		//WICED_BT_TRACE("\n IPconf wrong  ServerIp is worng \n");
			stop_Timer_led();
			stop_Timer_led2();
			stop_Timer_led3();
			stop_Timer_Error();
			//wiced_hal_puart_disable_tx();     /* Desabilito la capacidad de transmitir */

			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
//			wiced_rtos_delay_milliseconds(2000,ALLOW_THREAD_TO_SLEEP);
//
//			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
//			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
//			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
//			wiced_rtos_delay_milliseconds(2000,ALLOW_THREAD_TO_SLEEP);
//			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
//			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
//			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
			//data_status = WICED_FALSE;		//<------------------
			//wiced_hal_puart_enable_tx();     /* Habilito la capacidad de transmitir */
			//start_Timer_led();   													//BLINK LED EN ROJO
		}
	else if(strstr(texto_global,"ServerIPG") || strstr(texto_global,"IPG") || strstr(texto_global,"DHCPG")) // || texto_global[10] == 'g' || texto_global[11] == 'g' || texto_global[12] =='g' || texto_global[13] == 'g' || letra == 'g')
		{
				queue = 0;
				data_status = WICED_TRUE;		//------------------>
				//WICED_BT_TRACE("\n IP config is good \n");
				stop_Timer_led();
				stop_Timer_led2();
				stop_Timer_led3();
				stop_Timer_Error();
				//wiced_hal_puart_disable_tx();     /* Desabilito la capacidad de transmitir */
				wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
				wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
				wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);

				//data_status = WICED_FALSE;		//<------------------

		}

}

/*
 * Function name: successful_data(void)
 *
 * Smmary: Function that displays a flashing
 * led in green when a good configuration made
 *
 * @param none
 *
 * @return none
 *
 */
extern void successful_data(void)
{
	stop_Timer_led();
	stop_Timer_led2();
	stop_Timer_led3();
	stop_Timer_Error();
	//wiced_hal_puart_disable_tx();     /* Desabilito la capacidad de transmitir */
	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
	wiced_rtos_delay_milliseconds(700,ALLOW_THREAD_TO_SLEEP);

	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);  //LOW es encenndido
	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
	wiced_rtos_delay_milliseconds(700,ALLOW_THREAD_TO_SLEEP);

	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
	//wiced_hal_puart_enable_tx();     /* Habilito la capacidad de transmitir */
}
