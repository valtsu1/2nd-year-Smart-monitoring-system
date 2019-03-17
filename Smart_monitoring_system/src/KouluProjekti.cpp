/*
 ===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#define I2C_MODE    (0)
#define I2C_CLK_DIVIDER         (40)
#define I2C_BITRATE         (55000)
static I2CM_XFER_T i2cmXferRec;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include <cstring>
#include <cstdio>
#include <string>

#include "ModbusMaster.h"
#include "ModbusRegister.h"
#include "LpcUart.h"
#include "MotorController.h"

#include "DigitalIoPin.h"
#include "LiquidCrystal.h"
#include "pSensor.h"

/***************************
 * Private types/enumerations/variables
 **************************/

/***************************
 * Public types/enumerations/variables
 **************************/

/***************************
 * Private functions
 **************************/

/***************************
 * Public functions
 **************************/
static volatile int counter;
static volatile uint32_t systicks;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void) {
	systicks++;
	if (counter > 0)
		counter--;
}
#ifdef __cplusplus
}
#endif

void Sleep(int ms) {
	counter = ms;
	while (counter > 0) {
		__WFI();
	}
}

/* this function is required by the modbus library */
uint32_t millis() {
	return systicks;
}

/**
 * @brief	Main UART program body
 * @return	Always returns 1
 */
//automatic mode
void autoMode(MotorController *moto, LiquidCrystal *lcd, pSensor *p,
		DigitalIoPin *b1, DigitalIoPin *b2, DigitalIoPin *b3) {
	int value;
	int target = 70;
	int offset = 2;
	int increment = 1;
	int lowerLimit = 0;
	int upperLimit = 120;
	int timelimit = 20;
	int timer = 0;
	std::string clear;
	std::string out;
	bool modeActive = true;
	moto->setSpeed(3000);

	for (int i = 0; i < 32; ++i) {
		clear += " ";
	}

	while (modeActive) {
		//int pReading = p.getReading();
		if (b1->read()) {
//			while (b1->read()) {
//
//			}
			target += increment;
			timer = 0;
		}
		if (b2->read()) {
			modeActive = false;
		}
		if (b3->read()) {
//			while (b3->read()) {
//
//			}
			target -= increment;
			timer = 0;
		}

		if (target < lowerLimit)
			target = lowerLimit;
		if (target > upperLimit)
			target = upperLimit;

		value = p->getReading();
		moto->setFreq(value, target);
		out = "AM ";
		out += "to " + std::to_string(target) + " is " + std::to_string(value);
		if (value < target + offset && value > target - offset) {
			timer = 0;
		}
		if (timer > timelimit) {
			out += "  took too long";
		}
		lcd->Print(clear);
		lcd->Print(out);

		Sleep(1000);
		++timer;
	}
}

//manual mode
void manualMode(MotorController *moto, LiquidCrystal *lcd, pSensor *p,
		DigitalIoPin *b1, DigitalIoPin *b2, DigitalIoPin *b3) {

	int value = 0;
	int increment = 2000;
	int lowerLimit = 0;
	int upperLimit = 20000;
	std::string clear;
	std::string out;
	bool modeActive = true;

	for (int i = 0; i < 32; ++i) {
		clear += " ";
	}

	while (modeActive) {
		//int pReading = p.getReading();
		if (b1->read()) {
			while (b1->read()) {

			}
			value += increment;
		}
		if (b2->read()) {
			modeActive = false;
		}
		if (b3->read()) {
			while (b3->read()) {

			}
			value -= increment;
		}

		if (value < lowerLimit)
			value = lowerLimit;
		if (value > upperLimit)
			value = upperLimit;

		int power = moto->setSpeed(value);
		out = "Manual Mode: " + std::to_string(power);
		if (power < 10) {
			out += "  pressure " + std::to_string(p->getReading());
		} else if (power >= 10 && power < 100) {
			out += " pressure " + std::to_string(p->getReading());
		} else if (power >= 100) {
			out += "pressure " + std::to_string(p->getReading());
		}
		lcd->Print(clear);
		lcd->Print(out);
		Sleep(1);
	}
}

int main(void) {

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	Chip_RIT_Init(LPC_RITIMER);
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif
	LpcPinMap none = { -1, -1 }; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8
			| UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1, false, txpin, rxpin,
			none, none };
	LpcUart dbgu(cfg);

	/* Set up SWO to PIO1_2 */
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2); // Needed for SWO printf

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

	Board_LED_Set(0, false);

	Chip_RIT_Init(LPC_RITIMER);

	printf("Started\n"); // goes to ITM console if retarget_itm.c is included
	dbgu.write("Hello, world\n");

	int deviceAddress = 0x40;
	int cmd = 0xF1;
	I2C_config I2Cconf;
	pSensor sensor(I2Cconf, deviceAddress, cmd);

	DigitalIoPin rs(0, 8, false, false, false);
	DigitalIoPin en(1, 6, false, false, false);
	DigitalIoPin d4(1, 8, false, false, false);
	DigitalIoPin d5(0, 5, false, false, false);
	DigitalIoPin d6(0, 6, false, false, false);
	DigitalIoPin d7(0, 7, false, false, false);

	DigitalIoPin b1(0, 0, true, true, true);
	DigitalIoPin b2(1, 3, true, true, true);
	DigitalIoPin b3(0, 9, true, true, true);

	LiquidCrystal lcd(&rs, &en, &d4, &d5, &d6, &d7);
	lcd.setCursor(0, 0);

	MotorController moto(1);
	std::string clear;
	for (int i = 0; i < 32; ++i) {
		clear += " ";
	}
	Sleep(1000);
	while (1) {

		lcd.Print("manual mode leftauto mode right");
		if (b1.read()) {
			lcd.print(clear);
			while (b1.read()) {
				lcd.Print("Activating      auto mode");
			}

			autoMode(&moto, &lcd, &sensor, &b1, &b2, &b3);
		}
		if (b2.read()) {
			lcd.Print(clear);
		}
		if (b3.read()) {
			lcd.Print(clear);
			while (b3.read()) {
				lcd.Print("Activating      manual mode");
			}

			manualMode(&moto, &lcd, &sensor, &b1, &b2, &b3);
		}

	}

	return 1;
}
