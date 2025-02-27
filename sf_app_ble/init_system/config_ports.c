/*
 * config_ports.c
 *
 *  Created on: 1 mar 2021
 *      Author: Jared
 */


#include "wiced_bt_dev.h"
#include "sparcommon.h"

#include "wiced_hal_gpio.h"
#include "wiced_hal_mia.h"
#include "wiced_gki.h"
#include "wiced_platform.h"
#include "wiced_timer.h"
#include "wiced_bt_trace.h"
#include "wiced_hal_puart.h"
#include "wiced_bt_stack.h"
#include "config_ports.h"


void set_outPuts(void)
{
    /* Configure LED PIN as input and initial outvalue as high */
	//wiced_hal_gpio_configure_pin( LED_GPIO_P07, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
    wiced_hal_gpio_configure_pin( LED_RED, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
    wiced_hal_gpio_configure_pin( LED_GREEN, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);
    wiced_hal_gpio_configure_pin( LED_BLUE, GPIO_OUTPUT_ENABLE, GPIO_PIN_OUTPUT_HIGH);

    wiced_hal_gpio_set_pin_output( LED_GREEN, GPIO_PIN_OUTPUT_LOW);  //LOW es encenndido
    wiced_hal_gpio_set_pin_output( LED_BLUE, GPIO_PIN_OUTPUT_LOW);
    wiced_hal_gpio_set_pin_output( LED_RED, GPIO_PIN_OUTPUT_HIGH);


    //wiced_hal_gpio_set_pin_output(LED3, 1);

	//wiced_hal_gpio_configure_pin(PORT_INT_14, ( GPIO_INPUT_ENABLE | GPIO_PULL_UP_DOWN_NONE | GPIO_EN_INT_FALLING_EDGE ), GPIO_PIN_OUTPUT_HIGH );
	//wiced_hal_gpio_configure_pin(PORT_INT_26, ( GPIO_INPUT_ENABLE | GPIO_PULL_UP_DOWN_NONE | GPIO_EN_INT_FALLING_EDGE ), GPIO_PIN_OUTPUT_HIGH );
	//wiced_hal_gpio_register_pin_for_interrupt( PORT_INT_13, button_cback_4, 0 );
	//wiced_hal_gpio_register_pin_for_interrupt( PORT_INT_14, button_cback_26, 0 );
}


