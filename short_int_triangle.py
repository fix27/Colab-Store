import math
def is_square(integerx):
 return integerx == int(math.sqrt(integerx if integerx>1 else 3) + 0.5) ** 2
for a in range(1,500) :
 for b in range(1,700) :
  for c in range(1,1500) :
    p=(a+b+c)/2
    if is_square(p*(p-a)*(p-b)*(p-c)) and is_square(2*b**2+2*c**2-a**2) and is_square(2*a**2+2*c**2-b**2) and is_square(2*a**2+2*b**2-c**2) :
       print (a,b,c,2*b**2+2*c**2-a**2,2*a**2+2*c**2-b**2,2*a**2+2*b**2-c**2,p*(p-a)*(p-b)*(p-c))
