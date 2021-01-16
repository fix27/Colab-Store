#program AutoTicket;
countLenStr = 32
kombcount= [0, 1, 2, 6, 24, 120]
t5Byte = [0,0,0,0,0]
t5 = [0,0,0,0,0]
t6 = [0,0,0,0,0,0]
t7 = [0,0,0,0,0,0,0]
initcomb = True
nums = t7.copy()
iSign = t6.copy()
#var
#  counttrue: comp;
#  nums: array [1 .. 6] of longint;
#  LenStr: array [1 .. 6] of byte;
#  calcNumber: array [1 .. 6] of single;
#  iSign, calcOrder, calcSign: t5Byte;
#  LenStrAll: array [1 .. countLenStr, 1 .. 6] of byte;
#  kombAll: array [1 .. 5, 1 .. 120] of t5Byte;
#  { kombAllIndex: array [1 .. 5, 1 .. 120, 1 .. 5] of byte; }
#  rezbol, fixLenZero, exzero: boolean;
#  numStr,tmps: String;
#  CountMathOper, iCalcOrder, iMathOper, firstSign, countmoveel: byte;
#  gi: longint;
#  i, i1, iLenStr: Integer;

if initcomb :
#var
#  mtmp: array [1 .. 5] of byte;
#  flag1: boolean;
#  i11, i12, comb, iLenStr0: byte;
#begin
  # 0
  kombAll=[]
  kombAll.append(0)
  # 1
  a3 = [1]
  a2 = []
  a2.append(a3)
  kombAll.append(a2)
  # 2
  a2 = []
  a3 = [1,2]
  a2.append(a3)
  a4 = [2,1]
  a2.append(a4)
  kombAll.append(a2)
  

 # kombAll[1, 1, 1] := 1;
 # { kombAllIndex[1, 1, 1] := 1; }
  # 3
  mtmp=t5.copy()
  a2=[]
  comb = 0
  mtmp[0] = 0
  while mtmp[0] < 3 :
    mtmp[0] = mtmp[0] + 1;
    mtmp[1] = 0
    while mtmp[1] < 3 :
      mtmp[1] = mtmp[1] + 1;
      mtmp[2] = 0
      while mtmp[2] < 3 :
        mtmp[2] = mtmp[2] + 1;
        flag1 = True
        for i11 in range(2)  :
          for i12 in range(i11 + 1,3)  :
            if mtmp[i11] == mtmp[i12] :
              flag1 = False
        if flag1 :
          comb=comb+1
          #for i11 := 1 to 3 do
          a2.append(mtmp.copy())
            
  kombAll.append(a2)
  #4
  a2=[]
  comb = 0
  mtmp=t5.copy()
  mtmp[0] = 0
  while mtmp[0] < 4 :
    mtmp[0] = mtmp[0] + 1
    mtmp[1] = 0
    while mtmp[1] < 4 :
      mtmp[1] = mtmp[1] + 1
      mtmp[2] = 0
      while mtmp[2] < 4 :
        mtmp[2] = mtmp[2] + 1
        mtmp[3] = 0
        while mtmp[3] < 4 :
         mtmp[3] = mtmp[3] + 1
         flag1 = True;
         for i11 in range(3) :
           for i12 in range(i11 + 1,4)  :
              if mtmp[i11] == mtmp[i12] :
                flag1 = False
         if flag1 :
            comb=comb+1
            a2.append(mtmp.copy())
            
  kombAll.append(a2)           


