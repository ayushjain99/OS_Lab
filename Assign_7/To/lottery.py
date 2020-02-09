from random import randint
class Process:

	def __init__(self,id,share,ops):
		self.id = id
		self.share = share
		self.ops = ops
		self.burst = int(self.ops[1])
		self.j = 0
		#self.tat = 0
		#self.rt = -1
		#self.wt = 0
		self.start = 0
		self.end = share-1
		#for i in range(1, len(self.ops), 2):
			#self.wt += int(self.ops[i])

processes = []
#wait_proc = Queuee()
#processor.quantum = quantum
with open("lottery.dat", "r") as file:
    data = file.readlines()
for i in range(len(data)):
	l = len(data[i])
	data[i] = data[i][:l-1]

for i in range(2, len(data)):
	data[i] = data[i].split()

tickets = int(data[0])
num_proc = int(data[1])


for i in range(2, len(data)):
	#print(data[i])
	p = Process(int(data[i][0]), int(data[i][1]), data[i][2:])
	#print(data[i][3:])
	processes.append(p)

t = 0
for process in processes:
	t += process.share
prev = 0
for process in processes:
	process.start += prev
	process.end += prev
	prev = process.share

#print(t)
processor = []
for process in processes:
	processor.append(process)
def lottery():
	print("for first come first serve cpu scheduling")
	time = 0
	io = []
	i = 0
	while len(io)>0 or len(processor)>0:
		time += 1
		r =  randint(0, t + 1)

		#print("timer : ", time)
		flag = False


		if len(processor) > 0:
			for i in range(len(processor)):
				if processor[i].start <= r <= processor[i].end:
					print("Processing process ",processor[i].id)
					processor[i].burst -= 1
					#if processor[i].rt == -1:
					#	processor[i].rt = time - processor[i].at
					if processor[i].burst == 0:
						processor[i].j += 2
						j = processor[i].j
						if processor[i].ops[j] == '-1':
							print('finished an removing processes {} from processor queue'.format(processor[i].id))
							#processor[i].tat = time - processor[i].tat
							del processor[i]
							break
						else:
							processor[i].burst = int(processor[i].ops[j+1])

							p = processor[i]
							del processor[i]
							print(" process {} removed from processor queue and added to io queue".format(p.id))
							flag = True

							io.append(p)
							break


		if len(io) > 0:
			if io[0].burst > 0 and flag is False:
				io[0].burst -= 1
			if io[0].burst == 0:
				io[0].j += 2
				j = io[0].j
				if io[0].ops[j] == '-1':
					print('finished and removing processes {} from io queue'.format(io[0].id))
					#processor[0].tat = time - processor[0].tat
					io.pop(0)
				else:
					io[0].burst = int(io[0].ops[j+1])
					p = io.pop(0)
					print(" process {} added to processor queue from io queue".format(p.id))

					processor.append(p)
		#print("processes",len(processes))
		#print("processor",len(processor))
		#print("io",len(io))

	#for process in processes:
		#process.wt = process.tat - process.wt

	total_tat = 0
	total_wt = 0
	total_rt = 0

	# for process in processes:
	# 	 print("for process : ",process.id)
	# 	 print('turn around time : ',process.tat)
	# 	 print('waiting time : ', process.wt)
	# 	 print('response time : ', process.rt)
	# 	 print()
	# 	 total_tat += process.tat
	# 	 total_wt += process.wt
	# 	 total_rt += process.rt
	# print("avg turn around time", round(total_tat/len(processes), 2))
	# print("avg waiting time", round(total_wt/len(processes),2))
	# print("avg response time", round(total_rt/len(processes), 2))


		# print()
		# print('processor queue : ',end='')
		# for process in processor:
		# 	print(process.id, end=' ')
		# print()
		# print('input/output queue : ',end='')
		# for process in io:
		# 	print(process.id, end=' ')
		# print()
		# print()
lottery()
