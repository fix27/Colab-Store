#include <iostream>
#include <cmath> 
using namespace std;

bool isPerfectSquare(long long n){
    long long squareRootN=(long long)(sqrt((double)n)+0.5);
    return squareRootN*squareRootN == n;
}
  
int main() { 
  long int p = 0;
  for(int a = 3; a < 20000; a++)
   for(int b = a; b < a+a+a; b++)
    for(int c = b; c < b+b+b; c++)
     {
      p=(a+b+c)/2;
      if (isPerfectSquare(p*(p-a)*(p-b)*(p-c)) && isPerfectSquare(2*b*b+2*c*c-a*a)  && isPerfectSquare(2*a*a+2*c*c-b*b) && (true || isPerfectSquare(2*a*a+2*b*b-c*c)) )
      {
       std::cout  << a << " ";
       std::cout  << b << " ";
       std::cout  << c << " ";
       std::cout  << (sqrt(2*b*b+2*c*c-a*a))/2 << " ";
       std::cout  << (sqrt(2*a*a+2*c*c-b*b))/2 << " ";
       std::cout  << (sqrt(2*a*a+2*b*b-c*c))/2 << " ";
       std::cout  << sqrt((p*(p-a)*(p-b)*(p-c))) << std::endl;
      }
    }

  return 0; 
} 
