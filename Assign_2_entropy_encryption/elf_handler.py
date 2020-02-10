# Ayush Jain - 2017UCP1168
# Extracting the basic information from an exe file
import os
import sys
import subprocess

def main():
    if(len(sys.argv) != 2):
        print("Incorrect Syntax, exiting")
        print("Executable file name should be command-line argument")
        sys.exit(0)
    name = str(sys.argv[1])
    os.system('readelf -h ' + name + ' > output.txt')
    print("Created file output.txt")
    
if __name__ == '__main__':
    main()
