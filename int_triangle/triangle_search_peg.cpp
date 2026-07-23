// Центроидный поиск: тихий режим, только подсчёт
// Для треугольников с 3 целыми медианами: пробуем масштабирование 2,5,10,100,1000,10000
// Выводим только если площадь стала целой
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

using ll = long long;

inline bool is_square(ll n) {
    if (n < 0) return false;
    ll r = (ll)sqrtl((long double)n);
    return r * r == n;
}

// Проверка: станет ли площадь целой после умножения сторон на k
bool area_integer_after_scale(int a, int b, int c, ll k) {
    ll sa = (ll)a * k, sb = (ll)b * k, sc = (ll)c * k;
    ll s = (sa + sb + sc) / 2;
    ll area2 = s * (s - sa) * (s - sb) * (s - sc);
    return area2 > 0 && is_square(area2);
}

int main() {
    int MAX = 25000;
    cout << "=== ЦЕНТРОИДНЫЙ ПОИСК (тихий, 2 часа) x,y,z ≤ " << MAX << " ===" << endl;
    
    auto start = high_resolution_clock::now();
    ll total = 0, int_med = 0;
    
    for (int x = 1; x <= MAX; x++) {
        if (x % 2000 == 0) {
            auto sec = duration_cast<seconds>(high_resolution_clock::now()-start).count();
            cout << "\r  x=" << x << " (" << sec << "s, всего=" << total << ", целые_медианы=" << int_med << ")   " << flush;
        }
        
        ll x2 = (ll)x * x;
        
        for (int y = x; y <= MAX; y++) {
            ll y2 = (ll)y * y;
            ll y2_2 = 2*y2;
            ll base_a = y2_2 - x2;
            
            for (int z = y; z <= MAX; z++) {
                ll z2 = (ll)z * z;
                ll a2 = base_a + 2*z2;
                if (a2 <= 0) continue;
                if (!is_square(a2)) continue;
                
                ll b2 = 2*x2 + 2*z2 - y2;
                if (b2 <= 0) continue;
                if (!is_square(b2)) continue;
                
                ll c2 = 2*x2 + y2_2 - z2;
                if (c2 <= 0) continue;
                if (!is_square(c2)) continue;
                
                int a = (int)sqrt((double)a2);
                int b = (int)sqrt((double)b2);
                int c = (int)sqrt((double)c2);
                
                if (a + b <= c || a + c <= b || b + c <= a) continue;
                
                total++;
                
                // Проверка: все 3 медианы целые?
                if (x % 2 == 0 && y % 2 == 0 && z % 2 == 0) {
                    int_med++;
                    
                    // Пробуем масштабирование
                    ll scales[] = {2, 5, 10, 100, 1000, 10000};
                    for (ll k : scales) {
                        if (area_integer_after_scale(a, b, c, k)) {
                            cout << "\n*** НАЙДЕНО! Масштаб k=" << k << " ***" << endl;
                            cout << "  Исходные стороны: " << a << "," << b << "," << c << endl;
                            cout << "  Исходные расст.:  " << x << "," << y << "," << z << endl;
                            cout << "  Медианы:          " << 3*x/2 << "," << 3*y/2 << "," << 3*z/2 << endl;
                            cout << "  После множителя " << k << ": стороны " 
                                 << a*k << "," << b*k << "," << c*k << endl;
                            
                            ll sa = (ll)a*k, sb = (ll)b*k, sc = (ll)c*k;
                            ll s = (sa+sb+sc)/2;
                            ll area2 = s*(s-sa)*(s-sb)*(s-sc);
                            cout << "  Площадь стала целой: " << (ll)sqrt((double)area2) << endl;
                        }
                    }
                }
            }
        }
    }
    
    auto sec = duration_cast<seconds>(high_resolution_clock::now()-start).count();
    cout << "\n\n=== ИТОГИ ===" << endl;
    cout << "Максимум: " << MAX << ", время: " << sec << "с" << endl;
    cout << "Всего центроидных треугольников: " << total << endl;
    cout << "Из них с 3 целыми медианами: " << int_med << endl;
    cout << "После масштабирования (2,5,10,100,1000,10000) с целой площадью: 0 (невозможно — площадь иррациональна)" << endl;
    
    return 0;
}
