# Ayush Jain - 2017UCP1168
# Implementation of Play Fair Cipher
def find_in_matrix(matrix,char):
    for i in range(5):
        for j in range(5):
            if(matrix[i][j] == char):
                return (i,j)

fhand = open("input.dat","r") ; i=0
for line in fhand:
    if(i==0):
        plain_text = line.rstrip()
    else:
        key = line.rstrip()
    i += 1
fhand.close()
print("\nKey is : {}".format(key))
print("\nInput Plain text is : {}".format(plain_text))
ddd = dict()
for char in key:
    ddd[char] = None
# print(ddd)
matrix = [[None for j in range(5)] for i in range(5)]
i = 0; j = 0;
for char in key:
    if(ddd[char] is None):
        matrix[i][j] = char
        j += 1
        if(j == 5):
            i += 1
            j = 0
        ddd[char] = 1
for k in range(97,123):
    tmp = chr(k)
    if(tmp not in ddd) and (tmp != 'j'):
        matrix[i][j] = tmp
        j += 1
        if(j == 5):
            i += 1
            j = 0
print("\nKey Square is as follows : \n")
for i in range(5):
    for j in range(5):
        print(matrix[i][j],end=' ')
    print()
############### ENCRYPTION ##############
if(len(plain_text)%2 != 0):
    plain_text += 'z'
# Replace all j with i
for i in range(len(plain_text)):
    if(plain_text[i] == 'j'):
        plain_text[i] = 'i'
cipher = ''
for i in range(0,len(plain_text),2):
    c1 = plain_text[i]
    c2 = plain_text[i+1]
    (i1,j1) = find_in_matrix(matrix,c1)
    (i2,j2) = find_in_matrix(matrix,c2)
    if(i1 == i2):
        cipher += matrix[i1][(j1+1)%5]
        cipher += matrix[i1][(j2+1)%5]
    elif(j1 == j2):
        cipher += matrix[(i1+1)%5][j1]
        cipher += matrix[(i2+1)%5][j1]
    else:
        cipher += matrix[i1][j2]
        cipher += matrix[i2][j1]
print("\nEncrypted cipher text is : {}\n".format(cipher))
fhand = open("cipher.dat","w")
fhand.write(cipher) ; fhand.close()
print("Enter cipher text to be decrypted : ",end="")
cipher = input()
ans_plain = ''
for i in range(0,len(cipher),2):
    c1 = cipher[i]
    c2 = cipher[i+1]
    (i1,j1) = find_in_matrix(matrix,c1)
    (i2,j2) = find_in_matrix(matrix,c2)
    if(i1 == i2):
        ans_plain += matrix[i1][(j1-1)%5]
        ans_plain += matrix[i1][(j2-1)%5]
    elif(j1 == j2):
        ans_plain += matrix[(i1-1)%5][j1]
        ans_plain += matrix[(i2-1)%5][j1]
    else:
        ans_plain += matrix[i1][j2]
        ans_plain += matrix[i2][j1]
print("\nDecrypted Plain text is : {}\n".format(ans_plain))
