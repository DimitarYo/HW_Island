
from serial import Serial
from time import sleep
import re

wait_time = 0.001
brake_time = 1.0

class Motor():
    def __init__(self, serial_path,baudr):
        self.ser =  Serial(serial_path,baudr)
        self.stepSpeed = 12000
        self.stepTime = 0.5

    def setStep(self,t,v):
        self.stepTime = t
        self.stepSpeed = v
    
    def sendCMD(self,cmd):
        self.ser.write(f"A{cmd}\r".encode(encoding='ascii',errors='ignore'))
        sleep(wait_time)
        print(self.ser.read_all())

    def step(self):
        self.sendCMD(f"ROR 0, {self.stepSpeed}")
        sleep(self.stepTime)
        self.sendCMD("MST 0")
        sleep(brake_time)

    def sendList(self,cmdList):
        for cmd in cmdList:
            if cmd.contains("sleep"):
                time = re.match("\\d*\\.\\d*",cmd)
                if time:
                    sleep(float(time[0]))
            self.sendCMD(cmd)



        


