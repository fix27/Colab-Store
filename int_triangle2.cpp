#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    for (int a = 1; a <= 100900; a++) {
        for (int b = a; b <= 109000; b++) {
            for (int c = b+1; c < a+b; c++) {
                unsigned long long s = (a + b + c) / 2; // полупериметр
                unsigned long long medA = sqrt(2 * b * b + 2 * c * c - a * a) / 2; // медиана, проведенная из вершины A
                unsigned long long medB = sqrt(2 * a * a + 2 * c * c - b * b) / 2; // медиана, проведенная из вершины B
                unsigned long long medC = sqrt(2 * a * a + 2 * b * b - c * c) / 2; // медиана, проведенная из вершины C
                unsigned long long area = sqrt(s * (s - a) * (s - b) * (s - c)); // площадь треугольника
                unsigned long long meds = (medA + medB + medC) / 2;
                if ((area*area) == (meds * (meds - medA) * (meds - medB) * (meds - medC))*9/16// проверка, что это треугольник с медианами
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
