import re
import sys

inptfl = sys.argv[1] # Input File (Eg: sh.txt)
try:
    file = open(inptfl,"r", encoding="utf8")
    x=file.readline()
    flag=0 #flag for double couts
    sflag=0 #flag for single couts
    nflag=0 #flag for new line character
    optfl = sys.argv[2] # Output Dialog File (Eg: sh_output.txt)
    writef = open(optfl,"w") #Output File
    wsent="" # To store the text in double couts
    dialg=[] # To store strings for single couts
    drastrt=0
    while x:
        if x == "DRACULA\n": drastrt = 1
        if drastrt == 1 and re.search("CHAPTER",x): 
            x=x.split("\n")[0]
            chap = x + "-"
            x=file.readline()
            while x == "\n": x=file.readline()
            chap += x
            writef.write("\n\n"+chap)
        if re.search("^ *[IXV]+\. [A-Z]+.",x):
            writef.write("\n\n"+x)
        for alpha in range(len(x)):
            if x[alpha] == "\n": #Checking new line character
                if nflag == 0: nflag=1  #setting flag to 1 for new line character
                elif nflag == 1: #Checking consucutive occurance of new line character to elimate no end couts
                    nflag=0
                    for n in dialg:
                        writef.write(n+"\n")
                    dialg=[]# returning all the values to default
                    wsent=""
                    flag=0
                    sflag=0
                if sflag == 1: dialg[len(dialg)-1] += " " # adding space so that the words dont join after the new sentence
                if flag == 1: wsent+=" " 
                continue
            nflag=0 # Prevent moving to next paragraph untill consucutive new line character are found
            if x[alpha] == "\"": # Identifing Dumb double couts
                wsent+=x[alpha]
                if flag == 0: flag=1
                elif flag == 1:
                    flag=0
                    writef.write(wsent+"\n")
                    dialg=[]
                    sflag=0
                    wsent=""
                continue
            if x[alpha] == "“": #Identifing Smart starting double couts
                flag=1
                wsent+=x[alpha]
                continue
            if x[alpha] == "”": #Identifing smart end double couts
                flag=0
                wsent+=x[alpha]
                writef.write(wsent+"\n")
                dialg=[]
                sflag=0
                wsent=""
                continue
            if x[alpha] == "‘": #Identifing smart start single couts
                sflag=1
                dialg.append("")
            if x[alpha] == "’" and x[alpha+1].isalpha() != True and sflag == 1 and x[alpha - 1] != 's': #Identifing smart end single couts
                sflag=0
                dialg[len(dialg)-1]+="’"
                
            if flag == 1: #Appending to wsent when the double couts are open
                wsent+=x[alpha]
            if sflag == 1:#Appending to wsent when the single couts are open
                dialg[len(dialg)-1]+=x[alpha]
                    
        x=file.readline()
    writef.close()
    file.close()
    print("Your output file has been successfully generated based on your input file")
except IOError:
    print("File doesn't exist")