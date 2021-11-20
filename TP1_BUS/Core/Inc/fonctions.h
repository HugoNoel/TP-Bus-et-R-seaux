/*
 * fonctions.h
 *
 *  Created on: 20 oct. 2021
 *      Author: pensi
 */

#ifndef INC_FONCTIONS_H_
#define INC_FONCTIONS_H_

#endif /* INC_FONCTIONS_H_ */

#include "stm32l4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"

typedef uint32_t BMP280_U32_t;
typedef int32_t BMP280_S32_t;
typedef int64_t BMP280_S64_t;

static const uint8_t BMP280_ADDR = 0x77 << 1;

extern I2C_HandleTypeDef hi2c1;

void Get_id();
int BMP280_Write_Reg(uint8_t reg, uint8_t value);
uint8_t* BMP280_Read_Reg(uint8_t reg, uint8_t length);
void Get_calib();
void Set_config();
BMP280_S32_t Get_T();
BMP280_S32_t Get_P();
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T);
BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P);
