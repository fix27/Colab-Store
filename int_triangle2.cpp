#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    for (long long a = 1; a <= 100900; a++) {
        for (long long b = a; b <= 109000; b++) {
            for (long long c = b+1; c < a+b; c++) {
                long long s = (a + b + c) / 2; // полупериметр
                long long area = sqrt(s * (s - a) * (s - b) * (s - c)); // площадь треугольника                
                long long medA = sqrt(2 * b * b + 2 * c * c - a * a) / 2; // медиана, проведенная из вершины A
                long long medB = sqrt(2 * a * a + 2 * c * c - b * b) / 2; // медиана, проведенная из вершины B
                long long medC = sqrt(2 * a * a + 2 * b * b - c * c) / 2; // медиана, проведенная из вершины C
                long long meds = (medA + medB + medC) / 2;
                if (area!=0  && (area*area) == (meds * (meds - medA) * (meds - medB) * (meds - medC))*9/16// проверка, что это треугольник с медианами
                    ) // проверка, что площадь кратна 6 area
                {
                    cout << "a,b,c: " << a << ", " << b << ", " << c << endl;
                    cout << "Медианы: " << medA << ", " << medB << ", " << medC << endl;
                    cout << "S: " << area << endl;
                }
            }
        }
    }
    return 0;
}
