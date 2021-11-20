from flask import Flask, jsonify, abort, render_template, request
import json

app = Flask(__name__)

@app.route('/')
def hello_world():
	return 'Hello, World!\n'

welcome="Welcome to 3ESE API!"

#@app.route('/api/welcome/')
#def api_welcome():
#	return welcome

@app.route('/api/welcome/', methods=['GET','POST','DELETE'])
@app.route('/api/welcome/<int:index>',methods=['GET','POST','PUT','PATCH','DELETE'])
def api_welcome_index(index=None):
	global welcome
	resp={
		"method": request.method,
		"url": request.url,
		"args": request.args,
		"headers": dict(request.headers),
	}
	if index == None:
		if request.method == 'POST':
			welcome=request.args["create"]
			resp["create"]=request.args["create"]
			return jsonify(resp)
		if request.method == 'GET':
			resp["retreive"]=welcome
			return jsonify(resp)
		if request.method == 'DELETE':
			welcome=""
			resp["delete"]=welcome
			return jsonify(resp)
	else:
		if request.method == 'GET':
			try:
				#welcome_index=jsonify({"index": index, "val": welcome[index]})
				resp["retreive"]=welcome[index]
				return jsonify(resp)
			except Exception:
				abort(404)
		if request.method == 'PUT':
			try:
				w_split=welcome.split()
				w_split.insert(index,request.args["update"])
				welcome=' '.join(w_split)
				resp["update"]=welcome
				return jsonify(resp)
			except Exception:
				abort(404)
		if request.method == 'PATCH':
			w_list=list(welcome)
			w_list[index]=request.args["update"]
			welcome="".join(w_list)
			try:
				resp["update"]=welcome
				return jsonify(resp)
			except Exception:
				abort(404)
		if request.method == 'DELETE':
			try:
				welcome=welcome[0:index]+welcome[index+1:]
				resp["delete"]=welcome
				return jsonify(resp)
			except Exception:
				abort(404)
	return jsonify(resp)

@app.errorhandler(404)
def page_not_found(error):
	return render_template('page_not_found.html'), 404

@app.route('/api/request/', methods=['GET', 'POST'])
@app.route('/api/request/<path>', methods=['GET','POST'])
def api_request(path=None):
	resp = {
		"method": request.method,
		"url": request.url,
		"path" : path,
		"args": request.args,
		"headers": dict(request.headers),
	}

	if request.method == 'POST':
		resp["POST"] = {
			"data": request.get_json(),
			}
	return jsonify(resp)
