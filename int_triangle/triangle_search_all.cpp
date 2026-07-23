// Поиск треугольника с целыми сторонами, медианами и площадью.
// Тестируем формулы: a = f(x), b = f(y), c = f(z)
// с увеличенным диапазоном (2x) и новыми формулами.
//
// Формулы:
//   1. f(x) = x^2 - 1    (квадрат минус 1)
//   2. f(x) = x^2 + 1    (квадрат плюс 1) — доказано: нечетные => невозможно
//   3. f(x) = x(x+1)     (пронические, произведение соседних)
//   4. f(x) = x(x+1)/2   (треугольные числа)
//   5. f(x) = x^3        (кубы) — доказано: невозможно
//   6. f(x) = x^2        (квадраты) — доказано: невозможно
//   7. f(x) = x!         (факториалы) — доказано: невозможно
//
// Для возможных: поиск с проверкой медиан + площади.

#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

using ll = long long;

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

// Проверка медиан для треугольника (a,b,c)
// Возвращает true, если все три медианы целые
bool medians_ok(ll a, ll b, ll c) {
    if (a + b <= c || a + c <= b || b + c <= a) return false;

    ll d_a = 2LL * b * b + 2LL * c * c - a * a;
    if (d_a <= 0 || d_a % 4 != 0) return false;
    if (!is_square(d_a / 4)) return false;

    ll d_b = 2LL * a * a + 2LL * c * c - b * b;
    if (d_b <= 0 || d_b % 4 != 0) return false;
    if (!is_square(d_b / 4)) return false;

    ll d_c = 2LL * a * a + 2LL * b * b - c * c;
    if (d_c <= 0 || d_c % 4 != 0) return false;
    if (!is_square(d_c / 4)) return false;

    return true;
}

// Проверка площади (через __int128 для избежания переполнения)
bool area_ok(ll a, ll b, ll c) {
    ll p2 = a + b + c;
    __int128 s2_16 = (__int128)p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0) return false;
    if (s2_16 % 16 != 0) return false;
    ll s2 = (ll)(s2_16 / 16);
    return is_square(s2);
}

void search_formula(const string& name, int max_param,
                    ll (*func)(int), const string& parity_note,
                    bool skip_x_even, bool skip_x_odd) {
    cout << "\n=== " << name << " ===" << endl;
    if (!parity_note.empty()) {
        cout << "  " << parity_note << endl;
    }

    auto start = high_resolution_clock::now();

    vector<ll> vals(max_param + 1);
    for (int i = 1; i <= max_param; i++) {
        vals[i] = func(i);
    }

    ll checked = 0, median_pass = 0;
    int found = 0;

    for (int xi = 1; xi <= max_param && !found; xi++) {
        if (skip_x_even && xi % 2 == 0) continue;
        if (skip_x_odd && xi % 2 == 1) continue;

        ll a = vals[xi];
        if (a <= 0) continue;

        for (int yi = xi; yi <= max_param && !found; yi++) {
            if (skip_x_even && yi % 2 == 0) continue;
            if (skip_x_odd && yi % 2 == 1) continue;

            ll b = vals[yi];

            for (int zi = yi; zi <= max_param && !found; zi++) {
                if (skip_x_even && zi % 2 == 0) continue;
                if (skip_x_odd && zi % 2 == 1) continue;

                ll c = vals[zi];
                if (a + b <= c) continue;
                checked++;

                if (medians_ok(a, b, c)) {
                    median_pass++;
                    if (area_ok(a, b, c)) {
                        cout << "\n*** НАЙДЕНО! ***" << endl;
                        cout << "x=" << xi << " y=" << yi << " z=" << zi << endl;
                        cout << "a=" << a << " b=" << b << " c=" << c << endl;

                        ll m_a = isqrt((2LL*b*b + 2LL*c*c - a*a) / 4);
                        ll m_b = isqrt((2LL*a*a + 2LL*c*c - b*b) / 4);
                        ll m_c = isqrt((2LL*a*a + 2LL*b*b - c*c) / 4);
                        cout << "Медианы: " << m_a << ", " << m_b << ", " << m_c << endl;

                        ll p2 = a + b + c;
                        ll s = isqrt((ll)((__int128)p2*(b+c-a)*(a+c-b)*(a+b-c) / 16));
                        cout << "Площадь: " << s << endl;
                        found = 1;
                    }
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    if (!found) {
        cout << "  Не найдено (проверено " << checked
             << ", медианы целые у " << median_pass << ")" << endl;
    }
    cout << "  Время: " << sec << " сек" << endl;
}

// f(x) = x^2 - 1
ll sq_minus_1(int x) { return (ll)x * x - 1; }

// f(x) = x^2 + 1
ll sq_plus_1(int x) { return (ll)x * x + 1; }

// f(x) = x(x+1) — пронические
ll pronic(int x) { return (ll)x * (x + 1); }

// f(x) = x(x+1)/2 — треугольные
ll triangular(int x) { return (ll)x * (x + 1) / 2; }

int main() {
    cout << "ПОИСК ТРЕУГОЛЬНИКОВ С ЦЕЛЫМИ МЕДИАНАМИ И ПЛОЩАДЬЮ" << endl;
    cout << "Стороны заданы формулой a = f(x)" << endl;

    // --- ФОРМУЛА: x^2 - 1 (диапазон 2x: 1000 -> 2000) ---
    // Только нечётные x (чётные дают нечётную сторону)
    search_formula("f(x) = x^2 - 1 (x <= 2000, только нечётные)",
                   2000, sq_minus_1,
                   "После сокращения на 8: треугольные числа. Возможно.",
                   true, false);  // skip even x

    // --- ФОРМУЛА: x^2 + 1 (проверка, хотя доказано: невозможно) ---
    // x^2 + 1 всегда нечётно => все стороны нечётные => d_a ≡ 3 mod 4
    search_formula("f(x) = x^2 + 1 (x <= 1000)",
                   1000, sq_plus_1,
                   "Доказано: все стороны нечётные => d_a ≡ 3 mod 4 => невозможно",
                   false, false);

    // --- ФОРМУЛА: x(x+1) — пронические ---
    // Всегда чётные. v2 зависит от x. Может работать.
    search_formula("f(x) = x(x+1) (x <= 2000)",
                   2000, pronic,
                   "Пронические числа. Всегда чётные. v2 варьируется.",
                   false, false);

    // --- ФОРМУЛА: треугольные числа x(x+1)/2 ---
    search_formula("f(x) = x(x+1)/2 (x <= 2000)",
                   2000, triangular,
                   "Треугольные числа. Чётность: T_x mod 2 = 0,1,1,0,...",
                   false, false);

    return 0;
}
