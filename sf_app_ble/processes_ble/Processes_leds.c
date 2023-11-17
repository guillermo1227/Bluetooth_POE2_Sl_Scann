/*
 * Processes_leds.c
 *
 *  Created on: 15 nov 2023
 *      Author: Usuario1
 */

#include "Processes_leds.h"
uint8_t tart_color_same_time = 0;

void process_led(char texto_global[])
{
	//WICED_BT_TRACE("\n Entro en el encendido de LEDS \n");
	//WICED_BT_TRACE("\n **** %s \n",&texto_global[8]);
	if(strstr(&texto_global[8],"IP/ON"))
	{
		//WICED_BT_TRACE("\n Enciendo led verde \n");
		stop_Timer_led();
		stop_Timer_led2();
		stop_Timer_led3();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"IP/OFF"))   /* Toogle Green led */
	{
		stop_Timer_led2();
		stop_Timer_led3();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
		start_Timer_led();
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"IP/NEW")) /* Toogle Green led */
	{
		stop_Timer_led3();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
		start_Timer_led();
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"ERROR01"))   //IP/NEW tengo que quitarlo de aqui
	{
		stop_Timer_led();
		stop_Timer_led2();
		stop_Timer_led3();
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
		start_Timer_Error(1);
		tart_color_same_time = 0;
	}

	/*  Led de Mac */
	if(strstr(&texto_global[8],"ARP/ON"))
		{
			stop_Timer_led();
			stop_Timer_led2();
			stop_Timer_led3();
			stop_Timer_Error();
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
			tart_color_same_time = 0;
		}
	else if(strstr(&texto_global[8],"ERROR02"))
			{
			stop_Timer_led();
			stop_Timer_led2();
			stop_Timer_led3();
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
			start_Timer_Error(2);
			tart_color_same_time = 0;
			}
	/* Led de conexion exitosa */
	if(strstr(&texto_global[8],"CLIENTE/WFC"))  /*   Morado  */
	{
		stop_Timer_led();
		stop_Timer_led2();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
		start_Timer_led3();
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"CLIENTE/ON"))
	{
		stop_Timer_led();
		stop_Timer_led2();
		stop_Timer_led3();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"CLIENTE/BLINK"))                     /*   AZUL CLARO  */
	{
		stop_Timer_led();
		stop_Timer_led2();
		stop_Timer_led3();
		stop_Timer_Error();
		if(tart_color_same_time == 0)
		{
			//WICED_BT_TRACE("\n Otra opcion \n");
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
			tart_color_same_time=1;
		}
		//WICED_BT_TRACE("\n Toogle del LED \n");
		wiced_hal_gpio_set_pin_output( LED_GREEN, ~(wiced_hal_gpio_get_pin_input_status(LED_GREEN)));
		wiced_hal_gpio_set_pin_output( LED_BLUE, ~(wiced_hal_gpio_get_pin_input_status(LED_BLUE)));
	}
	else if(strstr(&texto_global[8],"CLIENTE/ERROR03"))    /*   ROJO  */
		{
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
