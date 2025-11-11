def crc(msg,div):
    msg+='0'*(len(div)-1)
    s=''
    for i in range(len(msg)):
        s+=msg[i]
        if len(s)==len(div):
            s=bin(int(s,2)^int(div,2))[2:]
            s=str(int(s))
    return s
def check(msg,div):
    p=crc(msg,div)
    if len(p)<len(div)-1:
        msg+='0'*(len(div)-1-len(p))+p
    s=''
    for i in range(len(msg)):
        s+=msg[i]
        if len(s)==len(div):
            s=bin(int(s,2)^int(div,2))[2:]
            s=str(int(s))
    if int(s)==0:
        return "No error"
    else:
        return "Error detected"
m=input()
d=input()
r=crc(m,d)
print(r)
print(check(m,d))