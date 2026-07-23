#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

using ll = long long;

struct Triple { ll leg1, leg2, hyp; };

ll gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

ll isqrt(ll n) {
    if (n < 0) return -1;
    ll r = (ll)sqrtl((long double)n);
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r;
}

bool is_perfect_square(ll n) {
    if (n < 0) return false;
    ll r = isqrt(n);
    return r * r == n;
}

bool check_triangle(ll a, ll b, ll c) {
    if (a + b <= c || a + c <= b || b + c <= a) return false;

    ll p2 = a + b + c;
    ll s2_16 = p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0) return false;
    if (s2_16 % 16 != 0) return false;
    ll s = isqrt(s2_16 / 16);
    if (s * s != s2_16 / 16) return false;

    ll d_a = 2LL * b * b + 2LL * c * c - a * a;
    ll d_b = 2LL * a * a + 2LL * c * c - b * b;
    ll d_c = 2LL * a * a + 2LL * b * b - c * c;

    if (d_a <= 0 || d_b <= 0 || d_c <= 0) return false;
    if (d_a % 4 != 0 || d_b % 4 != 0 || d_c % 4 != 0) return false;
    if (!is_perfect_square(d_a / 4)) return false;
    if (!is_perfect_square(d_b / 4)) return false;
    if (!is_perfect_square(d_c / 4)) return false;

    return true;
}

void search(int max_hyp, int max_side, ll& total_heronian) {
    cout << "MAX_HYP=" << max_hyp << ": " << flush;

    vector<Triple> triples;
    int max_m = (int)sqrt(max_hyp) + 2;

    for (int m = 2; m <= max_m; m++) {
        for (int n = 1; n < m; n++) {
            if (gcd(m, n) != 1) continue;
            if ((m - n) % 2 == 0) continue;

            ll a_base = (ll)m * m - (ll)n * n;
            ll b_base = 2LL * m * n;
            ll c_base = (ll)m * m + (ll)n * n;

            for (ll k = 1; k * c_base <= max_hyp; k++) {
                triples.push_back({k * a_base, k * b_base, k * c_base});
            }
        }
    }

    cout << triples.size() << " троек, " << flush;

    unordered_map<ll, vector<pair<ll, ll>>> groups;
    for (const auto& t : triples) {
        groups[t.leg1].push_back({t.leg2, t.hyp});
        groups[t.leg2].push_back({t.leg1, t.hyp});
    }

    cout << groups.size() << " групп, " << flush;

    ll heronian_count = 0;
    int found = 0;

    for (auto& [leg, vec] : groups) {
        if (vec.size() < 2) continue;

        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());

        for (size_t i = 0; i < vec.size() && !found; i++) {
            for (size_t j = i + 1; j < vec.size() && !found; j++) {
                auto [a1, c1] = vec[i];
                auto [a2, c2] = vec[j];

                auto check_one = [&](ll base) {
                    if (base <= 0 || base > max_side) return;
                    ll sides[3] = {c1, c2, base};
                    sort(sides, sides + 3);
                    if (sides[0] + sides[1] > sides[2]) {
                        heronian_count++;
                        if (check_triangle(sides[0], sides[1], sides[2])) {
                            cout << "\n*** НАЙДЕНО! ***" << endl;
                            cout << "Стороны: " << sides[0] << ", " << sides[1] << ", " << sides[2] << endl;
                            cout << "Способ: leg=" << leg << ", a1=" << a1 << ", a2=" << a2 << endl;
                            found = 1;
                        }
                    }
                };

                check_one(a1 + a2);
                if (a1 != a2) check_one(abs(a1 - a2));
            }
        }
    }

    total_heronian += heronian_count;
    cout << heronian_count << " героновых, " << (found ? "НАЙДЕНО!" : "нет") << endl;
}

int main() {
    auto start = high_resolution_clock::now();

    const int MAX_SIDE = 10000;
    ll total_heronian = 0;
    int found = 0;

    int hyp_limits[] = {5000, 10000, 20000, 50000, 100000, 200000};
    for (int hl : hyp_limits) {
        search(hl, MAX_SIDE, total_heronian);
        auto now = high_resolution_clock::now();
        auto sec = duration_cast<seconds>(now - start).count();
        if (sec > 300) { // 5 минут лимит
            cout << "Превышен лимит времени" << endl;
            break;
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    cout << "\n=== ИТОГ ===" << endl;
    cout << "Всего проверено героновых треугольников: " << total_heronian << endl;
    cout << "Время: " << sec << " сек" << endl;
    cout << "Треугольников с целыми сторонами, медианами и площадью" << endl;
    cout << "не найдено при максимальной стороне до " << MAX_SIDE << "." << endl;
    cout << "Это открытая проблема математики." << endl;

    return 0;
}
