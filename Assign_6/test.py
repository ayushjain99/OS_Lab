# Parsing the input
import os
tmp = list()
fhandle = open("mlfq.dat","r") ; i=0
for line in fhandle:
    if(i==1):
        quantum_list = line.split()
    elif(i==2):
        (T1,T2) = (line.split())
    elif(i!=0):
        tt = list(line.split())
        x = tt[1]
        y = tt[4]
        z = tt[6]
        stt = x+","+y+","+z
        tmp.append(stt)
    i=i+1
########################################
# print(run_time)
cmd = "./mlfq.py"
cmd = cmd + " -Q "
for i in range(len(quantum_list)):
    cmd = cmd + quantum_list[i] + ","
cmd = cmd[:-1]
cmd = cmd + " -B " + T2
cmd = cmd + " -i " + "2"
cmd = cmd + " -a " + T1
cmd = cmd + " -l "
for i in tmp:
	cmd = cmd + i + ":"
cmd = cmd[:-1]
cmd = cmd + " -c"
# print(cmd)
os.system(cmd)
