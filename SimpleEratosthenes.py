import math
import numpy 
import datetime
from bitarray import bitarray 
tb = datetime.datetime.now()
print (tb)
maxan = 10000000   
 #//50*1024*1024;//1669597379;
maxx = maxan*12;
Resheto = bitarray(maxan*8)
Resheto.setall(1);
simple=''
with open('simple.csv', 'w') as outfile:
 outfile.write('n;x\n')
 outfile.write('1;2\n')
 outfile.write('2;3\n')
 an=3
 print('Write file...')
 i=5
 maxs=math.trunc(math.sqrt(maxx))+1
 print('.', end='');
 while i<maxx :
  j=i
  if Resheto[int((((i-5) // 6) << 1)+(1+numpy.sign(((i-5) % 6))))]!=0 :
   simple+=str(an)+';'+str(j)+'\n'
   if len(simple)>1000000 :
    outfile.write(simple); 
    simple=''
    print('.', end='');
   an+=1
   if j<maxs :
    while j<maxx :
     if ((j % 2)*(j % 3) != 0) :
      Resheto[int((((j-5) // 6) << 1)+(1+numpy.sign(((j-5) % 6))))]=0
     j+=i
  i+=2
  if (i % 3)==0 : i+=2
 outfile.write(simple); 
 simple=''  
 outfile.close()
print('')
print('Finish')
te = datetime.datetime.now()
print (te)
delta = te - tb
print (delta.seconds)
