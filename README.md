# TP - Bus et Réseaux

ESE NOEL/PENSIVY

Le but de cette série de TP est de mettre en place l'ensemble des composants suivant:
- capteur IMU 10DOF (BMP280 et MPU9250)
- moteur pas à pas
- transceiver CAN
- STM32
- PI Zero
- Routeur WIFI
 
Ce document fournit l'interfaçage des différents éléments entre eux pour chaque TP.

## TP1: Interrogation des capteurs par le bus I²C

Le port SDA du capteur est connecté au PB9 du STM32 (I2C1_SDA).<br />
Le port SCL du capteur est connecté au PB8 du STM32 (I2C1_SCL).<br />
Les masses du capteur et du STM32 sont reliées entre elles.

Le port PA0 (UART4_TX) du STM32 est connecté au port GPIO 15 (RX) de la raspberry.<br />
Le port PA1 (UART4_RX) du STM32 est connecté au port GPIO 14 (TX) de la raspberry.<br />
Les masses du STM32 et de la raspberry sont reliées entre elles.

## TP2: Interfaçage STM32 <-> Raspberry Pi

Même interfaçage raspberry/STM32/capteur que le TP1.

## TP3: Interface Web sur Raspberry Pi

Même interfaçage raspberry/STM32/capteur que le TP1.

## TP4: Interface API Rest & pilotage d'actionneur par bus CAN

Le port SDA du capteur est connecté au PB11 du STM32 (I2C2_SDA).<br />
Le port SCL du capteur est connecté au PB10 du STM32 (I2C2_SCL).<br />
Les masses du capteur et du STM32 sont reliées entre elles.

Même interfaçage entre la raspberrry et la STM32 que le TP1.

## TP5: Integration 12C - Serial - REST - CAN

Même interfaçage raspberry/STM32/capteur que le TP4.

