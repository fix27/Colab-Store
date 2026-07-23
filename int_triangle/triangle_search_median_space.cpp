// Метод 1: Поиск по пространству медиан (оптимизированная версия)
// D = (m_b²-m_a²)/3 = (m_b-m_a)(m_b+m_a)/3 = t·s/3
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;
using namespace chrono;

using ll = long long;

ll isqrt(ll n) {
    ll r = (ll)sqrtl((long double)n);
    while ((r+1)*(r+1) <= n) r++;
    while (r*r > n) r--;
    return r;
}

bool is_square(ll n) {
    if (n < 0) return false;
    ll r = isqrt(n);
    return r*r == n;
}

// Все делители числа n (с учётом знака)
vector<ll> get_divisors(ll n) {
    vector<ll> divs;
    if (n == 0) return divs;
    ll abs_n = n > 0 ? n : -n;
    for (ll d = 1; d*d <= abs_n; d++) {
        if (abs_n % d == 0) {
            divs.push_back(d);
            if (d*d != abs_n) divs.push_back(abs_n/d);
        }
    }
    return divs;
}

int main() {
    ll MAX_M = 20000;
    cout << "=== МЕТОД 1: Пространство медиан (max m = " << MAX_M << ") ===" << endl;
    
    auto start = high_resolution_clock::now();
    ll found_2 = 0, found_3 = 0;
    
    for (ll ma = 1; ma <= MAX_M; ma++) {
        if (ma % 2000 == 0) {
            auto sec = duration_cast<seconds>(high_resolution_clock::now() - start).count();
            cout << "\r  m_a = " << ma << " (" << sec << "s, 2м=" << found_2 << ", 3м=" << found_3 << ")     " << flush;
        }
        
        for (ll mb = 1; mb <= MAX_M; mb++) {
            if (ma == mb) continue;
            
            ll s = mb + ma; // m_b + m_a
            ll t = mb - ma; // m_b - m_a (может быть < 0)
            if (t == 0) continue;
            
            // D = (m_b²-m_a²)/3 = s·t/3
            bool s_div3 = (s % 3 == 0);
            bool t_div3 = (t % 3 == 0);
            if (!s_div3 && !t_div3) continue;
            if (s_div3 && t_div3) continue; // 9 делит, пропускаем (D не целое)
            
            ll base, factor;
            if (s_div3) { base = s/3; factor = t; }
            else         { base = s;   factor = t/3; }
            
            if (base <= 0 || factor <= 0) continue;
            
            // Делители D = base * factor
            auto divs_base = get_divisors(base);
            auto divs_factor = get_divisors(factor);
            
            // Комбинируем делители
            for (ll db : divs_base) {
                for (ll df : divs_factor) {
                    ll d1 = db * df;
                    ll d2 = (base / db) * (factor / df);
                    
                    // d1*d2 = D
                    // u = (d1+d2)/2, v = (d2-d1)/2 (если d2 > d1)
                    // или u = (d1+d2)/2, v = (d1-d2)/2 (если d1 > d2)
                    ll u = (d1 + d2) / 2;
                    ll v = (d2 - d1) / 2;
                    if (v < 0) { v = -v; } // v = |d2-d1|/2
                    
                    if (u <= 0 || v <= 0) continue;
                    if (u == v) continue;
                    
                    // w² = (m_a² + u² - 2v²)/2
                    ll num_w2 = ma*ma + u*u - 2*v*v;
                    if (num_w2 <= 0 || num_w2 % 2 != 0) continue;
                    ll w2 = num_w2 / 2;
                    if (!is_square(w2)) continue;
                    ll w = isqrt(w2);
                    
                    // ПРОВЕРЯЕМ: m_b² = 2u² + 2w² - v²
                    if (2*u*u + 2*w*w - v*v != mb*mb) continue;
                    
                    // ПРОВЕРЯЕМ: m_c² = 2u² + 2v² - w²
                    ll mc2 = 2*u*u + 2*v*v - w*w;
                    if (mc2 <= 0 || !is_square(mc2)) continue;
                    ll mc = isqrt(mc2);
                    
                    // Треугольное неравенство
                    if (u + v <= w || u + w <= v || v + w <= u) continue;
                    
                    ll a = 2*u, b = 2*v, c = 2*w;
                    
                    // Проверка площади
                    __int128 s2_16 = (__int128)(a+b+c) * (__int128)(b+c-a) * (__int128)(a+c-b) * (__int128)(a+b-c);
                    bool area_ok = false;
                    if (s2_16 > 0 && s2_16 % 16 == 0) {
                        area_ok = is_square((ll)(s2_16 / 16));
                    }
                    
                    if (area_ok) {
                        found_3++;
                        ll area = (ll)isqrt((ll)(s2_16/16));
                        cout << "\n*** 3 МЕДИАНЫ + ПЛОЩАДЬ! ***" << endl;
                        cout << "  Стороны: (" << a << "," << b << "," << c << ")" << endl;
                        cout << "  Медианы: (" << ma << "," << mb << "," << mc << ")" << endl;
                        cout << "  Площадь: " << area << endl;
                    } else {
                        found_2++;
                        if (found_2 <= 5) {
                            cout << "\n  2 медианы: (" << a << "," << b << "," << c
                                 << ") m=(" << ma << "," << mb << "," << mc << ")" << endl;
                        }
                    }
                }
            }
        }
    }
    
    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();
    
    cout << "\n\n=== ИТОГИ ===" << endl;
    cout << "2 целых медианы: " << found_2 << endl;
    cout << "3 целых медианы + площадь: " << found_3 << endl;
    cout << "Время: " << sec << "c" << endl;
    
    return 0;
}
