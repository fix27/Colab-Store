#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    for (long long a = 1; a <= 100900; a++) {
        for (long long b = a ; b <= 109000; b++) {
            for (long long c = b+1 ; c < a+b-2; c++) {
                long long s = (a + b + c) / 2; // полупериметр
                long long area2 = s * (s - a) * (s - b) * (s - c)
                long long area = sqrt(area2); // площадь треугольника
                if ( area*area=area2)
                    long long medA = sqrt(2 * b * b + 2 * c * c - a * a) / 2; // медиана, проведенная из вершины A
                    long long medB = sqrt(2 * a * a + 2 * c * c - b * b) / 2; // медиана, проведенная из вершины B
                    long long medC = sqrt(2 * a * a + 2 * b * b - c * c) / 2; // медиана, проведенная из вершины C
                    long long meds = (medA + medB + medC) / 2;
                    if ( area2*9 == (meds * (meds - medA) * (meds - medB) * (meds - medC))*16)
                    {
                        cout << "a,b,c: " << a << ", " << b << ", " << c << endl;
                        cout << "Медианы: " << medA << ", " << medB << ", " << medC << endl;
                        cout << "S: " << sqrt(s * (s - a) * (s - b) * (s - c)) << endl;
                    }
            }
        }
    }
    return 0;
}
