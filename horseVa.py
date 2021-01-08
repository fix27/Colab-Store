import random
import datetime
maxx=8
maxy=8
x1=4
y1=4
hod = [ (1, 2, 1), (-1, 2, 2), (2, 1, 3), (2, -1, 4), (1, -2, 5), (-1, -2, 6), (-2, -1 , 7), (-2, 1, 8) ]
hcount=maxx*maxy
z127 = [-1,0,maxx+1,maxx+2]
def rek2(x, y):
   global n
   global a
   global hod
   hodt = []  
   for j in range(0,9): hodt.append(13)
   n+=1
   a[x][y]=n
   if (n==hcount) :
     n=777777
     global res
     for i in range(0,maxx+2): 
       for j in range(0,maxy+2): res[i][j]=a[i][j]
   elif(n<111111): 
     for m in hod:
             xh=x+m[0]
             yh=y+m[1]
             if (a[xh][yh]==0): 
               resT=0
               for hht in hod:
                 if (a[xh+hht[0]][yh+hht[1]]==0) : resT +=1
               hodt[m[2]]=resT
             else : 
               hodt[m[2]]=11
     for va in range(0,8):
            for m in hod:
              if (hodt[m[2]]==va) : 
                rek2(x+m[0],y+m[1])
   n-=1
   a[x][y]=0
   return 0
res = []
for k in range(-1,maxx+2):
    res2 = []
    for j in range(-1,maxy+2):
        res2.append(0)
    res.append(res2)
a = []
for k in range(-1,maxx+2):
    a2 = []  
    for j in range(-1,maxy+2): 
        a2.append(0)
    a.append(a2)
for i in range(-1,maxx+2):
  for j in z127:
    a[i][j]=127 
for i in range(-1,maxy+2):
  for j in z127:
    a[j][i]=127  

n=0
tb = datetime.datetime.now()
print(tb)
rek2(x1,y1)
for i in range(0,maxx+2):
  print(res[i][0:maxy+2])
te = datetime.datetime.now()
print(te)
delta = te-tb
print(delta.seconds)
