/*
 * fonctions.c
 *
 *  Created on: 20 oct. 2021
 *      Author: pensi
 */

#include "fonctions.h"

BMP280_S32_t t_fine;

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;

//Identification du BMP280
void Get_id(){
	uint8_t buf[1];
	HAL_StatusTypeDef ret;
	buf[0] = 0xD0;

	ret = HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR, buf, 1, HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Tx\r\n");
	}

	ret = HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR, buf, 1,HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Rx\r\n");
	}

	printf("L'ID est 0x%x\r\n", buf[0]);
}

int BMP280_Write_Reg(uint8_t reg, uint8_t value) {
	uint8_t buf[3];
	HAL_StatusTypeDef ret;

	buf[0] = reg;
	buf[1] = value;
	ret = HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR, buf, 2, HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Tx\r\n");
	}

	ret = HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR, buf, 1, HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Rx\r\n");
	}

	if (buf[0] == value) {
		return 0;
	} else {
		return 1;
	}
}

uint8_t* BMP280_Read_Reg(uint8_t reg, uint8_t length) {
	uint8_t *buf;
	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDR, &reg, 1, HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Tx\r\n");
	}

	buf = (uint8_t*) malloc(length);
	ret = HAL_I2C_Master_Receive(&hi2c1, BMP280_ADDR, buf, length,HAL_MAX_DELAY);
	if (ret != 0) {
		printf("Erreur Rx\r\n");
	}

	return buf;
}

//Config du BMP280
void Set_config(){
	HAL_StatusTypeDef ret;
	uint8_t val = 0x57;
	uint8_t reg = 0xF4;

	ret = BMP280_Write_Reg(reg, val);
	if (ret == 0) {
		printf("Config Ok\r\n");
	} else {
		printf("Erreur Config\r\n");
	}
}

void Get_calib(){
	uint8_t *buf;
	uint8_t reg = 0x88;
	uint8_t length = 24;

	buf = BMP280_Read_Reg(reg, length);
//	dig_T1 = ((uint16_t)buf[0] << 4) | (buf[1] >> 4);
//	dig_T2 = ((int16_t)buf[2] << 4) | (buf[3] >> 4);
//	dig_T3 = ((int16_t)buf[4] << 4) | (buf[5] >> 4);
//	dig_P1 = ((uint16_t)buf[6] << 4) | (buf[7] >> 4);
//	dig_P2 = ((int16_t)buf[8] << 4) | (buf[9] >> 4);
//	dig_P3 = ((int16_t)buf[10] << 4) | (buf[11] >> 4);
//	dig_P4 = ((int16_t)buf[12] << 4) | (buf[13] >> 4);
//	dig_P5 = ((int16_t)buf[14] << 4) | (buf[15] >> 4);
//	dig_P6 = ((int16_t)buf[16] << 4) | (buf[17] >> 4);
//	dig_P7 = ((int16_t)buf[18] << 4) | (buf[19] >> 4);
//	dig_P8 = ((int16_t)buf[20] << 4) | (buf[21] >> 4);
//	dig_P9 = ((int16_t)buf[22] << 4) | (buf[23] >> 4);
	dig_T1 = buf[0] | buf[1] << 8;
	dig_T2 = buf[2] | buf[3] << 8;
	dig_T3 = buf[4] | buf[5] << 8;
	dig_P1 = buf[6] | buf[7] << 8;
	dig_P2 = buf[8] | buf[9] << 8;
	dig_P3 = buf[10] | buf[11] << 8;
	dig_P4 = buf[12] | buf[13] << 8;
	dig_P5 = buf[14] | buf[15] << 8;
	dig_P6 = buf[16] | buf[17] << 8;
	dig_P7 = buf[18] | buf[19] << 8;
	dig_P8 = buf[20] | buf[21] << 8;
	dig_P9 = buf[22] | buf[23] << 8;

	free(buf);
}

BMP280_S32_t Get_T() {
	uint8_t *buf;
	BMP280_S32_t adc_T;
	uint8_t reg = 0xFA;
	uint8_t length = 3;

	buf = BMP280_Read_Reg(reg, length);

	adc_T = ((BMP280_S32_t) (buf[0]) << 12) | ((BMP280_S32_t) (buf[1]) << 4)
			| ((BMP280_S32_t) (buf[2]) >> 4);

	free(buf);

	return adc_T;
}

BMP280_S32_t Get_P() {
	uint8_t *buf;
	BMP280_S32_t adc_P;
	uint8_t reg = 0xF7;
	uint8_t length = 3;

	buf = BMP280_Read_Reg(reg, length);

	adc_P = ((BMP280_S32_t) (buf[0]) << 12) | ((BMP280_S32_t) (buf[1]) << 4)
			| ((BMP280_S32_t) (buf[2]) >> 4);

	free(buf);

	return adc_P;
}

BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T){
	BMP280_S32_t var1, var2, T;
	var1  = ((((adc_T>>3)-((BMP280_S32_t)dig_T1<<1))) * ((BMP280_S32_t)dig_T2)) >> 11;
	var2  = (((((adc_T>>4)-((BMP280_S32_t)dig_T1)) * ((adc_T>>4)-((BMP280_S32_t)dig_T1))) >> 12) *((BMP280_S32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T  = (t_fine * 5 + 128) >> 8;
	return T;
}

BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P){
	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)t_fine)-128000;
	var2 = var1 * var1 * (BMP280_S64_t)dig_P6;
	var2 = var2 + ((var1*(BMP280_S64_t)dig_P5)<<17);
	var2 = var2 + (((BMP280_S64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (BMP280_S64_t)dig_P3)>>8) + ((var1 * (BMP280_S64_t)dig_P2)<<12);
	var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BMP280_S64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BMP280_S64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)dig_P7)<<4);
	return (BMP280_U32_t)p;
}
