import serial
import time

def UART_WR(ser,cmd):
	cmd2=cmd+'\r'
	cmd3=cmd2.encode()
	for c in cmd3:
		ser.write(c)
		time.sleep(0.01)
	s=ser.read(100)
	print(s)

def GET_T(ser):
	UART_WR(ser,'GET_T')

def GET_P(ser):
	UART_WR(ser,'GET_P')

with serial.Serial('/dev/ttyAMA0',115200,timeout=1) as ser:
	print('Getting T ...')
	GET_T(ser)
	print('Getting P ...')
	GET_P(ser)
	ser.close()
