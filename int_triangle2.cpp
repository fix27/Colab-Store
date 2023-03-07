#include <iostream>
#include <cmath>
using namespace std;

int main() {
    for (int a = 1; a <= 10000; a++) {
        for (int b = a; b <= 10000; b++) {
            for (int c = b; c < a+b; c++) {
                int s = (a + b + c) / 2; // полупериметр
                int medA = sqrt(2 * b * b + 2 * c * c - a * a) / 2; // медиана, проведенная из вершины A
                int medB = sqrt(2 * a * a + 2 * c * c - b * b) / 2; // медиана, проведенная из вершины B
                int medC = sqrt(2 * a * a + 2 * b * b - c * c) / 2; // медиана, проведенная из вершины C
                int area = sqrt(s * (s - a) * (s - b) * (s - c)); // площадь треугольника
                if (medA * medA + medB * medB == 2 * medC * medC // проверка, что это треугольник с медианами
                    && area % 6 == 0) // проверка, что площадь кратна 6
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
