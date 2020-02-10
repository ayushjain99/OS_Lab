# Ayush Jain - 2017UCP1168
# Implementation of Hill Cipher
import numpy as np
import math
import sys
###################################
fhand = open("input.dat","r") ; i=0
key = list()
for line in fhand:
    if(i==0):
        plaintext = line.split()
    else:
        tmp = line.split()
        key.append(tmp)
    i=i+1
####################################
for i in range(len(plaintext)):
    tmp = plaintext[i].lower()
    plaintext[i] = ord(tmp) - 97
for i in range(3):
    for j in range(3):
        tmp = key[i][j].lower()
        key[i][j] = ord(tmp)-97
####################################
print("\nPlaintext is : {}\n".format(plaintext))
print("Key matrix is : \n")
for tmp in key:
    for x in tmp:
        print("%-3d"%(x),end=" ")
    print("\n")
cipher = ""
for i in range(0,len(plaintext),3):
    for j in range(3):
        t1 = key[j][0]*plaintext[i]
        t2 = key[j][1]*plaintext[i+1]
        t3 = key[j][2]*plaintext[i+2]
        cipher += chr(((t1+t2+t3)%26) + 97)
print("CipherText is :",cipher + "\n")
#####################################
tmp = np.array(key)
det = int(np.linalg.det(tmp)) ; tt2 = det % 26
tt = math.gcd(tt2,26)
if(tt != 1):
    print("This key matrix has no inverse..DECRYPTION NOT POSSIBLE")
    print("Choose a different key")
    sys.exit(1)
for i in range(26):
    if(i*det)%26 == 1:
        break;
# print(i)
