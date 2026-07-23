// Поиск треугольника с целыми сторонами, медианами и площадью
// Два подхода: (1) полный перебор до N, (2) кубы сторон: a = x^3
//
// Это открытая проблема математики — ни одного такого треугольника
// не найдено, но и не доказано, что их не существует.

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

using ll = long long;
using ull = unsigned long long;

ll isqrt(ll n) {
    if (n < 0) return -1;
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

bool check_triangle(ll a, ll b, ll c) {
    if (a + b <= c || a + c <= b || b + c <= a) return false;

    ll p2 = a + b + c;
    ull s2_16 = (ull)p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 == 0) return false;
    if (s2_16 % 16 != 0) return false;
    if (!is_square((ll)(s2_16 / 16))) return false;

    ll d_a = 2LL * b * b + 2LL * c * c - a * a;
    ll d_b = 2LL * a * a + 2LL * c * c - b * b;
    ll d_c = 2LL * a * a + 2LL * b * b - c * c;

    if (d_a <= 0 || d_b <= 0 || d_c <= 0) return false;
    if (d_a % 4 != 0 || d_b % 4 != 0 || d_c % 4 != 0) return false;
    if (!is_square(d_a / 4)) return false;
    if (!is_square(d_b / 4)) return false;
    if (!is_square(d_c / 4)) return false;

    return true;
}

// Подход 1: полный перебор сторон до max_side
void brute_force(int max_side) {
    cout << "\n=== ПОЛНЫЙ ПЕРЕБОР до " << max_side << " ===" << endl;
    auto start = high_resolution_clock::now();

    ll total = 0, heronian = 0;
    int found = 0;

    // Все три стороны должны быть чётными (математически доказано)
    for (int a = 2; a <= max_side && !found; a += 2) {
        if (a % 200 == 0) {
            auto sec = duration_cast<seconds>(high_resolution_clock::now() - start).count();
            cout << "  a=" << a << " (" << sec << "c) героновых=" << heronian << endl;
        }

        for (int b = a; b <= max_side && !found; b += 2) {
            for (int c = b; c <= min(max_side, a + b - 1) && !found; c += 2) {
                total++;

                // Быстрая проверка: медиана к a целая?
                // d_a = 2*b^2 + 2*c^2 - a^2 должно быть полным квадратом, делиться на 4
                ll d_a = 2LL * b * b + 2LL * c * c - a * a;
                if (d_a <= 0 || d_a % 4 != 0) continue;
                ll r_a = isqrt(d_a / 4);
                if (r_a * r_a * 4 != d_a) continue;

                ll d_b = 2LL * a * a + 2LL * c * c - b * b;
                if (d_b <= 0 || d_b % 4 != 0) continue;
                ll r_b = isqrt(d_b / 4);
                if (r_b * r_b * 4 != d_b) continue;

                ll d_c = 2LL * a * a + 2LL * b * b - c * c;
                if (d_c <= 0 || d_c % 4 != 0) continue;
                ll r_c = isqrt(d_c / 4);
                if (r_c * r_c * 4 != d_c) continue;

                // Все три медианы целые — проверяем площадь
                ll p2 = a + b + c;
                ull s2_16 = (ull)p2 * (b + c - a) * (a + c - b) * (a + b - c);
                if (s2_16 == 0) continue;
                if (s2_16 % 16 != 0) continue;
                ll s = isqrt((ll)(s2_16 / 16));
                if (s * s != s2_16 / 16) continue;

                heronian++;

                // НАЙДЕНО!
                cout << "\n*** НАЙДЕНО! ***" << endl;
                cout << "a=" << a << " b=" << b << " c=" << c << endl;
                cout << "S=" << s << endl;
                cout << "Медианы: " << r_a << ", " << r_b << ", " << r_c << endl;
                found = 1;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    if (!found) {
        cout << "Не найдено (перебрано " << total << ", героновых " << heronian << ")" << endl;
    }
    cout << "Время: " << sec << " сек" << endl;
}

// Подход 2: стороны — точные кубы: a = x^3, b = y^3, c = z^3
void search_cubes(int max_n) {
    cout << "\n=== КУБЫ: a = x^3, b = y^3, c = z^3, x,y,z ≤ " << max_n << " ===" << endl;

    vector<ll> cubes;
    for (int i = 1; i <= max_n; i++) {
        ll c = (ll)i * i * i;
        if (c <= 0) break; // защита от переполнения
        cubes.push_back(c);
    }

    cout << "Кубов: " << cubes.size() << " (max=" << cubes.back() << ")" << endl;

    auto start = high_resolution_clock::now();
    int found = 0;
    ll checked = 0;

    for (size_t ai = 0; ai < cubes.size() && !found; ai++) {
        for (size_t bi = ai; bi < cubes.size() && !found; bi++) {
            ll a = cubes[ai], b = cubes[bi];
            for (size_t ci = bi; ci < cubes.size() && !found; ci++) {
                ll c = cubes[ci];

                if (a + b <= c) continue;
                checked++;

                if (check_triangle(a, b, c)) {
                    cout << "\n*** НАЙДЕНО! ***" << endl;
                    cout << "x=" << ai+1 << " y=" << bi+1 << " z=" << ci+1 << endl;
                    cout << "a=" << a << " b=" << b << " c=" << c << endl;
                    found = 1;
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    if (!found) {
        cout << "Не найдено (проверено " << checked << ")" << endl;
    }
    cout << "Время: " << sec << " сек" << endl;
}

int main() {
    // Полный перебор до 3000
    brute_force(3000);

    // Кубы: a = x^3, b = y^3, c = z^3, x,y,z до 3000
    // (осторожно: 3000^3 = 27e9 — нужна 64-битная арифметика)
    search_cubes(3000);

    cout << "\nЭто открытая проблема. Найдено 0 треугольников." << endl;
    return 0;
}
