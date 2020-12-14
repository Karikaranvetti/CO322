import matplotlib.pyplot as plt
f = open("recursion.txt", "r")      #geting the recurtion method runtimes 
points=list()
cordinates_y=list()
cordinates_x=list()
for line in f:
    points.append(line)
f.close()

F = open("iteration.txt", "r")        #geting the iterative method runtimes 
points_I=list()
cordinates_yI=list()
cordinates_xI=list()
for line in F:
    points_I.append(line)
F.close()


for x in range(len(points)):      # makeing the x,y cordinates 
    cordinates_y.append(int(points[x]))
    cordinates_x.append(x)
print(cordinates_y)
print(cordinates_x)

for x in range(len(points_I)):       # makeing the x,y cordinates 
    cordinates_yI.append(int(points_I[x]))
    cordinates_xI.append(x)
print(cordinates_yI)
print(cordinates_xI)



plt.plot(cordinates_xI,cordinates_yI,'c')     #ploting the iterative method 
plt.plot(cordinates_x,cordinates_y,'r')         # ploting the recursion method 
plt.show()
 