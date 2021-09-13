/*
 * Captures an image from an 0V7670 camera (without FIFIO)
 * frame.bmp must be copied to the mbed USB disk, it is used to provide a 
 * valid .bmp header for the output file.
 *
 * Saves output frame to OUT.BMP
 */

#include "mbed.h"
#include "ov7670.h"

/*
 * Parallel camera data port mask
 * mbed pin numbers: MSB [ p27, p28, p5, p6, p7, p8, p29, p30 ] LSB
 */
#define DATA_MASK 0x00000FF0
/* Size of bitmap file header to copy */
#define BMP_HEADER_SIZE 0x8A
/* Image resolution */
#define HRES 172
#define VRES 144
#define LINE_COUNT 144

DigitalOut myled(LED1);

/* Control (I2C) bus for the camera */
I2C sccb(p9, p10);
/* Parallel data in */
PortIn data_port(Port0, DATA_MASK);
/* Camera sync signals */
DigitalIn Vsync(p24);
InterruptIn Href(p26);
InterruptIn Pclk(p25);

/* Mount USB filesystem at /local */
LocalFileSystem local("local");

/* Global volatiles for use by the ISRs */
volatile bool capturing = false;
volatile bool enabled = false;
volatile int byte_count = 0;
volatile int line_no = 0;
volatile int want_line = 0;
volatile int stop_line = 1;
volatile int pixel_count = 0;

/* Buffer to store pixel data in */
uint8_t line_buffer[HRES * VRES] = {0};

int OV7670_WriteReg(uint8_t addr, uint8_t value) {
	int ret;

	sccb.start();
	ret = sccb.write(OV7670_W_ADDR);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	ret = sccb.write(addr);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	ret = sccb.write(value);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	sccb.stop();
	return ret;
}

int OV7670_ReadReg(uint8_t addr, uint8_t *value) {
	int ret;

	sccb.start();
	ret = sccb.write(OV7670_W_ADDR);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	ret = sccb.write(addr);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	sccb.stop();

	sccb.start();
	ret = sccb.write(OV7670_R_ADDR);
	if (!ret) {
		sccb.stop();
		return 0;
	}
	*value = sccb.read(0);
	sccb.stop();

	return ret;
}

void OV7670_Init() {     
	/* 
	 * Disable PLL multiplier and divide clock by 16.
	 * Expect PCLK to be 1 MHz now
	 */
	OV7670_WriteReg(REG_CLKRC, CLKRC_SET_SCALE(9));
	/* Enable scaling and downsample/crop/window */
	OV7670_WriteReg(REG_COM3, 0x0C);
	/* Set QCIF image size (176x144) and RGB color */ 
	OV7670_WriteReg(REG_COM7, COM7_SIZE_QCIF | COM7_FMT_RGB);
	/* Stop PCLK during Hblank */
	OV7670_WriteReg(REG_COM10, (1 << 5));
	/* Set output range 0 - 255 and format RGB565 */
	OV7670_WriteReg(REG_COM15, COM15_RANGE_HIGH | COM15_RGB565);

	data_port.mode(PullNone);
}

/* Fires when HREF goes high - i.e. start of line */
void startLine() {    
	if (!capturing && (line_no == want_line) && enabled) {
		/*
		 * This is the line we're after and we aren't capturing
		 * already so we should restart the pixel counter and start
		 * capturing
		 */
		byte_count = 0;
		pixel_count = 0;
		capturing = true;
	}

	line_no++;
}

/* Fires when HREf goes low - i.e. end of line */
void stopLine() {
	/* 
	 * If capturing multiple lines at a time, could check a
	 * "stop_line" variable here to see if we should stop capturing
	 */
	if (capturing && (stop_line == line_no)) {
		/* Stop capturing */
		capturing = false;
	}
}

/* Fires on PCLK rising edge (data valid) */
void getPclk() {
	if (capturing) {
		/* 
		 * Save the data in the buffer. Needs to be shifted
		 * down because data mask = 0xFF0
		 */
		if (byte_count++ % 2){
			line_buffer[pixel_count++] = data_port >> 4;
		}
	}
}

int main() {
	int ret;
	uint8_t val;
	printf("Hello\r\n");

	ret = OV7670_ReadReg(REG_PID, &val);
	if (ret) {
		printf("Read Successful\r\n");
	} else {
		printf("Unable to read PID. Check comms, XCLK...\r\n");
	}
	printf("Product ID: 0x%02x\r\n", val);

	OV7670_Init();

	/* Init IO pins */
	Vsync.mode(PullNone);
	Href.mode(PullNone);
	Pclk.mode(PullNone);

	/* Set up interrupts */
	Pclk.rise(&getPclk);
	Href.rise(&startLine);
	Href.fall(&stopLine);

	while(1) {
		printf("Press a key to start capture\r\n");
		getchar();

		FILE *out = fopen("/local/out.bmp", "w");
		FILE *in = fopen("/local/frame.bmp", "r");

		/* Copy the BMP header to the output file */
		char buf;
		for (int i = 0; i < BMP_HEADER_SIZE; i++){
			fread(&buf, 1, 1, in);
			fwrite(&buf, 1, 1, out);
		}
		fclose(in);        

		printf("Getting picture\r\n");

		enabled = false;

		for (want_line = 0, stop_line = LINE_COUNT; want_line < VRES; want_line += LINE_COUNT, stop_line += LINE_COUNT) {

			/* Wait for start-of-frame */
			while(!Vsync);
			enabled = true;
			/* Reset line counter */
			line_no = 0;

			/* 
			 * This will be set true by the startLine interrupt handler
			 * when the correct line (set by want_line) is reached
			 */
			capturing = false;

			/* Wait to reach the correct line */
			while(!capturing);

			/* 
			 * Wait until the line is captured. capturing is cleared
			 * by the stopLine interrupt handler
			 */
			while(capturing);
			enabled = false;

			printf("Line %i finished. Got %i bytes\r\n", want_line, pixel_count);
			/* Write this line to file */
			for (int i = 0; i < pixel_count; i++) {
				uint16_t pixel = 0;
				uint8_t blue = line_buffer[i] & 0x1f;
				pixel = blue + (blue << 6) + (blue << 11);
				/* 
				 * Have to swap the bytes, because data from camera
				 * is MSByte first, and file is LSByte first
				 */

				fwrite(&pixel, 2, 1, out);
			}
		}
		printf("Done\r\n");
		fclose(out);
	}
}
