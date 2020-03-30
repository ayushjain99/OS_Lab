# FIFO Page Replacement
import sys
fhand = open("test.dat","r")
numPages = fhand.readline()
numPages = int(numPages)
tmp = list(map(int,fhand.readline().split()))
if(tmp[-1] != -1):
    print("Incorrect input format..Try Again..Exiting")
    sys.exit(1)
tmp = tmp[:-1]
ref_string = tmp
############# Input from file done ##############
bool_arr = [0 for i in range(100)]
queue = [] ; count = 0
num_Hits = 0 ; ttt = 0
for i in range(len(ref_string)):
    count += 1 ; ttt += 1
    tmp = ref_string[i]
    if(bool_arr[tmp] == 1):
        print("Page Requested : ",tmp," - Hit",sep='')
        num_Hits += 1
    else:
        print("Page Requested : ",tmp," - Miss",sep='')
        bool_arr[tmp] = 1
        if(len(queue) < numPages):
            queue.append(tmp)
        else:
            x = queue[0]
            bool_arr[x] = 0
            queue = queue[1:]
            queue.append(tmp)
    if(ttt == 25):
        print("Hit Ratio = ",(num_Hits/count)*100,"%")
        ttt = 0
print("Hit Ratio = ",(num_Hits/count)*100,"%")
