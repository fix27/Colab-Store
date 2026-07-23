// Дополнительные формулы для поиска треугольника с целыми медианами
//
// Новые формулы:
//   1. f(x) = x(x+2)         — произведение с шагом 2
//   2. f(x) = x(2x+1)        — произведение с шагом x+1
//   3. f(x) = (2x+1)(2x+3)   — произведение последовательных нечетных
//   4. f(x) = x(2x-1)        — аналог pronic с шагом x-1

#include <iostream>
#include <cmath>
#include <chrono>

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

bool area_ok(ll a, ll b, ll c) {
    ll p2 = a + b + c;
    __int128 s2_16 = (__int128)p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0 || s2_16 % 16 != 0) return false;
    return is_square((ll)(s2_16 / 16));
}

void search(const string& name, int max_x, ll (*f)(int),
            int even_skip, int odd_skip) {
    cout << "=== " << name << " ===" << endl;
    auto start = high_resolution_clock::now();
    ll checked = 0, med_ok = 0;
    int found = 0;

    for (int xi = 1; xi <= max_x && !found; xi++) {
        if ((xi % 2 == 0 && even_skip) || (xi % 2 == 1 && odd_skip)) continue;
        ll a = f(xi);
        if (a <= 0) continue;

        for (int yi = xi; yi <= max_x && !found; yi++) {
            if ((yi % 2 == 0 && even_skip) || (yi % 2 == 1 && odd_skip)) continue;
            ll b = f(yi);

            for (int zi = yi; zi <= max_x && !found; zi++) {
                if ((zi % 2 == 0 && even_skip) || (zi % 2 == 1 && odd_skip)) continue;
                ll c = f(zi);
                if (a + b <= c) continue;
                checked++;

                if (medians_ok(a, b, c)) {
                    med_ok++;
                    if (area_ok(a, b, c)) {
                        cout << "*** НАЙДЕНО! *** x=" << xi << " y=" << yi << " z=" << zi
                             << " a=" << a << " b=" << b << " c=" << c << endl;
                        found = 1;
                    }
                }
            }
        }
    }

    auto sec = duration_cast<seconds>(high_resolution_clock::now() - start).count();
    cout << "  Проверено: " << checked << ", медианы: " << med_ok
         << ", найдено: " << (found ? "ДА" : "НЕТ") << " (" << sec << "c)" << endl;
}

ll f1(int x) { return (ll)x * (x + 2); }        // x(x+2)
ll f2(int x) { return (ll)x * (2 * x + 1); }    // x(2x+1)
ll f3(int x) { return (ll)(2*x+1) * (2*x+3); } // произведение нечетных
ll f4(int x) { return (ll)x * (2 * x - 1); }    // x(2x-1)

int main() {
    cout << "ДОПОЛНИТЕЛЬНЫЕ ФОРМУЛЫ" << endl;

    // f(x) = x(x+2) — только чётные x (нечетные дают нечетное)
    search("f(x) = x(x+2), x <= 2000, четные", 2000, f1, false, true);
    // f(x) = x(x+2) — только нечётные x  
    search("f(x) = x(x+2), x <= 2000, нечетные", 2000, f1, true, false);

    // f(x) = x(2x+1) — только чётные (нечетные дают нечетное)
    search("f(x) = x(2x+1), x <= 2000, четные", 2000, f2, false, true);

    // f(x) = (2x+1)(2x+3) — всегда нечетное
    search("f(x) = (2x+1)(2x+3), x <= 2000", 2000, f3, false, false);

    // f(x) = x(2x-1) — только чётные
    search("f(x) = x(2x-1), x <= 2000, четные", 2000, f4, false, true);

    return 0;
}
