// Комбинированный поиск — финальная версия
// Используем int64 (sides ≤ 10⁷) + бинпоиск по k-диапазону
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <chrono>
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

int main() {
    cout << "=== КОМБИНИРОВАННЫЙ ПОИСК (все формулы, чётные, 48 ≤ side ≤ 10⁷) ===" << endl;
    
    set<ll> raw_set;
    
    auto add_even = [&](ll start, ll end, ll step, auto f) {
        for (ll x = start; x <= end; x += step) {
            ll v = f(x);
            if (v > 0 && v % 2 == 0 && v <= 10000000) raw_set.insert(v);
        }
    };
    
    add_even(3, 3000, 2, [](ll x){ return x*x - 1; });
    add_even(2, 5000, 2, [](ll x){ return x*x + 1; });
    add_even(3, 500, 2, [](ll x){ return x*x*x - 1; });
    add_even(3, 500, 2, [](ll x){ return x*x*x + 1; });
    add_even(2, 3000, 1, [](ll x){ return x*x*x / 2; });
    add_even(1, 10000, 1, [](ll x){ return x*(x+1); });
    add_even(1, 10000, 1, [](ll x){ return x*(x+1)/2; });
    add_even(2, 3000, 2, [](ll x){ return x*(x+2); });
    add_even(2, 3000, 2, [](ll x){ return x*(2*x+1); });
    add_even(2, 3000, 2, [](ll x){ return x*(2*x-1); });
    add_even(1, 2000, 1, [](ll x){ return (2*x+1)*(2*x+3); });
    
    ll fact = 2;
    for (int x = 3; x <= 20; x++) {
        fact *= x;
        if (fact > 1e7) break;
        raw_set.insert(fact);
    }
    
    ll f1=1,f2=2;
    raw_set.insert(2);
    for (int i=3;i<=100;i++) {
        ll f3=f1+f2;
        if (f3>1e7) break;
        if (f3%2==0) raw_set.insert(f3);
        f1=f2; f2=f3;
    }
    
    string e_digits =
        "71828182845904523536028747135266249775724709369995"
        "95749669676277240766303535475945713821785251664274"
        "27466391932003059921817413596629043572900334295260";
    for (int bs = 2; bs <= 7; bs++)
        for (size_t i = 0; i+bs <= e_digits.size(); i++) {
            ll v = stoll(e_digits.substr(i, bs));
            if (v%2==0 && v>=48 && v<=1e7) raw_set.insert(v);
        }
    
    string pi_digits =
        "14159265358979323846264338327950288419716939937510"
        "58209749445923078164062862089986280348253421170679"
        "82148086513282306647093844609550582231725359408128";
    for (int bs = 2; bs <= 7; bs++)
        for (size_t i = 0; i+bs <= pi_digits.size(); i++) {
            ll v = stoll(pi_digits.substr(i, bs));
            if (v%2==0 && v>=48 && v<=1e7) raw_set.insert(v);
        }
    
    vector<ll> cand(raw_set.begin(), raw_set.end());
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    
    ll N = cand.size();
    cout << "Кандидатов: " << N << " (от " << cand[0] << " до " << cand[N-1] << ")" << endl;
    cout << "Плотность: ~" << N*1e7/(cand[N-1]-cand[0]) << " на 10⁷" << endl;
    
    auto start = high_resolution_clock::now();
    ll total = 0, found_2 = 0, found_3 = 0, area_ok_count = 0;
    
    for (ll ia = 0; ia < N; ia++) {
        ll a = cand[ia];
        if (ia % 500 == 0) {
            auto sec = duration_cast<seconds>(high_resolution_clock::now()-start).count();
            cout << "\r  i=" << ia << " a=" << a << " (" << sec << "s, 2м=" << found_2 << ", 3м=" << found_3 << ")     " << flush;
        }
        
        for (ll ib = ia; ib < N; ib++) {
            ll b = cand[ib];
            if (a + b <= b) continue;
            
            ll c_max = a + b - 1;
            ll ik_start = ib;
            auto it_end = upper_bound(cand.begin(), cand.end(), c_max);
            ll ik_end = it_end - cand.begin();
            
            for (ll ik = ik_start; ik < ik_end; ik++) {
                ll c = cand[ik];
                total++;
                
                // Все три медианы через int64 (sides ≤ 10⁷: 2b²+2c²-a² ≤ 2e14, int64 safe)
                ll d_a = 2*b*b + 2*c*c - a*a;
                ll d_b = 2*a*a + 2*c*c - b*b;
                ll d_c = 2*a*a + 2*b*b - c*c;
                
                int cnt = 0;
                ll m_a_val=0, m_b_val=0, m_c_val=0;
                
                if (d_a > 0 && d_a % 4 == 0) { ll r = isqrt(d_a/4); if (r*r == d_a/4) { cnt++; m_a_val = r; } }
                if (cnt < 2 && d_b > 0 && d_b % 4 == 0) { ll r = isqrt(d_b/4); if (r*r == d_b/4) { cnt++; m_b_val = r; } }
                if (cnt < 2 && d_c > 0 && d_c % 4 == 0) { ll r = isqrt(d_c/4); if (r*r == d_c/4) { cnt++; m_c_val = r; } }
                // Если уже cnt<2 после проверки d_a,d_b: проверяем d_c только если cnt==1
                if (cnt >= 1 && d_c > 0 && d_c % 4 == 0) { ll r = isqrt(d_c/4); if (r*r == d_c/4) { cnt++; m_c_val = r; } }
                // Если после d_a cnt==0: проверяем d_b,d_c
                if (cnt == 0 && d_b > 0 && d_b % 4 == 0) { ll r = isqrt(d_b/4); if (r*r == d_b/4) { cnt++; m_b_val = r; } }
                if (cnt <= 1 && d_c > 0 && d_c % 4 == 0) { ll r = isqrt(d_c/4); if (r*r == d_c/4) { cnt++; m_c_val = r; } }
                
                // Правильный подсчёт: все три независимо
                cnt = 0;
                if (d_a > 0 && d_a % 4 == 0 && is_square(d_a/4)) { cnt++; m_a_val = isqrt(d_a/4); }
                if (d_b > 0 && d_b % 4 == 0 && is_square(d_b/4)) { cnt++; m_b_val = isqrt(d_b/4); }
                if (d_c > 0 && d_c % 4 == 0 && is_square(d_c/4)) { cnt++; m_c_val = isqrt(d_c/4); }
                
                if (cnt < 2) continue;
                
                if (cnt == 3) {
                    // Проверка площади
                    __int128 S16 = (__int128)(a+b+c)*(b+c-a)*(a+c-b)*(a+b-c);
                    if (S16 > 0 && S16 % 16 == 0 && is_square((ll)(S16/16))) {
                        found_3++;
                        ll area = isqrt((ll)(S16/16));
                        cout << "\n*** 3 МЕДИАНЫ + ПЛОЩАДЬ! ***" << endl;
                        cout << "  (" << a << "," << b << "," << c << ")" << endl;
                        cout << "  m=(" << m_a_val << "," << m_b_val << "," << m_c_val << ") S=" << area << endl;
                    }
                    area_ok_count++;
                } else {
                    found_2++;
                }
            }
        }
    }
    
    auto sec = duration_cast<seconds>(high_resolution_clock::now()-start).count();
    cout << "\n\n=== ИТОГИ ===" << endl;
    cout << "Проверено: " << total << " за " << sec << "c" << endl;
    cout << "2 медианы: " << found_2 << ", 3 медианы: " << area_ok_count << ", 3+площадь: " << found_3 << endl;
    
    return 0;
}
