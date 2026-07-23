import math
def is_square(apositiveint):
  if apositiveint<3 : return False
  x = apositiveint // 2
  seen = set([x])
  while x * x != apositiveint:
    x = (x + (apositiveint // x)) // 2
    if x in seen: return False
    seen.add(x)
  return True


for a in range(1,5000) :
 for b in range(1,5000) :
  for c in range(1,5000) :
    p=(a+b+c)/2
    ma=2*b**2+2*c**2-a**2
    mb=2*a**2+2*c**2-b**2
    mc=2*a**2+2*b**2-c**2
    s=p*(p-a)*(p-b)*(p-c)
    if is_square(ma) and  is_square(mb) and  is_square(mc) and is_square(s):
       print (a,b,c,ma,mb,mc,s)
