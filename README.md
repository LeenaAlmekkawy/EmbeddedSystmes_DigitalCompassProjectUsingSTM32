# Digital Compass Project

This project implements a digital compass using an STM32f401CCU6 microcontroller, the ST7735 TFT display module, and the GY-271 magnetometer sensor.

## Features

- Displays the current compass heading on a 1.8" ST7735 TFT display
- Utilizes the GY-271 magnetometer sensor to measure the earth's magnetic field and determine the compass direction
- Includes a calibration routine to compensate for magnetic field distortions

## Hardware Components

- STM32 microcontroller
- ST7735 1.8" TFT display module
- GY-271 magnetometer sensor

## Software Components

- HAL (Hardware Abstraction Layer) drivers for the ST7735 TFT display and the GY-271 magnetometer
- MCAL (Microcontroller Abstraction Layer) drivers for SPI, I2C, and GPIO
- Calibration code implemented in C, using a Python script for the calibration process

## Calibration

The digital compass requires calibration to account for local magnetic field distortions. To know more information about the calibration process using this link:-
[Magnetometer Compass with Raspberry PI Pico: GY-271 HMC5883L wiring and use with MicroPython](https://peppe8o.com/magnetometer-compass-with-raspberry-pi-pico-gy-271-hmc5883l-wiring-and-use-with-micropython/)

## Usage

1. Connect the ST7735 TFT display and the GY-271 magnetometer to the STM32 development board.
2. Build and upload the digital compass firmware to the STM32 board.
3. The compass heading will be displayed on the TFT screen, updated in real-time.

## Code Structure

The project is organized into the following folders and files:

- `HAL/`: Contains the Hardware Abstraction Layer (HAL) drivers for the ST7735 TFT display and the GY-271 magnetometer.
- `MCAL/`: Contains the Microcontroller Abstraction Layer (MCAL) drivers for SPI, I2C, and GPIO.
- `main.c`: The main application file that integrates the HAL and MCAL layers to implement the digital compass functionality.
