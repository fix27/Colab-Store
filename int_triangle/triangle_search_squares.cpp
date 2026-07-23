// Поиск треугольников с квадратными сторонами: a = x^2, b = y^2, c = z^2
// Математически доказано: такие треугольники НЕ МОГУТ иметь целые медианы.
// Но проверим для полноты (x,y,z до 5000).

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

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

int main() {
    const int MAX_N = 5000;
    cout << "Квадраты: a = x^2, b = y^2, c = z^2, x,y,z <= " << MAX_N << endl;
    cout << "Математически невозможно: нечётные примитивные стороны => d_a ≡ 3 mod 4" << endl;

    // Предвычисляем квадраты
    vector<ll> sq(MAX_N + 1);
    for (int i = 1; i <= MAX_N; i++) sq[i] = (ll)i * i;

    auto start = high_resolution_clock::now();
    ll total = 0;
    int found = 0;

    for (int xi = 1; xi <= MAX_N && !found; xi++) {
        if (xi % 500 == 0) {
            auto sec = duration_cast<seconds>(high_resolution_clock::now() - start).count();
            cout << "  x=" << xi << " (" << sec << "c, проверено " << total << ")" << endl;
        }

        ll a = sq[xi];

        for (int yi = xi; yi <= MAX_N && !found; yi++) {
            ll b = sq[yi];

            // треугольное неравенство: a + b > c => z^2 < a + b = xi^2 + yi^2
            // z^2 < xi^2 + yi^2 => z < sqrt(xi^2 + yi^2)
            ll max_zz = xi*xi + yi*yi; // это c = z^2, не z!
            
            // For z from yi to sqrt(max_zz):
            int max_zi = min(MAX_N, (int)sqrt((double)max_zz));

            for (int zi = yi; zi <= max_zi && !found; zi++) {
                ll c = sq[zi];
                if (a + b <= c) continue;
                total++;

                // Медианы
                ll d_a = 2LL * b * b + 2LL * c * c - a * a;
                if (d_a <= 0 || d_a % 4 != 0) continue;
                ll m_a = isqrt(d_a / 4);
                if (m_a * m_a * 4 != d_a) continue;

                ll d_b = 2LL * a * a + 2LL * c * c - b * b;
                if (d_b <= 0 || d_b % 4 != 0) continue;
                ll m_b = isqrt(d_b / 4);
                if (m_b * m_b * 4 != d_b) continue;

                ll d_c = 2LL * a * a + 2LL * b * b - c * c;
                if (d_c <= 0 || d_c % 4 != 0) continue;
                ll m_c = isqrt(d_c / 4);
                if (m_c * m_c * 4 != d_c) continue;

                // Площадь (используем __int128 для избежания переполнения)
                ll p2 = a + b + c;
                __int128 s2_16 = (__int128)p2 * (b + c - a) * (a + c - b) * (a + b - c);
                if (s2_16 <= 0) continue;
                if (s2_16 % 16 != 0) continue;
                ll s2 = (ll)(s2_16 / 16);
                ll s = isqrt(s2);
                if (s * s != s2) continue;

                cout << "\n*** НАЙДЕНО! ***" << endl;
                cout << "x=" << xi << " y=" << yi << " z=" << zi << endl;
                cout << "a=" << a << " b=" << b << " c=" << c << endl;
                cout << "S=" << s << endl;
                cout << "Медианы: " << m_a << ", " << m_b << ", " << m_c << endl;
                found = 1;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto sec = duration_cast<seconds>(end - start).count();

    if (!found) {
        cout << "\nНе найдено (проверено " << total << " треугольников)" << endl;
        cout << "Теоретически невозможно: примитивная тройка всегда нечётная" << endl;
    }
    cout << "Время: " << sec << " сек" << endl;

    return 0;
}
