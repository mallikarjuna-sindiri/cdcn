def charframing(data):
    d=data.split(" ")
    for i in d:
        print(len(i)+1,end=" ")
        print(i,end=" ")
    print()
def charstuff(data):
    d=data.split(" ")
    for i in d:
        if i=='esc' :
            print("esc "*(2),end=" ")
        elif i=='flag':
            print("flag "*(2),end=" ")
        else:
            print(i,end=" ")
    print()
def bitstuff(data):
    c=0
    s=''
    for i in data:
        s+=i
        if i=='1':
            c+=1
            if c==5:
                s+='0'
                c=0
        else:
            c=0
    print(s)
data=input()
charframing(data)
charstuff(data)
bitstuff(data)