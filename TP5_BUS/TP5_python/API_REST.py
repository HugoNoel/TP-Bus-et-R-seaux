from flask import Flask, jsonify, abort, render_template, request
import json
import serial
import time

def UART_WR(ser,cmd):
	cmd2=cmd+'\r'
	cmd3=cmd2.encode()
	for c in cmd3:
		ser.write(c)
		time.sleep(0.01)
	s=ser.read(100)
	return s

def GET_T(ser):
	UART_WR(ser,'GET_T')

def GET_P(ser):
	UART_WR(ser,'GET_P')

app = Flask(__name__)

T=[]
T_index=-1
P=[]
P_index=-1
K=1

@app.route('/temp/', methods=['GET','POST'])
@app.route('/temp/<int:index>',methods=['GET','DELETE'])
def temp(index=None):
	global T
	global T_index
	resp={}
	if index == None:
		if request.method == 'POST':
			with serial.Serial('/dev/ttyAMA0',115200,timeout=1) as ser:
				s = GET_T(ser)
				T_index=T_index+1
				ser.close()
			T.append(s)
			resp["T"]=s
		if request.method == 'GET':
			for i in range(T_index+1):
				Ti="T%d" % T_index
				resp[Ti]=T[i]
	else:
		if request.method == 'GET':
			try:
				Ti="T%d" % index
				resp[Ti]= T[index]
			except Exception:
				abort(404)
		if request.method == 'DELETE':
			try:
				T=T[0:index]+T[index+1:]
				T_index=T_index-1
				for i in range(T_index+1):
					Ti="T%d" % T_index
					resp[Ti]=T[i]
			except Exception:
				abort(404)
	return jsonify(resp)

@app.route('/pres/', methods=['GET','POST'])
@app.route('/pres/<int:index>',methods=['GET','DELETE'])
def temp(index=None):
	global P
	global P_index
	resp={}
	if index == None:
		if request.method == 'POST':
			with serial.Serial('/dev/ttyAMA0',115200,timeout=1) as ser:
				s = GET_P(ser)
				P_index=P_index+1
				ser.close()
			P.append(s)
			resp["P"]=s
		if request.method == 'GET':
			for j in range(P_index+1):
				Pj="P%d" % P_index
				resp[Pj]=P[j]
	else:
		if request.method == 'GET':
			try:
				Pj="P%d" % index
				resp[Pj]= P[index]
			except Exception:
				abort(404)
		if request.method == 'DELETE':
			try:
				P=P[0:index]+P[index+1:]
				P_index=P_index-1
				for j in range(P_index+1):
					Pj="P%d" % P_index
					resp[Pj]=P[j]
			except Exception:
				abort(404)
	return jsonify(resp)

@app.route('/scale/', methods=['GET'])
@app.route('/temp/<int:index>',methods=['POST'])
def scale(index=None):
	global K
	resp={}
	if index == None:
		if request.method == 'GET':
			resp["K"]=K
	else:
		if request.method == 'POST':
			K = index
			resp["K"]=K
	return jsonify(resp)

@app.route('/angle/', methods=['GET'])
def scale():
	global K
	global T
	global T_index
	resp={}
	if request.method == 'GET':
		try:
			A=K*int(T[T_index])
			resp["Angle"]=A
		except Exception:
			abort(404)
	return jsonify(resp)

@app.errorhandler(404)
def page_not_found(error):
	return render_template('page_not_found.html'), 404