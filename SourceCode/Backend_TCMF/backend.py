from flask import Flask, request
from flask_cors import CORS, cross_origin
from datetime import datetime
from hashlib import sha256
import json

#========== MCU ==========#
from practicum import findDevices,McuBoard
from time import sleep

device = findDevices()
b = McuBoard(device[0])

#========== CONFIG PASSWORD ==========#
def encrypt(password):
    h = sha256()
    password_binary = f'{password}'.encode('utf-8')
    h.update(password_binary)
    hash = h.hexdigest()
    return hash

f = open("config.json")
data = json.load(f)
HARDWAREPASSWORD = data["hardware_password"]
FRONTENDPASSWORD = data["frontend_password"]
f.close()

#========== MAIN ==========#
app = Flask(__name__)
cors = CORS(app, resource={r"/": {"origins": "*"}})
#CORS(app)

@app.route('/enter_password', methods=["POST"])
@cross_origin()
def enter_password():
    data = request.json
    if encrypt(data["password"]) == FRONTENDPASSWORD:
        with open("Double_lock_safebox.log", 'a') as log_file:
            parsed_line = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))+" login success from website"+"\n"
            log_file.write(parsed_line)
        b.usbWrite(3, value=1)
        return {"result": "login success"}
    else:
        with open("Double_lock_safebox.log", 'a') as log_file:
            parsed_line = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))+" login fail from website"+" password is "+ data["password"]+"\n"
            log_file.write(parsed_line)
        b.usbWrite(3, value=0)
        return {"result": "login fail"}

@app.route('/check', methods=["GET"])
@cross_origin()
def check():
    tmp = b.usbRead(2, length=8)
    read_hardware_password = ""
    for i in tmp:
        read_hardware_password = read_hardware_password + str(i)
    if encrypt(read_hardware_password) == HARDWAREPASSWORD:
        with open("Double_lock_safebox.log", 'a') as log_file:
            parsed_line = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))+" login success from hardware"+"\n"
            log_file.write(parsed_line)
        return {"check": 1}
    elif read_hardware_password[0] != "0":
        with open("Double_lock_safebox.log", 'a') as log_file:
            parsed_line = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))+" login fail from hardware"+" password is "+ read_hardware_password +"\n"
            log_file.write(parsed_line)
        b.usbWrite(3, value=0)
        return {"check": 0}
    else:
        with open("Double_lock_safebox.log", 'a') as log_file:
            parsed_line = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))+" no password from hardware"+"\n"
            log_file.write(parsed_line)
        return {"check": 0}
  
if __name__ == '__main__':
    app.run(host='0.0.0.0', port='3000', debug=True)
