#include <bits/stdc++.h> 
using namespace std; 
  
bool isPerfectSquare(long double x) 
{   
  // Find floating point value of  
  // square root of x. 
  long double sr = sqrt(x); 
  // If square root is an integer 
  return ((sr - floor(sr)) == 0); 
} 
  
int main() { 
  long int p = 0;
  for(int a = 3; a < 20000; a++ )
   for(int b = a; b < a+a+a; b++)
    for(int c = b; c < b+b+b; c++)
      p=(a+b+c)/2;
      if (is_perfect_square(p*(p-a)*(p-b)*(p-c)) && ((is_perfect_square(2*b*b+2*c*c-a*a) | True) && is_perfect_square(2*a*a+2*c*c-b*b) && is_perfect_square(2*a*a+2*b*b-c*c)) )
      {
       cout << a;
       cout << b;
       cout << c;
       cout << (sqrt(2*b**2+2*c**2-a**2))/2;
       cout << (qrt(2*a**2+2*c**2-b**2))/2;
       cout << (sqrt(2*a**2+2*b**2-c**2))/2;
       cout << sqrt((p*(p-a)*(p-b)*(p-c))));
      }

  return 0; 
} 
