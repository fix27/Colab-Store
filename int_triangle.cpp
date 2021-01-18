#include <iostream>
#include <cmath> 
using namespace std;

bool isPerfectSquare(long long n){
    long long squareRootN=(long long)(sqrt((double)n)+0.5);
    return squareRootN*squareRootN == n && n>3;
}
  
int main(int argc, char* argv[]) { 
  cout.precision(20);
  if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
  {
      long ar1 = stoi(argv[1]);
      long ar2 = stoi(argv[2]);
      long ar3 = stoi(argv[3]);
      
      for(long  a = ar1 ; a < ar2; a++)
      {
       if (a % 500 == 0) cout << "a=" << a << std::endl;
       for(long  b = a+1; b < ar3; b++)
       for(long  c = b; c < a+b; c++)
        {
         long double p=(a+b+c)/2;
         if (isPerfectSquare(p*(p-a)*(p-b)*(p-c)) &&  isPerfectSquare(2*b*b+2*c*c-a*a) && isPerfectSquare(2*a*a+2*c*c-b*b) &&  isPerfectSquare(2*a*a+2*b*b-c*c))
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
        }
  }
  return 0; 
} 
