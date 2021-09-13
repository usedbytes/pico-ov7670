#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"

#include "ov7670_reg.h"

int ov7670_write(uint8_t addr, uint8_t value) {
	int ret;
	static uint8_t data[2];

	data[0] = addr;
	data[1] = value;
	ret = i2c_write_blocking(i2c0, OV7670_ADDR, data, 2, false);
	if (ret != 2) {
		return -1;
	}

	return 0;
}

int ov7670_read(uint8_t addr, uint8_t *value) {
	int ret = i2c_write_blocking(i2c0, OV7670_ADDR, &addr, 1, false);
	if (ret != 1) {
		return -1;
	}

	ret = i2c_read_blocking(i2c0, OV7670_ADDR, value, 1, false);
	if (ret != 1) {
		return -2;
	}

	return 0;
}

void main(void)
{
	stdio_init_all();

	clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 10);

	i2c_init(i2c0, 100000);
	gpio_set_function(0, GPIO_FUNC_I2C);
	gpio_set_function(1, GPIO_FUNC_I2C);
	gpio_pull_up(0);
	gpio_pull_up(1);

	int ret;
	uint8_t val;

	while (1) {
		printf("Hello, World!\n");

		ret = ov7670_read(OV7670_REG_PID, &val);
		if (ret) {
			printf("Error reading PID: %d\n", ret);
		} else {
			printf("Product ID: 0x%02x\n", val);
		}

		ret = ov7670_read(OV7670_REG_VER, &val);
		if (ret) {
			printf("Error reading VER: %d\n", ret);
		} else {
			printf("Ver: 0x%02x\n", val);
		}

		sleep_ms(1000);
	}
}
