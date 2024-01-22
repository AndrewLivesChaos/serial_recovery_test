#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec ledRed = GPIO_DT_SPEC_GET(DT_NODELABEL( led_red ), gpios);
static const struct gpio_dt_spec ledBlue = GPIO_DT_SPEC_GET(DT_NODELABEL( led_blue ), gpios);
static const struct gpio_dt_spec ledGreen = GPIO_DT_SPEC_GET(DT_NODELABEL( led_green ), gpios);

void main(void)
{
    int ret;

    if (!device_is_ready(ledRed.port) || !device_is_ready(ledBlue.port) || !device_is_ready(ledGreen.port)) {
        return;
    }

    ret = gpio_pin_configure_dt(&ledRed, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return;
    }

    ret = gpio_pin_configure_dt(&ledBlue, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return;
    }

    ret = gpio_pin_configure_dt(&ledGreen, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return;
    }

    while (1) {
        ret = gpio_pin_toggle_dt(&ledRed);
        if (ret < 0) {
            return;
        }
        k_msleep(1000);
    }
}