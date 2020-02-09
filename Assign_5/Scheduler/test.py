# Parsing the input
import os
fhandle = open("input2.dat","r")
for line in fhandle:
	t_list = line.split()
	if(len(t_list) == 0):
		break
	if(t_list[0] == 'policy'):
		policy = t_list[1]
	elif(t_list[0] == 'jobs'):
		numJobs = t_list[1]
	elif(t_list[0] == 'quantum_time'):
		quantum_time = t_list[1]
	elif(t_list[0] == 'run_time'):
		run_time = list()
		for i in range(1,int(numJobs)+1):
			run_time.append(t_list[i])
########################################
# print(run_time)
cmd = "./scheduler.py"
cmd = cmd + " -p " + policy
cmd = cmd + " -j " + numJobs
cmd = cmd + " -l "
for i in run_time:
	cmd = cmd + i + ","
cmd = cmd[:-1]
cmd = cmd + " -q " + quantum_time
cmd = cmd + " -c"
# print(cmd)
os.system(cmd)


		
	
