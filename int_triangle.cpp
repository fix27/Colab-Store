#include <iostream>
#include <cmath> 
using namespace std;

int main(int argc, char* argv[]) { 
  cout.precision(20);
  if (argc > 1)// если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)
  {
      long long ar1 = stoi(argv[1]);
      long long ar2 = stoi(argv[2]);
      long long ar3 = stoi(argv[3]);
      long double intpart;
      long double p;
      for(long long  a = ar1 ; a < ar2; a++)
      {
       if (a % 100 == 0) cout << "a=" << a << std::endl;
       for(long long  b = a+1; b < ar3; b++)
       {    
        p=a/2+b-0.5;
        for(long long  c = b; c < a+b; c++)
        {
         p+=0.5;
         if  (  modfl(sqrt(p*(p-a)*(p-b)*(p-c)), &intpart) == 0.0 
             && modfl(sqrt(2*b*b+2*c*c-a*a), &intpart) == 0.0 
             && modfl(sqrt(2*a*a+2*c*c-b*b), &intpart) == 0.0 
             && modfl(sqrt(2*a*a+2*b*b-c*c), &intpart) == 0.0)
          {
            std::cout << a << " " << b << " " << c << " ";
            std::cout << (sqrt(2*b*b+2*c*c-a*a))/2 << " " << (sqrt(2*a*a+2*c*c-b*b))/2 << " " << (sqrt(2*a*a+2*b*b-c*c))/2 << " ";
            std::cout << sqrt(p*(p-a)*(p-b)*(p-c)) << std::endl;
          }
        }
       }
      }
  }
  return 0; 
} 