#5
  a2=[]
  comb = 0
  mtmp=t5.copy()
  mtmp[0] = 0
  while mtmp[0] < 5 :
    mtmp[0] = mtmp[0] + 1
    mtmp[1] = 0
    while mtmp[1] < 5 :
      mtmp[1] = mtmp[1] + 1
      mtmp[2] = 0
      while mtmp[2] < 5 :
        mtmp[2] = mtmp[2] + 1
        mtmp[3] = 0
        while mtmp[3] < 5 :
         mtmp[3] = mtmp[3] + 1
         mtmp[4] = 0
         while mtmp[4] < 5 :
            mtmp[4] = mtmp[4] + 1
            flag1 = True;
            for i11 in range(4) :
             for i12 in range(i11 + 1,5)  :
               if mtmp[i11] == mtmp[i12] :
                 flag1 = False
            if flag1 :
              comb=comb+1
              a2.append(mtmp.copy())
            
  kombAll.append(a2)           

  LenStrAll = []
  LenStr = t7.copy()
  iLenStr0 = 0
  LenStr[0] = 0
  LenStr[6] = 0
  while LenStr[6] < 2:
    LenStr[5] = 0;
    while LenStr[5] < 3:
      LenStr[4] = 0
      while LenStr[4] < 4:
        LenStr[3] = 0;
        while LenStr[3] < 5:
          LenStr[2] = 0;
          while LenStr[2] < 6:
            LenStr[1] = 1;
            while LenStr[1] < 7:
              if ((LenStr[1] + LenStr[2] + LenStr[3] + LenStr[4] + LenStr[5] +
                LenStr[6]) == 6) :
                fixLenZero = True
                for i11 in range(2,6) :
                  if (LenStr[i11] == 0) and (LenStr[i11 + 1] > 0) :
                    fixLenZero = False
                if fixLenZero :
                
                  iLenStr0 = iLenStr0 + 1
                  #LenStrAll[iLenStr0]
                  LenStrAll.append(LenStr.copy());
                
                

              LenStr[1] = LenStr[1] + 1

            LenStr[2] = LenStr[2] + 1

          LenStr[3] = LenStr[3] + 1

        LenStr[4] = LenStr[4] + 1

      LenStr[5] = LenStr[5] + 1

    LenStr[6] = LenStr[6] + 1

  if iLenStr0 != countLenStr :

    print( 'error countLenStr');
    print( countLenStr);
    print( iLenStr0);

