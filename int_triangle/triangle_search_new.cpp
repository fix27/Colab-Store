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

    // Используем __int128 для избежания переполнения (нужно для кубов > 1154)
    auto check_d = [](ll a, ll b, ll c) -> bool {
        __int128 d = (__int128)2 * b * b + (__int128)2 * c * c - (__int128)a * a;
        if (d <= 0 || d % 4 != 0) return false;
        ll d4 = (ll)(d / 4);
        return is_square(d4);
    };

    if (!check_d(a, b, c)) return false;
    if (!check_d(b, a, c)) return false;
    if (!check_d(c, a, b)) return false;
    return true;
}

bool area_ok(ll a, ll b, ll c) {
    ll p2 = a + b + c;
    __int128 s2_16 = (__int128)p2 * (b + c - a) * (a + c - b) * (a + b - c);
    if (s2_16 <= 0 || s2_16 % 16 != 0) return false;
    return is_square((ll)(s2_16 / 16));
}

void search(const string& name, int max_x, ll (*f)(int),
            bool skip_even, bool skip_odd, const string& note) {
    cout << "=== " << name << " ===" << endl;
    if (!note.empty()) cout << "  " << note << endl;
    auto start = high_resolution_clock::now();
    ll checked = 0, med_ok = 0;
    int found = 0;

    for (int xi = 1; xi <= max_x && !found; xi++) {
        if (xi % 2 == 0 && skip_even) continue;
        if (xi % 2 == 1 && skip_odd) continue;
        ll a = f(xi);
        if (a <= 0) continue;

        for (int yi = xi; yi <= max_x && !found; yi++) {
            if (yi % 2 == 0 && skip_even) continue;
            if (yi % 2 == 1 && skip_odd) continue;
            ll b = f(yi);

            // Двоичный поиск макс z через линейный скан (быстро для монотонной f)
            int max_z = yi;
            while (max_z + 1 <= max_x && f(max_z + 1) < a + b) max_z++;

            for (int zi = yi; zi <= max_z && !found; zi++) {
                if (zi % 2 == 0 && skip_even) continue;
                if (zi % 2 == 1 && skip_odd) continue;
                ll c = f(zi);
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

ll cube_minus_1(int x) { return (ll)x * x * x - 1; }
ll cube_plus_1(int x) { return (ll)x * x * x + 1; }
ll cube_div_2(int x) { return (ll)x * x * x / 2; }

int main() {
    cout << "=== НОВЫЕ ФОРМУЛЫ ===" << endl;

    // cubes - 1: нечетные x (четные дают нечетные стороны)
    search("f(x) = x^3 - 1, нечетные x", 1500, cube_minus_1,
           true, false,  // skip even, don't skip odd
           "После сокращения 2^{1+min(v2(k))}: min(v2) даёт odd, >min даёт even");

    // cubes + 1: нечетные x (четные дают нечетные стороны)
    search("f(x) = x^3 + 1, нечетные x", 1500, cube_plus_1,
           true, false,
           "x=2k+1 → a=2(4k^3+6k^2+3k+1). Чётность зависит от k");

    // cubes // 2: все x (обе чётности возможны)
    search("f(x) = x^3 / 2 (целочисл.)", 2000, cube_div_2,
           false, false,
           "x=2k → a=4k^3 (чет); x=2k+1 → a=4k^3+6k^2+3k (чет/нечет)");

    return 0;
}
