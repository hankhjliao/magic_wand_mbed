import numpy as np
import serial
import sys
import time

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)

data = []
tmp = []
while True:
  try:
    line = s.readline().decode()
    if '---start---' in line:
      tmp.clear()
      print("---")
    elif '---stop---' in line:
      print("---")
      if len(tmp) > 0:
        print(tmp)
        data.append(tmp.copy())
      print("Data Num =", len(data))
    elif '---delete---' in line:
      if len(data) > 0:
        data.pop()
      print("Data Num =", len(data))
    else:
      print(line, end="")
      tmp.append(line)
  except KeyboardInterrupt:
    filename = "gesture-"+str(time.strftime("%Y%m%d%H%M%S"))+".txt"
    with open(filename, "w") as f:
      for lines in data:
        f.write("-,-,-\n")
        for line in lines:
          f.write(line)
    print("Exiting...")
    print("Save file in", filename)
    s.close()
    sys.exit()

