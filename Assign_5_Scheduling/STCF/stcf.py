# Ayush Jain - 2017UCP1168
# Shortest Time to Completion First (STCF)
fhand = open("input.dat","r") ; i=0
job_des = list()
for line in fhand:
    if(i==0):
        numJobs = int(line)
    elif(i==1):
        quantum = int(line)
    else:
        job_des.append(line.split())
    i=i+1
for i in range(len(job_des)):
    for j in range(len(job_des[i])):
        if(job_des[i][j] != 'P') and (job_des[i][j] != 'I') and (job_des[i][j] != 'O'):
            job_des[i][j] = int(job_des[i][j])
#################################################################
t_global = job_des[0][2]
for i in range(len(job_des)):
    if(job_des[i][2] < t_global):
        t_global = job_des[i][2]
#################################################################
io_queue = []
job_ptr = []
for i in range(numJobs):
    job_ptr.append(3)
turnaround = []
response = []
for i in range(numJobs):
    turnaround.append(-1)
    response.append(-1)
#################################################################
while(numJobs > 0):
    t_list = []
    for i in range(len(job_des)):
        if(job_des[i][job_ptr[i]] == 'P') and (job_des[i][2] <= t_global) and (job_des[i][1] != 'R'):
            t_list.append((i,job_des[i][job_ptr[i]+1]))
        if(job_des[i][1]=='R'):
            job_des[i][1] = 1
    if(len(t_list) != 0):
        var = t_list[0][1] ; min_burst_req = t_list[0][0]
        for i in range(len(t_list)):
            if(t_list[i][1] < var):
                var = t_list[i][1]
                min_burst_req = t_list[i][0]
        if(response[min_burst_req] == -1):
            response[min_burst_req] = t_global
        print("t =",t_global,": Job",job_des[min_burst_req][0])
        job_des[min_burst_req][job_ptr[min_burst_req]+1] -= 1
        if(job_des[min_burst_req][job_ptr[min_burst_req]+1] == 0):
            job_ptr[min_burst_req] += 2
        if(job_des[min_burst_req][job_ptr[min_burst_req]] == -1):
            numJobs -= 1
            print("Job",job_des[min_burst_req][0],"Finished")
            turnaround[min_burst_req] = t_global - job_des[min_burst_req][2]
        elif(job_des[min_burst_req][job_ptr[min_burst_req]] == 'I') or (job_des[min_burst_req][job_ptr[min_burst_req]] == 'O'):
            io_queue.append([min_burst_req,job_des[min_burst_req][job_ptr[min_burst_req]+1]])
            job_ptr[min_burst_req] += 1
    if(len(io_queue) != 0):
        io_queue[0][1] -= 1
        if(io_queue[0][1] == 0):
            job_ptr[io_queue[0][0]] += 1
            job_des[io_queue[0][0]][1] = 'R' # Ready state
            del io_queue[0]
    t_global = t_global + 1
for i in range(len(turnaround)):
    print("Turnaround time of Job",job_des[i][0],":",turnaround[i])
    print("Response time of Job  ",job_des[i][0],":",response[i])
print()
print("Average Turnaround time =",sum(turnaround)/len(turnaround))
print("Average Response time =",sum(response)/len(turnaround))
