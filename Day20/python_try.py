
with open('bernhard.txt') as f:
    content = [complex(a.strip()) for a in f.readlines()]

i = 0

print(len(content))

while i < len(content):
    if content[i].imag == 1:
        i += 1
        continue
    
    # get new Position and Insert at Index
    newPos = int((content[i].real + i) % len(content)) + 1 
    
    if ((content[i].real + i) < 0) :
        newPos -= 1
    elif (content[i].real + i) == 0 :
        newPos = len(content) 
    
    content.insert(newPos, content[i] + 1j)
    
    # delete old Value and decide on new line-index
    i += (i >= newPos)
    #print("I: ", i, "   ", content, " preDel")
    del content[i % len(content)]
    print("I: ", i, "   ", content, " postDel")

#ret = 0

#for i in range(1000, 3001, 1000):
#    ret += content[(i+content.index(1j)) % len(content)]

#print("    Ret: ", ret)


