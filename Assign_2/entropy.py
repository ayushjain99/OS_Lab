# Calculating entropy of file
# Ayush Jain - 2017UCP1168
import sys
import math

def main():
    """
    if (len(sys.argv) != 2):
        print("Incorrect Syntax, exiting")
        print("python3 entropy.py <filename>")
        sys.exit(1)
    """
    print("Extension : ",end="") ; ext = input()
    for index in range(1,6):
        filename = ext + "/" + str(index) + "." + ext
        # print(filename)
        file_handle = open(filename,"rb")
        char_arr = list(file_handle.read())
        file_handle.close()
        size = len(char_arr)
        # print("Size of file =",size,"bytes")
        freq = list()
        for i in range(256):
            count = 0
            for char in char_arr:
                if (char == i):
                    count += 1
            freq.append(float(count)/size)
        entropy = 0.0
        for tmp in freq:
            if tmp > 0:
                entropy += tmp*math.log(tmp, 2)
        entropy = -entropy
        print("Entropy =",entropy)
    return 0

if __name__ == '__main__':
    main()
