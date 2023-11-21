/*
 * Processes_leds.c
 *
 *  Created on: 15 nov 2023
 *      Author: Usuario1
 */

#include "Processes_leds.h"
uint8_t tart_color_same_time = 0;

void process_led(char texto_global[])     //Inicio de proceso led en rojo
{
	//WICED_BT_TRACE("\n Entro en el encendido de LEDS \n");
	//WICED_BT_TRACE("\n **** %s \n",&texto_global[8]);
	if(strstr(&texto_global[8],"IP/ON"))                                //ESTADO: IP/ON
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
	else if(strstr(&texto_global[8],"IP/NEW")) /* Toogle Green led */     //ESTADO: IP/NEW   Blinkeo red en Rojo
	{
		stop_Timer_led2();
		stop_Timer_led3();
		stop_Timer_Error();
		wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
		wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
		start_Timer_led();
		tart_color_same_time = 0;
	}
	else if(strstr(&texto_global[8],"Error01"))   							//ESTADO: ERROR01
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
	if(strstr(&texto_global[8],"ARP/ON"))                             //ESTADO ARP/ON
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
	else if(strstr(&texto_global[8],"Error02"))							 //ESTADO: ARP/ON
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
	if(strstr(&texto_global[8],"CLIENTE/WFC"))  /*   Morado tooglee  */
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
	else if(strstr(&texto_global[8],"Error03"))    /*   ROJO  */    //ESTADO: ERROR03  NO PUEDE ENLAZAR CON EL SERVIDOR    ESTADO: Error03
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

extern void prender_leeds(void)
{
	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);
	wiced_rtos_delay_milliseconds(1500,ALLOW_THREAD_TO_SLEEP);

	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
	wiced_rtos_delay_milliseconds(1500,ALLOW_THREAD_TO_SLEEP);

	wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
	wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
	wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
	wiced_rtos_delay_milliseconds(1500,ALLOW_THREAD_TO_SLEEP);
}

void wrong_configuration(char texto_global[])
{
		if(strstr(&texto_global[10],"good") || strstr(&texto_global[11],"good") || strstr(&texto_global[12],"good"))
		{
			stop_Timer_led();
			stop_Timer_led2();
			stop_Timer_led3();
			stop_Timer_Error();
			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);
		}
		else if(strstr(&texto_global[10],"wrong") || strstr(&texto_global[12],"wrong"))   /*  IPconf is wrong  */  /* ServerIP is wrong */
		{
		WICED_BT_TRACE("\n IPconf wrong  ServerIp is worng \n");
			stop_Timer_led2();
			stop_Timer_led3();
			stop_Timer_Error();
			wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_HIGH);
			wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_LOW);
			start_Timer_led();   													//BLINK LED EN ROJO
		}
}