#print(kombAll[5][119][4])
with open('output.txt', 'w') as outfile:

 counttrue= 0
 for gi in range(999999) :
  
    rezbol = False
    tmps=''
    numStr = str(gi)
    while len(numStr) < 6 :
      numStr = '0' + numStr;
    for iLenStr in range(countLenStr) : 
      for i in range(1,7) :
        nums[i] = 1000000;
      i = 0
      CountMathOper = 0

      while i < 6:
        CountMathOper=CountMathOper+1
        if LenStrAll[iLenStr][ CountMathOper] > 0 :
          nums[CountMathOper] = int('0'+numStr[i:i+int(LenStrAll[iLenStr][ CountMathOper])])
         # print(nums[CountMathOper],i,LenStrAll[iLenStr][ CountMathOper])
        i = i + int(LenStrAll[iLenStr][ CountMathOper])
      
      for firstSign in range( 1,3 ) :
     
        nums[1] = abs(nums[1]) if firstSign == 1 else (abs(nums[1]) * (-1))
        #  nums[1] = abs(nums[1])
        #else :
        #  nums[1] = abs(nums[1]) * (-1)
        iSign[1] = 1
        while not (rezbol or (iSign[1] > 1 + (5 *  ( 1 if CountMathOper > 1 else 0) ))) :
          iSign[2] = 1
          while not (rezbol or (iSign[2] > 1 + (5 * ( 1 if CountMathOper > 2 else 0) ))) :
            iSign[3] = 1
            while not (rezbol or (iSign[3] > 1 + (5 * ( 1 if CountMathOper > 3 else 0)))) :
              iSign[4] = 1
              while not (rezbol or (iSign[4] > 1 + (5 * ( 1 if CountMathOper > 4 else 0)))) :
                iSign[5] = 1
                while not (rezbol or (iSign[5] > 1 + (5 * ( 1 if CountMathOper > 5 else 0)))) :
                  calcNumber=t7.copy()

                  for i in range(kombcount[CountMathOper - 1]) :
                  
                    exzero = False
                    #for i1 in range(1,CountMathOper+1) :
                    #  calcNumber[i1] = nums[i1]
                    calcNumber = nums.copy()
                    calcSign = iSign.copy()
                    calcOrder = kombAll[CountMathOper - 1][ i].copy()

                    for iMathOper in range(1, CountMathOper ) :
       
                      #iCalcOrder = 0
                      
                      #while iCalcOrder<len(calcOrder) and calcOrder[iCalcOrder] != iMathOper :
                      #  iCalcOrder=iCalcOrder+1
                      #iCalcOrder=iCalcOrder+1

                      iCalcOrder = calcOrder.index(iMathOper)+1
                      if (calcNumber[(iCalcOrder + 1)] == 0) and (calcSign[iCalcOrder] in [4, 6]) :
                        exzero = True
                      if exzero :
                        break;
                      if calcSign[iCalcOrder] == 1 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] + calcNumber[(iCalcOrder + 1)]
                      elif calcSign[iCalcOrder] == 2 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] -  calcNumber[(iCalcOrder + 1)]
                      elif calcSign[iCalcOrder] == 3 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] *  calcNumber[(iCalcOrder + 1)]
                      elif calcSign[iCalcOrder] == 4 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] / calcNumber[(iCalcOrder + 1)]
                      elif calcSign[iCalcOrder] == 5 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] * (-1 * calcNumber[(iCalcOrder + 1)])
                      elif calcSign[iCalcOrder] == 6 :
                          calcNumber[iCalcOrder] = calcNumber[iCalcOrder] / (-1 * calcNumber[(iCalcOrder + 1)])
                    
                     # countmoveel = CountMathOper - iMathOper - iCalcOrder
                      #calcNumber[iCalcOrder + 1]=calcNumber[iCalcOrder + 2].copy()
                      #calcSign[iCalcOrder] = calcSign[iCalcOrder + 1].copy()
                     # calcOrder[iCalcOrder] = calcOrder[iCalcOrder + 1].copy()
        
                      for i1 in range( iCalcOrder + 1 , (CountMathOper - iMathOper)+1 ):
                        
                        calcNumber[i1]    = calcNumber[i1 + 1]
                        calcSign[i1 - 1]  = calcSign[i1]
                        calcOrder[i1 - 2] = calcOrder[i1-1]
                      
                    if exzero :
                      continue
                    
                    if calcNumber[1] == 100 :
                      #print(calcNumber[1])
                      tmps = tmps + str(nums[1]) + ' '
                      for i1 in range(2 , CountMathOper +1) :
                        tmps = tmps + '(' + str(kombAll[CountMathOper - 1][ i][ i1 - 2]) + ') '
                        if iSign[(i1 - 1)] == 1 :
                            tmps = tmps + '+ '
                        elif iSign[(i1 - 1)]== 2 :
                            tmps = tmps + '- '
                        elif iSign[(i1 - 1)]== 3 :
                            tmps = tmps + '* '
                        elif iSign[(i1 - 1)]== 4 :
                            tmps = tmps + '/ '
                        elif iSign[(i1 - 1)]== 5 :
                            tmps = tmps + '* -'
                        elif iSign[(i1 - 1)]== 6 :
                            tmps = tmps + '/ -'
                        
                        tmps = tmps + str(nums[i1]) + ' '
                     
                      tmps = tmps + chr(13)+chr(10)
                      rezbol = True

                    if rezbol :
                      break;

                  iSign[5] = iSign[5] + 1

                iSign[4] = iSign[4] + 1

              iSign[3] = iSign[3] + 1

            iSign[2] = iSign[2] + 1

          iSign[1] = iSign[1] + 1

        if rezbol :
          break;
    
      if rezbol :
        break;

    if rezbol :
      counttrue = counttrue + 1

    outfile.write('Ticket '+ str(gi)+ ' Rezult:'+ str(rezbol)+  ' Count true:'+ str(counttrue)+  chr(13)+chr(10)+tmps)
    print('Ticket '+ str(gi)+ ' Rezult:'+ str(rezbol)+  ' Count true:'+ str(counttrue)+  chr(13)+chr(10)+tmps)
