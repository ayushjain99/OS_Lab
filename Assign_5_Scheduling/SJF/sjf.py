# Ayush Jain - 2017UCP1168
# Shortest Job First Scheduling
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
t_global = 0
io_queue = []
job_ptrs = []
turnaround = []
response = []
for i in range(numJobs):
    turnaround.append(-1)
    response.append(-1)
job_des.sort(key=lambda x:x[2])
t_global = job_des[0][2]
for i in range(numJobs):
    job_ptrs.append(3)

while(numJobs > 0):
    for i in range(len(job_des)):
        if(job_des[i][job_ptrs[i]] == 'P'):
            print("t =",t_global,":",job_des[i][0])
            if(response[i] == -1):
                response[i] = t_global
            job_des[i][job_ptrs[i]+1] -= 1
            if(job_des[i][job_ptrs[i]+1] == 0):
                job_ptrs[i] += 2
            if(job_des[i][job_ptrs[i]] == -1):
                print("Job",job_des[i][0],"Finished")
                numJobs -= 1
                turnaround[i] = t_global - job_des[i][2]
            break
        elif(job_des[i][job_ptrs[i]] == 'I') or (job_des[i][job_ptrs[i]] == 'O'):
            io_queue.append([i,job_des[i][job_ptrs[i]+1]])
            job_ptrs[i] += 1
    if(len(io_queue) != 0):
        io_queue[0][1] -= 1
        if(io_queue[0][1] == 0):
            job_ptrs[io_queue[0][0]] += 1
            del io_queue[0]
    t_global=t_global+1
for i in range(len(turnaround)):
    print("Turnaround time of Job",job_des[i][0],":",turnaround[i])
    print("Response time of Job",job_des[i][0],":",response[i])
print()
print("Average Turnaround time =",sum(turnaround)/len(turnaround))
print("Average Response time =",sum(response)/len(turnaround))
