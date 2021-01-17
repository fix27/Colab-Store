import math
def is_square(integerx):
 return  (False if integerx<4  else (integerx == int(math.sqrt(integerx) + 0.5) ** 2))
for a in range(156,20000) :
 for b in range(a,42000) :
  for c in range(b,90000) :
    p=(a+b+c)/2
    if is_square(p*(p-a)*(p-b)*(p-c)) and is_square(2*b**2+2*c**2-a**2)  and is_square(2*a**2+2*c**2-b**2) and is_square(2*a**2+2*b**2-c**2) :
     print(a,b,c,(math.sqrt(2*b**2+2*c**2-a**2))/2,(math.sqrt(2*a**2+2*c**2-b**2))/2,(math.sqrt(2*a**2+2*b**2-c**2))/2,math.sqrt((p*(p-a)*(p-b)*(p-c))))
