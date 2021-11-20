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
#include "string.h"

typedef uint32_t BMP280_U32_t;
typedef int32_t BMP280_S32_t;
typedef int64_t BMP280_S64_t;

static const char LIGNE[7] = "STM32> ";

static const char SET_K[6] = "SET_K\0";
static const char GET_K[6] = "GET_K\0";
static const char GET_A[6] = "GET_A\0";
static const char GET_P[6] = "GET_P\0";
static const char GET_T[6] = "GET_T\0";


static const uint8_t BMP280_ADDR = 0x77 << 1;
static const uint8_t ENTER = 0x0D;
static const uint8_t DEL = 0x7F;

extern char Commande[100];
extern int K;
char K1[10];
extern I2C_HandleTypeDef hi2c2;

void Ligne_Init(UART_HandleTypeDef *huart);
void Commande_exec(int i);
void Get_id();
int BMP280_Write_Reg(uint8_t reg, uint8_t value);
uint8_t* BMP280_Read_Reg(uint8_t reg, uint8_t length);
void Set_config();
void Get_calib();
BMP280_S32_t Get_T();
BMP280_S32_t Get_P();
void Set_K();
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T);
BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P);
