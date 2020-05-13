import sys
            
serchtext = sys.argv[1] # Output file to be searched (example: sh_output.txt)
while True:
    try:
        file = open(serchtext,"r")
        patterntext = input("Enter the dialog to be searched. Enter 'extsearch' (without quotes) to exit the search\n")
        if patterntext == "extsearch": 
            file.close() 
            break
        x=file.readline()
        chap=""
        flag=0
        found=0
        while x:
            if x == "\n":
                if flag == 0 : flag = 1
                elif flag == 1:
                    while x=="\n": x=file.readline()
                    chap = x
            if patterntext in x: 
                found=1
                print("The pattern was found in ",chap)
            x=file.readline()
        if found == 0:
            print("Pattern not found")
        file.close()
    except IOError:
        print("File doesn't exist")
        break