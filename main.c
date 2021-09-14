#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "ov7670_reg.h"

static int ov7670_write(uint8_t addr, uint8_t value) {
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

static int ov7670_read(uint8_t addr, uint8_t *value) {
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

static int ov7670_init(void) {
#if 0
	int ret;

	// Bring clock down to ~1MHz
	ret = ov7670_write(OV7670_REG_CLKRC, CLKRC_SET_SCALE(1));
	if (ret) {
		return ret;
	}

	// Output QCIF YUV422
	ret = ov7670_write(OV7670_REG_COM7, COM7_SIZE_QCIF /*| (1 << 1)*/);
	if (ret) {
		return ret;
	}

	/* Enable scaling and downsample/crop/window */
	ov7670_write(OV7670_REG_COM3, 0x0C);
	/* Stop PCLK during Hblank */
	ov7670_write(OV7670_REG_COM10, (1 << 5));
#endif

	// Preset QCIF from OV7670 IM
	ov7670_write(OV7670_REG_CLKRC,  0x02); // Note: 0x01 in the IM
	ov7670_write(OV7670_REG_COM7,   0x00);
	ov7670_write(OV7670_REG_COM3,   0x0C);
	ov7670_write(OV7670_REG_COM14,  0x11);
	ov7670_write(OV7670_REG_XSCALE, 0x3A);
	ov7670_write(OV7670_REG_YSCALE, 0x35);
	ov7670_write(OV7670_REG_SCDCW,  0x11);
	ov7670_write(OV7670_REG_SCPCLK, 0xF1);
	ov7670_write(OV7670_REG_SCPDLY, 0x52);

	return 0;
}

#define PIN_VSYNC 2
#define PIN_HREF  3
#define PIN_PXCLK 4
#define PIN_D0    5

#define IMG_W 176
#define IMG_H 144

uint8_t img[IMG_W * IMG_H];

void main(void)
{
	stdio_init_all();

	clock_gpio_init(21, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 8);

	i2c_init(i2c0, 100000);
	gpio_set_function(0, GPIO_FUNC_I2C);
	gpio_set_function(1, GPIO_FUNC_I2C);
	gpio_pull_up(0);
	gpio_pull_up(1);

	gpio_set_dir_in_masked((0xff << PIN_D0) | (0x7 << PIN_VSYNC));

	int ret;
	uint8_t val = 0;

	sleep_ms(100);

	ret = ov7670_read(OV7670_REG_PID, &val);
	if (ret) {
		printf("Error reading PID: %d\n", ret);
	}
	if (val != 0x70) {
		printf("Unexpected PID\n");
	}

	ov7670_init();

	while (!gpio_get(PIN_VSYNC));

	int x, y, eof, idx;
	while (1) {
		// Wait for vsync
		while (gpio_get(PIN_VSYNC));

		y = 0;
		eof = 0;
		idx = 0;
		while (!eof) {
			// Wait for href or vsync
			while (1) {
				uint32_t pins = gpio_get_all();
				if (pins & (1 << PIN_VSYNC)) {
					eof = 1;
					break;
				}

				if (pins & (1 << PIN_HREF)) {
					break;
				}
			}

			if (eof) {
				// vsync started
				break;
			}


			// Count pixels
			x = 0;
			idx = y * IMG_W;
			while (gpio_get(PIN_HREF)) {
				while (gpio_get(PIN_PXCLK));
				while (!gpio_get(PIN_PXCLK));
				x++;
				if (!(x & 1)) {
					uint32_t pins = gpio_get_all();
					img[idx] = (pins >> PIN_D0) & 0xff;
					idx++;
				}
				while (gpio_get(PIN_PXCLK));
			}
			y++;
		}
		int i, j;
		printf("P2\n%d %d\n255\n", IMG_W, IMG_H);

		for (i = 0; i < IMG_H; i++) {
			for (j = 0; j < IMG_W; j++) {
				printf("%d ", img[i * IMG_W + j]);
			}
			printf("\n");
		}
	}
}
