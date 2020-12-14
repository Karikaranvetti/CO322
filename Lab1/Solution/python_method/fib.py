#!/usr/bin/python
import time 
import matplotlib.pyplot as plt
def fib_r(x) :
    if (x <= 2):
        return 1
    return fib_r(x-1) + fib_r(x-2)


def fib_i(x) :
    a = 1
    b = 1
    fib = 1
    i = 2
    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1
        
    return fib

x = 6
t1=time.time()
print ("Fib of " + str(x) + " = " + str(fib_r(x)))
t2=time.time()
print  (t2-t1)

print ("Fib of " + str(x) + " = " + str(fib_i(x)))
t3=time.time()
print  (t3-t2)
list_x=[]
list_Y=[]
list_x1=[]
list_Y1=[]

for i in range (0,40):
    t4=time.time()
    print(str(i)+"th "+str(fib_r(i)))
    t5=time.time()
    list_Y.insert(i,t5-t4)
    list_x.insert(i,i)
print(list_x)
print(list_Y)

for c in range (0,40):
    t6=time.time()
    print(str(c)+"th "+str(fib_i(c)))
    t7=time.time()
    list_Y1.insert(c,t7-t6)
    list_x1.insert(c,c)
print(list_x1)
print(list_Y1)
plt.plot(list_x,list_Y,'r')
plt.plot(list_x1,list_Y1,'c')
#plt.plot(list_x1,list_Y1)
plt.show()



