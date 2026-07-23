// Поиск треугольников с 2 целыми медианами из 3.
// Какие формулы дают наибольшее количество «почти найденных» треугольников?

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace chrono;

using ll = long long;

ll isqrt(ll n) {
    ll r = (ll)sqrtl((long double)n);
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r;
}

bool is_square(ll n) {
    if (n < 0) return false;
    ll r = isqrt(n);
    return r * r == n;
}

// Возвращает количество целых медиан (0-3)
int count_int_medians(ll a, ll b, ll c) {
    if (a + b <= c || a + c <= b || b + c <= a) return -1;
    int cnt = 0;
    
    auto check = [&cnt](ll x, ll y, ll z) {
        __int128 d = (__int128)2 * y * y + (__int128)2 * z * z - (__int128)x * x;
        if (d > 0 && d % 4 == 0 && is_square((ll)(d / 4))) cnt++;
    };
    
    check(a, b, c);
    check(b, a, c);
    check(c, a, b);
    return cnt;
}

// --- Формулы для тестирования ---
ll sq_minus_1(int x) { return (ll)x * x - 1; }
ll sq_plus_1(int x) { return (ll)x * x + 1; }
ll cube_minus_1(int x) { return (ll)x * x * x - 1; }
ll cube_plus_1(int x) { return (ll)x * x * x + 1; }
ll pronic(int x) { return (ll)x * (x + 1); }
ll triangular(int x) { return (ll)x * (x + 1) / 2; }
ll cube_div_2(int x) { return (ll)x * x * x / 2; }
ll pronic2(int x) { return (ll)x * (x + 2); }
ll x2x1(int x) { return (ll)x * (2 * x + 1); }

void test_formula(const string& name, int max_x, ll (*f)(int),
                  bool skip_even, bool skip_odd) {
    auto start = high_resolution_clock::now();
    
    ll stats[4] = {0, 0, 0, 0}; // 0,1,2,3 целых медиан
    ll total = 0;
    
    // Первые примеры с 2 медианами для каждой формулы
    vector<tuple<int,int,int,ll,ll,ll>> best_examples;
    
    for (int xi = 1; xi <= max_x; xi++) {
        if (xi % 2 == 0 && skip_even) continue;
        if (xi % 2 == 1 && skip_odd) continue;
        
        __int128 a = f(xi);
        if (a <= 0) continue;
        
        for (int yi = xi; yi <= max_x; yi++) {
            if (yi % 2 == 0 && skip_even) continue;
            if (yi % 2 == 1 && skip_odd) continue;
            
            __int128 b = f(yi);
            
            for (int zi = yi; zi <= max_x; zi++) {
                if (zi % 2 == 0 && skip_even) continue;
                if (zi % 2 == 1 && skip_odd) continue;
                
                __int128 c = f(zi);
                if (a + b <= c) continue;
                total++;
                
                ll aa = (ll)a, bb = (ll)b, cc = (ll)c;
                int cnt = count_int_medians(aa, bb, cc);
                if (cnt >= 0) stats[cnt]++;
                
                if (cnt >= 2 && best_examples.size() < 5) {
                    best_examples.push_back({xi, yi, zi, aa, bb, cc});
                }
            }
        }
    }
    
    auto sec = duration_cast<seconds>(high_resolution_clock::now() - start).count();
    
    cout << name << ":" << endl;
    cout << "  Всего: " << total 
         << " | 0м: " << stats[0]
         << " | 1м: " << stats[1]
         << " | 2м: " << stats[2]
         << " | 3м: " << stats[3]
         << " (" << sec << "c)" << endl;
    
    if (!best_examples.empty()) {
        cout << "  Примеры с 2 медианами:" << endl;
        for (auto& [x,y,z,aa,bb,cc] : best_examples) {
            __int128 d_a = (__int128)2 * bb * bb + (__int128)2 * cc * cc - (__int128)aa * aa;
            __int128 d_b = (__int128)2 * aa * aa + (__int128)2 * cc * cc - (__int128)bb * bb;
            ll m_a = isqrt((ll)(d_a / 4));
            ll m_b = isqrt((ll)(d_b / 4));
            // какая медиана не целая?
            bool a_ok = (d_a > 0 && d_a % 4 == 0 && m_a * m_a * 4 == d_a);
            bool b_ok = (d_b > 0 && d_b % 4 == 0 && m_b * m_b * 4 == d_b);
            cout << "    (" << x << "," << y << "," << z << ") → "
                 << "(" << aa << "," << bb << "," << cc << ")"
                 << " нецелая: " << (!a_ok ? 'a' : ' ') << (!b_ok ? 'b' : ' ') << (!(a_ok&&b_ok) ? 'c' : ' ')
                 << endl;
        }
    }
}

int main() {
    cout << "=== ПОДСЧЁТ ЦЕЛЫХ МЕДИАН ДЛЯ РАЗНЫХ ФОРМУЛ ===" << endl;
    cout << "(треугольники с 3 целыми медианами = решение проблемы)" << endl << endl;
    
    // Тестируем все формулы на одинаковом диапазоне
    int R = 500; // единый диапазон для сравнения
    
    // Формулы с skip параметрами для чётности
    // (true=skip/false=keep)
    test_formula("f(x)=x^2-1 (только нечетные)", R, sq_minus_1, true, false);
    test_formula("f(x)=x^2+1 (только четные)", R, sq_plus_1, false, true);
    test_formula("f(x)=x^3-1 (только нечетные)", R, cube_minus_1, true, false);
    test_formula("f(x)=x^3+1 (только нечетные)", R, cube_plus_1, true, false);
    test_formula("f(x)=x(x+1) (все)", R, pronic, false, false);
    test_formula("f(x)=x(x+1)/2 (все)", R, triangular, false, false);
    test_formula("f(x)=x^3/2 (все)", R, cube_div_2, false, false);
    test_formula("f(x)=x(x+2) (только четные)", R, pronic2, false, true);
    test_formula("f(x)=x(2x+1) (только четные)", R, x2x1, false, true);
    
    cout << "\n=== ФИНАЛЬНЫЙ АНАЛИЗ ===" << endl;
    cout << "Формулы с наибольшим числом 2-медианных треугольников" << endl;
    cout << "могут указать направление для поиска 3-медианного решения." << endl;
    
    return 0;
}
