# Parsing the input
import os
tmp = list()
fhandle = open("lottery.dat","r") ; i=0
for line in fhandle:
    if(i==0):
        num_tickets = int(line)
    elif(i==1):
        num_jobs = int(line)
    else:
        tt = list(line.split())
        tt = tt[:4]
        tmp.append(tt)
    i=i+1
########################################
cmd = "./lottery.py"
cmd = cmd + " -l "
for i in range(len(tmp)):
    r_time = tmp[i][3]
    share = int(tmp[i][1])
    tickets = (share/100)*(num_tickets)
    tickets = int(round(tickets))
    tickets = str(tickets)
    cmd = cmd + r_time + ":" + tickets + ","
cmd = cmd[:-1]
cmd = cmd + " -q 3"
cmd = cmd + " -c"
# print(cmd)
os.system(cmd)
