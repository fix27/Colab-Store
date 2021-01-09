import math
import datetime
tb = datetime.datetime.now()
print (tb)
#MaxLifeWidth=384
#MaxLifeHeight=512 
MaxLifeWidth=80
MaxLifeHeight=80 

def calc(LifeWidth,LifeHeight,LifeSpace):
 OldLife = []
 for i in range(-MaxLifeWidth,MaxLifeWidth):
    a2 = []
    for j in range(-MaxLifeHeight,MaxLifeHeight):
    # a2.insert(0,(conversion_c2i[simple_bubble_board[i*(wy)+j]]))
        a2.append(0)
    #print(a2)
  # a.insert(0,  a2)
    OldLife.append(a2)
  
 i11=0
 i01=0
 j01=0
 j11=0
 j02=0
 j12=0
 i=0
 j=0
 cur=0
 o=0
 
 #t:pointer
 
 imin=0
 imax=0
 jzone=0
 NewLifeWidth=0
 NewLifeHeight=0
 oper=0
 
 while oper<2700:
  oper=oper+1
  #imin=max(-LifeWidth-1,-MaxLifeWidth)
  #imax=min(MaxLifeWidth,LifeWidth+1)
  #jzone=min(MaxLifeHeight,LifeHeight+2)
  #NewLifeWidth=LifeWidth
  #NewLifeHeight=LifeHeight
  t=LifeSpace
  LifeSpace=OldLife
  OldLife=t
  
  #for i in range(imin,imax):
   #for j in range(-jzone,jzone):
  for i in range(-MaxLifeWidth,MaxLifeWidth):
    for j in range(-MaxLifeHeight,MaxLifeHeight):
     LifeSpace[i][j]=0
  for j in range(-MaxLifeHeight,MaxLifeHeight):
  #for j in range(-jzone,jzone):
  
   j01=((j+1+MaxLifeHeight) % (MaxLifeHeight*2+1))-MaxLifeHeight
   j11=((j-1+MaxLifeHeight*3+1) % (MaxLifeHeight*2+1))-MaxLifeHeight
   j02=((j+2+MaxLifeHeight) % (MaxLifeHeight*2+1))-MaxLifeHeight
   j12=((j-2+MaxLifeHeight*3+1) % (MaxLifeHeight*2+1))-MaxLifeHeight
   for i in range(-MaxLifeWidth,MaxLifeWidth):
   #for i in range(imin,imax):
    if (OldLife[i][j] & 16)==16 :
     cur=OldLife[i][j] & 1
     i01=((i+1+MaxLifeWidth)  % (MaxLifeWidth*2+1)) -MaxLifeWidth
     i11=((i-1+MaxLifeWidth*3+1)  % (MaxLifeWidth*2+1)) -MaxLifeWidth
     o=(OldLife[i][j02]+
        OldLife[i][j12]+
        OldLife[i][j01]+
        OldLife[i][j11]+
        OldLife[i11][j]+
        OldLife[i01][j]+
        OldLife[i01][j01]+
        OldLife[i01][j11]+
        OldLife[i11][j01]+
        OldLife[i11][j11]) & 15 
#    if not (((cur=1) and (o=2)) or ((cur=0) and(o in [3,5,6]))) then Continue
     if 0!=(cur*(o ^ 2)+(1-cur)*(o ^ 3)*(o ^ 5)*(o ^ 6)) : continue
#    if 0<>(cur*(o xor 7)+(1-cur)*(o xor 3)*(o xor 4)*(o xor 6)) then Continue
 #    if NewLifeWidth < abs(i) : NewLifeWidth =i
 #    if NewLifeHeight< j      : NewLifeHeight=j
     LifeSpace[i][j]=LifeSpace[i][j] | 17
     LifeSpace[i][j02]=LifeSpace[i][j02] | 16
     LifeSpace[i][j12]=LifeSpace[i][j12] | 16
     LifeSpace[i][j01]=LifeSpace[i][j01] | 16
     LifeSpace[i][j11]=LifeSpace[i][j11] | 16
     LifeSpace[i11][j]=LifeSpace[i11][j] | 16
     LifeSpace[i01][j]=LifeSpace[i01][j] | 16
     LifeSpace[i01][j01]=LifeSpace[i01][j01] | 16
     LifeSpace[i01][j11]=LifeSpace[i01][j11] | 16
     LifeSpace[i11][j01]=LifeSpace[i11][j01] | 16
     LifeSpace[i11][j11]=LifeSpace[i11][j11] | 16

  #   if  LifeWidth < abs(NewLifeWidth) :
  #    if MaxLifeWidth  > abs(NewLifeWidth) : 
  #     LifeWidth  = abs(NewLifeWidth)                                  
  #    else :
  #     LifeWidth  = MaxLifeWidth
  #   if  LifeHeight < NewLifeHeight :
  #    if MaxLifeHeight > NewLifeHeight     :
  #     LifeHeight = NewLifeHeight                  
  #    else :
   #    LifeHeight = MaxLifeHeight
 return LifeSpace


LifeSpace = []
for i in range(-MaxLifeWidth,MaxLifeWidth):
    a2 = []
    for j in range(-MaxLifeHeight,MaxLifeHeight):
    # a2.insert(0,(conversion_c2i[simple_bubble_board[i*(wy)+j]]))
        a2.append(0)
    #print(a2)
    # a.insert(0,  a2)
    LifeSpace.append(a2)
LifeWidth=10
LifeHeight=10
LifeSpace[3][8] = 17
LifeSpace[4][7] = 17
LifeSpace[5][8] = 17
LifeSpace[3][9] = 17
LifeSpace[4][9] = 17
LifeSpace[5][9] = 17

LifeSpace[3][-7] = 17
LifeSpace[4][-6] = 17
LifeSpace[5][-7] = 17
LifeSpace[3][-8] = 17
LifeSpace[4][-8] = 17
LifeSpace[5][-8] = 17

LifeSpace[0][0] = 17
LifeSpace[0][1] = 17
LifeSpace[1][0] = 17
LifeSpace[1][1] = 17

LifeSpace[-3][-8] = 17
LifeSpace[-4][-7] = 17
LifeSpace[-5][-8] = 17
LifeSpace[-3][-9] = 17
LifeSpace[-4][-9] = 17
LifeSpace[-5][-9] = 17
 
 
LifeSpace[-3][7] = 17
LifeSpace[-4][6] = 17
LifeSpace[-5][7] = 17
LifeSpace[-3][8] = 17
LifeSpace[-4][8] = 17
LifeSpace[-5][8] = 17
for i in range(-11,11):
  for j in range(-11,11):
    LifeSpace[i][j]= LifeSpace[i][j] | 16
s = ''
for i in range(-MaxLifeWidth,MaxLifeWidth):
    s += chr(13)+chr(10)
    for j in range(-MaxLifeHeight,MaxLifeHeight):
      if LifeSpace[i][j]==16:  s += str(1)
      else:  s += str(0)
#print(s)
#print(LifeSpace)
#LifeSpace,OldLife:PLifeSpace
#Life:TLife
LifeSpaceEnd=calc(LifeWidth,LifeHeight,LifeSpace)
s = ''
for i in range(-MaxLifeWidth,MaxLifeWidth):
    s += chr(13)+chr(10)
    for j in range(-MaxLifeHeight,MaxLifeHeight):
      if LifeSpaceEnd[i][j]==17:  s += str(1)
      else:  s += str(0)
print(s)
te = datetime.datetime.now()
print (te)
delta = te - tb
print (delta.seconds)
