#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("Error, gpio is not ready\n");
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		LOG_ERR("Error configuring gpio: %d\n", ret);
		return 0;
	}

	LOG_DBG("LED configured and ready to blink\n");
	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			LOG_ERR("Error toggling led\n");
			return 0;
		}

		led_state = !led_state;
		printf("LED is now: %s\n", led_state ? "ON" : "OFF");

		k_msleep(1000);
	}
	return 0;
}
