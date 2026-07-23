// Поиск Heronian треугольников с целыми медианами через склейку пифагоровых троек
// C++ версия для больших диапазонов
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <numeric>

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

struct Triple {
    ll other; // другой катет
    ll hyp;   // гипотенуза
};

int main() {
    ll MAX_HYP = 5000000;
    cout << "=== Heronian triangles через пифагоровы тройки (max hyp=" << MAX_HYP << ") ===" << endl;
    
    auto start = high_resolution_clock::now();
    
    // Группируем тройки по общему катету
    unordered_map<ll, vector<Triple>> triples_by_leg;
    ll max_m = (ll)sqrtl(MAX_HYP) + 1;
    ll triple_count = 0;
    
    for (ll m = 2; m <= max_m; m++) {
        for (ll n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (std::gcd(m, n) != 1) continue;
            
            ll a0 = m*m - n*n;
            ll b0 = 2*m*n;
            ll c0 = m*m + n*n;
            if (c0 > MAX_HYP) continue;
            
            for (ll k = 1; k * c0 <= MAX_HYP; k++) {
                ll a = k * a0;
                ll b = k * b0;
                ll c = k * c0;
                
                // (h, p) where h=common leg, p=other leg
                triples_by_leg[a].push_back({b, c});
                triples_by_leg[b].push_back({a, c});
                triple_count++;
            }
        }
    }
    
    auto gen_time = high_resolution_clock::now();
    cout << "Сгенерировано " << triple_count << " троек ("
         << triples_by_leg.size() << " уникальных катетов) за "
         << duration_cast<milliseconds>(gen_time - start).count() << "ms" << endl;
    
    ll stats[4] = {0,0,0,0}; // 0,1,2,3 medians
    ll total = 0;
    ll near_miss_ab = 0, near_miss_ac = 0, near_miss_bc = 0; // ровно 2 medians по типам
    ll med_entries[4] = {0,0,0,0};
    
    // Для записи находок
    struct Found {
        ll a,b,c,m1,m2,m3;
        ll h, p, q;
        int cnt;
    };
    vector<Found> found_2plus;
    
    // Доп. статистика: топ h по числу троек
    vector<pair<ll,int>> top_legs;
    int h_ge2 = 0, h_ge5 = 0, h_ge10 = 0, h_ge50 = 0, h_ge100 = 0;
    
    for (auto& [h, pairs] : triples_by_leg) {
        ll sz = pairs.size();
        
        // Статистика h
        if (sz >= 2) h_ge2++;
        if (sz >= 5) h_ge5++;
        if (sz >= 10) h_ge10++;
        if (sz >= 50) h_ge50++;
        if (sz >= 100) h_ge100++;
        if (sz >= 50) {
            top_legs.push_back({h, (int)sz});
        }
        
        if (sz < 2) {
            med_entries[0] += sz;
            continue;
        }
        
        med_entries[1] += sz;
        if (sz > med_entries[2]) med_entries[2] = sz;
        if (sz > med_entries[3]) med_entries[3] = sz;
        
        for (ll i = 0; i < sz; i++) {
            auto [p, c] = pairs[i];
            for (ll j = i; j < sz; j++) {
                auto [q, b] = pairs[j];
                ll a = p + q;
                
                if (a <= 0) continue;
                if (a >= b + c || b >= a + c || c >= a + b) continue;
                
                total++;
                
                // Проверка медиан
                int cnt = 0;
                ll m_a = 0, m_b = 0, m_c = 0;
                
                // median to a
                __int128 d_a = (__int128)2*b*b + (__int128)2*c*c - (__int128)a*a;
                if (d_a > 0 && d_a % 4 == 0) {
                    ll d4 = (ll)(d_a / 4);
                    ll r = isqrt(d4);
                    if (r*r == d4) { cnt++; m_a = r; }
                }
                
                // median to b
                __int128 d_b = (__int128)2*a*a + (__int128)2*c*c - (__int128)b*b;
                if (d_b > 0 && d_b % 4 == 0) {
                    ll d4 = (ll)(d_b / 4);
                    ll r = isqrt(d4);
                    if (r*r == d4) { cnt++; m_b = r; }
                }
                
                // median to c
                __int128 d_c = (__int128)2*a*a + (__int128)2*b*b - (__int128)c*c;
                if (d_c > 0 && d_c % 4 == 0) {
                    ll d4 = (ll)(d_c / 4);
                    ll r = isqrt(d4);
                    if (r*r == d4) { cnt++; m_c = r; }
                }
                
                stats[cnt]++;
                
                if (cnt >= 2) {
                    found_2plus.push_back({a,b,c,m_a,m_b,m_c,h,p,q,cnt});
                }
                
                if (cnt >= 2) {
                    // Определяем какие медианы целые
                    bool a_ok = m_a > 0, b_ok = m_b > 0, c_ok = m_c > 0;
                    if (a_ok && b_ok && !c_ok) near_miss_ab++;
                    if (a_ok && !b_ok && c_ok) near_miss_ac++;
                    if (!a_ok && b_ok && c_ok) near_miss_bc++;
                }
                
                if (cnt == 3) {
                    cout << "\n*** НАЙДЕНО РЕШЕНИЕ ***" << endl;
                    cout << "(" << a << "," << b << "," << c << ")" << endl;
                    cout << "m=(" << m_a << "," << m_b << "," << m_c << ")" << endl;
                    cout << "h=" << h << " p=" << p << " q=" << q << endl;
                    
                    // Проверка площади
                    ll s = a + b + c;
                    if (s % 2 == 0) {
                        __int128 s2_16 = (__int128)s * (__int128)(b+c-a) * (__int128)(a+c-b) * (__int128)(a+b-c);
                        if (s2_16 > 0 && s2_16 % 16 == 0) {
                            ll area2 = (ll)(s2_16 / 16);
                            if (is_square(area2)) {
                                cout << "Площадь: " << isqrt(area2) << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    
    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();
    
    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "Проверено треугольников: " << total << " за " << sec << "c" << endl;
    cout << "Статистика медиан: 0=" << stats[0] << " 1=" << stats[1] 
         << " 2=" << stats[2] << " 3=" << stats[3] << endl;
    cout << "Типы 2-медианных: mₐ+m_b=" << near_miss_ab 
         << " mₐ+m_c=" << near_miss_ac
         << " m_b+m_c=" << near_miss_bc << endl;
    cout << "Среднее число троек на катет: " << (double)triple_count/triples_by_leg.size() << endl;
    cout << "h с ≥2 тройками: " << h_ge2 << ", ≥5: " << h_ge5 << ", ≥10: " << h_ge10
         << ", ≥50: " << h_ge50 << ", ≥100: " << h_ge100 << endl;
    
    if (!top_legs.empty()) {
        sort(top_legs.begin(), top_legs.end(),
             [](auto& a, auto& b) { return a.second > b.second; });
        cout << "Топ-10 h по числу троек:" << endl;
        for (int ti = 0; ti < min(10, (int)top_legs.size()); ti++) {
            cout << "  h=" << top_legs[ti].first << " (" << top_legs[ti].second << " троек)" << endl;
        }
    }
    
    if (!found_2plus.empty()) {
        cout << "\nТреугольники с 2+ целыми медианами:" << endl;
        for (auto& f : found_2plus) {
            cout << "  (" << f.a << "," << f.b << "," << f.c << ")"
                 << " m=(" << f.m1 << "," << f.m2 << "," << f.m3 << ")"
                 << " h=" << f.h << " p=" << f.p << " q=" << f.q
                 << " cnt=" << f.cnt << endl;
        }
    } else {
        cout << "\nНет треугольников с 2+ целыми медианами." << endl;
        cout << "Попробуйте увеличить MAX_HYP." << endl;
    }
    
    return 0;
}
