/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2023 Conexio Technologies, Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <stdio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN		DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN		0
#define FLAGS	0
#endif

#if defined(CONFIG_STRATUS_SHIELD)
/* The devicetree node identifier for the "led1" alias. */
#define LED1_NODE DT_ALIAS(led1)
#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED1	DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1	DT_GPIO_PIN(LED1_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an Orange LED 1. */
#error "Unsupported board: led1 devicetree alias is not defined"
#define LED1	""
#define PIN1	0
#endif
#endif

#ifndef FLAGS
#define FLAGS	0
#endif


int main(void)
{
	printf("Hello from %s\n", CONFIG_BOARD);
    
    const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
	bool led_is_on = true;
	int ret_0;

	if (!device_is_ready(led_0.port)) {
		return 0;
	}

#if defined(CONFIG_STRATUS_SHIELD)
	const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
	int ret_1;
	if (!device_is_ready(led_1.port)) {
		return 0;
	}
#endif

	ret_0 = gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret_0 < 0) {
		return 0;
	}

#if defined(CONFIG_STRATUS_SHIELD)
	ret_1 = gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret_1 < 0) {
		return 0;
	}
#endif

    /* main loop */
	while (1) {
		/* LED 0 on main board */
		gpio_pin_set(led_0.port, PIN, (int)led_is_on);

#if defined(CONFIG_STRATUS_SHIELD)
		/* LED 1 on Stratus shield */
		gpio_pin_set(led_1.port, PIN1, (int)led_is_on);
#endif

		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
	}
}
